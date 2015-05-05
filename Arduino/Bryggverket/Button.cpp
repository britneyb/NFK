/*
 Class to handle all the buttons
*/

#include "Arduino.h"
#include "Button.h"


void Button::Begin()
{
	pinMode(stopButton, INPUT);
	pinMode(startButton,INPUT);
}
