/*
 Main class to handle the boilshedule
*/

#include "Arduino.h"
#include "Boil.h"



Boil::Boil(String* hopsArr, int* timeArr, int totalTime, int steps)
{
	_hopsArr = hopsArr;
	_timeArr = timeArr;

	setTime(0,totalTime,0,0,0,0);
	_totalTime = now();
	_steps = steps;

	totTime = _totalTime;
	curStarted = false;
    _step=1;

    lcd.Begin();
    sensors.requestTemperatures();
	CurrentTemp = sensors.getTempCByIndex(0) + Calibrator;
}

boolean Boil::Start()
{
	if (curStarted)
	{
		totTime = _totalTime - now();
	}
	
	if(second() % 2 == 0) //Updates the temp every two seconds
	{
		sensors.requestTemperatures();
		CurrentTemp = sensors.getTempCByIndex(0) + Calibrator;
	}

	if(CurrentTemp >= boilingPoint && !curStarted)
	{
		setTime(0,0,0,0,0,0);
		curStarted = true;
	}

	lcd.totalTime(totTime);
	lcd.currentTemp(CurrentTemp, 0, curStarted);

	lcd.step(2, _step, 0, _timeArr[_step-1],_steps);
}