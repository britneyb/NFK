/*
 Class to handle all the Relays
*/

#include "Arduino.h"
#include "Relay.h"


void Relay::Begin()
{
	pinMode(RELAY1, OUTPUT);
	pinMode(RELAY2, OUTPUT);
	pinMode(RELAY3, OUTPUT);
	pinMode(RELAY4, OUTPUT);
	pinMode(PUMP, OUTPUT);
}

void Relay::AllLow()
{
	digitalWrite(PUMP, LOW);
	digitalWrite(RELAY1, LOW);
	digitalWrite(RELAY2, LOW);
	digitalWrite(RELAY3, LOW);
	digitalWrite(RELAY4, LOW);
}
