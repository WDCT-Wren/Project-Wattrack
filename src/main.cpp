#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "PulseSensor.h"

// define lcd address
LiquidCrystal_I2C lcd(0x27, 24, 4);

// define pin
const uint8_t ledPin = 13;

void display() {
  lcd.setCursor(0, 0);
  lcd.print("Pulses: ");
  lcd.print(totalPulses);

  lcd.setCursor(0, 1);
  lcd.print("kwh: ");
  lcd.print(safeKwhRead);

  lcd.setCursor(0, 3);
  lcd.print(PULSE_CONSTANT);
  lcd.print(" imp/kwh");
}

void setup() {
  // LCD Setup 
  lcd.init();
  lcd.backlight();
  lcd.clear();

  initSensor();
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // deliberately trigger two close-together transitions to simulate chatter
  digitalWrite(ledPin, HIGH);
  delay(5);
  digitalWrite(ledPin, LOW);
  delay(5);
  digitalWrite(ledPin, HIGH);   // second rapid transition, well inside 50ms window
  delay(5);
  digitalWrite(ledPin, LOW);
  delay(200);  // now well clear of debounce, safe gap before next real pulse

  display();
  
  delay(50);

  noInterrupts();
  safeKwhRead = kwh; 
  interrupts();
}