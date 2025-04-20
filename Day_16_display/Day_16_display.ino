#include "Arduino.h"
#include <TM1637Display.h>

// all_on pins connected to the TM1637 display
const byte CLK_PIN = 6;
const byte DIO_PIN = 5;

// Create display object of type TM1637Display:
TM1637Display lander_display = TM1637Display(CLK_PIN, DIO_PIN);
 // Create array that turns all segments on:
const byte all_on[] = { 0b11111111,
                        0b11111111,
                        0b11111111,
                        0b11111111 };
 const byte done[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,          // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,  // O
  SEG_C | SEG_E | SEG_G,                          // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G           // E
};
 

void setup() {
  // put your setup code here, to run once:
  lander_display.setBrightness(1);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Clear the display (all segments off)
  lander_display.clear();
  delay(1000);
 
  // Light up all segments of the display
  lander_display.setSegments(all_on);
  delay(1000);
 
  // Clear the display (all segments off)
  lander_display.clear();
  delay(1000);
  for (int i = 0; i < 4; i++) {
    lander_display.showNumberDecEx(1200, 0b01000000);
    delay(500);
    lander_display.clear();
    delay(500);
  }
 
  // Show counter including negative sign for negative numbers
  // NOTE: negative numbers cannot be less than -999 since the negative sign
  //       uses the left most digit of the display.
  for (int i = -100; i <= 100; i++) {
    lander_display.showNumberDec(i);
    delay(50);
  }
  delay(1000);
 
  // Clear the display (all segments off)
  lander_display.clear();
  delay(1000);
 
  // Display the message "dOnE"
  lander_display.setSegments(done);
 
  delay(10000);  // Delay 10 seconds and then repeat our demo.
}
