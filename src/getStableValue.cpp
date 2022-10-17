#include <Arduino.h>
#include <stdio.h>
#include <math.h>
#include <getStableValue.h>
/*

1----uint8_t _pin ==> the number of the ADC pin (exp: 35 in esp 32 and A0 in arduino).
2----int _nvs = 100, ==> number of simplings of anologueRead(pin) you have to read before and get result of (the  most repeated value on them).
3----int _x = 4 ==> number of loops of (get the most repeated value) from (the most repeated value of the previous chaine (step--3)).
4----int _dep = 2 ==> number of time you repeat all the previous steps then get a value (_x) times then out a result1,
exemple: if _dep = 2 then the result2 = to _x * result1----> result1 = _x * step3 -----> step3 = _x * step2 -------> step2 = _nvs * analogueRead(pin).
the final result will be result2.
result = the most repeated value.

this function get the most repeated value of a ADC pin by a special algorithm,
- it get the most repeated value (resultA) of nvs * analogueRead(pin), and stored in an array (t1).
- then it repeat the previous loops x times, until we have x * result1 in dep1.
- then it get the most repeated value in t1 array (result2) and stored in dep2.
- then it repeat the previous loops x times, until we have x * result2 in dep2.
- then it get the most repeated value in t2 array (result3) and return it.
- then it get the most repeated value in t1 array (result2) and stored in dep..n.
- and so on it repeat the previous loops x times, until we have x * result..n in dep..n.
- then it get the most repeated value in t2 array (result..N) and return it.
*/

int getStableValue::GSV(uint8_t _pin, int _nvs, int _x, int _dep)
{
  int pin = _pin;
  int nvs = _nvs; // number of arrow in the array
  int x = _x;
  int dep = _dep;
  int t1[2][x];
  int result = 5; // the most repeated value of resultA * x.

  if (dep > 0)
  {

    for (int i = 0; i < x; i++)
    {

      t1[0][i] = GSV(pin, nvs, x, dep - 1);
      t1[1][i] = 0;
    }
  }
  if (dep == 0)
  {

    int INpin;          // store the new analogRead pin
    int values[2][nvs]; // make an array
    int d;              // variabel to store the new data
    // store simplings in the values array
    for (int i = 0; i < nvs; i++)
    {
      INpin = analogRead(pin);
      values[0][i] = INpin;
      values[1][i] = 0;
    }
    // search how many times every simpling value repeated
    for (int i = 0; i < nvs; i++)
    {
      d = values[0][i];
      for (int x = 0; x < nvs; x++)
      {
        if (d == values[0][x])
        {
          values[1][x] += 1;
        }
      }
    }
    d = 0; // return d to 0 to reuse in the next function
    // find the most repeated simpling
    for (int i = 0; i < nvs; i++)
    {
      if (d < values[1][i])
      {
        d = values[1][i];
        result = values[0][i];
      }
    }
  }
  else
  {
    // search how many times every simpling value repeated
    int d;
    for (int i = 0; i < x; i++)
    {
      d = t1[0][i];
      for (int i = 0; i < x; i++)
      {
        if (d == t1[0][i])
        {
          t1[1][i] += 1;
        }
      }
    }
    d = 0; // return d to 0 to reuse in the next function
    // find the most repeated simpling
    for (int i = 0; i < x; i++)
    {
      if (d < t1[1][i])
      {
        d = t1[1][i];
        result = t1[0][i];
      }
    }
  }
  return result;
}
