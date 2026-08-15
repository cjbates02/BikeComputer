#include "Button.h"
#include <Arduino.h>
#include <string>

Button::Button(int gpio_pin, std::string btn_name) : pin(gpio_pin), name(btn_name) {
    Serial.print("Created button ");
    Serial.print(btn_name.c_str());
    Serial.print(" on GPIO pin ");
    Serial.println(gpio_pin);
}

void Button::init()
{
    pinMode(pin, INPUT_PULLUP);
}

bool Button::isPressed()
{
    if (digitalRead(pin) == LOW) {
        Serial.println("Button Pressed.");
    }
    return digitalRead(pin) == LOW;
}