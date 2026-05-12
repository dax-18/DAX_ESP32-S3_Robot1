# 🤖 Smart Obstacle-Avoiding Robot with OLED Expressions

## 📌 Overview

This project is a WiFi-controlled mobile robot built using an ESP32.
It combines movement, obstacle detection, and expressive OLED animations to create a small but intelligent robotic system.

The robot can be controlled through a web interface and includes a safety system that automatically stops movement when obstacles are detected.

---

## 🚀 Features

* 🔌 **WiFi Control**

  * Control the robot using simple HTTP URLs from any device on the same network

* 🚗 **Movement System**

  * Forward, backward, left, right, and stop controls

* 🛑 **Obstacle Detection (Front + Back)**

  * Automatically stops when an object is detected
  * Works regardless of movement direction

* 👀 **OLED Eye Animations**

  * Idle, blinking, happy, angry, scared, focused, sleepy
  * Adds personality to the robot

* 🧱 **Physical Design**

  * Hard plastic base for strength
  * Custom shock absorbers (sponge + tape) to reduce impact damage
  * Enclosed display housing for clean wiring

---

## 🧠 How It Works

* The ESP32 hosts a web server
* When a URL is triggered (e.g. `/forward`), the robot moves
* Sensors constantly check for obstacles
* If any sensor detects an object → **ALL movement stops immediately**
* OLED display runs animations in parallel to simulate emotions

---

## 🌐 Control Endpoints

| Action     | URL         |
| ---------- | ----------- |
| Forward    | `/forward`  |
| Backward   | `/backward` |
| Left       | `/left`     |
| Right      | `/right`    |
| Stop       | `/stop`     |
| Happy Face | `/happy`    |
| Angry Face | `/angry`    |
| Sleep Mode | `/sleep`    |

Example:

```
http://<ESP32-IP>/forward
```

---

## 🔧 Components Used

* ESP32 Board
* 2x DC Motors with Gearbox
* Motor Driver Module
* OLED Display (SH1106 - I2C)
* 2x IR Obstacle Sensors (Front & Back)
* Li-ion Battery + Charging Module
* Buck Converter (for voltage regulation)
* Wires, cardboard, plastic base

---

## ⚡ Power Setup

* Motors powered separately from main logic
* ESP32, OLED, and sensors powered via regulated supply
* Common ground shared across all components

---

## 🛠️ Setup Instructions

1. Install required libraries:

   * `WiFi.h`
   * `WebServer.h`
   * `FastLED.h`
   * `Adafruit_GFX`
   * `Adafruit_SH110X`

2. Upload the code to ESP32

3. Connect to WiFi (credentials in code)

4. Open Serial Monitor to get IP address

5. Use browser:

```
http://<IP_ADDRESS>/forward
```

---

## 🧩 Challenges Faced

* Motor integration caused power instability (resolved by separating systems)
* OLED compatibility issue (SSD1306 → switched to SH1106)
* Power distribution across motors and logic circuits
* Sensor calibration and reliability

---

## 🎯 Purpose

This project was built as a starting point in robotics and AI development.
It demonstrates understanding of:

* Embedded systems
* Sensor-based safety logic
* Hardware + software integration
* Real-time control systems

---

## 👨‍💻 Author

Dinod Randil

---

## 🏁 Status

✅ Completed (Version 1)
🚀 Next Project: AI Robot with Voice

---

*"Every robot starts as wires and ideas. This one learned how to see, react, and express."*
