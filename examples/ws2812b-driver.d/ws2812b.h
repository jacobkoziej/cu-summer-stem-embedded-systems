// SPDX-License-Identifier: MPL-2.0
/*
 * ws2812b.h -- WS2812B driver
 * Copyright (C) 2025  Jacob Koziej <jacobkoziej@gmail.com>
 */

#ifndef WS2812B_H
#define WS2812B_H

#include <stdint.h>

typedef enum ws2812b_color {
	WS2812B_COLOR_GREEN,
	WS2812B_COLOR_RED,
	WS2812B_COLOR_BLUE,
	WS2812B_COLOR_TOTAL,
} ws2812b_color_t;

typedef uint8_t ws2812b_buffer_t[WS2812B_COLOR_TOTAL];

void ws2812b_tx(
	volatile uint8_t * const port,
	const uint8_t bit,
	const ws2812b_buffer_t * const buffer,
	const size_t pixels);

#endif  // WS2812B_H
