# Pointers

*If you thought shooting yourself in the foot hurt, just wait till you blow off your leg!*

## Outline

- Harvard vs Von Neumann architecture
- Pointers:
  - `NULL`
  - Pointer arithmetic
  - `uintptr_t`
- Multi-level pointers
- Function pointers
- `void` pointers
- `_Static_assert()`

## Exercises

1. Let's make our own digital IO functions like the Arduino framework!

   1. Create `digital.c` and `digital.h` files; these will store your digital IO functionality.

   2. Create a function with the following signature: `volatile uint8_t *digital_pin_to_port(uint8_t pin)`.
      If you reference the register summary of the ATmega328P datasheet, you'll see that the port registers reside next to one another; use this information to your advantage to simplify your logic.
      If the user specifies an invalid pin number, return `NULL`.

   3. `typedef` an `enum` called `digital_register_type_t` to let us specify if we're interested in `PORTx`, `DDRx`, or `PINx` of a port register.

   4. Create a function with the following signature: `volatile uint8_t *digital_port_offset(volatile uint8_t * const port, digital_register_type_t type)`.
      If you define `digital_register_type_t` in a clever manner, you can simply add the value of `type` to `port` to get the correct offset.
      To make sure this works as intended, add static assertions to your header to make sure that your `enum` values are indeed valid offsets.

   5. Create a function with the following signature: `int digital_pin_to_bit(uint8_t pin)`.
      This function should return the bit offset of a pin inside a port register.
      If the user specifies an invalid pin number, return `-1`.

   6. `typedef` an `enum` called `digital_mode_t` to let us specify if we're interested in `INPUT`, `OUTPUT`, or `INPUT_PULLUP`.

   7. Create functions with the following signatures:

      - `bool digital_pin_mode(uint8_t pin, digital_mode_t mode)`
      - `bool digital_write(uint8_t pin, bool high)`
      - `bool digital_read(uint8_t pin, bool * const pin_state)`

      These functions should make calls to all three of the previous helper functions to simplify the internals and return `true` or `false` to indicate the success of execution.

2. Rewrite your vending machine state machine to utilize a lookup table of function pointers to remove the existing `switch`-`case`.
   Remove all uses of global variables; instead, pass a pointer to a shared `static struct` in your state machine function.
