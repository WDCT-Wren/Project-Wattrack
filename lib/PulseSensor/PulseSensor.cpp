#include "pulseSensor.h"

volatile unsigned long kwh = 0;
volatile unsigned long lastPulseTime = 0;
volatile unsigned long rawFires = 0;
volatile unsigned long totalPulses = 0;

unsigned long safeKwhRead = 0;

void initSensor() {
  pinMode(SENSOR_PIN, INPUT);

  attachInterrupt(
    digitalPinToInterrupt(SENSOR_PIN),
    readPulse,
    FALLING
  );
}

void updateSafeKwh() {
  noInterrupts();
  safeKwhRead = kwh;
  interrupts();
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