#include <Arduino.h>
#include <Wire.h>
#include "TTP299_touch_keypad.h"

// 0x57 is device address
// the addressing without the R/W bit -> 01010111 = 57
#define TTP229_LSF 0x57

TTP299_touch_keypad::TTP299_touch_keypad() {
  _password[0] = -100;
  _password[1] = -100;
}
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
  Serial.println();
  delay(1000);
}

void TTP299_touch_keypad::setPassword() {
  Serial.print("Enter password... ");
  delay(1000);
  // TODO: do prelim pword check to reduce errors from bad reading
  Serial.println("(hold for a few more seconds)");
  delay(1000);
  // TODO: add another pword check to reduce errors
  byte aa,bb = 0;

  // get the first and second half of the password as two bytes
  getTTP229data(&aa, &bb);

  _password[0] = (int) aa;
  _password[1] = (int) bb;

  _firstHalf = aa;
  _secondHalf = bb;

  Serial.print("Your password is: ");
  printByte(aa);
  printByte(bb);
  delay(1000);
}

bool TTP299_touch_keypad::checkPassword(int debug) {
  if(_password[0] == -100 && _password[1] == -100) {
    Serial.println("You haven't set a password yet!");
    return false;
  }

  Serial.println("Please enter the password: ");
  delay(2000);
  // TODO: add multiple checks to reduce errors
  byte aa,bb = 0;
  getTTP229data(&aa, &bb);

  int password[2];
  if(password[0] == _password[0] && password[1] == _password[1]) {
    Serial.println("Correct!");
    return true;
  }
  else {
    Serial.println("Incorrect!");
    Serial.println("You entered: ");
    printByte(aa);
    printByte(bb);

    if(debug == 1) {
      Serial.println("The correct password is: ");
      printByte(_firstHalf);
      printByte(_secondHalf);
    }
    return false;
  }
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
