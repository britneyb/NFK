/*
 Main class to handle the mashshedule
 
Example Mash: mash,Demo,128,4,25,1,27,1,30,2,32,2
mash,Demo,60,2,25,1,27,1
mash,Demo15,3,2,852,16,25,10,26,15,27,20,28,25,29,30,30,10,31,20,32,25,33,15,34,30,35,20,36,5,37,25,38,15,39,5,40,40,
mash,testa1,4,1,273,5,21,10,21,10,25,10,21,10,25,109,

Example Boil: boil,Dipa,210,3,60,HumleX,60,HumleY,55,HumleZ,10
boil,Dipa,208,3,59,HumleX,59,HumleY,55,HumleZ,10
boil,Test,241,3,60,bu1,57,bu2,55,bu3,53
boil,Demo,45,3,7,HumleX,6,HumleY,4,HumleZ,3
boil,Dipa2,4,3,267,5,60,HumleX,60,HumleY,55,HumleZ,10,KryddaX,10,KryddaY,30,

Example Cooling: cooling,Dipa,16,12,

*/

#ifndef Mash_h
#define Mash_h

#include <Time.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "Arduino.h"
#include "Display.h"
#include "Pins.h"
#include "Relay.h"

class Mash
{
  public:
    Mash(int id, int* tempArr, int* timeArr, int arrSize, int elHeating, int elRandom);
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
	int _id;
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

	int _elHeating;
    int _elRandom;
};

#endif
