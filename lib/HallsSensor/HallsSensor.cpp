#include "HallsSensor.h"
#include <thread>
#include <chrono>

void HallsSensor::poll() {
    while (true) {
        Serial.println(analogRead(GPIO_PIN));
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void HallsSensor::init() {
    analogReadResolution(12);
    std::thread pollThread(&HallsSensor::poll, this);
    pollThread.detach();
}
