#include "BikeComputer.h"

BikeComputer::BikeComputer()
{
    setupSerialLogging();
    setupDisplay();
    currentScreen->draw(metrics);
    selectBtn->init();
}