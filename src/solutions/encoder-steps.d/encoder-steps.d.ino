// SPDX-License-Identifier: MPL-2.0
/*
 * encoder steps
 * Copyright (C) 2025  Jacob Koziej <jacobkoziej@gmail.com>
 */

#include "encoder.h"

const static uint32_t BAUD = 115200;

void setup(void)
{
  encoder_setup();

  Serial.begin(BAUD);
}

void loop(void)
{
  Serial.println(encoder_steps());
}
