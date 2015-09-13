/*
 Main class to handle the whole program.
*/

#ifndef Program_h
#define Program_h

#include <OneWire.h>
#include <DallasTemperature.h>

#include "Arduino.h"
#include "Mash.h"
#include "Boil.h"
#include "Cooling.h"
#include "Display.h"
#include "SerialString.h"
#include "Pins.h"
#include "Button.h"
#include "Switch.h"
#include "Relay.h"


class Program
{

public:
    void Default();
    void Receive();
    void Pause(Mash mSchedule, Boil bSchedule, Cooling cSchedule);
    void ProgramFinished();

private:
  	OneWire oneWire = OneWire(ONE_WIRE_BUS);
  	DallasTemperature sensors = DallasTemperature(&oneWire); //Pass our oneWire reference to Dallas Temperature.

  	Display lcd; //Our display functions
    Relay relay; //Our relay functions 
  	SerialString serialStr; //Our Serial functions

    String type;
    String name;
    int checkSum;
    int noSteps;
    int totalTime;
    int check;
    String ip;
    int elHeating;
    int elRandom;
    int id;
    int boilTemp;

  	int arrSize; //Stores the number of steps in the current scheme
  	boolean loaded; //A flag to check if the scheme has been loaded or not 
  	int CurrentTemp; //Stores the current temp
  	int state; //Stores the input if the button is pressed or not
  	boolean running;

    int* tempArr;
    int* timeArr;
    String* hopsArr;
    int coolingTemp;
};













#endif