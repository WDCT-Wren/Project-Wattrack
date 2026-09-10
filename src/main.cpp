#include <Arduino.h>
#include <Wire.h>
#include "PulseSensor.h"
#include "Display.h"

// define pin
const uint8_t ledPin = 13;

void setup() {
  initSensor();
  initDisplay();

  pinMode(ledPin, OUTPUT);
}

void loop() {
  // deliberately trigger two close-together transitions to simulate chatter
  digitalWrite(ledPin, HIGH);
  delay(5);
  digitalWrite(ledPin, LOW);
  delay(5);
  digitalWrite(ledPin, HIGH);   // second rapid transition, well inside 50ms window
  delay(5);
  digitalWrite(ledPin, LOW);
  delay(200);  // now well clear of debounce, safe gap before next real pulse

  displayData();
  
  delay(50);

  updateSafeKwh();
}