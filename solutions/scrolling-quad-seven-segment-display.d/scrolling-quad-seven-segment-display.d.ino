// SPDX-License-Identifier: MPL-2.0
/*
 * scrolling quad seven-segment display
 * Copyright (C) 2025  Jacob Koziej <jacobkoziej@gmail.com>
 */

/*
 * Here we create a constant array of characters for the message we wish
 * to scroll on the seven segment display along with the scrolling delay
 * and time each digit is enabled in microseconds.
 *
 * NOTE: when calculating the message size, we subtract one from the
 * result of sizeof(). This is because the string literal we used for
 * assignment includes a trailing NULL character. Since this is not a
 * printable, we simply exclude it.
 */
static const char     MESSAGE[]       = "COOPER EE25 ";
static const uint8_t  MESSAGE_SIZE    = sizeof(MESSAGE) - 1;
static const int32_t  SCROLL_DELAY_US = 500000;
static const uint16_t DIGIT_TIME_US   = 250;

/*
 * Here we map each segment to an array and bit index for a seven-
 * segment digit. In this case, we treat the LSB as a decimal point and
 * the MSB as segment A.
 */
enum {
  SEGMENT_DP,
  SEGMENT_G,
  SEGMENT_F,
  SEGMENT_E,
  SEGMENT_D,
  SEGMENT_C,
  SEGMENT_B,
  SEGMENT_A,
  SEGMENTS_TOTAL,
};

/*
 * Here we create a lookup table that maps segment index to pin number
 * on the Arduino Uno Rev3. We explicitly assign with the array index as
 * to make this code "self documenting" and reduce the probability of
 * incorrect assignments while editing the order of pins.
 */
static const uint8_t SEGMENT_TO_PIN[SEGMENTS_TOTAL] = {
  [SEGMENT_DP] = 8,
  [SEGMENT_G]  = 7,
  [SEGMENT_F]  = 4,
  [SEGMENT_E]  = 2,
  [SEGMENT_D]  = A3,
  [SEGMENT_C]  = A2,
  [SEGMENT_B]  = A1,
  [SEGMENT_A]  = A0,
};

/*
 * Since a display can possibly have any number of digits, we don't go
 * through the effort of creating an enum for each of the digits (unless
 * there's a need to refer to specific digits by name). We also store
 * the number of digits using sizeof() so that the constant dynamically
 * updates if we were to add/remove digits in the future.
 *
 * NOTE: we divide the size of the array by the size of the first
 * element as there is no guarantee that a uint8_t is the smallest
 * integer size on our target architecture unlike a char.
 */
static const uint8_t DIGIT_TO_PIN[] = {9, 6, 5, 3};
static const uint8_t DIGITS_TOTAL
  = sizeof(DIGIT_TO_PIN) / sizeof(DIGIT_TO_PIN[0]);

/*
 * In our case, the quad seven-segment display digits are active low
 * while segments are active high. If we were to change our display in
 * the future, we can just change the following constants to adjust the
 * logic levels elsewhere in our code as opposed to inverting a bunch of
 * HIGH/LOW constants.
 */
static const uint8_t DIGIT_ON    = LOW;
static const uint8_t DIGIT_OFF   = HIGH;
static const uint8_t SEGMENT_ON  = HIGH;
static const uint8_t SEGMENT_OFF = LOW;

/*
 * Since we're only concerned with a subset of the printable ASCII
 * characters, we create a condensed lookup table with bitmasks we can
 * show on the seven-segment display. To facilitate this reduced lookup
 * table size, we must also write a function that remaps ASCII values.
 */
static const uint8_t ASCII_DIGIT_OFFSET  = 1;
static const uint8_t ASCII_LETTER_OFFSET = 10 + ASCII_DIGIT_OFFSET;

