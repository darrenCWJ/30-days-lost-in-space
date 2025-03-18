// C++ code
//

 
// RGB LED pins
const byte RED_PIN = 11;    // pin controlling the red leg of our RGB LED
const byte GREEN_PIN = 10;  // pin ccontrolling the green leg of our RGB LED
const byte BLUE_PIN = 9;    // pin ccontrolling the blue leg of our RGB LED

const byte PHOTORESISTOR_PIN = A1;

const byte RED_SWITCH_PIN = 2;
const byte GREEN_SWITCH_PIN = 3;  
const byte BLUE_SWITCH_PIN = 4;
const byte WHITE_SWITCH_PIN = 5;

const byte OFF = 0;                 // Selected color is OFF
const byte DIM = 64;                // Selected color is 1/4 intensity
const byte BRIGHTER = DIM + 64;     // Selected color is 1/2 intensity
const byte BRIGHT = BRIGHTER + 64;  // Selected color is 3/4 intensity
const byte BRIGHTEST = 255;         // Selected color is maximum intensity (255)

/*
 * Display a color on our RGB LED by providing an intensity for
 * our red, green and blue LEDs.
 */
 
void setup() {
  // Declare the RGB LED pins as outputs:
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
 
  pinMode(PHOTORESISTOR_PIN, INPUT);
  
  // Configure the switch pins as INPUT pins
  pinMode(RED_PIN, INPUT);    // pin connected to switch 1 (cabin lights)
  pinMode(GREEN_SWITCH_PIN, INPUT);  // pin connected to switch 2 (storage lights)
  pinMode(BLUE_SWITCH_PIN, INPUT);  // pin connected to switch 3 (exterior lights)
  pinMode(WHITE_SWITCH_PIN, INPUT);
  
  // Start serial monitor
  Serial.begin(9600);
}

void displayColor(
  byte red_intensity,    // red LED intensity (0-255)
  byte green_intensity,  // green LED intensity (0-255)
  byte blue_intensity    // blue LED intensity (0-255)
) {
  analogWrite(RED_PIN, red_intensity);      // Set red LED intensity using PWM
  analogWrite(GREEN_PIN, green_intensity);  // Set green LED intensity using PWM
  analogWrite(BLUE_PIN, blue_intensity);    // Set blue LED intensity using PWM
}
 
void loop() {
  
if (digitalRead(RED_SWITCH_PIN) == HIGH || 
    digitalRead(GREEN_SWITCH_PIN) == HIGH || 
    digitalRead(BLUE_SWITCH_PIN) == HIGH || 
    digitalRead(WHITE_SWITCH_PIN) == HIGH) {
    byte redVal = 0;
    byte greenVal = 0;
    byte blueVal = 0;
    
    if (digitalRead(RED_SWITCH_PIN) == HIGH) {
      redVal = 255;
    }

    if (digitalRead(GREEN_SWITCH_PIN) == HIGH) {
      greenVal = 255;
    }

    if (digitalRead(BLUE_SWITCH_PIN) == HIGH) {
      blueVal = 255;
    }
    if (digitalRead(WHITE_SWITCH_PIN) == HIGH){
      redVal = 255;
      greenVal = 255;
      blueVal = 255;
    }
    if (redVal == 255 || greenVal == 255 || blueVal == 255) {
      displayColor(redVal, greenVal, blueVal);
    }
  }
  else {
    int sensorValue = analogRead(PHOTORESISTOR_PIN);

    // Assuming sensorValue ranges from 0 to 1023
    int third = 1024 / 3;
    int twoThirds = 2 * third;
    
    if (sensorValue < third) {
      // Bottom 1/3: Red
      analogWrite(RED_PIN, 255);
      analogWrite(GREEN_PIN, 0);
      analogWrite(BLUE_PIN, 0);
  } else if (sensorValue < twoThirds) {
    // Middle 1/3: Blue
    analogWrite(RED_PIN, 0);
    analogWrite(GREEN_PIN, 0);
    analogWrite(BLUE_PIN, 255);
  } else {
    // Top 1/3: Green
    analogWrite(RED_PIN, 0);
    analogWrite(GREEN_PIN, 255);
    analogWrite(BLUE_PIN, 0);
  }

  delay(100); // Adjust delay
    
  }
}