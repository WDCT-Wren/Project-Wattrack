#include "header.h"

void setup() {
  Serial.begin(115200);
  initStorage();
  initSensor();
  initLED();
  initWebServer();
}

void loop() {
  pulseLED();

  Serial.print("Pulses counted: ");
  Serial.println(totalPulses);
  
  delay(50);

  updateSafeKwh();
  savePulseCount(totalPulses);
}