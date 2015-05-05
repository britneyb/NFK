/*
 Main class to handle the whole program.
*/

#ifndef Program_h
#define Program_h

#include "Arduino.h"
#include "Mash.h"
#include "Boil.h"
#include "Cooling.h"

#include "Button.h"
#include "Switch.h"
#include "Relay.h"

#include <OneWire.h>
#include <DallasTemperature.h>
#include "Display.h"
#include "SerialString.h"
#include "Pins.h"


class Program
{

public:
    void Default();
    void Receive();
    void Start();
    void Pause();

private:
  	OneWire oneWire = OneWire(ONE_WIRE_BUS);
  	DallasTemperature sensors = DallasTemperature(&oneWire); //Pass our oneWire reference to Dallas Temperature.

  	Display lcd; //Our display functions
  	SerialString serialStr; //Our Serial functions
	String name = ""; //The name for the scheme
	Mash mSchedule;

	int* arr; //Array that stores the values of time and temp 
	int arrSize; //Stores the number of steps in the current scheme
	boolean loaded; //A flag to check if the scheme has been loaded or not 
	int CurrentTemp; //Stores the current temp
	int state; //Stores the input if the button is pressed or not
	boolean running;

};













#endif