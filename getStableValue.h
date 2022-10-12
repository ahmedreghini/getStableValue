/*
  getStableValue.h - Library for get stable value from esp32 or arduino ADC input.
  Created by Ahmed REGHINI, 2022.
  Released into the public domain.
*/

#ifndef Morse_h
#define Morse_h

#include "Arduino.h"

class getStableValue
{
Public:
getStableValue(uint8_t pin, int nvs = 100, int x = 4, int dep = 2);
};
#endif
