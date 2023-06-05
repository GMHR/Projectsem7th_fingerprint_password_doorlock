//This Library contains all of the global Variables, Functions and Definitions Reside//

//included library

  // Include Arduino Wire library for I2C[password]
  #include <Wire.h>
  // Include Keypad library[password]
  #include <Keypad.h>
  // Include NewPing Library[ultrasonic]
  #include "NewPing.h"

//PIN definitions

  //PIN used for Relay
  int lockpin = 33;
  //Pin for ultrasonic
  #define TRIGGER_PIN  10
  #define ECHO_PIN     13
  #define MAX_DISTANCE 400


//VARIABLE Definitions

  //for Ultrasonic
   
    NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
    float duration, distance;

  // for pass
    // Length of password + 1 for null character
    #define Password_Length 8
    // Character to hold password input
    char Data[Password_Length];
    
    // Password
    char Master[Password_Length] = "123A456";
    
    // Counter for character entries
    byte data_count = 0;
    
    // Character to hold key input
    char customKey;
    
    // Constants for row and column sizes
    const byte ROWS = 4;
    const byte COLS = 4;
    
    // Array to represent keys on keypad
    char hexaKeys[ROWS][COLS] = {
      {'1', '2', '3', 'A'},
      {'4', '5', '6', 'B'},
      {'7', '8', '9', 'C'},
      {'*', '0', '#', 'D'}
    };
    
    // Connections to Arduino
    byte rowPins[ROWS] = {9, 8, 7, 6};
    byte colPins[COLS] = {5, 4, 3, 2};
    // Create keypad object
    Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);



//setup Function [GLOBAL]
void setup_g(){
  //for Relay
  pinMode(lockpin, OUTPUT);  
}

//Global Functions

//Lock/unlock function
void lock(){
  digitalWrite(lockpin, HIGH);
  delay(3000);
  digitalWrite(lockpin, LOW);
}

//Ultrasound Lock/Unlock Function
void ultrasound(){  
  duration = sonar.ping();  
  // Determine distance from duration
  // Use 343 metres per second as speed of sound 
  distance = (duration / 2) * 0.0343;
  
  // Send results to Serial Monitor
  Serial.println("Distance = ");
  if (distance >= 3 || distance <= 2) {
    Serial.println("Door is unlocked");
    lock();    
  } 
  delay(500);
}


//Password Unlock Function


void pass() {
  Serial.println("Enter Password:");

  // Look for keypress
  customKey = customKeypad.getKey();
  if (customKey) {
    // Enter keypress into array and increment counter
    Data[data_count] = customKey;
    //lcd.setCursor(data_count, 1);
    Serial.println(Data[data_count]);
    data_count++;
  }

  // See if we have reached the password length
  if (data_count == Password_Length - 1) {

    if (!strcmp(Data, Master)) {
      // Password is correct
      Serial.println("Correct");
      lock();     
    }
    else {
      // Password is incorrect
      Serial.println("Incorrect");
    }

    // Clear data display
    //lcd.clear();
    // Go through array and clear data
  while (data_count != 0) {
    Data[data_count--] = 0;
  }
  }
}
