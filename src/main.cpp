#include <Wire.h>
#include "Adafruit_MPR121.h"
 
#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif
 
// Create two MPR121 objects
Adafruit_MPR121 cap1 = Adafruit_MPR121();
Adafruit_MPR121 cap2 = Adafruit_MPR121();
 
// Track touches for each board
uint16_t lasttouched1 = 0;
uint16_t currtouched1 = 0;
 
uint16_t lasttouched2 = 0;
uint16_t currtouched2 = 0;
 
void setup() {
  Serial.begin(9600);
  while (!Serial) { delay(10); }
 
  Serial.println("Dual MPR121 Capacitive Touch Test");
 
  // Initialize first board at 0x5A
  if (!cap1.begin(0x5A)) {
    Serial.println("MPR121 #1 not found at 0x5A, check wiring!");
    while (1);
  }
  Serial.println("MPR121 #1 found!");
 
  // Initialize second board at 0x5B
  if (!cap2.begin(0x5B)) {
    Serial.println("MPR121 #2 not found at 0x5B, check wiring!");
    while (1);
  }
  Serial.println("MPR121 #2 found!");
 
  // Optional: Auto-configure both
  cap1.setAutoconfig(true);
  cap2.setAutoconfig(true);
 
  Serial.println("Initialization complete.");
}
 
void loop() {
  // Read touches from board 1
  currtouched1 = cap1.touched();
  for (uint8_t i = 0; i < 6; i++) { // Only first 6 sensors
    if ((currtouched1 & _BV(i)) && !(lasttouched1 & _BV(i))) {
      Serial.print("Board 1: "); Serial.print(i); Serial.println(" touched");
    }
    if (!(currtouched1 & _BV(i)) && (lasttouched1 & _BV(i))) {
      Serial.print("Board 1: "); Serial.print(i); Serial.println(" released");
    }
  }
  lasttouched1 = currtouched1;
 
  // Read touches from board 2
  currtouched2 = cap2.touched();
  for (uint8_t i = 0; i < 7; i++) { // Only first 7 sensors
    if ((currtouched2 & _BV(i)) && !(lasttouched2 & _BV(i))) {
      Serial.print("Board 2: "); Serial.print(i); Serial.println(" touched");
    }
    if (!(currtouched2 & _BV(i)) && (lasttouched2 & _BV(i))) {
      Serial.print("Board 2: "); Serial.print(i); Serial.println(" released");
    }
  }
  lasttouched2 = currtouched2;
 
  delay(100); // Small delay for stability
}