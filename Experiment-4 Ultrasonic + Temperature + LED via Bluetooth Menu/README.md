# Experiment 4: Ultrasonic, Temperature Sensor and LED with ESP32 via Bluetooth  

### 🎯 Aim  
Read ultrasonic sensor, LM35 temperature sensor, and control LED via Bluetooth menu using **Serial Bluetooth Terminal app**.  

### 📜 Code Explanation  
- Menu options:  
  1. Read Ultrasonic Distance  
  2. Read Temperature  
  3. Turn LED ON  
  4. Turn LED OFF  
- Interacts via **Serial Bluetooth Terminal app**.  

### 🔌 Connections  
- **HC-SR04 Ultrasonic Sensor:**  
  - VCC → 5V  
  - GND → GND  
  - TRIG → GPIO 5  
  - ECHO → GPIO 18  
- **LM35 Temperature Sensor:**  
  - VCC → 3.3V  
  - GND → GND  
  - OUT → GPIO 34 (analog)  
- **LED:** GPIO 2  
