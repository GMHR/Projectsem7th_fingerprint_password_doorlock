#include <Adafruit_Fingerprint.h>


#define mySerial Serial2

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup_f()
{
  Serial.begin(9600);
  finger.begin(57600);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) {
      delay(1);
    }
  }
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK) return p;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) return p;

  p = finger.fingerSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    return p;
  }

  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  display.clearDisplay();
  display.setCursor(10, 10);
  display.println("Unlocked");
  display.display();
  digitalWrite(buzzer, HIGH);//
  delay(150);                //
  digitalWrite(buzzer, LOW); //
  delay(50);                //
  digitalWrite(buzzer, HIGH);//
  delay(150);                //
  digitalWrite(buzzer, LOW); //
  digitalWrite(RELAY_PIN, HIGH);  // unlock the door for 20 seconds
  delay(3000);
  digitalWrite(RELAY_PIN, LOW); // lock the door

  return finger.fingerID;
}

void loop_f()
{
  uint8_t result = getFingerprintID();
  if (result == FINGERPRINT_OK) {
    return;
  }
  delay(50);
}
