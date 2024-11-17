const byte PHOTORESISTOR_PIN = A0;  // Photoresistor analog pin
const unsigned int BATTERY_CAPACITY = 50000;  // Maximum battery capacity

void setup() {
  pinMode(PHOTORESISTOR_PIN, INPUT);  // Input current light level from photoresistor
 
  Serial.begin(9600);  // Initialize Serial Monitor to 9600 baud
}

unsigned int battery_level = 0; 

void loop() {
  // put your main code here, to run repeatedly:
  if (battery_level < BATTERY_CAPACITY) {

    battery_level += analogRead(PHOTORESISTOR_PIN);  // read light level and add to battery level
    if (battery_level > BATTERY_CAPACITY) {          // If this would make charge over 100%...
      battery_level = BATTERY_CAPACITY;              // ...set current level to maximum capacity.
    }
  }

  printBatteryChargeLevel();  // Display current charge percentage on Serial Monitor
 
  delay(100);
}


void printBatteryChargeLevel() {
  if (battery_level < BATTERY_CAPACITY) {  // if not fully charged
    // Percentage of charge is current level divided by capacity, multiplied by 100 to get a percentage.
    Serial.print(((double)battery_level / (double)BATTERY_CAPACITY) * 100);  // display charge % to Serial Monitor
    Serial.println("%");
  } else {
    Serial.println("FULLY CHARGED");  // ...indicate fully charged on Serial Monitor
  }
}