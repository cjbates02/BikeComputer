#include "Screen.h"
#include "BikeMetrics.h"
#pragma once

class Dashboard : public Screen
{
public:
    Dashboard(Adafruit_SSD1306& screenDisplay);
    void draw(BikeMetrics& metrics) override;
};