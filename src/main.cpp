#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// define lcd address
LiquidCrystal_I2C lcd(0x27, 24, 4);

// define pin
const uint8_t sensorPin = 2;  
const uint8_t ledPin = 13;

constexpr uint16_t PULSE_CONSTANT = 1600;
const unsigned long DEBOUNCE_MILLIS =  50; // 0.05 seconds

volatile unsigned long totalPulses = 0;
volatile unsigned long kwh = 0;
volatile unsigned long lastPulseTime = 0;

volatile unsigned long rawFires = 0;

unsigned long safeKwhRead = 0;

/*
  reads and detects pulses of light from the photodiode
*/
void readPulse() {
  unsigned long now = millis();
  rawFires++;

  //Debounce logic 
  if (now - lastPulseTime < DEBOUNCE_MILLIS) return;

  lastPulseTime = now; 

  totalPulses++;
  kwh = totalPulses / PULSE_CONSTANT;
}

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

  pinMode(sensorPin, INPUT); 
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);      

  attachInterrupt(
    digitalPinToInterrupt(sensorPin),
    readPulse,
    FALLING
  );
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