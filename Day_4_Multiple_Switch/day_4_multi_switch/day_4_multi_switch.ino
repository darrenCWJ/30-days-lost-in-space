#include "Arduino.h"  // include information about our HERO


const byte CABIN_LIGHTS_PIN = 10;    // pin controlling the cabin lights
const byte STORAGE_LIGHTS_PIN = 11;  // pin controlling the storage lights
const byte COCKPIT_LIGHTS_PIN = 12;  // pin controlling the exterior lights

const byte CABIN_LIGHTS_SWITCH_PIN = 4;    // switch controlling the cabin lights
const byte STORAGE_LIGHTS_SWITCH_PIN = 3;  // switch controlling the storage lights
const byte COCKPIT_LIGHTS_SWITCH_PIN = 2; 


void setup() {
  // put your setup code here, to run once:
  // Configure our LED control pins as OUTPUT pins
  pinMode(CABIN_LIGHTS_PIN, OUTPUT);    // pin controlling the cabin lights
  pinMode(STORAGE_LIGHTS_PIN, OUTPUT);  // pin controlling the storage lights
  pinMode(COCKPIT_LIGHTS_PIN, OUTPUT);  // pin controlling the exterior lights

  // Configure the switch pins as INPUT pins
  pinMode(CABIN_LIGHTS_SWITCH_PIN, INPUT);    // pin connected to switch 1 (cabin lights)
  pinMode(STORAGE_LIGHTS_SWITCH_PIN, INPUT);  // pin connected to switch 2 (storage lights)
  pinMode(COCKPIT_LIGHTS_SWITCH_PIN, INPUT);  // pin connected to switch 3 (exterior lights)
}

void loop() {
  // Control cabin lights based on setting on switch 1
  if (digitalRead(CABIN_LIGHTS_SWITCH_PIN) == HIGH) {  // if switch is on (HIGH voltage)
    digitalWrite(CABIN_LIGHTS_PIN, HIGH);              // turn on LED by providing HIGH voltage (5v)
  } else {
    digitalWrite(CABIN_LIGHTS_PIN, LOW);  // turn off LED by setting output to LOW (zero volts)
  }

  // Control storage lights based on setting on switch 2
  if (digitalRead(STORAGE_LIGHTS_SWITCH_PIN) == HIGH) {  // if switch is on (HIGH voltage)
    digitalWrite(STORAGE_LIGHTS_PIN, HIGH);              // turn on LED by providing HIGH voltage (5v)
  } else {
    digitalWrite(STORAGE_LIGHTS_PIN, LOW);  // turn off LED by setting output to LOW (zero volts)
  }

  // Control exterior lights based on setting on switch 3
  if (digitalRead(COCKPIT_LIGHTS_SWITCH_PIN) == HIGH) {  // if switch is on (HIGH voltage)
    digitalWrite(COCKPIT_LIGHTS_PIN, HIGH);              // turn the LED on (HIGH is the voltage level)
  } else {
    digitalWrite(COCKPIT_LIGHTS_PIN, LOW);  // turn off LED by setting output to LOW (zero volts)
  }
}