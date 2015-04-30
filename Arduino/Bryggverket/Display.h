/*
 Library to print a string to a 20x4 Display and a Display-controller with an address of 0x27
*/

#ifndef Display_h
#define Display_h

#include <Wire.h> 
#include <LiquidCrystal.h>
#include "Arduino.h"

class Display
{
  public:
    Display();
    void Print(String str, int row = 0, int column = 0);
    void Begin();
    void getTemp(String temp);
  private:
  	LiquidCrystal lcd = LiquidCrystal(0x27,20,4);
};

#endif