# Experiment 8: Interface an LED with Web Server through ESP32

---

## 🎯 Aim
To interface an LED with ESP32 and control it using a Web Server.


## Explanation
- The ESP32 connects to Wi-Fi using SSID and password.
- A Web Server runs on port 80.
- When a client visits the ESP32 IP in the browser, an HTML page is shown with ON/OFF buttons.
- Clicking buttons sends GET requests, toggling LED state.


## 🔌 Connections
- **ESP32 Pin 12** → **LED (Positive terminal)**
- **ESP32 GND** → **LED Negative terminal (via 220Ω resistor)**

