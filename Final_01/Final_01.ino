#include "pass.h"
#include "finger.h"






char keyevent;
char firstevent = 'A';
char secondevent = 'B';
void setup() {
  
  screen();
  setup_p();
  setup_f();
  digitalWrite(buzzer , HIGH);   //
  delay(500);                    // long beep  (initiate)
  digitalWrite(buzzer, LOW);     //
  
 
  }



void loop() {
  // put your main code here, to run repeatedly:
 
  keyevent = keypad.getKey();
  if (keyevent == firstevent){
    
    loop_p();
    
    
  }
  if (keyevent == secondevent){
    display.clearDisplay();
    display.setCursor(10, 10);
    display.println("press finger");
    display.display();
    delay(50);
    loop_f();
  }
 
  
    
}
