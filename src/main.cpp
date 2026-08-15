#include "Display.h"
#include "Welcome.h"
#include "Dashboard.h"
#include "Utils.h"
#include "BikeMetrics.h"
#include <Arduino.h>

Screen* currentScreen;
BikeMetrics metrics = {0, 0, 0, 0};

void setup() {
  setupSerialLogging();
  setupDisplay();
  // currentScreen = new Welcome(display);
  currentScreen = new Dashboard(display);
}

void loop() {
  currentScreen->draw(metrics);
  currentScreen->update();
}