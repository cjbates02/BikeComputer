#include "HallsSensor.h"
#include <thread>
#include <chrono>

HallsSensor* HallsSensor::instance = nullptr;

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
}

float HallsSensor::getSpeed() {
    float seconds =
        revolutionTime / 1000000.0f;
    return wheelSize / seconds;
}

void HallsSensor::pollInterrupts() {
    
}
