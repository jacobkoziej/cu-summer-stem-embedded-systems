// SPDX-License-Identifier: MPL-2.0
/*
 * encoder.h -- encoder steps
 * Copyright (C) 2025  Jacob Koziej <jacobkoziej@gmail.com>
 */

#ifndef ENCODER_STEPS_ENCODER_H
#define ENCODER_STEPS_ENCODER_H

#include <stdint.h>

void     encoder_setup(void);
uint32_t encoder_steps(void);

#endif  // ENCODER_STEPS_ENCODER_H
