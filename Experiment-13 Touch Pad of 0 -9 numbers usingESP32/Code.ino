#include <WiFi.h>
#include <WebServer.h>

// WiFi credentials
const char* ssid = "Redmi Note 12 Pro 5G";
const char* password = "shashwat";

// Web server
WebServer server(80);

// Pins
const int potPin = 34;   // Potentiometer (ADC)
const int ledPin = 18;   // LED pin (PWM capable)

// Variables
int potValue = 0;
int brightness = 0;
bool ledEnabled = true;

// Webpage
String webpage() {
  String html = "<!DOCTYPE html><html>";
  html += "<head><title>ESP32 LED Dimmer</title></head>";
  html += "<body style='font-family: Arial; text-align:center;'>";
  html += "<h2>ESP32 Potentiometer + LED Brightness Control</h2>";
  html += "<p><b>Potentiometer Value: </b>" + String(potValue) + "</p>";
  html += "<p><b>Brightness (0–255): </b>" + String(brightness) + "</p>";
  html += "<p><b>LED State: </b>" + String(ledEnabled ? "ON" : "OFF") + "</p>";
  html += "<a href='/ledON'><button style='padding:10px 20px;'>Enable LED</button></a>";
  html += "<a href='/ledOFF'><button style='padding:10px 20px; margin-left:20px;'>Disable LED</button></a>";
  html += "<meta http-equiv='refresh' content='2'>";
  html += "</body></html>";
  return html;
}

// Root page
void handleRoot() {
  potValue = analogRead(potPin);
  brightness = map(potValue, 0, 4095, 0, 255);

  if (ledEnabled) {
    analogWrite(ledPin, brightness);
  } else {
    analogWrite(ledPin, 0);
  }

  server.send(200, "text/html", webpage());
}

// Enable LED
void handleLedOn() {
  ledEnabled = true;
  handleRoot();
}

// Disable LED
void handleLedOff() {
  ledEnabled = false;
  analogWrite(ledPin, 0);
  handleRoot();
}

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);

  // WiFi connect
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  // Routes
  server.on("/", handleRoot);
  server.on("/ledON", handleLedOn);
  server.on("/ledOFF", handleLedOff);

  server.begin();
}

void loop() {
  server.handleClient();
}
Output: