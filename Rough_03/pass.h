/*
   This ESP32 code is created by esp32io.com

   This ESP32 code is released in the public domain

   For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-door-lock-system-using-password
*/

#include <Keypad.h>



#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define I2C_SDA 2
#define I2C_SCL 4


// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);





bool pcomplete = false;
#define buzzer 23 //buzzer pin

int RELAY_PIN = 15 ;// ESP32 pin GIOP14 connected to the IN pin of relay
#define ROW_NUM     4  // four rows
#define COLUMN_NUM  4  // four columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pin_rows[ROW_NUM] = {13, 12, 14, 27}; // GIOP19, GIOP18, GIOP5, GIOP17 connect to the row pins
byte pin_column[COLUMN_NUM] = {26, 25, 33, 32}; // GIOP16, GIOP4, GIOP0, GIOP2 connect to the column pins

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

const String password_1 = "0156CAB"; // change your password here
const String password_2 = "5642CD";  // change your password here
const String password_3 = "545423";  // change your password here
String input_password;

void setup_p() {
  Serial.begin(9600);
  input_password.reserve(32); // maximum input characters is 32
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // lock the door
  digitalWrite(buzzer , HIGH);   //
  delay(250);                    // short beep  (keyevent)
  digitalWrite(buzzer, LOW);     //
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Input Password");
  display.display();
}

void screen() {
  // put your setup code here, to run once:

  Wire.begin(I2C_SDA, I2C_SCL);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.setTextSize(1);
  display.setTextColor(WHITE);

}



bool pass() {



  char key = keypad.getKey();
  pcomplete = false;

  if (key) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println(key);
    display.display();

    if (key == '*') {
      input_password = ""; // reset the input password
      display.clearDisplay();
      display.setCursor(10,0);
      display.println("Enter the ");
      display.setCursor(5,10);
      display.println("password again");
      display.display();
      digitalWrite(buzzer, HIGH);
      delay(150);
      digitalWrite(buzzer, LOW);
      delay(100);
      digitalWrite(buzzer, HIGH);
      delay(150);
      digitalWrite(buzzer, LOW);
      
    } else if (key == '#') {
      digitalWrite(buzzer , HIGH);
      delay(250);
      digitalWrite(buzzer, LOW);
      if (input_password == password_1 || input_password == password_2 || input_password == password_3) {
        display.clearDisplay();
        display.setCursor(10, 10);
        display.println("Valid Password => unlock the door");
        display.display();
        digitalWrite(buzzer, HIGH);//
        delay(250);                //
        digitalWrite(buzzer, LOW); //
        delay(100);                //
        digitalWrite(buzzer, HIGH);//
        delay(250);                //
        digitalWrite(buzzer, LOW); //
        delay(100);                //
        digitalWrite(buzzer, HIGH);//
        delay(250);                //
        digitalWrite(buzzer, LOW); //
        digitalWrite(RELAY_PIN, HIGH);  // unlock the door for 20 seconds
        delay(3000);
        digitalWrite(RELAY_PIN, LOW); // lock the door
        pcomplete = true;
      } else {
        digitalWrite(buzzer, HIGH);//
        delay(100);                //
        digitalWrite(buzzer, LOW); //
        delay(50);                 //
        digitalWrite(buzzer, HIGH);//
        delay(100);                //
        digitalWrite(buzzer, LOW); //
        display.clearDisplay();
        display.setCursor(10, 10);
        display.println("Invalid Password");
        display.setCursor(5, 20);
        display.println(" => Try again");
        display.display();
        pcomplete = true;

      }

      input_password = ""; // reset the input password
    } else {
      input_password += key; // append new character to input password string
    }

  }
  return pcomplete;
}

void loop_p() {
  Serial.println("a");
  while (!pass()) {
    pass();
  }
 

}
