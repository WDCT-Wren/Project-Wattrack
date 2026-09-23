#pragma once

#include <Arduino.h>

constexpr uint8_t SENSOR_PIN = 4;

constexpr uint16_t PULSE_CONSTANT = 1600; // 1600 imp/kwh
const unsigned long DEBOUNCE_MILLIS = 50; // 50 milliseconds

extern volatile unsigned long kwh;
extern volatile unsigned long lastPulseTime;
extern volatile unsigned long rawFires;
extern volatile unsigned long totalPulses;

extern double safeKwhRead;

void readPulse();
void initSensor();
void updateSafeKwh();