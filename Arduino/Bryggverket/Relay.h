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
	void Begin();
	void AllLow();
	void ElementLow();
	void ReadElements();
	void Random(boolean firstRun);
	int Unique();

private:
	int randNum[noRandom];
	
};


#endif