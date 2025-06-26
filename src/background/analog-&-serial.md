# Analog & Serial

*More interesting interactions with the world.*

## Outline

- Quantization
- Pulse-Width Modulation (PWM)
- Potentiometers
- Analog to Digital Conversion (ADC)
- [`map()`] function
- Hysteresis
- [`Serial`] communication:
  - RX vs TX
  - Baud rate
  - Parity
  - Serialization
  - Serial console
- ASCII encoding
- RGB(A) color model
- RGB LEDs
- [`Serial`] debugging

## Exercises

1. In anticipation of building your own audio amplifier, you decide to create a volume indicator.
   Using four LEDs, create a 4-bit volume indicator where a potentiometer serves as the volume knob.
   Ensure that hysteresis is added to each of the volume regions to prevent flickering of volume levels.

2. Since I'm a huge Pink Floyd fan, let's pick [Any Colour You Like].
   Utilize three potentiometers to change the color of an RGB LED to any color you like.
   **Optionally**, add a button to dim the LED brightness by 50%.

3. Since moving our hands from the keyboard is such a hassle, let's instead utilize the serial console to control the color of the LED.
   Your code should expect a valid hex RGB value followed by a newline.
   If this value is malformed, return an error to the user with a meaningful error code; otherwise, return a success code.
   **Optionally**, add support for an optional alpha channel.
   If the user supplies no alpha channel, assume alpha is 100%.

[any colour you like]: https://open.spotify.com/track/6FBPOJLxUZEair6x4kLDhf
[`map()`]: https://docs.arduino.cc/language-reference/en/functions/math/map/
[`serial`]: https://docs.arduino.cc/language-reference/en/functions/communication/serial/
