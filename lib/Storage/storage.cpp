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
        EEPROM.put(EEPROM_PULSE_ADDR, 0UL);
        EEPROM.put(EEPROM_INIT_ADDR, EEPROM_INIT_MAGIC);
        EEPROM.commit();
    } else {
        totalPulses = readSavedPulseCount();
        Serial.print("Loaded pulses: ");
        Serial.println(totalPulses);
    }
}

void savePulseCount(unsigned long pulseCount) {
    EEPROM.put(EEPROM_PULSE_ADDR, pulseCount);
    EEPROM.commit();
}

unsigned long readSavedPulseCount() {
    unsigned long savedTotalPulse = 0;
    EEPROM.get(EEPROM_PULSE_ADDR, savedTotalPulse);
    return savedTotalPulse;
}