Link for the documents
https://drive.google.com/drive/folders/1lK0Hoi9WDIRBQLXSx8eXpKu54PIBpUFk?usp=sharing
 
 Anti-Theft Alarm System

This project uses a PIR motion sensor with NodeMCU ESP8266 to detect unauthorized motion and alert users via a buzzer, LED indicators, and Telegram call/message using CallMeBot API.

---

 📁 Project Structure

- `Code.cpp` - Arduino sketch for NodeMCU
- `README.md` - Run instructions and overview
- `project_requirements.pdf` - Requirements and documentation

---

🚀 How to Run the Project

 Hardware Setup

1. Components Needed:**
   - NodeMCU ESP8266
   - PIR Sensor
   - Red and Green LEDs
   - Buzzer
   - Jumper Wires
   - Breadboard (optional)

2. Wiring Guide:**
   - PIR Sensor Output → D5  
   - Red LED → D1  
   - Green LED → D3  
   - Buzzer → D2  
   - GND and VCC connected accordingly

3. Power the NodeMCU via USB or external source.

---

 💻 Software Setup

1. Install [Arduino IDE](https://www.arduino.cc/en/software)  
2. Add the ESP8266 board to Arduino IDE via Board Manager  
   - Board URL: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`  
3. Install necessary libraries:
   - ESP8266WiFi
   - WiFiClientSecure
   - UniversalTelegramBot
   - Callmebot_ESP8266.h  

4. Replace WiFi credentials and Telegram username in the code:
   ```cpp
   const char* ssid = "Your_SSID";
   const char* password = "Your_PASSWORD";
   const String username = "@your_telegram_username";
