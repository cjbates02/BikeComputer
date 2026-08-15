#include <string>

class Button
{
protected:
    int pin;
    std::string name;

public:
    Button(int gpio_pin, std::string btn_name);
    bool isPressed();
    void init();
};