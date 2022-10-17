/*
  getStableValue.h - Library for get stable value from esp32 or arduino ADC input.
  Created by Ahmed REGHINI, 2022.
  Released into the public domain.
*/

#ifndef getStableValue_h
#define getStableValue_h

#include "Arduino.h"

class getStableValue
{
  public: 
  int GSV(uint8_t _pin, int _nvs = 100, int _x = 4, int _dep = 2);

private:
  int pin;
  int nvs; // number of arrow in the array
  int x;
  int dep;
  int t1[2][x];
  int result; // the most repeated value of resultA * x.
};
#endif
