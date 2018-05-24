#include <TTP299_touch_keypad.h>

#include <Wire.h>

TTP299_touch_keypad touchpad;
  
void setup() {
  Serial.begin(9600);
}

void loop() {
  touchpad.printData();
}

