// ESP32 Touch Keypad (1–9 + 0 on long press of Key 1)
const int numKeys = 9;
const int touchPins[numKeys] = {4, 2, 15, 13, 12, 14, 27, 33, 32}; 
const int thresholds[numKeys] = {40,40,40,40,40,40,40,40,40}; 

void setup() {
  Serial.begin(115200);
  Serial.println("ESP32 Touch Keypad (1-9 + 0 via long press)");
}

void loop() {
  for (int i = 0; i < numKeys; i++) {
    int val = touchRead(touchPins[i]);
    if (val < thresholds[i]) {
      if (i == 0) { // Key1 = GPIO4
        delay(700); // check if still pressed = long press
        if (touchRead(touchPins[i]) < thresholds[i]) {
          Serial.println("Key pressed: 0"); // long press = 0
        } else {
          Serial.println("Key pressed: 1"); // short press = 1
        }
      } else {
        Serial.print("Key pressed: ");
        Serial.println(i+1);
      }
      delay(500); // debounce
    }
  }
}