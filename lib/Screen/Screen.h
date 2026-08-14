#include <Adafruit_SSD1306.h>
#pragma once

class Screen {
    protected:
        Adafruit_SSD1306& display;
    public:
        Screen(Adafruit_SSD1306& screenDisplay) : display(screenDisplay) {}
        virtual void enter() {
            display.clearDisplay();
        }; // initial state of a screen.
        virtual void update() {}; // what needs to happen for this screen to update?
        virtual void draw() = 0; // what should be shown on the screen right now?
        virtual void exit() {
            display.clearDisplay();
        };  // cleanup stuff.
        virtual ~Screen() = default;
};