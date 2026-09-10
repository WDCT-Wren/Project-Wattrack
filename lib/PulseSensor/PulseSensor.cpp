#include <Arduino.h>
#include "PulseSensor.h"

void initSensor() {
  pinMode(SENSOR_PIN, INPUT);

  attachInterrupt(
    digitalPinToInterrupt(SENSOR_PIN),
    readPulse,
    FALLING
  );
}

/*
  reads and detects pulses of light from the photodiode
*/
void readPulse() {
  unsigned long now = millis();
  rawFires++;

  //Debounce logic 
  if (now - lastPulseTime < DEBOUNCE_MILLIS) return;

  lastPulseTime = now; 

  totalPulses++;
  kwh = totalPulses / PULSE_CONSTANT;
}