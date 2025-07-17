static const uint8_t ECHO_PIN    = 2;
static const uint8_t TRIGGER_PIN = 4;

/*
 * In Standard Temperature and Pressure (STP), sound travels at 343 m/s.
 * Here we define this constant but in terms of microseconds to make it
 * easy for us to convert to meters given our measurement in
 * microseconds.
 */
static const float STP_SOUND_METERS_PER_US = 343e-6f;

static const uint32_t BAUD            = 115200;
static const uint8_t  PULSE_LENGTH_US = 10;
static const uint8_t  SAMPLE_DELAY_MS = 10;

static volatile bool     pulse_ready;
static volatile uint16_t pulse_time_us;

static void echo_isr(void)
{
  /*
   * NOTE: On ATmega328P, only one interrupt can execute at a time. This
   * becomes problematic when using millis() or micros() inside of an
   * interrupt context as the underlying timers which drive these
   * functions are only 16-bit! This means the upper 16 bits of the
   * returned value is stored independent of the timer value and
   * incremented with an overflow interrupt. Since timers don't stop in
   * interrupt contexts, it's possible for the timer to overflow between
   * the start and end times, causing a possible erroneous reading of
   * about (1 << 32) - (1 << 16). To avoid this, we only store the lower
   * 16 bits of the return value of millis() or micros(), more
   * specifically, the actual timer value, allowing us to avoid this
   * issue all together!
   */
  static uint16_t pulse_start_us;

  // erroneous interrupt
  if (pulse_ready)
    return;

  if (digitalRead(ECHO_PIN)) {
    pulse_start_us = micros();

    return;
  }

  const uint16_t pulse_end_us = micros();

  pulse_time_us = pulse_end_us - pulse_start_us;
  pulse_ready   = true;
}

void setup(void)
{
  pinMode(ECHO_PIN, INPUT);

  digitalWrite(TRIGGER_PIN, LOW);
  pinMode(TRIGGER_PIN, OUTPUT);

  Serial.begin(BAUD);

  attachInterrupt(digitalPinToInterrupt(ECHO_PIN), echo_isr, CHANGE);
}

void loop(void)
{
  pulse_ready = false;

  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(PULSE_LENGTH_US);
  digitalWrite(TRIGGER_PIN, LOW);

  // NOTE: your code can be doing other things while we wait for the
  // pulse to come in, like timeout---we just have nothing to do
  while (!pulse_ready)
    continue;

  // since the pulse travels to the object and back, we need to divide
  // the total time in half since we measure double the distance
  const float distance_m = STP_SOUND_METERS_PER_US * (pulse_time_us / 2);

  Serial.print(distance_m);
  Serial.println("m");

  // if we don't wait here, the HC-SR04 becomes unhappy and doesn't
  // ever send the next pulse we request :(
  delay(SAMPLE_DELAY_MS);
}
