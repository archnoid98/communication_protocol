Communication Protocol Project


Overview:

This project demonstrates the implementation of three types of communication protocols on an ESP32 microcontroller:

    ->WiFi Communication via WebSocket

    ->Bluetooth Serial Communication (HC-05 Module)

    ->Infrared (IR) Radio Wave Communication

In addition, a passive buzzer feedback system provides audible tones to acknowledge commands received through any of these protocols.
Features

    WiFi Protocol:
    Connects to a WebSocket server and listens for single-character commands to control LEDs.

    Bluetooth Protocol:
    Receives single-character commands via serial Bluetooth communication.

    IR Protocol:
    Uses an IR receiver (CL1838) to decode remote control signals and trigger commands.

    Passive Buzzer Feedback:
    Plays distinct tones corresponding to each command received, giving audible confirmation.

    AC Bulb Indicators:
    Controls two AC Bulb (White and Yellow) based on received commands.

Hardware Components

    ESP32 Development Board

    CL1838 IR Receiver Module

    HC-05 Bluetooth Module

    Passive Buzzer

    Two AC Bulb (connected to GPIO 2 and GPIO 22)
    
    Realy Module
     
    Necessary wiring

    

Pin Configuration
Component	ESP32 GPIO Pin
White AC Bulb 2
Yellow AC Bulb 22
IR Receiver	21
Passive Buzzer	23
HC-05 RX	(connected to ESP32 TX)
HC-05 TX	(connected to ESP32 RX)
Commands
Command	Action	 Buzzer Tone Frequency  (Hz)
a	White AC Bulb  ON   (active LOW)	1000
b	White AC Bulb  OFF	                1200
c	Yellow AC Bulb ON   (active LOW)	1400
d	Yellow AC Bulb OFF	                1600
Software Setup
Requirements

    Arduino IDE with ESP32 Board support

    Libraries:

        WiFi.h

        WebSocketsClient.h

        IRremoteESP8266

        IRrecv.h

        IRutils.h

Usage

    Clone this repository to your local machine.

    Open the Arduino sketch.

    Configure your WiFi credentials and WebSocket server IP.

    Connect hardware as per pin configuration.

    Upload the sketch to your ESP32.

    Use your IR remote, Bluetooth terminal, or WebSocket client to send commands.

    Observe AC Bulbs' states and hear buzzer feedback.

WebSocket Server

A WebSocket server (e.g., implemented in Python) is required to send commands over WiFi. Commands are single characters: a, b, c, or d.
