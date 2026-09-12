#include "header.h"

void setup() {
  initSensor();
  initDisplay();
  initLED();
}

void loop() {
  pulseLED();
  displayData();
  
  delay(50);

  updateSafeKwh();
}