/*
 Class to handle all the switches
*/

#include "Arduino.h"
#include "Switch.h"


void Switch::Begin()
{
	pinMode(SWITCH1, INPUT);
	pinMode(SWITCH2, INPUT);
	pinMode(SWITCH3, INPUT);
	pinMode(SWITCH4, INPUT);
	pinMode(SWITCH5, INPUT);
}
