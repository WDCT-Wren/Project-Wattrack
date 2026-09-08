#include <Arduino.h>

// define pin
const uint8_t sensorPin = 2;  
constexpr uint8_t PULSE_CONSTANT = 1600;

volatile unsigned long totalPulses = 0;
volatile unsigned long kwh = 0;

unsigned long safeKwhRead = 0;

void setup() {
  pinMode(sensorPin, INPUT); 
  Serial.begin(9600);      

  attachInterrupt(
    digitalPinToInterrupt(sensorPin),
    readPulse,
    FALLING
  );
}

void loop() {
  Serial.print("Pulses counted: ");
  Serial.println(totalPulses);
  delay(800);

  noInterrupts();
  safeKwhRead = kwh; 
  interrupts();
}

/*
  reads and detects pulses of light from the photodiode
*/
void readPulse() {
  totalPulses++;
  kwh = totalPulses / (float) PULSE_CONSTANT;
}