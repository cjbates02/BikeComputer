#include <string>
#include "Events.h"

enum class ButtonEventTypes
{
    Pressed,
    Released,
    None
};

enum class ButtonIds
{
    Select,
    Next,
    Previous
};

struct ButtonEvent
{
    ButtonEventTypes type;
    ButtonIds id;
};

class Button
{
protected:
    int pin;
    std::string name;
    ButtonIds id;
    EventQueue<ButtonEvent>& event_q;

    ButtonEventTypes determineButtonEventType(int lastState, int currentState);
    std::string buttonEventToString(ButtonEventTypes event);
    void poll(); // poll the gpio pin for state changes.
public:
    Button(int gpio_pin, std::string btn_name, ButtonIds btn_id, EventQueue<ButtonEvent>& event_q);
    void init();
};