/*
 Class to handle all the Relays
*/

#include "Arduino.h"
#include "Relay.h"


void Relay::Begin()
{
	pinMode(ELEMENT1, OUTPUT);
	pinMode(ELEMENT2, OUTPUT);
	pinMode(ELEMENT3, OUTPUT);
	pinMode(ELEMENT4, OUTPUT);
	pinMode(PUMP, OUTPUT);
}

void Relay::AllLow()
{
	digitalWrite(PUMP, LOW);
	digitalWrite(ELEMENT1, LOW);
	digitalWrite(ELEMENT2, LOW);
	digitalWrite(ELEMENT3, LOW);
	digitalWrite(ELEMENT4, LOW);
}

void Relay::ElementLow()
{
	digitalWrite(ELEMENT1, LOW);
	digitalWrite(ELEMENT2, LOW);
	digitalWrite(ELEMENT3, LOW);
	digitalWrite(ELEMENT4, LOW);
}

void Relay::ReadElements()
{
	int stateRelay1 = digitalRead(SWITCH1);
	int stateRelay2 = digitalRead(SWITCH2);
	int stateRelay3 = digitalRead(SWITCH3);
	int stateRelay4 = digitalRead(SWITCH4);

	if(stateRelay1 == HIGH)
		digitalWrite(ELEMENT1,HIGH);
	else
		digitalWrite(ELEMENT1,LOW);
	if(stateRelay2 == HIGH)
		digitalWrite(ELEMENT2,HIGH);
	else
		digitalWrite(ELEMENT2,LOW);
	if(stateRelay3 == HIGH)
		digitalWrite(ELEMENT3,HIGH);
	else
		digitalWrite(ELEMENT3,LOW);
	if(stateRelay4 == HIGH)
		digitalWrite(ELEMENT4,HIGH);
	else
		digitalWrite(ELEMENT4,LOW);
}


