// Explicitly include Arduino.h
#include "Arduino.h"
 
// Include Keypad library
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;
 
const byte ROW_PINS[ROWS] = { 5, 4, 3, 2 };
const byte COL_PINS[COLS] = { 6, 7, 8, 9 };
 
char BUTTONS[ROWS][COLS] = {
  { '1', '2', '3', 'A' },  // 1st row
  { '4', '5', '6', 'B' },  // 2nd row
  { '7', '8', '9', 'C' },  // 3rd row
  { '*', '0', '#', 'D' }   // 4th row
};
 
Keypad myAwesomePad = Keypad(makeKeymap(BUTTONS), ROW_PINS, COL_PINS, ROWS, COLS);
 
const unsigned int TONES[ROWS][COLS] = {
  // a frequency tone for each button
  { 31, 93, 147, 208 },
  { 247, 311, 370, 440 },
  { 523, 587, 698, 880 },
  { 1397, 2637, 3729, 0 }  // Use frequency of 0 for bottom right key to end tone.
};
 
const byte BUZZER_PIN = 10;  // pin 10 drives the buzzer
 
void setup() {
  Serial.begin(9600);  // Begin monitoring via the serial monitor
}

void loop() {
  // put your main code here, to run repeatedly:
 char button_character = myAwesomePad.waitForKey();
  unsigned int tone_frequency = 0;  // Frequency to use for tone (default to 0, no tone)
  for (byte i = 0; i < ROWS; i++) {
    for (byte j = 0; j < COLS; j++) {
      if (button_character == BUTTONS[i][j]) {  // found it, get the corresponding tone
        tone_frequency = TONES[i][j];
      }
 
    }  // end j loop
  }    // end i loop
 
  Serial.print("Key: ");  //   send the button_character to serial monitor...
  Serial.print(button_character);
  Serial.print("   Freq: ");
  Serial.println(tone_frequency);
 
  /*
   * The tone() function plays a tone until stopped.  The code continues to run as the tone plays.
   */
  if (tone_frequency > 0) {                // If tone frequency greater than 0...
    tone(BUZZER_PIN, tone_frequency);  // ...then play the tone at that frequency until stopped
  } else {
    Serial.println("Stop tone");
    noTone(BUZZER_PIN);  // Stop pressed (tone frequency of 0) so stop any tone playing
  }
}