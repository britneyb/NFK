/*
   Main class to handle the coolingshedule
*/

#include "Arduino.h"
#include "Cooling.h"

Cooling::Cooling(int temp)
{
	setTime(0,0,0,0,0,0);
	_temp = temp;

    lcd.Begin();
    sensors.requestTemperatures();
	CurrentTemp = sensors.getTempCByIndex(0) + Calibrator;
}

boolean Cooling::Start()
{
	totTime = now();

	if(second() % 2 == 0) //Updates the temp every two seconds
	{
		sensors.requestTemperatures();
		CurrentTemp = sensors.getTempCByIndex(0) + Calibrator;
	}

	lcd.cooling(totTime, CurrentTemp, _temp);

	digitalWrite(COOLINGPUMP,HIGH);

	if(CurrentTemp <= _temp)
	{
		relay.AllLow();
		return false;
	}

	return true;
}

void Cooling::Unpause()
{
	setTime(totTime);
}