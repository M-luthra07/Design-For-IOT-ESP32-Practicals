const int ledPin = 15;    // GPIO 15
// setting PWM properties
const int freq = 5000;
const int resolution = 8;

void setup() {
  // configure LED PWM
  ledcAttach(ledPin, freq, resolution);
  // if you want to attach a specific channel:
  // ledcAttachChannel(ledPin, freq, resolution, 0);
}

void loop() {
  // increase the LED brightness
  for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle++) {
    ledcWrite(ledPin, dutyCycle);
    delay(15);
  }

  // decrease the LED brightness
  for (int dutyCycle = 255; dutyCycle >= 0; dutyCycle--) {
    ledcWrite(ledPin, dutyCycle);
    delay(15);
  }
}
