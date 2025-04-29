#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <Callmebot_ESP8266.h>

const String username = "@abhishek_b6";
const char* ssid = "iPhone";  // Enter your WiFi name
const char* password = "12345672";          // Enter your WiFi password

X509List cert(TELEGRAM_CERTIFICATE_ROOT);

WiFiClientSecure client;

const int pirPin = D5;       // PIR sensor output pin D5
const int redLedPin = D1;    // Red LED pin
const int buzzerPin = D2;    // Buzzer pin
const int greenLedPin = D3;  // Green LED pin

const int timeSeconds = 10;
bool motionDetected = false;
unsigned long now = millis();
unsigned long lastTrigger = 0;


void setup() {
  Serial.begin(115200);

  // Configure time and security
  configTime(0, 0, "pool.ntp.org");  // Get UTC time via NTP
  client.setTrustAnchors(&cert);

  pinMode(redLedPin, OUTPUT);     // RED LED
  pinMode(buzzerPin, OUTPUT);     // BUZZER
  pinMode(greenLedPin, OUTPUT);   // LED GREEN
  pinMode(pirPin, INPUT_PULLUP);  // PIR SENSOR OUTPUT PIN D5

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
  Callmebot.telegramMessage(username, "Bot started");
}

IRAM_ATTR void detectsMovement() {
  Serial.println("MOTION DETECTED!!!");
  motionDetected = true;
  lastTrigger = millis();
}


void checkSensor() {
  Serial.println("System is ON");
  attachInterrupt(digitalPinToInterrupt(pirPin), detectsMovement, RISING);
  if (motionDetected) {
    digitalWrite(redLedPin, HIGH);   // Turn on red LED
    digitalWrite(buzzerPin, HIGH);   // Turn on buzzer
    digitalWrite(greenLedPin, LOW);  // Turn off green LED
    if (WiFi.status() == WL_CONNECTED) {
      String message = "WARNING! Please check your security system";
      Callmebot.telegramCall(username,message,"en-US-Neural2-J",2,"yes",60000);
    }
  } else {
    digitalWrite(redLedPin, LOW);     // Turn off red LED
    digitalWrite(buzzerPin, LOW);     // Turn off buzzer
    digitalWrite(greenLedPin, HIGH);  // Turn on green LED
  }
  delay(5000);
}

void loop() {
  checkSensor();  // Check sensor status
  now = millis();
  if (motionDetected && (now - lastTrigger > (timeSeconds * 1000))) {
    digitalWrite(redLedPin, LOW);     // Turn off red LED
    digitalWrite(buzzerPin, LOW);     // Turn off buzzer
    digitalWrite(greenLedPin, HIGH);  // Turn on green LED
    motionDetected = false;
  }
}