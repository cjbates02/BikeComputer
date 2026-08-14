#include "Welcome.h"
#include <Arduino.h>

Welcome::Welcome(Adafruit_SSD1306 &display) : Screen(display)
{
    Serial.println("Welcome screen created.");
}

void Welcome::draw()
{
    Serial.println("Drawwing !!");
    display.clearDisplay();
    // Wheels
    display.drawCircle(32, 45, 14, SSD1306_WHITE);
    display.drawCircle(96, 45, 14, SSD1306_WHITE);

    // Wheel spokes
    for (int i = 0; i < 8; i++)
    {
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