static const uint8_t ASCII_LOOKUP[] = {
  [' ' - ' ']                       = 0b00000000,
  ['0' - '0' + ASCII_DIGIT_OFFSET]  = 0b11111100,
  ['1' - '0' + ASCII_DIGIT_OFFSET]  = 0b01100000,
  ['2' - '0' + ASCII_DIGIT_OFFSET]  = 0b11011010,
  ['3' - '0' + ASCII_DIGIT_OFFSET]  = 0b11110010,
  ['4' - '0' + ASCII_DIGIT_OFFSET]  = 0b01100110,
  ['5' - '0' + ASCII_DIGIT_OFFSET]  = 0b10110110,
  ['6' - '0' + ASCII_DIGIT_OFFSET]  = 0b00111110,
  ['7' - '0' + ASCII_DIGIT_OFFSET]  = 0b11100000,
  ['8' - '0' + ASCII_DIGIT_OFFSET]  = 0b11111110,
  ['9' - '0' + ASCII_DIGIT_OFFSET]  = 0b11110110,
  ['a' - 'a' + ASCII_LETTER_OFFSET] = 0b11101110,
  ['b' - 'a' + ASCII_LETTER_OFFSET] = 0b00111110,
  ['c' - 'a' + ASCII_LETTER_OFFSET] = 0b10011100,
  ['d' - 'a' + ASCII_LETTER_OFFSET] = 0b01111010,
  ['e' - 'a' + ASCII_LETTER_OFFSET] = 0b10011110,
  ['f' - 'a' + ASCII_LETTER_OFFSET] = 0b10001110,
  ['g' - 'a' + ASCII_LETTER_OFFSET] = 0b11110110,
  ['h' - 'a' + ASCII_LETTER_OFFSET] = 0b00101110,
  ['i' - 'a' + ASCII_LETTER_OFFSET] = 0b00100000,
  ['j' - 'a' + ASCII_LETTER_OFFSET] = 0b01111000,
  ['k' - 'a' + ASCII_LETTER_OFFSET] = 0b01101110,
  ['l' - 'a' + ASCII_LETTER_OFFSET] = 0b00011100,
  ['m' - 'a' + ASCII_LETTER_OFFSET] = 0b10101010,
  ['n' - 'a' + ASCII_LETTER_OFFSET] = 0b00101010,
  ['o' - 'a' + ASCII_LETTER_OFFSET] = 0b00111010,
  ['p' - 'a' + ASCII_LETTER_OFFSET] = 0b11001110,
  ['q' - 'a' + ASCII_LETTER_OFFSET] = 0b11100110,
  ['r' - 'a' + ASCII_LETTER_OFFSET] = 0b00001010,
  ['s' - 'a' + ASCII_LETTER_OFFSET] = 0b10110110,
  ['t' - 'a' + ASCII_LETTER_OFFSET] = 0b00011110,
  ['u' - 'a' + ASCII_LETTER_OFFSET] = 0b00111000,
  ['v' - 'a' + ASCII_LETTER_OFFSET] = 0b01111100,
  ['w' - 'a' + ASCII_LETTER_OFFSET] = 0b10111000,
  ['x' - 'a' + ASCII_LETTER_OFFSET] = 0b01101110,
  ['y' - 'a' + ASCII_LETTER_OFFSET] = 0b01110110,
  ['z' - 'a' + ASCII_LETTER_OFFSET] = 0b11011010,
};

/*
 * Here we create a function that maps ASCII characters to our lookup
 * table indices. This function checks ranges of contiguous ASCII
 * characters and adds appropriate offsets.
 */
static uint8_t ascii_to_index(const char c)
{
  if (c == ' ')
    return c - ' ';

  if ((c >= '0') && (c <= '9'))
    return c - '0' + ASCII_DIGIT_OFFSET;

  if ((c >= 'A') && (c <= 'Z'))
    return c - 'A' + ASCII_LETTER_OFFSET;

  if ((c >= 'a') && (c <= 'z'))
    return c - 'a' + ASCII_LETTER_OFFSET;

  return 0;
}

/*
 * To simplify using the seven-segment display, we create a function,
 * that given a bitmask, will write it to the display using the bit
 * values as to identify which segments to turn on/off.
 */
static void digit_write(const uint8_t digit)
{
  for (size_t i = 0; i < SEGMENTS_TOTAL; i++)
    digitalWrite(
      SEGMENT_TO_PIN[i],
      digit & (1 << i) ? SEGMENT_ON : SEGMENT_OFF);
}

void setup(void)
{
  // on reset, we disable the display to get it into a consistent state

  for (size_t i = 0; i < DIGITS_TOTAL; i++) {
    digitalWrite(DIGIT_TO_PIN[i], DIGIT_OFF);
    pinMode(DIGIT_TO_PIN[i], OUTPUT);
  };

  for (size_t i = 0; i < SEGMENTS_TOTAL; i++) {
    digitalWrite(SEGMENT_TO_PIN[i], SEGMENT_OFF);
    pinMode(SEGMENT_TO_PIN[i], OUTPUT);
  };
}

void loop(void)
{
  static uint8_t index;
  static int32_t scroll_delay_us = SCROLL_DELAY_US;

  for (size_t i = 0; i < DIGITS_TOTAL; i++) {
    const uint8_t letter = MESSAGE[(index + i) % MESSAGE_SIZE];
    const uint8_t digit  = ASCII_LOOKUP[ascii_to_index(letter)];

    // set segments before enabling digits to reduce flicker
    digit_write(digit);

    digitalWrite(DIGIT_TO_PIN[i], DIGIT_ON);
    delayMicroseconds(DIGIT_TIME_US);
    digitalWrite(DIGIT_TO_PIN[i], DIGIT_OFF);
  }

  scroll_delay_us -= DIGITS_TOTAL * DIGIT_TIME_US;

  if (scroll_delay_us <= 0) {
    index = (index + 1) % MESSAGE_SIZE;

    scroll_delay_us = SCROLL_DELAY_US;
  }
}
