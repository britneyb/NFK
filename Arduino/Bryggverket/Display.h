/*
 Library to print a string to a 20x4 Display and a Display-controller with an address of 0x27
*/

#ifndef Display_h
#define Display_h

#include <Wire.h> 
#include <LiquidCrystal.h>
#include <Time.h>
#include "Arduino.h"

class Display
{
  public:
    Display();
    void Print(String str, int row = 0, int column = 0);
    void Begin();
    void Default(boolean loaded, int temp, String type, String ip);
    void getTemp(int row, int temp, boolean clear = false);
    void failed();
    void paused(int temp);
    void totalTime(time_t time);
    void currentTemp(int temp, time_t curTime, boolean started);
    void step(int row, int cStep, int cTemp, int cTime, int steps);
  private:
  	LiquidCrystal lcd = LiquidCrystal(0x27,20,4);
};

#endif