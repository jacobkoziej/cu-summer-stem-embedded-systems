static const uint32_t DELAY_US = 500000;

static uint32_t previous_time_us;

void setup(void)
{
  digitalWrite(LED_BUILTIN, LOW);
  pinMode(LED_BUILTIN, OUTPUT);

  previous_time_us = micros();
}

void loop(void)
{
  uint32_t current_time_us;

  if ((current_time_us = micros()) - previous_time_us >= DELAY_US) {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

    previous_time_us = current_time_us;
  }
}
