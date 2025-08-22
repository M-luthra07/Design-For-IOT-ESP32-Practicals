#include <Arduino.h>
#include "BluetoothSerial.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Bluetooth
BluetoothSerial SerialBT;

// OLED display setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pins
const int trigPin = 5;
const int echoPin = 18;
const int tempPin = 34; // Analog input for LM35
const int ledPin = 2;

// Variables
long duration;
float distance;
float temperatureC;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT");

  // Pin modes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // OLED Init
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED init failed!");
    while (1);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("ESP32 Sensor & LED");
  display.display();
  delay(2000);

  Serial.println("ESP32 Sensor & LED Interface");
  SerialBT.println("ESP32 Sensor & LED Interface (Bluetooth)");

  printMenu();
}

void loop() {
  if (SerialBT.available() > 0) {
    char option = SerialBT.read();

    switch (option) {
      case '1':
        readUltrasonic();
        break;
      case '2':
        readTemperature();
        break;
      case '3':
        ledControl(true);
        break;
      case '4':
        ledControl(false);
        break;
      case 'm':
      case 'M':
        printMenu();
        break;
      default:
        SerialBT.println("Invalid option! Press 'm' for menu.");
        break;
    }
  }
}

void printMenu() {
  SerialBT.println("\n--- Menu ---");
  SerialBT.println("1: Read Ultrasonic Sensor Distance");
  SerialBT.println("2: Read Temperature Sensor (°C)");
  SerialBT.println("3: Turn LED ON");
  SerialBT.println("4: Turn LED OFF");
  SerialBT.print("Select option: ");
}

void readUltrasonic() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Ultrasonic Reading:");

  if (duration == 0) {
    SerialBT.println("No echo received - object too far or no object.");
    display.println("No echo received");
  } else {
    distance = (duration * 0.0343) / 2;
    SerialBT.print("Distance: ");
    SerialBT.print(distance);
    SerialBT.println(" cm");

    display.print("Distance: ");
    display.print(distance);
    display.println(" cm");
  }

  display.display();
  printMenu();
}

void readTemperature() {
  int analogValue = analogRead(tempPin);
  float voltage = analogValue * (3.3 / 4095.0);
  temperatureC = voltage * 100.0;

  SerialBT.print("Temperature: ");
  SerialBT.print(temperatureC);
  SerialBT.println(" °C");

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Temperature Reading:");
  display.print(temperatureC);
  display.println(" C");
  display.display();

  printMenu();
}

void ledControl(bool state) {
  digitalWrite(ledPin, state);
  SerialBT.print("LED turned ");
  SerialBT.println(state ? "ON" : "OFF");

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("LED is ");
  display.println(state ? "ON" : "OFF");
  display.display();

  printMenu();
}
