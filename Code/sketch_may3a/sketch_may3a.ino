#include <WiFi.h>
#include <WebServer.h>
#include <FastLED.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

// ================= WIFI =================
const char* ssid = "Infinix HOT 50i";
const char* password = "qweMNB1230";

WebServer server(80);

// ================= MOTOR PINS =================
#define IN1 13
#define IN2 15
#define IN3 17
#define IN4 18

// ================= SENSORS =================
#define FRONT_SENSOR 4
#define BACK_SENSOR 5

// ================= LED =================
#define LED_PIN 48
#define NUM_LEDS 1
CRGB leds[NUM_LEDS];

// ================= OLED =================
Adafruit_SH1106G display(128, 64, &Wire, -1);

// ================= EYE SETTINGS =================
int eyeW = 34;
int eyeH = 26;
int eyeY = 18;

// ================= MOTOR =================
void stopRobot() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void forward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void backward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// ================= SENSOR SAFETY =================
bool dangerDetected() {
  return (digitalRead(FRONT_SENSOR) == LOW ||
          digitalRead(BACK_SENSOR) == LOW);
}

void safeRun(void (*action)()) {
  if (dangerDetected()) {
    stopRobot();
    eyeScared(); // 🔥 react visually
    return;
  }
  action();
}

// ================= LED =================
void setColor(CRGB c) {
  leds[0] = c;
  FastLED.show();
}

// ================= RESPONSE =================
void sendResponse() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "OK");
}

// ================= EYES CORE =================
void drawEyes(int offsetX, int blink, int tilt) {
  display.clearDisplay();

  int h = eyeH - blink;
  int y = eyeY + blink / 2;

  int leftX = 22 + offsetX;
  int rightX = 72 + offsetX;

  display.fillRoundRect(leftX, y, eyeW, h, 8, SH110X_WHITE);
  display.fillRoundRect(rightX, y + tilt, eyeW, h, 8, SH110X_WHITE);

  display.display();
}

// ================= NEW ADVANCED ANIMATIONS =================

// 👀 idle
void eyeIdle() {
  drawEyes(0, 0, 0);
}

// 😉 blink
void blink() {
  for (int i = 0; i <= 16; i += 4) {
    drawEyes(0, i, 0);
    delay(15);
  }
  for (int i = 16; i >= 0; i -= 4) {
    drawEyes(0, i, 0);
    delay(15);
  }
}

// 😊 happy
void eyeHappy() {
  drawEyes(0, 4, 0);
  delay(120);
  drawEyes(0, 0, 0);
}

// 😠 angry
void eyeAngry() {
  drawEyes(0, 0, -5);
  delay(150);
}

// 😨 scared
void eyeScared() {
  for (int i = 0; i < 6; i++) {
    drawEyes(random(-3, 3), 0, 0);
    delay(30);
  }
}

// 🎯 focused
void eyeFocused() {
  drawEyes(0, 0, 0);
  delay(120);
  drawEyes(4, 0, 0);
  delay(120);
  drawEyes(-4, 0, 0);
}

// 😴 sleepy
void eyeSleepy() {
  for (int i = 0; i <= 20; i += 2) {
    drawEyes(0, i, 0);
    delay(25);
  }
}

// 🤖 curious
void eyeCurious() {
  for (int i = 0; i < 5; i++) {
    drawEyes(random(-2, 2), 0, 0);
    delay(60);
  }
}

// ================= IDLE AI =================
void idleBrain() {
  int r = random(0, 100);

  if (r < 10) blink();
  else if (r < 20) eyeHappy();
  else if (r < 30) eyeFocused();
  else if (r < 40) eyeCurious();
  else if (r < 50) eyeSleepy();
  else if (r < 60) eyeScared();
  else if (r < 70) eyeAngry();
  else eyeIdle();
}

// ================= ROUTES =================
void setupRoutes() {

  server.on("/forward", []() {
    safeRun(forward);
    eyeFocused();
    sendResponse();
  });

  server.on("/backward", []() {
    safeRun(backward);
    eyeScared();
    sendResponse();
  });

  server.on("/left", []() {
    safeRun(left);
    eyeFocused();
    sendResponse();
  });

  server.on("/right", []() {
    safeRun(right);
    eyeFocused();
    sendResponse();
  });

  server.on("/stop", []() {
    stopRobot();
    eyeHappy();
    sendResponse();
  });
}

// ================= SETUP =================
void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  stopRobot();

  pinMode(FRONT_SENSOR, INPUT);
  pinMode(BACK_SENSOR, INPUT);

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  setColor(CRGB::Black);

  Wire.begin(21, 19);
  display.begin(0x3C, true);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
  }

  setupRoutes();
  server.begin();

  randomSeed(analogRead(0));
}

// ================= LOOP =================
void loop() {
  server.handleClient();

  if (dangerDetected()) {
    stopRobot();
    eyeScared();
  }

  idleBrain();
}