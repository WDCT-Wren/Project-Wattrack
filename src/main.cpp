#include <Arduino.h>

// define pin
const uint8_t sensorPin = 2;  

constexpr uint8_t PULSE_CONSTANT = 1600;
const unsigned long DEBOUNCE_MICROS =  10000; // 0.01 seconds

volatile unsigned long totalPulses = 0;
volatile unsigned long kwh = 0;
volatile unsigned long lastPulseTime = 0;

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
  unsigned long now = micros();
  if (now - lastPulseTime < DEBOUNCE_MICROS) return;
  lastPulseTime = now; 

  totalPulses++;
  kwh = totalPulses / (float) PULSE_CONSTANT;
}