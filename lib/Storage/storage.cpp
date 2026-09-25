#include "storage.h"

void initStorage() {
    if (!EEPROM.begin(sizeof(unsigned long) + 1)) {
        Serial.println("EEPROM initialization failed");
        return;
    }

    uint8_t flag;
    EEPROM.get(EEPROM_INIT_ADDR, flag);

    if (flag != EEPROM_INIT_MAGIC) {
        Serial.println("New storage");

        totalPulses = 0;
        pulseConstant = 1000; // default pulse constant if none was read
        EEPROM.put(EEPROM_PULSE_ADDR, 0UL);
        EEPROM.put(EEPROM_INIT_ADDR, EEPROM_INIT_MAGIC);
        EEPROM.commit();
    } else {
        totalPulses = readSavedPulseCount();

        Serial.print("Loaded pulses: ");
        Serial.println(totalPulses);
        Serial.print("Pulse Constant: ");
        Serial.println(pulseConstant);
    }
}

void savePulseCount(unsigned long pulseCount) {
    EEPROM.put(EEPROM_PULSE_ADDR, pulseCount);
    EEPROM.commit();
}

void savePulseCosntant(uint8_t pulseConstant) {
    EEPROM.put(EEPROM_CONSTANT_ADDR, pulseConstant);
    EEPROM.commit();
}

unsigned long readSavedPulseCount() {
    unsigned long savedTotalPulse = 0;
    EEPROM.get(EEPROM_PULSE_ADDR, savedTotalPulse);
    return savedTotalPulse;
}

uint8_t readSavedPulseConstant() {
    uint8_t pulseconstant = 0;
    EEPROM.get(EEPROM_CONSTANT_ADDR, pulseconstant);
    return pulseconstant;
}