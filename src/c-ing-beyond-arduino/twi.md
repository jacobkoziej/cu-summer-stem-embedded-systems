# 2-wire Serial Interface

*"Did you know that the 2-wire serial interface is compatible with Phillips’ I2C protocol!?" - Matthew Jeong*

## Outline

- I2C:
  - SDA & SCL
  - Master vs slave devices
  - START and STOP conditions
  - Addressing
  - Reading vs writing
  - ACK vs NACK
  - Multi-master configuration
- TWI:
  - Modes of operation
  - TWI registers
  - Clock generation
  - TWI interrupt
- MPU-6050:
  - Applications
  - Requesting data
  - External interrupt
- Drivers:
  - Definition
  - Non-blocking, interrupt-driven design

## Project

*MPU-6050 driver.*

1. Create a `twi` translation unit for your TWI driver.
   This translation unit must at the very least contain the following functions:

   - `twi_status_t twi_init(const uint32_t scl_frequency)`
   - `twi_status_t twi_enqueue(twi_message_t *messages, size_t message_count)`
   - `twi_status_t twi_status(void)`
   - `twi_status_t twi_cancel(void)`
   - `twi_status_t twi_deinit(void)`

   To simplify this assignment, we'll only consider master mode operation.
   To make our lives significantly easier, I suggest we take the following steps:

   01. Set the associated digital IO ports to inputs with their internal pull-up resistors enabled.
       This will allow us to avoid having to attach external pull-up resistors. However, please note that with these enabled, we can't set the SCL's frequency above 100 kHz.
   02. `typedef` an `enum` called `twi_status_t`.
       This `enum` should contain a list of TWI status codes your functions can return to indicate success, failure, or nominal operation.
   03. `typedef` a `struct` called `twi_message_t`.
       This `struct` should contain a pointer to a `uint8_t` buffer our driver can read from/write to, along with a size for this buffer in bytes.
   04. Define a `static` function for calculating our clock pre-scaler and `TWBR` values given an SCL frequency.
   05. Populate `ISR(TWI_vect)` with an empty `switch`-`case` using constants defined in [`<util/twi.h>`] related to master mode.
       Instead of directly `switch`ing on `TWSR`, utilize the `TW_STATUS` macro as it will automatically mask non-zero pre-scaler bits.
       Do note that a few of the status operations can be the same, so fall-through `case`s might be useful to reduce code duplication.
   06. Create a `static struct` local to the `twi` translation unit that will contain all variables we might share between the ISR and regular functions.
   07. `twi_init()` should set the SCL frequency on a best-effort basis, along with initializing the TWI peripheral to be in an idle state.
       This function is also a great point to set default values for any variables we will use in our ISR.
   08. `twi_enqueue()` should pass a pointer to a message or array of messages (if we intend to utilize the repeat START condition) along with a count of the number of messages we'll be transmitting to internal variables used in our ISR before successfully returning to the caller.
       There should also be some basic checks in place here to ensure that we don't interrupt an existing operation.
       In the case of an ongoing operation, we should fail gracefully and return control to the caller.
   09. At this point, we can start filling out our `switch`-`case` in our ISR.
       I recommend looking at [application note AVR315], which guides you through an [example master TWI driver].[^warning]
       If you read the AVR315 application note or ATmega328P datasheet, you'll notice that the TWI peripheral is a state machine we control with a handful of registers.
       I suggest tracing out possible execution paths and finding terminal states on success or failure.
       In either case, you should pass status information to the user, along with indicating that the operation has concluded.
   10. `twi_status()` gives our calling code a glimpse into what's happening in the background so that it can act accordingly.
       Once the enqueued TWI operation is complete, this function should return success to the caller, who can access any read data or enqueue a new operation.
   11. In the case of the I2C bus failing, you may want to timeout an operation.
       `twi_cancel()` serves the purpose of rescuing our code from this limbo as opposed to hanging like older versions of the [Arduino Wire library].
   12. Finally, add the ability to disable TWI entirely with `twi_deinit()`.
       In the case of an ongoing operation or an uninitialized TWI peripheral, this function should fail gracefully.

2. Create an `mpu-6050` translation unit for your MPU-6050 driver.
   **Functions and steps are TBD.**

[^warning]: Be highly skeptical of manufacturer code or other code you find on the internet!
    At least for the Atmel code linked above, it includes a few mistakes and poor design decisions:

    - Unbounded busy loops checking `TWINT`, which may never be unset if the I2C bus is disconnected.
    - Variables shared between regular functions and the ISR that are not `volatile`.
    - `TWSR` pre-scaler bits are not masked when checking TWI status bits, so a non-zero pre-scaler renders the driver useless.
    - `TWCR` is always overwritten, irrespective of user settings.
      For example, a user may wish to keep `TWEA` disabled for whatever reason.
    - Time and space get wasted copying buffered data to an internal TWI data buffer.

    There might not be all the errors, but the point still stands: code from manufacturers or the general internet should be nothing more than a reference and/or starting point, as opposed to an infallible source of truth!

[application note avr315]: https://ww1.microchip.com/downloads/aemDocuments/documents/OTH/ApplicationNotes/ApplicationNotes/00002480A.pdf
[arduino wire library]: https://docs.arduino.cc/language-reference/en/functions/communication/wire/
[example master twi driver]: https://ww1.microchip.com/downloads/en/AppNotes/Atmel-2564-Using-the-TWI-Module-as-I2C-Master_ApplicationNote_AVR315.zip
[`<util/twi.h>`]: https://avrdudes.github.io/avr-libc/avr-libc-user-manual/group__util__twi.html
