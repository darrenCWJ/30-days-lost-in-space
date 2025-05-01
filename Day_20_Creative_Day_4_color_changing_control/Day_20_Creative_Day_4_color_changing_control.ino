// Explicitly include Arduino.h
#include "Arduino.h"

// Include Keypad library
#include <Keypad.h>

// Include BasicEncoder library file
// Make sure you have this library installed
#include <BasicEncoder.h>

// --- Pin Definitions ---

// Rotary Encoder Pins (MUST use interrupt pins 2 and 3 for BasicEncoder)
const byte ENCODER_CLK_PIN = 2; // Interrupt pin connected to encoder CLK
const byte ENCODER_DT_PIN = 3;   // Interrupt pin connected to encoder DT

// RGB LED PWM Pins
const byte BLUE_PIN = 11;   // PWM pin for Red LED leg
const byte RED_PIN = 10; // PWM pin for Green LED leg
const byte GREEN_PIN = 9;    // PWM pin for Blue LED leg

// Keypad Pins
const byte ROWS = 1; // One row
const byte COLS = 4; // Four columns

// Define row and column pins connected to the keypad
const byte ROW_PINS[ROWS] = { 4 };     // Connect to row pin(s)
const byte COL_PINS[COLS] = { 5, 6, 7, 8 }; // Connect to column pins

// --- Keypad Setup ---

// Define the keymap (characters returned when a key is pressed)
// Corresponds to COL_PINS 5, 6, 7, 8
char keys[ROWS][COLS] = {
  {'1', '2', '3', '4'} // '1' for Red, '2' for Green, '3' for Blue, '4' unused
};

// Create Keypad instance
Keypad customKeypad = Keypad(makeKeymap(keys), ROW_PINS, COL_PINS, ROWS, COLS);

// --- Encoder Setup ---

// Create a *single* BasicEncoder instance for the rotary encoder
BasicEncoder encoder(ENCODER_CLK_PIN, ENCODER_DT_PIN);

// --- State Variables ---

// Enum to represent the selected color channel
enum ColorChannel {
  RED,
  GREEN,
  BLUE
};

// Variable to store the currently selected color channel for control
ColorChannel selectedColor = RED; // Start by controlling RED

// Variables to store the current intensity of each color (0-255)
int redIntensity = 0;
int greenIntensity = 0;
int blueIntensity = 0;

// --- Setup Function ---

void setup() {
  // Initialize Serial communication (for debugging)
  Serial.begin(9600);
  Serial.println("RGB LED Control Initialized");
  Serial.println("Press 1 for Red, 2 for Green, 3 for Blue");
  Serial.println("Turn encoder to adjust selected color intensity.");
  Serial.println("Watching encoder raw changes..."); // Added message

  // Set LED pins as OUTPUT
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // Initialize the LED to be off
  displayColor(0, 0, 0);
  Serial.println("Initial Intensities: R=0 G=0 B=0"); // Print initial state

  // Optional: Initialize encoder value if needed (BasicEncoder starts at 0)
  // encoder.set(0);
  /*
   * Our HERO board allow executing code to be "interrupted" when the value of a pin
   * changes.  These two commands allow us to provide code that is executed whenever
   * the level of a configured pin is changed (as occurs when the rotary encoder is
   * turned).
   *
   * When the rotary encoder is turned (in either direction) our "updateEncoder" function
   * will be executed.  When updateEncoder() completes the code resumes at exactly the
   * place where it was interrupted.
   */
  // Call Interrupt Service Routine (ISR) updateEncoder() when any high/low change
  // is seen on A (DEPTH_CONTROL_CLK_PIN) interrupt  (pin 2), or B (DEPTH_CONTROL_DT_PIN) interrupt (pin 3)
  attachInterrupt(digitalPinToInterrupt(ENCODER_CLK_PIN), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_DT_PIN), updateEncoder, CHANGE);
}

// --- Helper Function: Display Color ---

// Display a color by providing Red, Green and Blue intensities (0-255)
void displayColor(byte red_intensity, byte green_intensity, byte blue_intensity) {
  analogWrite(RED_PIN, red_intensity);   // Set red LED intensity using PWM
  analogWrite(GREEN_PIN, green_intensity); // Set green LED intensity using PWM
  analogWrite(BLUE_PIN, blue_intensity);  // Set blue LED intensity using PWM
}
/*
 * This is our interrupt handler function that we configured in setup().
 * Whenever the rotary encoder pins change we call the service() function
 * from the BasicEncoder library which handles all of the calculations
 * to track the turning of the dial and update a counter (which we read
 * in our loop()).
 */
void updateEncoder() {
  encoder.service();  // Call BasicEncoder library .service()
}

// --- Main Loop ---

void loop() {
  // Check for key press
  char key = customKeypad.getKey();

  if (key) {
    Serial.print("Key pressed: ");
    Serial.println(key);
    switch (key) {
      case '1':
        selectedColor = RED;
        Serial.println("Controlling Red");
        encoder.reset();
        break;
      case '2':
        selectedColor = GREEN;
        Serial.println("Controlling Green");
        encoder.reset();
        break;
      case '3':
        selectedColor = BLUE;
        Serial.println("Controlling Blue");
        encoder.reset();
        break;
      case '4':
        Serial.println("Key 4 pressed ");
        redIntensity = 0;
        blueIntensity = 0;
        greenIntensity = 0;
        displayColor(redIntensity, greenIntensity, blueIntensity);
        break;
    }
  }

  // Read the encoder value and update the selected color intensity
  long encoderChange = encoder.get_count(); // Get the change in encoder steps and reset the counter

  if (encoderChange != 0) {
    Serial.print("Encoder Change: ");
    Serial.println(encoderChange);

    switch (selectedColor) {
      case RED:
        redIntensity = constrain(redIntensity + encoderChange, 0, 255);
        Serial.print("Red Intensity: ");
        Serial.println(redIntensity);
        break;
      case GREEN:
        greenIntensity = constrain(greenIntensity + encoderChange, 0, 255);
        Serial.print("Green Intensity: ");
        Serial.println(greenIntensity);
        break;
      case BLUE:
        blueIntensity = constrain(blueIntensity + encoderChange, 0, 255);
        Serial.print("Blue Intensity: ");
        Serial.println(blueIntensity);
        break;
    }
    displayColor(redIntensity, greenIntensity, blueIntensity);
  }

  // Small delay to prevent excessive reads (optional, but good practice)
  // encoder.reset();
  delay(50);
}