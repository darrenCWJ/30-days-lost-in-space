#include "Arduino.h"
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

const byte ROW_PINS[ROWS] = { 5, 4, 3, 2 };
const byte COL_PINS[COLS] = { 6, 7, 8, 9 };

const char BUTTONS[ROWS][COLS] = {
  { '1', '2', '3', 'A' },  // Row 0
  { '4', '5', '6', 'B' },  // Row 1
  { '7', '8', '9', 'C' },  // Row 2
  { '*', '0', '#', 'D' }   // Row 3
};

Keypad heroKeypad = Keypad(makeKeymap(BUTTONS), ROW_PINS, COL_PINS, ROWS, COLS);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedly:
  char pressedButton = heroKeypad.waitForKey();
  Serial.println(pressedButton);
}
