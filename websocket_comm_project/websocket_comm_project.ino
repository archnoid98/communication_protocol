#include <WiFi.h>
#include <WebSocketsClient.h>

#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

#include "driver/ledc.h"  // For ESP32 tone (PWM-based)

// WiFi Credentials
const char* ssid = "Jarif";
const char* password = "Borno54321";

// WebSocket Server Details
const char* websocket_host = "192.168.68.111";
const uint16_t websocket_port = 8765;
const char* websocket_path = "/";

// Pins
#define white 2    
#define yellow 22 
#define IR_RECEIVE_PIN 21
#define buzzer 4    // Passive buzzer pin

IRrecv irrecv(IR_RECEIVE_PIN);
decode_results results;

char bluetooth_value;

WebSocketsClient webSocket;

// --- Function to play a tone ---
void playTone(uint16_t frequency, uint16_t duration_ms) {
  ledcSetup(0, frequency, 8); // channel 0, freq, 8-bit resolution
  ledcAttachPin(buzzer, 0);
  ledcWrite(0, 127); // 50% duty cycle for tone
  delay(duration_ms);
  ledcWrite(0, 0);   // Turn off tone
  ledcDetachPin(buzzer);
}

// --- Command Handler ---
void handleCommand(char cmd) {
  Serial.printf("Executing command: %c\n", cmd);
  
  switch(cmd) {
    case 'a':
      digitalWrite(white, LOW);
      playTone(1000, 200);  // Tone 1
      break;
    case 'b':
      digitalWrite(white, HIGH);
      playTone(1200, 200);  // Tone 2
      break;
    case 'c':
      digitalWrite(yellow, LOW);
      playTone(1400, 200);  // Tone 3
      break;
    case 'd':
      digitalWrite(yellow, HIGH);
      playTone(1600, 200);  // Tone 4
      break;
    default:
      break;
  }
}

// --- WebSocket Event Handler ---
void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_CONNECTED:
      Serial.println("WebSocket connected");
      break;
    case WStype_TEXT:
      Serial.printf("Received via WebSocket: %s\n", payload);
      if(length > 0) {
        handleCommand((char)payload[0]);
      }
      break;
    case WStype_DISCONNECTED:
      Serial.println("WebSocket disconnected");
      break;
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(white, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(buzzer, OUTPUT);

  digitalWrite(white, HIGH);
  digitalWrite(yellow, HIGH);

  irrecv.enableIRIn();
  Serial.println("IR Receiver Initialized on GPIO 21");

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");

  webSocket.begin(websocket_host, websocket_port, websocket_path);
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  webSocket.loop();

  if (irrecv.decode(&results)) {
    Serial.println(resultToHumanReadableBasic(&results));
    Serial.printf("IR Raw Value: 0x%X\n", results.value);

    if(results.value == 0xFF30CF) handleCommand('a');
    else if(results.value == 0xFF18E7) handleCommand('b');
    else if(results.value == 0xFF7A85) handleCommand('c');
    else if(results.value == 0xFF10EF) handleCommand('d');

    irrecv.resume();
  }

  if (Serial.available()) {
    bluetooth_value = Serial.read();
    Serial.print("Bluetooth Received: ");
    Serial.println(bluetooth_value);
    handleCommand(bluetooth_value);
  }
}
