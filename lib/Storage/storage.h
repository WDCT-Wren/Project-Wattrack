#pragma once

#include <EEPROM.h>
#include "pulseSensor.h"

#define EEPROM_INIT_ADDR 0
#define EEPROM_INIT_MAGIC 0xA5
#define EEPROM_PULSE_ADDR 1

void initStorage();
void savePulseCount(unsigned long pulseCount);
unsigned long readSavedPulseCount();