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
    float wheelCircumference = 81.68; // inches
    float milesPerRevolution = (wheelCircumference / 12.0f) / 5280.0f;
    float maxSpeed = 60.0; //mph
    uint32_t minRevolutionInterval = getMinRevolutionInterval(wheelCircumference, maxSpeed);
    
    Screen *dashboard = new Dashboard(display, ScreenId::Dashboard);
    Screen *welcome = new Welcome(display, ScreenId::Welcome);
    
    Button *selectBtn = new Button(1, "Select Button", ButtonIds::Select, event_q);
    HallsSensor *hallsSensor = new HallsSensor(event_q, minRevolutionInterval );

    Screen *currentScreen = welcome;
    BikeMetrics metrics = {0, 0, 0, 0};
    EventQueue<Event, 32> event_q;


    void processEvents();
    void handleEvent(Event event);
    void handleBtnPressed(Event event);
    void handleBtnReleased(Event event);
    void handleWheelRevolution(Event event);
    void toggleScreen();
    float calculateSpeedMph(uint32_t revolutionTime);
    float calculateDistance();

public:
    BikeComputer();
};
