// C++ code
//
//#include "Arduino.h"  // include information about our HERO


const byte RED_LIGHTS_PIN = 13;    // pin controlling the cabin lights
const byte GREEN_LIGHTS_PIN = 12;  // pin controlling the storage lights
const byte YELLOW_LIGHTS_PIN = 11;  // pin controlling the exterior lights
const byte BLUE_LIGHTS_PIN = 10;    // pin controlling the cabin lights
const byte ORANGE_LIGHTS_PIN = 9;  // pin controlling the storage lights
const byte WHITE_LIGHTS_PIN = 8;


const byte S1_LIGHTS_SWITCH_PIN = 2;    // switch controlling the cabin lights
const byte S2_LIGHTS_SWITCH_PIN = 3;  // switch controlling the storage lights
const byte S3_LIGHTS_SWITCH_PIN = 4; 


void setup()
{
  pinMode(RED_LIGHTS_PIN, OUTPUT);
  pinMode(GREEN_LIGHTS_PIN, OUTPUT);
  pinMode(YELLOW_LIGHTS_PIN, OUTPUT);
  pinMode(BLUE_LIGHTS_PIN, OUTPUT);
  pinMode(ORANGE_LIGHTS_PIN, OUTPUT);
  pinMode(WHITE_LIGHTS_PIN, OUTPUT);
  
  pinMode(S1_LIGHTS_SWITCH_PIN, INPUT);
  pinMode(S2_LIGHTS_SWITCH_PIN, INPUT);
  pinMode(S3_LIGHTS_SWITCH_PIN, INPUT);
}

void loop()
{

   if ( (digitalRead(S1_LIGHTS_SWITCH_PIN) == HIGH) && (digitalRead(S2_LIGHTS_SWITCH_PIN) == LOW) && (digitalRead(S3_LIGHTS_SWITCH_PIN) == LOW) ) {  // if switch is on (HIGH voltage)
    digitalWrite(RED_LIGHTS_PIN, HIGH);              // turn on LED by providing HIGH voltage (5v)
  } else {
    digitalWrite(RED_LIGHTS_PIN, LOW);  // turn off LED by setting output to LOW (zero volts)
  }
  
   if ( (digitalRead(S1_LIGHTS_SWITCH_PIN) == LOW) && (digitalRead(S2_LIGHTS_SWITCH_PIN) == HIGH) && (digitalRead(S3_LIGHTS_SWITCH_PIN) == LOW) ) {  // if switch is on (HIGH voltage)
    digitalWrite(GREEN_LIGHTS_PIN, HIGH);              // turn on LED by providing HIGH voltage (5v)
  } else {
    digitalWrite(GREEN_LIGHTS_PIN, LOW);  // turn off LED by setting output to LOW (zero volts)
  }
  
   if ( (digitalRead(S1_LIGHTS_SWITCH_PIN) == LOW) && (digitalRead(S2_LIGHTS_SWITCH_PIN) == LOW) && (digitalRead(S3_LIGHTS_SWITCH_PIN) == HIGH) ) {  // if switch is on (HIGH voltage)
    digitalWrite(YELLOW_LIGHTS_PIN, HIGH);              // turn on LED by providing HIGH voltage (5v)
  } else {
    digitalWrite(YELLOW_LIGHTS_PIN, LOW);  // turn off LED by setting output to LOW (zero volts)
  }
  
   if ( (digitalRead(S1_LIGHTS_SWITCH_PIN) == LOW) && (digitalRead(S2_LIGHTS_SWITCH_PIN) == HIGH) && (digitalRead(S3_LIGHTS_SWITCH_PIN) == HIGH) ) {  // if switch is on (HIGH voltage)
    digitalWrite(BLUE_LIGHTS_PIN, HIGH);              // turn on LED by providing HIGH voltage (5v)
  } else {
    digitalWrite(BLUE_LIGHTS_PIN, LOW);  // turn off LED by setting output to LOW (zero volts)
  }
  
   if ( (digitalRead(S1_LIGHTS_SWITCH_PIN) == HIGH) && (digitalRead(S2_LIGHTS_SWITCH_PIN) == LOW) && (digitalRead(S3_LIGHTS_SWITCH_PIN) == HIGH) ) {  // if switch is on (HIGH voltage)
    digitalWrite(ORANGE_LIGHTS_PIN, HIGH);              // turn on LED by providing HIGH voltage (5v)
  } else {
    digitalWrite(ORANGE_LIGHTS_PIN, LOW);  // turn off LED by setting output to LOW (zero volts)
  }
  
   if ( (digitalRead(S1_LIGHTS_SWITCH_PIN) == HIGH) && (digitalRead(S2_LIGHTS_SWITCH_PIN) == HIGH) && (digitalRead(S3_LIGHTS_SWITCH_PIN) == LOW) ) {  // if switch is on (HIGH voltage)
    digitalWrite(WHITE_LIGHTS_PIN, HIGH);              // turn on LED by providing HIGH voltage (5v)
  } else {
    digitalWrite(WHITE_LIGHTS_PIN, LOW);  // turn off LED by setting output to LOW (zero volts)
  }
  
}