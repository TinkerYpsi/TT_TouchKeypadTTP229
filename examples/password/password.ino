#include <Wire.h>
#include <TT_TouchKeypadTTP229.h>

TT_TouchKeypadTTP229 touchpad;
int password[2];

void setup() {
  Serial.begin(9600);
  touchpad.setPassword();
}

void loop() {
  if(touchpad.checkPassword()) {
    Serial.println("CORRECT!");
  }
  else {
    Serial.println("Try again!");
  }
  delay(2000);
}
