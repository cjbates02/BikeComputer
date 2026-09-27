#include "BikeComputer.h"

BikeComputer::BikeComputer()
{
    setupSerialLogging();
    setupDisplay();

    currentScreen->draw(metrics);
    selectBtn->init();
    hallsSensor->init();

    processEvents();
}

void BikeComputer::processEvents()
{
    Serial.println("starting event processor...");
    while (true)
    {
        Event event;
        if (event_q.pop(event)) {
            handleEvent(event);
        };
    }
}

void BikeComputer::handleEvent(Event event)
{
    // Serial.println("handling an event...");
    switch (event.id)
    {
    case EventIds::ButtonPressed:
        handleBtnPressed(event);
        break;
    case EventIds::ButtonReleased:
        handleBtnReleased(event);
        break;
    case EventIds::WheelRevolution:
        handleWheelRevolution(event);
    default:
        break;
    }
}

void BikeComputer::handleWheelRevolution(Event event) {
    float speedMph = calculateSpeedMph(event.wheel.revolutionTime);
    Serial.println("MPH: ");
    Serial.print(speedMph);
    Serial.println("");
}

void BikeComputer::handleBtnPressed(Event event)
{
    if (event.button.btnId == ButtonIds::Select)
    {
        Serial.println("handling select button press event...");
        toggleScreen();
    }
}

void BikeComputer::handleBtnReleased(Event event)
{
    return; // tbd
}

void BikeComputer::toggleScreen()
{
    Serial.println("toggle screen called...");
    switch (currentScreen->id)
    {
    case ScreenId::Dashboard:
        Serial.println("switching to welcome screen...");
        currentScreen = welcome;
        currentScreen->enter();
        currentScreen->draw(metrics);
        return;
    case ScreenId::Welcome:
        Serial.println("switching to dashboard screen...");
        currentScreen = dashboard;
        currentScreen->enter();
        currentScreen->draw(metrics);
        return;
    }
}

float BikeComputer::calculateSpeedMph(uint32_t revolutionTime) {
    if (revolutionTime == 0) return 0.0f;
    float milesPerRevolution = (wheelCircumference / 12.0f) / 5280.0f;
    float secondsPerRevolution = revolutionTime / 1000000.0f;
    return (milesPerRevolution / secondsPerRevolution) * 3600.0f;
}