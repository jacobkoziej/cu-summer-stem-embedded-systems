// SPDX-License-Identifier: MPL-2.0
/*
 * twi.c -- two-wire serial interface master
 * Copyright (C) 2025  Jacob Koziej <jacobkoziej@gmail.com>
 */

#include "twi.h"
#include "private/twi.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <util/twi.h>

static volatile twi_isr_t twi_isr;

twi_status_t twi_cancel(void)
{
	const uint8_t sreg = SREG;

	cli();

	twi_isr = (twi_isr_t) {
		.idle   = true,
		.status = TWI_STATUS_CANCELLED,
	};

	uint8_t twcr = TWCR;

	twcr &= 1 << TWSTA;
	twcr |= 1 << TWSTO;

	TWCR = twcr;

	SREG = sreg;

	return TWI_STATUS_SUCCESS;
}

twi_status_t twi_deinit(void)
{
	if (twi_status() == TWI_STATUS_BUSY)
		return TWI_STATUS_BUSY;

	TWCR = 1 << TWINT;

	return TWI_STATUS_SUCCESS;
}

twi_status_t twi_enqueue(twi_message_t * const messages, size_t message_count)
{
	const uint8_t sreg = SREG;

	cli();

	const uint8_t twcr = TWCR;
	const bool    idle = twi_isr.idle;

	SREG = sreg;

	if (!(twcr & (1 << TWEN)))
		return TWI_STATUS_DISABLED;

	if (!idle)
		return TWI_STATUS_BUSY;

	twi_isr = (twi_isr_t) {
		.idle          = false,
		.messages      = messages,
		.message_count = message_count,
	};


	TWCR = twcr | (1 << TWSTA);

	return TWI_STATUS_SUCCESS;
}

twi_status_t twi_init(const uint32_t scl_frequency)
{
	const uint8_t sreg = SREG;

	cli();

	const bool double_init = TWCR & (1 << TWEN);

	SREG = sreg;

	if (double_init)
		return TWI_STATUS_DOUBLE_INIT;

	uint8_t twbr;
	uint8_t twps;

	if (!scl_to_bitrate(scl_frequency, &twbr, &twps))
		return TWI_STATUS_INVALID_SCL;

	TWBR = twbr;
	TWSR = twps;

	TWAR = ~(1 << TWGCE);
	TWAMR = 0xFF;

	TWCR
		= (1 << TWINT)
		| (0 << TWEA)
		| (0 << TWSTA)
		| (0 << TWSTO)
		| (1 << TWEN)
		| (1 << TWIE);

	twi_isr = (twi_isr_t) {
		.idle = true,
		.status = TWI_STATUS_SUCCESS,
	};

	return TWI_STATUS_SUCCESS;
}

twi_status_t twi_status(void)
{
	const uint8_t sreg = SREG;

	cli();

	const twi_status_t status
		= twi_isr.idle
		? twi_isr.status
		: TWI_STATUS_BUSY;

	SREG = sreg;

	return status;
}

static void return_isr(const twi_status_t status)
{
	twi_isr = (twi_isr_t) {
		.idle   = true,
		.status = status,
	};
}

static bool scl_to_bitrate(
	const uint32_t f_scl,
	uint8_t * const twbr,
	uint8_t * const twps)
{
	// To avoid float-based division we perform a fixed-point
	// division by left shifting by 32. For this assumption to hold,
	// we must ensure that F_CPU stays below 1ULL << 32.
	static_assert(
		F_CPU < (1ULL << 32),
		"F_CPU must be less than 1ULL << 32");
	const uint64_t f_cpu = F_CPU << 32;

	// We have that F_SCL = F_CPU / (16 + (2 * TWBR * prescale)).
	// To solve for TWBR and the prescale value iteratively, we
	// rearrange this equality to the expression below.
	const uint64_t target = ((f_cpu / f_scl) - (16ULL << 32)) / 2;

	const bool f_cpu_sufficient = target >> 32;
	if (!f_cpu_sufficient) return false;

	for (*twps = 0; *twps < 4; (*twps)++) {
		const uint8_t prescaler = 1 << (*twps * 2);

		const uint64_t result = target / prescaler;
		const uint32_t potential_twbr
			= (result >> 32) + ((bool) (result & (1ULL << 31)));

		// We've exhausted our prescaler.
		if (!potential_twbr)
			break;

		if (potential_twbr <= UINT8_MAX) {
			*twbr = potential_twbr;
			return true;
		}
	}

	return false;
}

ISR(TWI_vect)
{
	static unsigned char *buffer;
	static size_t         size;

	twi_status_t status = TWI_STATUS_FAILURE;

	if (TWCR & (1 << TWWC)) {
		status = TWI_STATUS_WRITE_COLLISION;
		goto error;
	}

	twi_message_t * const message = twi_isr.messages;

	switch (TW_STATUS) {
		case TW_START:
		case TW_REP_START:
			TWDR = message->address;

			buffer = message->buffer;
			size   = message->size;

			uint8_t twcr = TWCR & ~(1 << TWSTA);

			const bool mr_mode = message->address & 1;

			if (mr_mode)
				twcr |= 1 << TWEA;

			TWCR = twcr;

			return;

		case TW_MT_SLA_ACK:
		case TW_MT_DATA_ACK:
			if (!size--) {
				const uint8_t bit
					= --twi_isr.message_count
					? ++twi_isr.messages, TWSTA
					: TWSTO;

				if (bit == TWSTO)
					return_isr(TWI_STATUS_SUCCESS);

				TWCR |= 1 << bit;

				return;
			}

			TWDR  = *(buffer++);
			TWCR |= 1 << TWINT;

			return;

		case TW_MR_DATA_NACK:
			if (size-- != TWI_MR_FINAL_BYTE) {
				status = TWI_STATUS_NACK;

				break;
			}

			[[fallthrough]];

		case TW_MR_DATA_ACK:
			if (!size--) {
				const uint8_t bit
					= --twi_isr.message_count
					? ++twi_isr.messages, TWSTA
					: TWSTO;

				if (bit == TWSTO)
					return_isr(TWI_STATUS_SUCCESS);

				TWCR |= 1 << bit;

				return;
			}

			*(buffer++) = TWDR;

			[[fallthrough]];

		case TW_MR_SLA_ACK:
			TWCR
				= size == TWI_MR_FINAL_BYTE
				? TWCR & ~(1 << TWEA)
				: TWCR;

			return;

		case TW_MR_SLA_NACK:
		case TW_MT_DATA_NACK:
		case TW_MT_SLA_NACK:
			status = TWI_STATUS_NACK;
			break;

		//   TW_MT_ARB_LOST:
		case TW_MR_ARB_LOST:
			status = TWI_STATUS_ARBITRATION_LOST;
			break;

		case TW_NO_INFO:
			status = TWI_STATUS_NO_INFO;
			break;

		case TW_BUS_ERROR:
			status = TWI_STATUS_BUS_ERROR;
			break;

		default:
			break;
	}

error:
	return_isr(status);

	TWCR |= 1 << TWSTO;
}
