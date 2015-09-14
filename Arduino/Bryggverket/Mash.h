/*
 Main class to handle the mashshedule

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
        time_t elementDelay; //number of seconds the elements have been on since last turn on.
        
	boolean randomOnce=true;
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
