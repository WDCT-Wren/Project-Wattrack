#pragma once
#include <Arduino.h>

inline const uint8_t SENSOR_PIN;

inline constexpr uint16_t PULSE_CONSTANT = 1600; // 1600 imp/kwh
inline const unsigned long DEBOUNCE_MILLIS = 50; // 50 milliseconds

inline volatile unsigned long kwh = 0;
inline volatile unsigned long lastPulseTime = 0;
inline volatile unsigned long rawFires = 0;
inline volatile unsigned long totalPulses = 0;

inline unsigned long safeKwhRead = 0;

void readPulse();
void initSensor();
