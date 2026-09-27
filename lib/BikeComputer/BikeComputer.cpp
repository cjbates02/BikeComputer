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
    default:
        break;
    }
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