#include "Display.h"
#include "Welcome.h"
#include "Utils.h"
#include <Arduino.h>

Screen* currentScreen;

void setup() {
  setupSerialLogging();
  setupDisplay();
  currentScreen = new Welcome(display);
}

void loop() {
  currentScreen->draw();
  currentScreen->update();
}