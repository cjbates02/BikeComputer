#include "Dashboard.h"

Dashboard::Dashboard(Adafruit_SSD1306 &display) : Screen(display) {};

void Dashboard::draw(BikeMetrics& metrics)
{
    display.clearDisplay();

    // =========================
    // Speed
    // =========================

    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);

    display.setCursor(0, 0);
    display.print(metrics.speed, 1);

    display.setTextSize(1);
    display.print(" MPH");

    // =========================
    // Cadence
    // =========================

    display.setTextSize(2);
    display.setCursor(70, 0);
    display.print(metrics.cadence);

    display.setTextSize(1);
    display.print(" RPM");

    // =========================
    // Divider
    // =========================

    display.drawLine(0, 20, 127, 20, SSD1306_WHITE);

    // =========================
    // Labels
    // =========================

    display.setTextSize(1);

    display.setCursor(5, 24);
    display.print("SPEED");

    display.setCursor(72, 24);
    display.print("CADENCE");

    // =========================
    // Distance
    // =========================

    display.setTextSize(2);
    display.setCursor(0, 36);
    display.print(metrics.distance, 1);

    display.setTextSize(1);
    display.print(" MI");

    // =========================
    // Time
    // =========================

    display.setTextSize(2);
    display.setCursor(72, 36);
    display.print(metrics.time, 1);

    display.setTextSize(1);
    display.print(" HR");

    // =========================
    // Bottom labels
    // =========================

    display.setCursor(5, 55);
    display.print("DISTANCE");

    display.setCursor(72, 55);
    display.print("TIME");

    display.display();
}