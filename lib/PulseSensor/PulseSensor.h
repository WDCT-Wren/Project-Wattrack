#pragma once

#include <Arduino.h>

#define SENSOR_PIN 4

const unsigned long DEBOUNCE_MILLIS = 50; // 50 milliseconds

extern volatile unsigned long lastPulseTime;
extern volatile unsigned long rawFires;
extern volatile unsigned long totalPulses;

extern double safeKwhRead;
extern uint8_t pulseConstant;

void readPulse();
void initSensor();
void updateSafeKwh();