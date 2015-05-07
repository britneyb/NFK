#ifndef Boil_h
#define Boil_h

#include <Time.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal.h>

#include "Arduino.h"
#include "Display.h"
#include "Pins.h"
#include "Relay.h"


class Boil
{

public:
Boil(String* hopsArr, int* timeArr, int totalTime, int steps);
boolean Start();

private:
	OneWire oneWire = OneWire(ONE_WIRE_BUS);
  	DallasTemperature sensors = DallasTemperature(&oneWire); //Pass our oneWire reference to Dallas Temperature.
  	int CurrentTemp; //Stores the current temp
  	Display lcd; //Our display functions
	Relay relay;

	String* _hopsArr;
	time_t* _timeArr;
	time_t _totalTime;
	int _steps;

	time_t totTime; //The total time
	time_t curTime; //The time of the current step
	time_t difTime; //The total time when the current step started
	boolean curStarted;
    int _step;

};


#endif