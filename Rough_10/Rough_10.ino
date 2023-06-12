#include "pass.h"
#include "finger.h"






char keyevent;
char firstevent = '1';
char secondevent = '2';
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
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("complete");
    display.display();
    
  }
  if (keyevent == secondevent){
    
    loop_f();
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("complete");
    display.display();
  }
 
  
    
}
