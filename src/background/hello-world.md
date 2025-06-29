# Hello, World!

*Getting the ball rolling with Arduino.*

## Outline

- The basics of Information Theory, in particular, defining entropy
- Working with different numeral systems:
  - Decimal, Binary, Octal, & Hexadecimal
  - Two's complement
  - Quick conversion between Binary, Octal, & Hexadecimal
- Circuit fundamentals:
  - Ohm's Law
  - Series vs Parallel
  - Power
  - Analog vs Digital
- Arduino basics:
  - Using the [language reference]
  - [`setup()`] & [`loop()`]
  - Interfacing with digital IO
  - Delaying actions
  - Defining variables and constants
  - Arithmetic operations and assignment
  - [`if`]-[`else`] statements
- Debouncing buttons
- Crude debugging with an LED

## Exercises

1. In an attempt to absorb as much information as possible during the lesson, you suffer an exceptionally unexpected event and magically become stranded on an island with nothing but a laptop and your trusty Arduino.
   To make matters worse, it's night, and a new moon is out.

   1. Right as you're about to start cursing your luck, you remember that the Arduino Uno Rev3 has a built-in LED, and there are some fishers about a mile out from the island.
      Using your newfound knowledge, write a program to blink SOS so that you can make it back in time for tomorrow's lesson!

   2. Fortunately for you, the fishers noticed your SOS, shot a flare, and are now heading your way.
      Unfortunately, you notice unsettling noises coming from the bushes not too far from you.
      Thinking quickly, you decide to change the LED blinking pattern to be irritating and scare away anything from coming out to the beach.
      Write a program that blinks the built-in LED in a range between 50 and 500 milliseconds.
      Change the delay by 50 milliseconds every cycle, alternating between increasing and decreasing the delay depending on whether the delay time is saturated.

   3. Having been rescued by the fishers, as a token of appreciation (and as a practical joke), you decide to make them a counter that keeps track of the number of fish that got away in a day.
      They only have four LEDs, some resistors, and two push buttons on board.
      Being resourceful, you build them a 4-bit, unsigned counter.
      Write a program that displays in binary the number of fish that got away.
      One button should increment the counter while the other should reset it back to zero.
      If the counter overflows, turn on the built-in LED and turn off the remaining LEDs.

2. Being soon-to-be broke college students, you'll need to be resourceful with what you have on hand.
   To prepare you for this reality, let's create a dimmable Arduino night light using the built-in LED and a push button.
   We can achieve this by varying the percentage of time we power the LED.
   However, we need to perform this switching at a high enough frequency (>1 kHz) so that we cannot perceive the flickering.
   Utilize a push button to create 10 different LED brightness levels along with an off state.
   The push button should cycle between increasing the brightness and turning off the LED.

[language reference]: https://docs.arduino.cc/language-reference/
[`else`]: https://docs.arduino.cc/language-reference/en/structure/control-structure/else/
[`if`]: https://docs.arduino.cc/language-reference/en/structure/control-structure/if/
[`loop()`]: https://docs.arduino.cc/language-reference/en/structure/sketch/loop/
[`setup()`]: https://docs.arduino.cc/language-reference/en/structure/sketch/setup/
