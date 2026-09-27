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
    EventQueue<Event, 32> &btn_event_q)
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
        EventIds eventId = determineButtonEvent(lastState, currentState);
        if (eventId != EventIds::None)
        {
            Serial.println(buttonEventToString(eventId).c_str());

            Event event;
            event.id = eventId;
            event.button.btnId = id;

            event_q.push(event);
        }
        lastState = currentState;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

EventIds Button::determineButtonEvent(int lastState, int currentState)
{
    if (lastState == HIGH && currentState == LOW)
    {
        return EventIds::ButtonPressed;
    }
    if (lastState == LOW && currentState == HIGH)
    {
        return EventIds::ButtonReleased;
    }
    return EventIds::None;
}

std::string Button::buttonEventToString(EventIds eventType)
{
    switch (eventType)
    {
    case EventIds::ButtonPressed:
        return "Pressed";
    case EventIds::ButtonReleased:
        return "Released";
    case EventIds::None:
        return "None";
    }
    return "Unknown Event";
}