/*
 Main class to handle the boilshedule
*/

#include "Arduino.h"
#include "Boil.h"



Boil::Boil(String* hopsArr, int* timeArr, int totalTime, int steps)
{
	_hopsArr = hopsArr;
	//_timeArr = timeArr;

	setTime(0,totalTime,0,0,0,0);
	_totalTime = now();
	_steps = steps;

	for(int i = 0; i < steps; i++)
	{
	    setTime(0,timeArr[i],0,0,0,0);
	    _timeArr[i] = now();
	}

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
		curTime = totTime - difTime;
	}
	
	if(second() % 2 == 0) //Updates the temp every two seconds
	{
		sensors.requestTemperatures();
		CurrentTemp = sensors.getTempCByIndex(0) + Calibrator;
	}

	if(CurrentTemp >= boilingPoint && !curStarted)
	{
		difTime = _timeArr[_step-1];
		setTime(0,0,0,0,0,0);
		curStarted = true;
	}

	lcd.totalTime(totTime);
	lcd.currentTemp(CurrentTemp, curTime, curStarted);

	lcd.step(2, _step, 0, minute(_timeArr[_step-1]),_steps);

	if(_step < _steps)
	{
		lcd.step(3, _step+1, 0, minute(_timeArr[_step]),0);
	}

	if(hour(totTime) < hour(_timeArr[_step-1]) && minute(totTime) < minute(_timeArr[_step-1]) && curStarted)
	{
	    _step++;
	}

}