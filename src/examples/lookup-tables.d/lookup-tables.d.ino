enum {
  RED,
  GREEN,
  BLUE,
  COLORS_TOTAL,
};

static const uint16_t ADC_MAX = (1 << 10) - 1;
static const uint8_t  PWM_MAX = (1 << 8)  - 1;

static const uint8_t COLOR_TO_PIN[COLORS_TOTAL] = {
  [RED]   = 9,
  [GREEN] = 10,
  [BLUE]  = 11,
};

static const uint8_t POTENTIOMETER_TO_PIN[COLORS_TOTAL] = {
  [RED]   = A0,
  [GREEN] = A1,
  [BLUE]  = A2,
};

void setup(void)
{
  for (uint8_t i = 0; i < COLORS_TOTAL; i++) {
    pinMode(POTENTIOMETER_TO_PIN[i], INPUT);

    pinMode(COLOR_TO_PIN[i], OUTPUT);
    digitalWrite(COLOR_TO_PIN[i], LOW);
  };
}

void loop(void)
{
  for (uint8_t i = 0; i < COLORS_TOTAL; i++) {
    const uint16_t sample = analogRead(POTENTIOMETER_TO_PIN[i]);
    analogWrite(COLOR_TO_PIN[i], map(sample, 0, ADC_MAX, 0, PWM_MAX));
  }
}
