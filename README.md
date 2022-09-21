# getStableValue

get stable value from any input exp: esp32 ADC, arduino... from any sensor or other input.

This function get the most repeated value of a ADC pin by a special algorithm,

you can adjust your result from three parameter :

step1----uint8_t _pin ==> the number of the ADC pin (exp: 35 in esp 32 and A0 in arduino).

step2----int _nvs = 100, ==> number of simplings of anologueRead(pin) you have to read before and get result of (the  most repeated value on them).

step3----int _x = 4 ==> number of loops of (get the most repeated value) from (the most repeated value of the previous chaine (step--3)).

step4----int _dep = 2 ==> number of time you repeat all the previous steps then get a value (_x) times then out a result1.

exemple1: 

if _dep = 2 then the result2 =  _x * result1----> result1 = _x * step3 -----> step3 = _x * step2 -------> step2 = _nvs * analogueRead(pin).
the final result will be result2.
result = the most repeated value.

exemple2: 
getStableValue(35,100,4,2);
result2 =  [4* result1] ====> [result1 = 4 * step3] ====> [step3 = 4 * step2] ====> [step2 = 100 * analogueRead(35)]

100*4*4*4*2 = 12800
it out a stable value from 12800 value.

- it get the most repeated value (resultA) of nvs * analogueRead(pin), and stored in an array (t1).
- then it repeat the previous loops x times, until we have x * result1 in dep1.
- then it get the most repeated value in t1 array (result2) and stored in dep2.
- then it repeat the previous loops x times, until we have x * result2 in dep2.
- then it get the most repeated value in t2 array (result3) and return it.
- then it get the most repeated value in t1 array (result2) and stored in dep..n.
- and so on it repeat the previous loops x times, until we have x * result..n in dep..n.
- then it get the most repeated value in t2 array (result..N) and return it.
