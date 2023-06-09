#include "pass.h"






char keyevent;
char firstevent = '1';
void setup() {
  Serial.begin(115200);
  screen();
  digitalWrite(buzzer , HIGH);   //
  delay(500);                    // long beep  (initiate)
  digitalWrite(buzzer, LOW);     //
  
 
  }



void loop() {
  // put your main code here, to run repeatedly:
  keyevent = keypad.getKey();
  if (keyevent == firstevent){
    setup_p();
    loop_p();
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("complete");
    display.display();
    
  }
 
  
    
}
