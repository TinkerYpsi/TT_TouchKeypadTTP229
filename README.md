# Robotdyn TTP229 Capacitive Touch Library

An Arduino library for controlling a 15 and 16 capacitive touch key pad and disk pads (model TTP229).
Tested with the Robotdyn I2C Capacitive Touch Module, Robotdyn Capacitive Touch Disk Pad, and Robotdyn Capacitive Touch Keypad

Written by Patrick Neggie <<patmn@umich.edu>>, 2018


Installation
------------

Clone this GitHub repository and place the `TTP299_touch_keypad` library folder in your `<arduinosketchfolder>/libraries/` folder. You may need to create the `libraries` subfolder if its your first library. Restart the Arduino IDE.

##### Note:
You must type `#include <Wire.h>` at the top of each file you intend to use with this library as this library is dependent on `<Wire.h>`.


Features
--------
- Set and check passwords to block intruders
- Print capacitive touch readings to the Serial monitor
```c
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
```

Usage
-----

Read the .h file for instructions on how to use each of the functions. Check out our examples to get some inspiration.
