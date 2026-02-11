#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ---------------- ROBOT MOODS ----------------
enum Mood {
  HAPPY,
  NEUTRAL,
  SLEEPY,
  SURPRISED,
  ANGRY
};

Mood currentMood = HAPPY;

unsigned long lastMoodChange = 0;
unsigned long lastBlink = 0;
bool eyesClosed = false;

// ---------------- SETUP ----------------
void setup() {
  Serial.begin(115200);
  Serial.println("Cute Robot Starting 🤖");

  Wire.begin(12, 14);   // SDA = GPIO12, SCL = GPIO14

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("OLED init failed");
    while (1);
  }

  randomSeed(analogRead(A0));
}

// ---------------- LOOP ----------------
void loop() {
  // change mood every 4 seconds
  if (millis() - lastMoodChange > 4000) {
    currentMood = (Mood)random(5);
    lastMoodChange = millis();
  }

  // blink every 3–5 seconds
  if (millis() - lastBlink > random(3000, 5000)) {
    eyesClosed = true;
    lastBlink = millis();
  }
  if (eyesClosed && millis() - lastBlink > 200) {
    eyesClosed = false;
  }

  drawRobot(currentMood, eyesClosed);
  delay(120);
}

// ---------------- DRAW ROBOT ----------------
void drawRobot(Mood mood, bool blink) {
  display.clearDisplay();

  // Head
  display.drawRoundRect(14, 2, 100, 60, 10, SSD1306_WHITE);

  // Antenna
  display.drawLine(64, 2, 64, 0, SSD1306_WHITE);
  display.fillCircle(64, 0, 2, SSD1306_WHITE);

  // Eyes
  if (blink || mood == SLEEPY) {
    eyesSleepy();
  } else {
    switch (mood) {
      case HAPPY:
      case NEUTRAL:
        eyesNormal();
        break;
      case SURPRISED:
        eyesBig();
        break;
      case ANGRY:
        eyesAngry();
        break;
    }
  }

  // Mouth
  switch (mood) {
    case HAPPY:     mouthSmile(); break;
    case NEUTRAL:   mouthFlat(); break;
    case SLEEPY:    mouthFlat(); break;
    case SURPRISED: mouthO(); break;
    case ANGRY:     mouthAngry(); break;
  }

  display.display();
}

// ---------------- EYES ----------------
void eyesNormal() {
  display.fillCircle(44, 28, 5, SSD1306_WHITE);
  display.fillCircle(84, 28, 5, SSD1306_WHITE);
}

void eyesBig() {
  display.drawCircle(44, 28, 7, SSD1306_WHITE);
  display.drawCircle(84, 28, 7, SSD1306_WHITE);
}

void eyesSleepy() {
  display.drawLine(38, 28, 50, 28, SSD1306_WHITE);
  display.drawLine(78, 28, 90, 28, SSD1306_WHITE);
}

void eyesAngry() {
  display.drawLine(38, 24, 50, 30, SSD1306_WHITE);
  display.drawLine(78, 30, 90, 24, SSD1306_WHITE);
  display.fillCircle(44, 30, 3, SSD1306_WHITE);
  display.fillCircle(84, 30, 3, SSD1306_WHITE);
}

// ---------------- MOUTH ----------------
void mouthSmile() {
  display.drawPixel(56, 44, SSD1306_WHITE);
  display.drawPixel(58, 46, SSD1306_WHITE);
  display.drawPixel(60, 47, SSD1306_WHITE);
  display.drawPixel(62, 48, SSD1306_WHITE);
  display.drawPixel(64, 48, SSD1306_WHITE);
  display.drawPixel(66, 48, SSD1306_WHITE);
  display.drawPixel(68, 47, SSD1306_WHITE);
  display.drawPixel(70, 46, SSD1306_WHITE);
  display.drawPixel(72, 44, SSD1306_WHITE);
}

void mouthFlat() {
  display.drawLine(52, 44, 76, 44, SSD1306_WHITE);
}

void mouthO() {
  display.drawCircle(64, 44, 6, SSD1306_WHITE);
}

void mouthAngry() {
  display.drawLine(56, 46, 64, 44, SSD1306_WHITE);
  display.drawLine(64, 44, 72, 46, SSD1306_WHITE);
}
