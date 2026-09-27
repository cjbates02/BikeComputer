#include "Display.h"
#include "Welcome.h"
#include "Dashboard.h"
#include "Utils.h"
#include "BikeMetrics.h"
#include "Button.h"
#include "Events.h"
#include "HallsSensor.h"

class BikeComputer
{
private:
    Screen *dashboard = new Dashboard(display, ScreenId::Dashboard);
    Screen *welcome = new Welcome(display, ScreenId::Welcome);
    
    Button *selectBtn = new Button(1, "Select Button", ButtonIds::Select, event_q);
    HallsSensor *hallsSensor = new HallsSensor();

    Screen *currentScreen = welcome;
    BikeMetrics metrics = {0, 0, 0, 0};
    EventQueue<Event, 32> event_q;

    void processEvents();
    void handleEvent(Event event);
    void handleBtnPressed(Event event);
    void handleBtnReleased(Event event);
    void toggleScreen();

public:
    BikeComputer();
};
