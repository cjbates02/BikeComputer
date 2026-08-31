#include "Button.h"
#include "Utils.h"
#include <Arduino.h>
#include <string>
#include <thread>
#include <chrono>

Button::Button(
    int gpio_pin,
    std::string btn_name,
    ButtonIds btn_id,
    EventQueue<ButtonEvent> &btn_event_q)
    : pin(gpio_pin),
      name(btn_name),
      id(btn_id),
      event_q(btn_event_q)
{
    Serial.println("Created button ");
    Serial.println(btn_name.c_str());
    Serial.println(" on GPIO pin ");
    Serial.println(gpio_pin);
}

void Button::init()
{
    pinMode(pin, INPUT_PULLUP);
    std::thread pollThread(&Button::poll, this);
    pollThread.detach();
}

void Button::poll()
{
    bool lastState = digitalRead(pin);
    while (true)
    {
        bool currentState = digitalRead(pin);
        ButtonEventTypes eventType = determineButtonEventType(lastState, currentState);
        if (eventType != ButtonEventTypes::None)
        {
            Serial.println(buttonEventToString(eventType).c_str());

            ButtonEvent event;
            event.type = eventType;
            event.id = id;

            event_q.push(event);
        }
        lastState = currentState;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

ButtonEventTypes Button::determineButtonEventType(int lastState, int currentState)
{
    if (lastState == HIGH && currentState == LOW)
    {
        return ButtonEventTypes::Pressed;
    }
    if (lastState == LOW && currentState == HIGH)
    {
        return ButtonEventTypes::Released;
    }
    return ButtonEventTypes::None;
}

std::string Button::buttonEventToString(ButtonEventTypes eventType)
{
    switch (eventType)
    {
    case ButtonEventTypes::Pressed:
        return "Pressed";
    case ButtonEventTypes::Released:
        return "Released";
    case ButtonEventTypes::None:
        return "None";
    }
    return "Unknown Event";
}