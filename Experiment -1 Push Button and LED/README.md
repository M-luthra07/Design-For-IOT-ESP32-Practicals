# Experiment 1: Push Button and LED with ESP32  

### 🎯 Aim  
Interface a push button and an LED with ESP32.  

### 📜 Code Explanation  
- **BUTTON_PIN = 4** → Push button as input with internal pull-up.  
- **LED_PIN = 2** → LED output.  
- Logic: LED glows when button is pressed.  

### 🔌 Connections  
- Push Button → GPIO 4  
- LED → GPIO 2 (with 220Ω resistor recommended)  
- Common GND  
