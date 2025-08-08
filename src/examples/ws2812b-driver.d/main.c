// SPDX-License-Identifier: MPL-2.0
/*
 * main.c -- sample code to interface with WS2812B
 * Copyright (C) 2025  Jacob Koziej <jacobkoziej@gmail.com>
 */

#include <assert.h>
#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>
#include <util/delay.h>

#include "ws2812b.h"

#define ROWS    2
#define COLUMNS 4
#define PIXELS  (ROWS * COLUMNS)

typedef uint8_t display_buffer_t[ROWS][COLUMNS][WS2812B_COLOR_TOTAL];

static volatile uint8_t * const PIXELS_DDR  = &DDRD;
static volatile uint8_t * const PIXELS_PORT = &PORTD;
static const uint8_t            PIXELS_BIT  = PD0;

// We create a union for display and ws2812b buffers to avoid violating
// the strict aliasing rule which would introduce undefined behavior.
static union {
	display_buffer_t display;
	ws2812b_buffer_t ws2812b[PIXELS];
} buffer;

static_assert(
	sizeof(buffer.display) == sizeof(buffer.ws2812b),
	"display and ws2812b buffers must match in size");

int main(void)
{
	// generate arbitrary pattern to display
	for (size_t i = 0; i < ROWS; i++)
		for (size_t j = 0; j < COLUMNS; j++)
			for (size_t k = 0; k < WS2812B_COLOR_TOTAL; k++)
				buffer.display[i][j][k] = (i + j + k + 1) << j;

	*PIXELS_DDR  |=   1 << PIXELS_BIT;
	*PIXELS_PORT &= ~(1 << PIXELS_BIT);

	// The WS2812B data line needs to be held low for at least 50 us
	// on initialization to latch onto transmitted bit sequences.
	_delay_us(50);

	ws2812b_tx(PIXELS_PORT, PIXELS_BIT, buffer.ws2812b, PIXELS);

	return EXIT_SUCCESS;
}
