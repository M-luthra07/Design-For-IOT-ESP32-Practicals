#include "DHT.h"
#define DHTPIN1 4
#define DHTPIN2 5
#define DHTTYPE DHT11
DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);
void setup() {
  Serial.begin(115200);
  Serial.println("Reading from two DHT11 sensors...");
  dht1.begin();
  dht2.begin();
}
void loop() {
  float temp1 = dht1.readTemperature();
  float hum1 = dht1.readHumidity();
  float temp2 = dht2.readTemperature();
  float hum2 = dht2.readHumidity();
  if (isnan(temp1) || isnan(hum1) || isnan(temp2) || isnan(hum2)) {
    Serial.println("Failed to read from one or both DHT sensors!");
    delay(2000);
    return;
  }
  Serial.println("Sensor 1:");
  Serial.print("Temp: "); Serial.print(temp1); Serial.print(" °C, ");
  Serial.print("Humidity: "); Serial.print(hum1); Serial.println(" %");
  Serial.println("Sensor 2:");
  Serial.print("Temp: "); Serial.print(temp2); Serial.print(" °C, ");
  Serial.print("Humidity: "); Serial.print(hum2); Serial.println(" %");
  Serial.println("-----------------------------------");
  delay(3000);
