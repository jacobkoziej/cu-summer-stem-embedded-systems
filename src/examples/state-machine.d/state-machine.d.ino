static const uint8_t MODE_BUTTON_PIN   = 2;
static const uint8_t ACTION_BUTTON_PIN = 4;

static const uint32_t BAUD = 115200;

enum {
  STATE_ADD,
  STATE_SUB,
  STATE_CLEAR,
  STATES_TOTAL,
};

static int32_t count;

static int state_add(void)
{
  if (digitalRead(MODE_BUTTON_PIN))
    return STATE_SUB;

  if (digitalRead(ACTION_BUTTON_PIN)) {
    ++count;

    Serial.print("Count: ");
    Serial.println(count);
  }

  return STATE_ADD;
}

static int state_sub(void)
{
  if (digitalRead(MODE_BUTTON_PIN))
    return STATE_CLEAR;

  if (digitalRead(ACTION_BUTTON_PIN)) {
    --count;

    Serial.print("Count: ");
    Serial.println(count);
  }

  return STATE_SUB;
}

static int state_clear(void)
{
  if (digitalRead(MODE_BUTTON_PIN))
    return STATE_ADD;

  if (digitalRead(ACTION_BUTTON_PIN)) {
    count = 0;

    Serial.println("Count cleared");
  }

  return STATE_CLEAR;
}

void setup(void)
{
  pinMode(MODE_BUTTON_PIN, INPUT);
  pinMode(ACTION_BUTTON_PIN, INPUT);

  Serial.begin(BAUD);
}

void loop(void)
{
  static uint8_t state;

  uint8_t new_state;

  switch (state) {
    case STATE_ADD: {
      new_state = state_add();
      break;
    };

    case STATE_SUB: {
      new_state = state_sub();
      break;
    };

    case STATE_CLEAR: {
      new_state = state_clear();
      break;
    };

    default: {
      new_state = STATE_ADD;
      break;
    };
  }

  if (state != new_state) {
    Serial.print("LOG: transitioning from state");
    Serial.print(state);
    Serial.print(" to ");
    Serial.print(new_state);
    Serial.println();
  }

  state = new_state;
}
