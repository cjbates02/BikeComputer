#include "BikeComputer.h"

BikeComputer::BikeComputer()
{
    setupSerialLogging();
    setupDisplay();
    currentScreen->draw(metrics);
    selectBtn->init();

    processEvents();
}

void BikeComputer::processEvents()
{
    Serial.println("starting event processor...");
    while (true)
    {
        ButtonEvent event = event_q.pop();
        handleEvent(event);
    }
}

void BikeComputer::handleEvent(ButtonEvent event)
{
    Serial.println("handling a button event...");
    switch (event.id)
    {
    case ButtonIds::Select:
        handleSelect(event);
    }
}

void BikeComputer::handleSelect(ButtonEvent event)
{
    Serial.println("handling select button event...");
    switch (event.type)
    {
    case ButtonEventTypes::Pressed:
        Serial.println("handling select button press event...");
        toggleScreen();
    case ButtonEventTypes::Released:
        return; // to be implemented.
    }
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