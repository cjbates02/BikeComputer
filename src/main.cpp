#include "Display.h"
#include "Welcome.h"
#include "Dashboard.h"
#include "Utils.h"
#include "BikeMetrics.h"
#include "Button.h"
#include <Arduino.h>

Screen* currentScreen;
BikeMetrics metrics = {0, 0, 0, 0};
Button* selectBtn = new Button(1, "Select Button");

void setup() {
  setupSerialLogging();
  setupDisplay();
  // currentScreen = new Welcome(display);
  currentScreen = new Dashboard(display);
  selectBtn->init();
}

void loop() {
  currentScreen->draw(metrics);
  currentScreen->update();
  selectBtn->isPressed();
}