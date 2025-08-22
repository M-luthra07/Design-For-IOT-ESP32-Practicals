# Experiment 2: Interface Two DHT11 Sensors with ESP32  

### 🎯 Aim  
Read temperature and humidity from two DHT11 sensors.  

### 📜 Code Explanation  
- Uses **DHT.h** library.  
- `DHTPIN1 = 4`, `DHTPIN2 = 5`.  
- Reads both sensors and prints values on Serial Monitor.  

### 🔌 Connections  
- DHT11 Sensor 1 → VCC (3.3V), GND, Data → GPIO 4  
- DHT11 Sensor 2 → VCC (3.3V), GND, Data → GPIO 5  
