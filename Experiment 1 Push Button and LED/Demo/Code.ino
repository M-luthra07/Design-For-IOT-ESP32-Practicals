#define BUTTON_PIN 4  // Push button connected to GPIO 4
#define LED_PIN 2     // LED connected to GPIO 2

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Button as input with internal pull-up
  pinMode(LED_PIN, OUTPUT);           // LED as output
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);  

  if (buttonState == LOW) { // Button pressed (LOW when pressed due to pull-up)
    digitalWrite(LED_PIN, HIGH);  // Turn on LED
  } else {
    digitalWrite(LED_PIN, LOW); // Turn off LED
  }
}
