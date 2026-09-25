#pragma once

#include <EEPROM.h>
#include "pulseSensor.h"

#define EEPROM_INIT_ADDR 0
#define EEPROM_INIT_MAGIC 0xA5
#define EEPROM_CONSTANT_ADDR 1
#define EEPROM_PULSE_ADDR 2

void initStorage();
void savePulseCount(unsigned long pulseCount);
void savePulseConstant(uint8_t pulseConstant);
unsigned long readSavedPulseCount();
uint8_t readSavedPulseConstant();