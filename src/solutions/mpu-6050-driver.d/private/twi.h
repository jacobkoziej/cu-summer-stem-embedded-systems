// SPDX-License-Identifier: MPL-2.0
/*
 * twi.h -- two-wire serial interface master
 * Copyright (C) 2025  Jacob Koziej <jacobkoziej@gmail.com>
 */

#ifndef PRIVATE_TWI_H
#define PRIVATE_TWI_H

#include "../twi.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

static const size_t TWI_MR_FINAL_BYTE = 1;

typedef struct twi_isr {
	bool           idle;
	twi_status_t   status;
	twi_message_t *messages;
	size_t         message_count;
} twi_isr_t;

static void return_isr(const twi_status_t status);
static bool scl_to_bitrate(
	const uint32_t f_scl,
	uint8_t * const twbr,
	uint8_t * const twps);

#endif  // PRIVATE_TWI_H
