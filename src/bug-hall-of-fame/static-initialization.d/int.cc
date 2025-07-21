extern "C" {
#include <stdint.h>
int digitalRead(uint8_t pin);
};

static const uint8_t PIN_ENCODER_CHANNEL_A = 2;
static const uint8_t PIN_ENCODER_CHANNEL_B = 3;

static volatile int32_t steps;

void channel_a_isr(void)
{
  int A = digitalRead(PIN_ENCODER_CHANNEL_A);
  int B = digitalRead(PIN_ENCODER_CHANNEL_B);

  steps += A ^ B ? 1 : -1;
}
