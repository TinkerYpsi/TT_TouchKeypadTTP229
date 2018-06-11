#include <TT_TouchKeypadTTP229.h>

#include <Wire.h>

TT_TouchKeypadTTP229 touchpad;

void setup() {
  Serial.begin(9600);
}

void loop() {
  touchpad.printData();
}
