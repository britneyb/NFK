#ifndef Cooling_h
#define Cooling_h

#include <Time.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal.h>

#include "Arduino.h"
#include "Display.h"
#include "Pins.h"
#include "Relay.h"


class Cooling
{

public:
	Cooling(int temp);
	boolean Start();
	void Unpause();
private:
	OneWire oneWire = OneWire(ONE_WIRE_BUS);
  	DallasTemperature sensors = DallasTemperature(&oneWire); //Pass our oneWire reference to Dallas Temperature.
  	int CurrentTemp; //Stores the current temp
  	Display lcd; //Our display functions
	Relay relay;

	time_t totTime; //The total time
	time_t curTime; //The time of the current step
	time_t difTime; //The total time when the current step started

	int _temp; //temporary variable for the temperature
};


#endif