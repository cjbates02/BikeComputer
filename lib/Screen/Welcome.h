#include "Screen.h"
#pragma once

class Welcome : public Screen {
    private:
        int wheelAngle = 0;
    public:
        Welcome(Adafruit_SSD1306& screenDisplay);
        void draw() override;
        void update() override;
};