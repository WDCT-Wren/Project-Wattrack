#pragma once

constexpr uint8_t SENSOR_PIN = 2;

constexpr uint16_t PULSE_CONSTANT = 1600; // 1600 imp/kwh
const unsigned long DEBOUNCE_MILLIS = 50; // 50 milliseconds

extern volatile unsigned long kwh;
extern volatile unsigned long lastPulseTime;
extern volatile unsigned long rawFires;
extern volatile unsigned long totalPulses;

extern unsigned long safeKwhRead;

void readPulse();
void initSensor();
void updateSafeKwh();