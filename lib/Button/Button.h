#include <string>

enum class ButtonEvents {
    Pressed,
    Released,
    None
};

class Button
{
protected:
    int pin;
    std::string name;
    ButtonEvents determineButtonEvent(int lastState, int currentState);
    std::string buttonEventToString(ButtonEvents event);
    void poll(); // poll the gpio pin for state changes.
public:
    Button(int gpio_pin, std::string btn_name);
    void init();
};