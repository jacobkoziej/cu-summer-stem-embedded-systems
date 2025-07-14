# Bit Manipulation & Lookup Tables

*Squeezing and pre-computing data.*

## Outline

- Standard integer types
- Endianness
- Bitwise operations:
  - AND
  - OR
  - XOR
  - NOT
  - Left shift
  - Right shift
- Bit masks
- Bit packing
- `enum`erations
- Lookup tables
- `sizeof` operator
- `static` storage class qualifier
- Seven-segment displays

## Exercises

1. You're working on a parallel, serial system where you bit-bang ASCII characters on the digital IO pins of the Arduino.
   Initially, you thought about using the IO pins in sequential order to write out the ASCII value easily with a bit shift; however, being the brilliant engineer you are, you anticipate a future where someone on the hardware team asks you to change a few of the IO pins you use.
   Create a lookup table that maps the bit position in an ASCII character to an IO pin.
   Utilizing this table, display any ASCII value using 7 LEDs.

2. You're working on a communication protocol, and following some clever math over [GF(2)], you end up with a `uint64_t` where each bit represents an irrecoverable bit error.
   Since you're working on a real-time system, you need to quickly determine if the number of bit errors is still recoverable.
   Write code that counts the number of bits set in a `uint64_t`.
   Make your code interactive by allowing a user to specify any integer over serial and reporting the number of bits set back to the user.

3. Since you're working in an embedded environment, memory is a scarce resource, making logging a headache.
   During the engineering design process, you and your team decide that you need to keep track of the occurrence of an event over the last eight time steps.
   Write code that cyclically fills a `uint8_t` where we represent the presence of an event by a set bit.
   When you press one push button, read the value of another to determine the occurrence of the event.
   **Optionally**, add another button that will print the last eight events over serial when pressed.
   During setup, zero the buffer to assume no events have happened.

4. **(Challenge)** When dealing with a vast amount of binary data, corruption is inevitable.
   Due to this possibility, we need a method to determine if our data has changed so that we can act accordingly.
   One method is to utilize a 32-bit [Cyclic Redundancy Check] (CRC-32).
   Implement a function that computes a CRC-32 given an array of `uint8_t`'s and the number of bytes using the standard IEEE polynomial of `0x04C11DB7` and initial condition of `0xFFFFFFFF`.
   **Remember**, endianness matters here!
   You might need to use the reversed version of the polynomial.
   Create an array with the message "cooper union" and check if your function reports a correct CRC-32.

[cyclic redundancy check]: https://en.wikipedia.org/wiki/Cyclic_redundancy_check
[gf(2)]: https://en.wikipedia.org/wiki/GF(2)
