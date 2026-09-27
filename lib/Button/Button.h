#include <string>
#include "Events.h"

class Button
{
protected:
    int pin;
    std::string name;
    ButtonIds id;
    EventQueue<Event, 32> &event_q;

    EventIds determineButtonEvent(int lastState, int currentState);
    std::string buttonEventToString(EventIds event);
    void poll(); // poll the gpio pin for state changes.
public:
    Button(int gpio_pin, std::string btn_name, ButtonIds btn_id, EventQueue<Event, 32> &event_q);
    void init();
};