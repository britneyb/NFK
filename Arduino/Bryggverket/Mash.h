/*
 Main class to handle the mashshedule
 
Example Mash: mash,Demo,128,4,25,1,27,1,30,2,32,2
mash,Demo,60,2,25,1,27,1

Example Boil: boil,Dipa,210,3,60,HumleX,60,HumleY,55,HumleZ,10
boil,Dipa,208,3,59,HumleX,59,HumleY,55,HumleZ,10

*/

#ifndef Mash_h
#define Mash_h

#include <Time.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal.h>

#include "Arduino.h"
#include "Display.h"
#include "Pins.h"
#include "Relay.h"

class Mash
{
  public:
    Mash(int* tempArr, int* timeArr, int arrSize);
    boolean Start();
    void Unpause();
    void ProgramFinshed();

  private:
	OneWire oneWire = OneWire(ONE_WIRE_BUS);
  	DallasTemperature sensors = DallasTemperature(&oneWire); //Pass our oneWire reference to Dallas Temperature.
  	
	int CurrentTemp; //Stores the current temp
  	long randNumber;

	Display lcd; //Our display functions
	Relay relay;
	
	int statePump;
	
	time_t totTime; //The total time
	time_t curTime; //The time of the current step
	time_t difTime; //The total time when the current step started

	boolean someFlag_2=true;
	boolean curStarted; //A flag to check whether the current step has started
	
	int _temp; //temporary variable for the temperature
	int _time;
	int _step;
	int _steps;

	int* _tempArr; //Just temporary
	int* _timeArr;
};

#endif
