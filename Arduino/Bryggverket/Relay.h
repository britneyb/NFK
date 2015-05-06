/*
 Class to handle all the relays
*/


#ifndef Relay_h
#define Relay_h

#include "Arduino.h"
#include "Pins.h"


class Relay
{

public:
	static void Begin();
	static void AllLow();
	static void ElementLow();
	static void ReadElements();

private:
	
};


#endif