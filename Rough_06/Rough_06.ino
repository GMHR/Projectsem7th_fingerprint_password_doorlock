#include "pass.h"


int buttonpin = 19;
int buttonstate = 0;




char keyevent;
char firstevent = '1';
void setup() {
  Serial.begin(115200);
  screen();
  setup_p();
  digitalWrite(buzzer , HIGH);   //
  delay(500);                    // long beep  (initiate)
  digitalWrite(buzzer, LOW);     //
  
 
  }



void loop() {
  // put your main code here, to run repeatedly:
  buttonstate = digitalRead(buttonpin);
  keyevent = keypad.getKey();
  if (keyevent == firstevent){
    
    loop_p();
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("complete");
    display.display();
    
  }
  if (buttonstate == HIGH){
    digitalWrite(buzzer , HIGH);   //
    delay(100);                    // short beep  
    digitalWrite(buzzer, LOW);     //
    digitalWrite(RELAY_PIN, HIGH);  // unlock the door for 20 seconds
    delay(3000);
    digitalWrite(RELAY_PIN, LOW); // lock the door
  }
  
 
  
    
}
