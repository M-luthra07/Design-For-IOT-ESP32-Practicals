# Experiment 5: Ultrasonic + Temp + LED + OLED with ESP32  

### 🎯 Aim  
Display sensor readings on OLED and control via Bluetooth menu using **Serial Bluetooth Terminal app**.  

### 📜 Code Explanation  
- Uses **Adafruit_GFX** and **Adafruit_SSD1306** libraries for OLED.  
- Displays ultrasonic distance and temperature values.  
- LED control via Bluetooth commands.  

### 🔌 Connections  
- **HC-SR04 Ultrasonic Sensor:**  
  - TRIG → GPIO 5  
  - ECHO → GPIO 18  
- **LM35 Temperature Sensor:** OUT → GPIO 34  
- **OLED Display (SSD1306 I2C):**  
  - VCC → 3.3V  
  - GND → GND  
  - SDA → GPIO 21  
  - SCL → GPIO 22  
- **LED:** GPIO 2  
