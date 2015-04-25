/*
 Main class to handle the mashshedule
 Example for a scheme: Dipa2,56,15,65,20,70,10,85,30,356,
*/

#ifndef MashSchedule_h
#define MashSchedule_h

#include "Arduino.h"
#include <Time.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "Display.h"
#include "SerialString.h"

//Defines our Pin
#define ONE_WIRE_BUS A0

class MashSchedule
{
  public:
    void Default();
    void Receive();
    void Start();
  private:

  	Display lcd; //Our display functions
  	SerialString serialStr; //Our Serial functions

  	OneWire oneWire = OneWire(ONE_WIRE_BUS);

  	DallasTemperature sensors = DallasTemperature(&oneWire); //Pass our oneWire reference to Dallas Temperature.

  	int maxStep = 32; //The max number of steps that can be received

  	const int Calibrator = 3.5; //Calibration for the temp-sensor
	int CurrentTemp; //Stores the current temp
	char degree = char(223); //To get the right Celcius-symbol
	String name = ""; //The name for the scheme
	int* arr = 0; //Array that stores the values of time and temp 
	int arrSize; //Stores the number of steps in the current scheme
	boolean loaded = false; //A flag to check if the scheme has been loaded or not 
	int state = LOW; //Stores the input if the button is pressed or not
	int buttonInput = 2; //The pin where the button is connected
	int led = 7; //The pin where the led is connected

	time_t totTime = 0; //The total time
	time_t curTime = 0; //The time of the current step
	time_t difTime = 0; //The total time when the current step started

	boolean curStarted = false; //A flag to check whether the current step has started
	int temp = 27; //temporary variable for the temperature
};

#endif
