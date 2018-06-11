#include <Arduino.h>
#include <Wire.h>
#include "TT_TouchKeypadTTP229.h"

// 0x57 is device address
// the addressing without the R/W bit -> 01010111 = 57
#define TTP229_LSF 0x57

TT_TouchKeypadTTP229::TT_TouchKeypadTTP229() {
  _password[0] = -100;
  _password[1] = -100;
}
TT_TouchKeypadTTP229::~TT_TouchKeypadTTP229() { }

void TT_TouchKeypadTTP229::getTTP229data(byte *a, byte *b) {
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
void TT_TouchKeypadTTP229::printData() {
  byte aa,bb = 0;
  getTTP229data(&aa, &bb);
  printByte(aa);
  printByte(bb);
  Serial.println();
  delay(1000);
}

void TT_TouchKeypadTTP229::setPassword() {
  Serial.println("NOTE: Keep fingers pressed down on keys for the most accurate results");
  delay(2000);
  Serial.println("Ready...");
  delay(500);
  Serial.println("On your marks...");
  delay(500);
  Serial.print("Enter password... ");
  delay(500);
  byte aa,bb = 0;
  // get the first and second half of the password as two bytes
  getTTP229data(&aa, &bb);

  int password1[2];
  password1[0] = (int) aa;
  password1[1] = (int) bb;

  Serial.println("(hold for a few more seconds)");
  delay(500);

  aa,bb = 0;
  getTTP229data(&aa, &bb);
  int password2[2];
  password2[0] = (int) aa;
  password2[1] = (int) bb;
  delay(500);

  aa,bb = 0;
  getTTP229data(&aa, &bb);
  int password3[2];
  password3[0] = (int) aa;
  password3[1] = (int) bb;

  bool password_reset;
  if(password1[0] == password2[0] && password2[0] == password3[0]) {
    if(password1[1] == password2[1] && password2[1] == password3[1]) {
      // a password was previously failed to be set
      if(_password[0] = 0 && _password[1] == 0) {
        password_reset = true;
      }
      _password[0] = (int) aa;
      _password[1] = (int) bb;
      _firstHalf = aa;
      _secondHalf = bb;
      Serial.print("Your password is: ");
      printByte(aa);
      printByte(bb);
      Serial.println();
      if(password_reset) {
        delay(500);
        Serial.println("Returning to password check... ");
        delay(500);
        return;
      }
      delay(1000);
    }
  }
  else {
    Serial.println("Sorry! I didn't quite catch that.");
    delay(1000);
    Serial.println("Retrying...");
    Serial.println();
    setPassword();
  }
}

bool TT_TouchKeypadTTP229::checkPassword(int debug) {
  if(_password[0] == 0 && _password[1] == 0) {
    Serial.println("You haven't pressed anything!");
    Serial.println("Retrying... ");
    setPassword();
  }

  Serial.println("Please enter the password: ");
  delay(2000);
  // TODO: add multiple checks to reduce errors
  byte aa,bb = 0;
  getTTP229data(&aa, &bb);

  int password[2];
  password[0] = (int) aa;
  password[1] = (int) bb;

  if(password[0] == _password[0] && password[1] == _password[1]) {
    Serial.println("Correct!");
    return true;
  }
  else {
    Serial.println("Incorrect!");
    Serial.println("You entered: ");
    printByte(aa);
    printByte(bb);
    Serial.println();

    if(debug == 1) {
      Serial.println();
      Serial.println("The correct password is: ");
      printByte(_firstHalf);
      printByte(_secondHalf);
      Serial.println();

      // uncomment code below to see your password represented as two ints
      // Serial.print("your password ints: ");
      // Serial.print(password[0]);
      // Serial.print(" , ");
      // Serial.println(password[1]);
      //
      // Serial.println();
      // Serial.print("correct password ints: ");
      // Serial.print(_password[0]);
      // Serial.print(" , ");
      // Serial.println(_password[1]);
      delay(3000);
    }
    return false;
  }
}

void TT_TouchKeypadTTP229::printByte(byte &b) {
  for(unsigned int mask = 0x80; mask; mask >>= 1) {
    if(mask & b) {
      Serial.print('1');
    }
    else {
      Serial.print('0');
    }
  }
}
