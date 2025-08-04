// SPDX-License-Identifier: MPL-2.0
/*
 * twi.h -- two-wire serial interface master
 * Copyright (C) 2025  Jacob Koziej <jacobkoziej@gmail.com>
 */

#ifndef TWI_H
#define TWI_H

#include <stddef.h>
#include <stddef.h>
#include <stdint.h>
#include <util/twi.h>

typedef enum twi_status {
	TWI_STATUS_SUCCESS,
	TWI_STATUS_ARBITRATION_LOST,
	TWI_STATUS_BUSY,
	TWI_STATUS_BUS_ERROR,
	TWI_STATUS_CANCELLED,
	TWI_STATUS_DISABLED,
	TWI_STATUS_DOUBLE_INIT,
	TWI_STATUS_FAILURE,
	TWI_STATUS_INVALID_ADDRESS,
	TWI_STATUS_INVALID_SCL,
	TWI_STATUS_NACK,
	TWI_STATUS_NO_INFO,
	TWI_STATUS_WRITE_COLLISION,
} twi_status_t;

typedef struct twi_message {
	uint8_t  address;
	uint8_t *buffer;
	size_t   size;
} twi_message_t;

static const uint8_t TWI_READ = TW_READ;
static const uint8_t TWI_WRITE = TW_WRITE;

twi_status_t twi_cancel(void);
twi_status_t twi_deinit(void);
twi_status_t twi_enqueue(twi_message_t * const messages, size_t message_count);
twi_status_t twi_init(const uint32_t scl_frequency);
twi_status_t twi_status(void);

#endif  // TWI_H
