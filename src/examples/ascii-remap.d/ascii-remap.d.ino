static const uint32_t BAUD = 115200;

static const uint8_t DIGITS = 10;
static const uint8_t INVALID_INDEX = 255;

static uint8_t ascii_to_index(const unsigned char c)
{
  if ((c >= '0') && (c <= '9'))
    return c - '0';

  if ((c >= 'A') && (c <= 'Z'))
    return c - 'A' + DIGITS;

  if ((c >= 'a') && (c <= 'z'))
    return c - 'a' + DIGITS;

  return INVALID_INDEX;
}

void setup(void)
{
  Serial.begin(BAUD);

  Serial.println(ascii_to_index('4'));
  Serial.println(ascii_to_index('J'));
  Serial.println(ascii_to_index('K'));
  Serial.println(ascii_to_index('!'));
}

void loop(void)
{
}
