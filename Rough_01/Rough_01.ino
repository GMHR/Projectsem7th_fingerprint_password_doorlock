
#include <Adafruit_Fingerprint.h>

#define mySerial Serial2
#include "enroll.h"
#include "global.h"








void setup()
{
  Serial.begin(9600);
  Serial.println("started");
 
  }

 


 // to get an input from serial monitor
  uint8_t readkeyevent() {
    uint8_t keyevent = 0;
  
    while (keyevent == 0) {
      while (! Serial.available());
       keyevent = Serial.parseInt();
    }
    return keyevent;
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(200);
  /*
   * since i am comparing a value from serial monitor i disguise of the variable "key" to another value, i also need to set that value
   * to another variable to compare. i.e. "x" or "y"
   */
  uint8_t key = readkeyevent();
 int x = 2;
 int y = 1 ;
  
  if (key == y){
    Serial.println("started");
    
    setup_e();
    loop_e();
  }
  if (key == x){
    Serial.println("lol");
  }

    
  
    
  }
