# Interrupts

*Like a crying child, some things just need your attention right away.*

## Outline

- The Fourier Transform
- Hardware low-pass filter for debouncing
- Ultrasonic sensors
- Interrupts
- [`attachInterrupt()`], [`detachInterrupt()`], & [`digitalPinToInterrupt()`]
- Function prototypes
- Header files
- Multi-file sketches
- Quadrature encoders

## Exercises

1. Utilize interrupts to keep track of encoder steps.
   Create a separate source file that encapsulates your encoder functionality and expose the current encoder steps with a function that has the following signature: `uint32_t encoder_steps(void)`.

[`attachinterrupt()`]: https://docs.arduino.cc/language-reference/en/functions/external-interrupts/attachInterrupt/
[`detachinterrupt()`]: https://docs.arduino.cc/language-reference/en/functions/external-interrupts/detachInterrupt/
[`digitalpintointerrupt()`]: https://docs.arduino.cc/language-reference/en/functions/external-interrupts/digitalPinToInterrupt/
