enum {
  BUTTON_MODE,
  BUTTON_ACTION,
  BUTTONS_TOTAL,
};

static const uint8_t BUTTON_TO_PIN[BUTTONS_TOTAL] = {
  [BUTTON_MODE]   = 2,
  [BUTTON_ACTION] = 4,
};

enum {
  STATE_ADD,
  STATE_SUB,
  STATE_CLEAR,
  STATES_TOTAL,
};

static const uint32_t BAUD = 115200;

static int32_t count;

static bool button_rising(const int button)
{
  static uint8_t previous_state[BUTTONS_TOTAL];

  const uint8_t current_state = digitalRead(BUTTON_TO_PIN[button]);

  const bool rising = !previous_state[button] && current_state;

  previous_state[button] = current_state;

  return rising;
}

static int state_add(void)
{
  if (button_rising(BUTTON_MODE))
    return STATE_SUB;

  if (button_rising(BUTTON_ACTION)) {
    ++count;

    Serial.print("Count: ");
    Serial.println(count);
  }

  return STATE_ADD;
}

static int state_sub(void)
{
  if (button_rising(BUTTON_MODE))
    return STATE_CLEAR;

  if (button_rising(BUTTON_ACTION)) {
    --count;

    Serial.print("Count: ");
    Serial.println(count);
  }

  return STATE_SUB;
}

static int state_clear(void)
{
  if (button_rising(BUTTON_MODE))
    return STATE_ADD;

  if (button_rising(BUTTON_ACTION)) {
    count = 0;

    Serial.println("Count cleared");
  }

  return STATE_CLEAR;
}

void setup(void)
{
  for (size_t i = 0; i < BUTTONS_TOTAL; i++)
    pinMode(BUTTON_TO_PIN[i], INPUT);

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
