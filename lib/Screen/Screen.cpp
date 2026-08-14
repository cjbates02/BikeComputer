#include <Adafruit_SSD1306.h>

class Screen {
    protected:
        Adafruit_SSD1306 display;
    public:
        Screen(Adafruit_SSD1306 screenDisplay) : display(screenDisplay) {}
        virtual void enter() {}; // initial state of a screen.
        virtual void update() {}; // what needs to happen for this screen to update?
        virtual void draw() = 0; // what should be shown on the screen right now?
        virtual void exit() {};  // cleanup stuff.
};