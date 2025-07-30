# Timers & PWM

*Good design demands good compromise.*

## Outline

- SREG
- Timers:
  - Groups
  - Prescalers
  - Interrupt sources
  - Clear conditions
- PWM:
  - Output compare unit
  - Fast PWM
  - Phase correct PWM
- AVR-LIBC ISRs

## Exercises

1. Create your function to keep track of microseconds.
   This function should utilize an 8-bit timer and an overflow interrupt to return an accurate 64-bit result.
2. Set the highest clock prescaler for the 16-bit timer and observe how different PWM modes behave when switching output compare values between `1 << 15` and `1 << 14`.
   Make sure to utilize the output compare interrupt to make switching between these two values seamless.
