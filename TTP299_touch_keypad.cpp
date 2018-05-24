#include <Arduino.h>
#include <Wire.h>
#include "TTP299_touch_keypad.h"

// 0x57 is device address
// the addressing without the R/W bit -> 01010111 = 57
#define TTP229_LSF 0x57

TTP299_touch_keypad::TTP299_touch_keypad() { }
TTP299_touch_keypad::~TTP299_touch_keypad() { }

void TTP299_touch_keypad::getTTP229data(byte *a, byte *b) {
  Wire.begin();
  // request 2 bytes from slave device TTP229
  Wire.requestFrom(TTP229_LSF, 2);

  int dataN = 0;
  // slave may send less than requested
  while(Wire.available()) {
    char c = Wire.read();
    if(dataN == 0) *a = c;
    if(dataN == 1) *b = c;
    dataN++;
  }
}

// NOTE: still need to Serial.begin() in Arduino IDE
void TTP299_touch_keypad::printData() {
  byte aa,bb = 0;
  getTTP229data(&aa, &bb);
  printByte(aa);
  printByte(bb);
  delay(1000);
}

void TTP299_touch_keypad::printByte(byte &b) {
  for(unsigned int mask = 0x80; mask; mask >>= 1) {
    if(mask & b) {
      Serial.print('1');
    }
    else {
      Serial.print('0');
    }
  }
}
