# Circular Buffers

*Don't look too far ahead; you might see what you've left behind.*

## Outline

- Modular arithmetic
- Circular buffers
- Multiplexing

## Project

*Scrolling quad seven-segment display.*

1. Create two lookup tables: one that maps seven-segment display segments to pins and another that maps digits to pins.
2. Write a function that, given a `uint8_t` bitmask, displays it on a seven-segment digit.
3. Write code that multiplexes between the different digits of the display.
   At this point, it should look as if all the digits are on at the same time.
4. Write a function that, given ASCII digits, letters, or the space character, returns an index into a lookup table of associated seven-segment bitmasks.
5. Implement a circular text buffer that can repeatedly scroll on your display.
