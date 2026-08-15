#include "Button.h"
#include "Utils.h"
#include <Arduino.h>
#include <string>
#include <thread>
#include <chrono>

Button::Button(int gpio_pin, std::string btn_name) : pin(gpio_pin), name(btn_name) {
    Serial.print("Created button ");
    Serial.print(btn_name.c_str());
    Serial.print(" on GPIO pin ");
    Serial.println(gpio_pin);
}

void Button::init()
{
    pinMode(pin, INPUT_PULLUP);
    std::thread pollThread(&Button::poll, this);
    pollThread.join();
}

void Button::poll() {
    bool lastState = digitalRead(pin);
    while (true) {
        bool currentState = digitalRead(pin);
        ButtonEvents event = determineButtonEvent(lastState, currentState);
        if (event != ButtonEvents::None) {
            Serial.println(buttonEventToString(event).c_str());
        }
        lastState = currentState;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

ButtonEvents Button::determineButtonEvent(int lastState, int currentState) {
    if (lastState == HIGH && currentState == LOW) {
        return ButtonEvents::Pressed;
    }
    if (lastState == LOW && currentState == HIGH) {
        return ButtonEvents::Released;
    }
    return ButtonEvents::None;
}

std::string Button::buttonEventToString(ButtonEvents event) {
    switch (event) {
        case ButtonEvents::Pressed: return "Pressed";
        case ButtonEvents::Released: return "Released";
        case ButtonEvents::None: return "None";
    }
    return "Unknown Event";
}