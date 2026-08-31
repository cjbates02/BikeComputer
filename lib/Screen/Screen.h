#include <Adafruit_SSD1306.h>
#include "BikeMetrics.h"
#pragma once

enum class ScreenId {
    Dashboard,
    Welcome
};

class Screen {
    protected:
        Adafruit_SSD1306& display;
    public:
        ScreenId id;
        Screen(Adafruit_SSD1306& screenDisplay, ScreenId screenId) : display(screenDisplay), id(screenId) {}
        virtual void enter() {
            display.clearDisplay();
        }; // initial state of a screen.
        virtual void update() {}; // what needs to happen for this screen to update?
        virtual void draw(BikeMetrics& metrics) = 0; // what should be shown on the screen right now?
        virtual void exit() {
            display.clearDisplay();
        };  // cleanup stuff.
        virtual ~Screen() = default;
};