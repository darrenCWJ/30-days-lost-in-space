// Explicitly include Arduino.h
#include "Arduino.h"
 
// Include Keypad library
#include <Keypad.h>
 
// Our HERO keypad has 4 rows, each with 4 columns.
const byte ROWS = 4;
const byte COLS = 4;
 
const byte PIN_LENGTH = 4;                           // PIN code is 4 button presses
char password[PIN_LENGTH] = { '0', '0', '0', '0' };  // Initial password is four zeros.
 
// Define what characters will be returned by each button
const char BUTTONS[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
 
// Define row and column pins connected to the keypad
const byte ROW_PINS[ROWS] = { 5, 4, 3, 2 };
const byte COL_PINS[COLS] = { 6, 7, 8, 13 };  // NOTE wire moved from Day 13's sketch to pin 13
 
// Create our keypad object from the keypad configuration above
Keypad heroKeypad = Keypad(makeKeymap(BUTTONS), ROW_PINS, COL_PINS, ROWS, COLS);
 
const byte BUZZER_PIN = 12;  // NOTE that pin 12 drives the buzzer now
 
const byte RED_PIN = 11;    // PWM pin controlling the red leg of our RGB LED
const byte GREEN_PIN = 10;  // PWM pin ccontrolling the green leg of our RGB LED
const byte BLUE_PIN = 9;    // PWM pin ccontrolling the blue leg of our RGB LED
 
void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
 
  // Since we start out "locked", we initially display a red color.
  displayColor(128, 0, 0);
 
  Serial.begin(9600);  // Begin monitoring via the serial monitor
  Serial.println("Press * to set new password or # to access the system.");
}
 
void loop() {
  char button_character = heroKeypad.getKey();  // Wait for a button press and save character
 
  // The '#' button unlocks our console
  if (button_character == '#') {          // Button to access system
    giveInputFeedback();                  // Short beep with blue light
    bool access_allowed = validatePIN();  // Have user enter PIN to allow access
 
    if (access_allowed) {
      Serial.println("Welcome, authorized user. You may now begin using the system.");
    } else {
      Serial.println("Access Denied.");
      Serial.println("\nPress * to enter new PIN or # to access the system.");
    }
  }
 
  // The '*' allows the user to enter a new PIN after entering current PIN for security
  if (button_character == '*') {          // Button to change password
    giveInputFeedback();                  // Short beep with blue light
    bool access_allowed = validatePIN();  // Have user enter PIN to allow access
 
    if (access_allowed) {
      displayColor(128, 80, 0);  // Display yellow LED while entering a NEW PIN
      Serial.println("Welcome, authorized user. Please Enter a new password: ");
 
      // Use a for() loop that runs once for each PIN character.  Each character read
      // replaces a character in our original PIN.
      for (int i = 0; i < PIN_LENGTH; i++) {
        password[i] = heroKeypad.waitForKey();  // replace PIN character with new character
        // NOTE: After the LAST button press we will give Success feedback, but up to the
        //       last character we simply give input feedback.  Since Array indices start
        //       at 0, this if() statement will be true for all but the LAST character of
        //       the new PIN.
        if (i < (PIN_LENGTH - 1)) {
          giveInputFeedback();
          displayColor(128, 80, 0);  // override color
        }
 
        Serial.print("*");
      }
 
      Serial.println();  // add new line after last asterisk so next message is on next line
      Serial.println("PIN Successfully Changed!");
      giveSuccessFeedback();  // TADA sound and green light for successful PIN change
    } else {
      Serial.println("Access Denied. Cannot change PIN without entering current PIN first.");
      Serial.println("\nPress * to enter new PIN or # to access the system.");
    }
  }
}
 
// Enter PIN and return false for bad PIN or true for good PIN
bool validatePIN() {
  char enteredPIN[PIN_LENGTH]; // Array to store the entered PIN
  Serial.println("Enter 4-digit PIN to continue.");
  // Collect the full 4-digit PIN
  for (int i = 0; i < PIN_LENGTH; i++) {
    char button_character = heroKeypad.waitForKey(); // Wait for each button press
    enteredPIN[i] = button_character; // Store the pressed character
    giveInputFeedback(); // Provide feedback for each input
    Serial.print("*"); // Print masked input as '*'
    }
  Serial.println(); // Add a new line after PIN entry for clarity
  // Compare entered PIN with the stored PIN
  for (int i = 0; i < PIN_LENGTH; i++) {
    if (enteredPIN[i] != password[i]) {
      giveErrorFeedback(); // Provide error feedback if any character doesn't match
      Serial.println("WRONG PIN: Try again.");
      return false; // Return false for incorrect PIN
      }
    }
  // If the loop completes without mismatches, the PIN is correct
  giveSuccessFeedback(); // Provide success feedback
  Serial.println("Device Successfully Unlocked!");
  return true;
}
 
// Display a color by providing Red, Green and Blue intensities (0-255)
void displayColor(byte red_intensity, byte green_intensity, byte blue_intensity) {
  analogWrite(RED_PIN, red_intensity);      // Set red LED intensity using PWM
  analogWrite(GREEN_PIN, green_intensity);  // Set green LED intensity using PWM
  analogWrite(BLUE_PIN, blue_intensity);    // Set blue LED intensity using PWM
}
 
// A recognized button was pressed.  Give short beep and blue LED
void giveInputFeedback() {
  displayColor(0, 0, 0);  // Turn off LED while playing tone
  tone(BUZZER_PIN, 880, 200);
  delay(200);               // Delay while tone is playing because tone() returns immediately
  displayColor(0, 0, 128);  // Restore blue LED
}
 
// A matching PIN has been entered or a new PIN has been accepted.
// Play TADA! sound and display green LED
void giveSuccessFeedback() {
  displayColor(0, 0, 0);  // Turn off LED while playing tone
  tone(BUZZER_PIN, 300, 200);
  delay(200);  // Delay while tone is playing because tone() returns immediately
 
  tone(BUZZER_PIN, 500, 500);
  delay(500);  // Delay while tone is playing because tone() returns immediately
  displayColor(0, 128, 0); // Display green LED
}
 
// Bad PIN entered.  Play descending tone and display red LED
void giveErrorFeedback() {
  displayColor(0, 0, 0);  // Turn off LED while playing tone
  tone(BUZZER_PIN, 300, 200);
  delay(200);  // Delay while tone is playing because tone() returns immediately
 
  tone(BUZZER_PIN, 200, 500);  // Frequency = 200Hz, Duration = 200ms
  delay(500);  // Delay while tone is playing because tone() returns immediately
  displayColor(128, 0, 0);  // Display red LED
}
