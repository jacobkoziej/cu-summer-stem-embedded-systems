static const char MESSAGE[] = "cooper union ";

static const uint8_t WINDOW_SIZE = 4;

// exclude the NULL character when calculating the size
static const uint8_t MESSAGES_SIZE = sizeof(MESSAGE) - 1;

static const uint32_t BAUD     = 115200;
static const uint16_t DELAY_MS = 500;

void setup(void)
{
  Serial.begin(BAUD);
}

void loop(void)
{
  static uint8_t index;

  for (size_t i = 0; i < WINDOW_SIZE; i++)
    Serial.print(MESSAGE[(index + i) % MESSAGES_SIZE]);

  Serial.print('\n');

  index = (index + 1) % MESSAGES_SIZE;

  delay(DELAY_MS);
}
