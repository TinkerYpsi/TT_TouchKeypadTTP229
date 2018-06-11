/*

   Created:     Patrick Neggie
   Date:        8 May 2018
   Last update: 8 May 2018
   Online:      https://github.com/TinkerYpsi/Robotdyn-TTP229-Capacitive-Touch-Library.git

   Tested with:
   Arduino IDE 1.8.4

   This library wouldn't have been possible without the help of Doctor Bit's online documentation
   Check out his website for more Arduino hacks: http://www.drbit.nl
*/

//////////////////////////////////////////////////////////////////
// Connections
//
// Uno:   SDA <-> A4 (SDA)
//        SCL <-> A5 (SCL)
//
// Mega:  SDA <-> 20 (SDA)
//        SCL <-> 21 (SCL)
//
// Leo:   SDA <-> 2 (SDA)
//        SCL <-> 3 (SCL)
//
//////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
// Addressing of the TTP229 LSF

// Slave Address : The identify code for the TTP229-LSF is〝 (1010) 〞. The device address B3 , B2 and
// B1 are fixed〝 111 〞

// Read/Write : The final (eighth) bit of the slave address defines the type of operation to be performed.
// If the R/W bit is〝 1 〞, a read operation is executed. If it is〝 0 〞, a write operation is executed. But
// the TTP229-LSF only accepts read operation.


// Slave Device Addressing
// Device Identifier         Device Address          R/W Bit
// B7 B6 B5 B4               B3 B2 B1                B0
// 1  0  1  0                1  1  1                 R (0)

//////////////////////////////////////////////////////////////////

#ifndef TT_TouchKeypadTTP229_h
#define TT_TouchKeypadTTP229_h

#include <Arduino.h>
#include <Wire.h>

class TT_TouchKeypadTTP229 {
public:
  // constructor and destructor are here to avoid Arduino compile errors
  TT_TouchKeypadTTP229();
  ~TT_TouchKeypadTTP229();

  // prints capacitive keys pressed to Serial monitor in form of bits
  // i.e. 2,5 and 13 pressed on a 16-key keypad would result in: 0100100000001000
  void printData();

  // captures password through pressing of keys
  // can press down any combination of keys to form password
  // open Serial monitor for optimal user experience
  void setPassword();

  // returns whether or not current keys pressed are the same as password
  // if debug == 1, user is prompted with correct password & incorrect password they entered
  bool checkPassword(int debug = 0);

private:
  void getTTP229data(byte *a, byte *b);
  void printByte(byte &b);

  byte _firstHalf;
  byte _secondHalf;
  int _password[2];
};

#endif
