# Timers & State Machines

*We can't describe everything in terms of finite states, but that sure hasn't stopped us from trying.*

## Outline

- [`millis()`] & [`micros()`]
- Super loops
- [`random()`] & [`randomSeed()`]
- `struct`ures
- `typedef`initions
- [`switch`]-[`case`]s
- State machines

## Exercises

1. Blink two LEDs every 389 and 991 milliseconds.

2. I miss the days of bringing quarters to school for a snack at the vending machine, so let's make one to bring this childhood memory of mine back to life!
   Create a simple state machine to turn your Arduino into a vending machine!
   Your state machine should have the following states:

   - Collecting quarters
   - Item dispensing
   - Returning change (if any)

   Since this is a "proof of concept" device, let's make the following simplifications:

   - Print status information to the serial console to let the user know what's going on.
   - Pressing a button adds a quarter.
   - Pressing a button will toggle between items.
   - Pressing a button returns users their change.

   And to complicate things a bit, let's consider the following:

   - Have at least three different priced items with a finite stock.
   - Add a 30s timeout from the last inserted quarter. On timeout, return all change.
   - Randomly reject quarters at a 1% rate and let users know about this failure.
   - Blink the built-in LED every second so users know the machine is still on.

[`case`]: https://docs.arduino.cc/language-reference/en/structure/control-structure/switchCase/
[`micros()`]: https://docs.arduino.cc/language-reference/en/functions/time/micros/
[`millis()`]: https://docs.arduino.cc/language-reference/en/functions/time/millis/
[`random()`]: https://docs.arduino.cc/language-reference/en/functions/random-numbers/random/
[`randomseed()`]: https://docs.arduino.cc/language-reference/en/functions/random-numbers/randomSeed/
[`switch`]: https://docs.arduino.cc/language-reference/en/structure/control-structure/switchCase/
