// SPDX-License-Identifier: MPL-2.0
/*
 * main.c -- sample code to interface with MPU-6050 over TWI
 * Copyright (C) 2025  Jacob Koziej <jacobkoziej@gmail.com>
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdlib.h>

#include "twi.h"

const uint32_t SCL_FREQUENCY = 100000;

int main(void)
{
	sei();

	uint8_t pin_mask = (1 << PC5) | (1 << PC4);

	DDRC  &= ~pin_mask;
	PORTC |=  pin_mask;

	twi_status_t status = twi_init(SCL_FREQUENCY);

	if (status != TWI_STATUS_SUCCESS)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}
