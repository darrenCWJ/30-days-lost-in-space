const byte PHOTORESISTOR_PIN = A1;  // Photoresistor analog pin
// RGB LED pins
const byte RED_PIN = 11;    // pin controlling the red leg of our RGB LED
const byte GREEN_PIN = 10;  // pin ccontrolling the green leg of our RGB LED
const byte BLUE_PIN = 9;    // pin ccontrolling the blue leg of our RGB LED
 
const unsigned long BATTERY_CAPACITY = 50000;  // Maximum battery capacity

void displayColor(
  byte red_intensity,    // red LED intensity (0-255)
  byte green_intensity,  // green LED intensity (0-255)
  byte blue_intensity    // blue LED intensity (0-255)
) {
  analogWrite(RED_PIN, red_intensity);      // write red LED intensity using PWM
  analogWrite(GREEN_PIN, green_intensity);  // write green LED intensity using PWM
  analogWrite(BLUE_PIN, blue_intensity);    // write blue LED intensity using PWM
}


void setup() {
  // Declare the RGB LED pins as outputs:
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
 
  // Start serial monitor
  Serial.begin(9600);
}
void loop() {
  // Use static because we need this variable to maintain it's value across
  // multiple loop() runs.
  static unsigned long battery_level = 0;  // Current battery charge level (set to 0 first time used)
 
  battery_level += analogRead(PHOTORESISTOR_PIN);  // Add current "charge amount" to our battery
 
  // We can't charge the battery higher than it's capacity, set level as full if it goes over
  if (battery_level > BATTERY_CAPACITY) {
    battery_level = BATTERY_CAPACITY;
  }

  // Compute battery charge percentage from our function
  float percentage = ((float)battery_level / (float)BATTERY_CAPACITY) * 100;
 
  if (percentage >= 50.0) {     // battery level is OK, display green
    displayColor(0, 128, 0);  // display green
  } else if (percentage >= 25.0 && percentage < 50.0) {
    displayColor(128, 80, 0);  // display yellow-ish/amber for early warning
  } else {                     // Level must be less than 25%, display "pulsating" red
    // To pulsate the red light we briefly turn the LED off and then display red, giving it
    // a pulsating effect.
    displayColor(0, 0, 0);    // Turn off our LED
    delay(20);                // ...and delay briefly
    displayColor(128, 0, 0);  // then display red
  }
  Serial.print(percentage);  // Display our floating point percentage (like 12.34) WITHOUT a newline
  Serial.println("%");       // then display the percent sign ("%") with a newline.
 
  delay(100);  // Delay 1/10 of a second so displayed values don't scroll too fast
}
 
