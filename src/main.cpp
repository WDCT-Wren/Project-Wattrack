#include <Arduino.h>

// define pin
const uint8_t sensorPin = 2;  

uint32_t pulseCount;
uint32_t CumKwh;

volatile uint8_t pulseState; 

void readPulse();

void setup() {
  pinMode(sensorPin, INPUT); 
  Serial.begin(9600);      

  // add the interupt function to the program
  attachInterrupt(
    digitalPinToInterrupt(sensorPin),
    readPulse,
    CHANGE
  );
}

void loop() {
  Serial.print("Pulses counted: ");
  Serial.println(pulseCount);
  delay(800);
}

/*
  reads and detects pulses of light from the photodiode
*/
void readPulse() {
  pulseState = digitalRead(sensorPin);

  if (pulseState == LOW) {
    pulseCount++;
  }
}