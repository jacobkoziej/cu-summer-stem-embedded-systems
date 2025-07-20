// SPDX-License-Identifier: MPL-2.0
/*
 * encoder.cc -- encoder steps
 * Copyright (C) 2025  Jacob Koziej <jacobkoziej@gmail.com>
 */

#include "encoder.h"

#include "pins.h"

#include <Arduino.h>
#include <stdint.h>

static volatile uint32_t steps;

static void channel_isr(bool reverse)
{
	const uint8_t A = digitalRead(PIN_ENCODER_CHANNEL_A);
	const uint8_t B = digitalRead(PIN_ENCODER_CHANNEL_B);

	steps += A ^ B ^ reverse ? 1 : -1;
}

static void channel_a_isr(void)
{
	channel_isr(false);
}

static void channel_b_isr(void)
{
	channel_isr(true);
}

void encoder_setup(void)
{
	pinMode(PIN_ENCODER_CHANNEL_A, INPUT);
	pinMode(PIN_ENCODER_CHANNEL_B, INPUT);

	steps = 0;

	attachInterrupt(
		digitalPinToInterrupt(PIN_ENCODER_CHANNEL_A),
		channel_a_isr,
		CHANGE);
	attachInterrupt(
		digitalPinToInterrupt(PIN_ENCODER_CHANNEL_B),
		channel_b_isr,
		CHANGE);
}

uint32_t encoder_steps(void)
{
	return steps;
}
