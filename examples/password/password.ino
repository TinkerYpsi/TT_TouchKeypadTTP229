#include <Wire.h>
#include <TTP299_touch_keypad.h>

TTP299_touch_keypad touchpad;
int password[2];

void setup() {
  Serial.begin(9600);
  touchpad.setPassword();
}

void loop() {
  if(touchpad.checkPassword(1)) {
    Serial.println("WHOA IT WORKS!!!");
  }
}
