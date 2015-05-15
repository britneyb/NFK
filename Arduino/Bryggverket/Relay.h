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
	void ReadElements(int noElements = 4);
	void SetRandom(int noRandom);
	void Random(boolean firstRun, int noRandom);
	int Unique(int noRandom);

private:
	int* randNum;	//[noRandom];
	
};


#endif