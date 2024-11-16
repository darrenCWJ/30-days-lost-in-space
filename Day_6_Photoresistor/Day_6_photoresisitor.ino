const byte PHOTORESISTOR_PIN = A0;
const unsigned int MIN_DELAY = 50;
const unsigned int MAX_DELAY = 500;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PHOTORESISTOR_PIN, INPUT); 

  Serial.begin(9600);  // This initializes the Serial Monitor and sets the speed to 9600 bits per second
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned int light_value = analogRead(PHOTORESISTOR_PIN);   // light value from 0 to 1024

  Serial.print("Light value: ");  // Display label string to serial monitor
  Serial.print(light_value);      // display the value read from our photoresistor


  static unsigned int darkest_light = light_value;    // this is the lowest value returned by the photoresistor
  static unsigned int brightest_light = light_value;  // this is the highest value returned by the photoresistor

  if (light_value < darkest_light) {  // If value is LESS THAN ('<') the darkest...
    darkest_light = light_value;      // ...then save current value as our new darkest value
  }
  if (light_value > brightest_light) {  // If value is GREATER THAN ('>') the brightest...
    brightest_light = light_value;      // ...then save current value as our new brightest value
  }


  unsigned int delay_value = map(light_value, darkest_light, brightest_light, MAX_DELAY, MIN_DELAY);
  Serial.print(", Delay value: ");  // display label after light_value
  Serial.println(delay_value);      // display delay_value returned by map() function with newline
 
  // now blink our built in LED using our delay_value.
  digitalWrite(LED_BUILTIN, HIGH);  // Turn on LED
  delay(delay_value);               // Leave on delay_value milliseconds
  digitalWrite(LED_BUILTIN, LOW);   // Turn off LED
  delay(delay_value);               // Leave off delay_value milliseconds
}
