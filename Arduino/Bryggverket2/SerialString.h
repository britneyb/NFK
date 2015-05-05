/*
 Library to have a basic communication with a Serial device.
*/

#ifndef SerialString_h
#define SerialString_h

#include "Arduino.h"

class SerialString
{
  public:
    //SerialString();
    void Print(String str);
    String Read();
};

#endif