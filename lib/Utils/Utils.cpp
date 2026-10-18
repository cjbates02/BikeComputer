#include <Arduino.h>
#include "Utils.h"

void setupSerialLogging() {
    Serial.begin(115200);    
}

uint32_t getMinRevolutionInterval(float wheelCircumference, float maxSpeed)
{
    return (wheelCircumference / 12.0f / 5280.0f) * (3600.0f / maxSpeed) * 1000000.0f;
}