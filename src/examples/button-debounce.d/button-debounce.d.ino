#define BUTTON      2
#define DEBOUNCE_MS 4

bool button_state;

void setup(void)
{
  pinMode(BUTTON, INPUT);

  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(LED_BUILTIN, button_state);
}

void loop(void)
{
  // get our initial sample of the button
  bool button_sample = digitalRead(BUTTON);

  // wait for the button to settle
  delay(DEBOUNCE_MS);

  // if the current sample is the same as the
  // previous we assume the new button state
  if (digitalRead(BUTTON) == button_sample)
    button_state = button_sample;

  digitalWrite(LED_BUILTIN, button_state);
}
