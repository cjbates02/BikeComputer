#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Display.h>

#define SDA_PIN 8
#define SCL_PIN 9
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    &Wire,
    -1
);

int wheelAngle = 0;

void drawBicycle(int wheelAngle) {
    // Wheels
    display.drawCircle(32, 45, 14, SSD1306_WHITE);
    display.drawCircle(96, 45, 14, SSD1306_WHITE);

    // Wheel spokes
    for (int i = 0; i < 8; i++) {
        float angle = (wheelAngle + i * 45) * PI / 180.0;

        int x1 = 32 + cos(angle) * 12;
        int y1 = 45 + sin(angle) * 12;

        int x2 = 96 + cos(angle) * 12;
        int y2 = 45 + sin(angle) * 12;

        display.drawLine(32, 45, x1, y1, SSD1306_WHITE);
        display.drawLine(96, 45, x2, y2, SSD1306_WHITE);
    }

    // Frame
    display.drawLine(32, 45, 55, 45, SSD1306_WHITE);
    display.drawLine(55, 45, 70, 27, SSD1306_WHITE);
    display.drawLine(70, 27, 32, 45, SSD1306_WHITE);

    // Seat tube
    display.drawLine(55, 45, 48, 28, SSD1306_WHITE);

    // Seat
    display.drawLine(43, 27, 52, 27, SSD1306_WHITE);

    // Handlebar
    display.drawLine(70, 27, 75, 20, SSD1306_WHITE);
    display.drawLine(75, 20, 81, 20, SSD1306_WHITE);
    display.drawLine(81, 20, 83, 24, SSD1306_WHITE);

    // Front fork
    display.drawLine(70, 27, 96, 45, SSD1306_WHITE);

    // Crank
    display.drawCircle(55, 45, 3, SSD1306_WHITE);
    display.drawLine(55, 45, 60, 49, SSD1306_WHITE);
}

void animateBicycle() {
    display.clearDisplay();
    drawBicycle(wheelAngle);
    if (wheelAngle > 360) {
        wheelAngle = 0;
    } else {
        wheelAngle += 10;
    }
    display.display();
}

void setupDisplay() {
    Wire.begin(SDA_PIN, SCL_PIN);

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.begin(115200);
        Serial.println("OLED failed!");
        while (true);
    }
}