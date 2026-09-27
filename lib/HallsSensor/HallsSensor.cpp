#include "HallsSensor.h"
#include <thread>
#include <chrono>

HallsSensor* HallsSensor::instance = nullptr;

HallsSensor::HallsSensor(EventQueue<Event, 32> &halls_event_q) : event_q(halls_event_q) {
    Serial.println("created halls sensor...");
}

void HallsSensor::init() {
    pinMode(GPIO_PIN, INPUT_PULLUP);
    instance = this;
    attachInterrupt(
        digitalPinToInterrupt(GPIO_PIN),
        HallsSensor::hallsInterrupt,
        FALLING
    );
}

void HallsSensor::hallsInterrupt() {
    if (instance == nullptr) {
        return;
    }

    uint32_t now = micros();
    instance->revolutionTime = now - instance->lastRevolutionTime;
    instance->lastRevolutionTime = now;

    Event event;
    event.id = EventIds::WheelRevolution;
    event.wheel.revolutionTime = instance->revolutionTime;
    instance->event_q.pushFromISR(event);
    Serial.println("halls interrupt called...");
}

float HallsSensor::getSpeed() {
    float seconds =
        revolutionTime / 1000000.0f;
    return wheelSize / seconds;
}
