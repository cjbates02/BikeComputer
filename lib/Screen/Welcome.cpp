#include "Welcome.h"
#include <Arduino.h>

Welcome::Welcome(Adafruit_SSD1306 &display) : Screen(display)
{
    Serial.println("Welcome screen created.");
}

void Welcome::draw()
{
    display.clearDisplay();

    // =========================
    // MOMENTUM
    // =========================

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    // Center "MOMENTUM"
    display.setCursor(46, 2);
    display.print("MOMENTUM");

    // Decorative lines
    display.drawLine(25, 6, 42, 6, SSD1306_WHITE);
    display.drawLine(86, 6, 103, 6, SSD1306_WHITE);

    // =========================
    // Bicycle
    // =========================

    // Wheels
    display.drawCircle(32, 36, 12, SSD1306_WHITE);
    display.drawCircle(96, 36, 12, SSD1306_WHITE);

    // Wheel spokes
    for (int i = 0; i < 8; i++)
    {
        float angle = (wheelAngle + i * 45) * PI / 180.0;

        int x1 = 32 + cos(angle) * 10;
        int y1 = 36 + sin(angle) * 10;

        int x2 = 96 + cos(angle) * 10;
        int y2 = 36 + sin(angle) * 10;

        display.drawLine(32, 36, x1, y1, SSD1306_WHITE);
        display.drawLine(96, 36, x2, y2, SSD1306_WHITE);
    }

    // Frame
    display.drawLine(32, 36, 55, 36, SSD1306_WHITE);
    display.drawLine(55, 36, 70, 20, SSD1306_WHITE);
    display.drawLine(70, 20, 32, 36, SSD1306_WHITE);

    // Seat tube
    display.drawLine(55, 36, 48, 21, SSD1306_WHITE);

    // Seat
    display.drawLine(44, 20, 52, 20, SSD1306_WHITE);

    // Handlebar / stem
    display.drawLine(70, 20, 75, 14, SSD1306_WHITE);
    display.drawLine(75, 14, 81, 14, SSD1306_WHITE);
    display.drawLine(81, 14, 83, 18, SSD1306_WHITE);

    // Front fork
    display.drawLine(70, 20, 96, 36, SSD1306_WHITE);

    // Crank
    display.drawCircle(55, 36, 3, SSD1306_WHITE);
    display.drawLine(55, 36, 60, 40, SSD1306_WHITE);

    // =========================
    // Divider
    // =========================

    display.drawLine(25, 51, 60, 51, SSD1306_WHITE);
    display.drawLine(68, 51, 103, 51, SSD1306_WHITE);

    // Center dot
    display.fillRect(63, 49, 2, 4, SSD1306_WHITE);

    // =========================
    // READY TO RIDE
    // =========================

    const char* message = "READY TO RIDE";

    // 13 characters at ~6 pixels each = 78 pixels
    // Center on 128 pixel display
    display.setCursor(25, 56);
    display.print(message);

    display.display();
}

void Welcome::update()
{
    if (wheelAngle > 360)
    {
        wheelAngle = 0;
    }
    else
    {
        wheelAngle += 10;
    }
}
