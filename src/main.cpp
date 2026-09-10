#include <Arduino.h>
#include <Wire.h>
#include "PulseSensor.h"
#include "Display.h"
#include "PulseLEDSim.h"

// define pin
const uint8_t ledPin = 13;

void setup() {
  initSensor();
  initDisplay();

  pinMode(ledPin, OUTPUT);
}

void loop() {
  pulseLED();
  displayData();
  
  delay(50);

  updateSafeKwh();
}