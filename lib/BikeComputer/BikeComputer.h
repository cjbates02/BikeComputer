#include "Display.h"
#include "Welcome.h"
#include "Dashboard.h"
#include "Utils.h"
#include "BikeMetrics.h"
#include "Button.h"

class BikeComputer {
    private:
        Screen* currentScreen = new Dashboard(display);
        BikeMetrics metrics = {0, 0, 0, 0};
        Button* selectBtn = new Button(1, "Select Button");
    public:
        BikeComputer();
};
