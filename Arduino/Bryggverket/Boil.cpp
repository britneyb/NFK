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
	curTime = totTime - _timeArr[0];
	curStarted = false;
	moreSteps = true;
    _step=1;

    lcd.Begin();
    sensors.requestTemperatures();
	CurrentTemp = sensors.getTempCByIndex(0) + Calibrator;
}

boolean Boil::Start()
{
	if (curStarted)
	{
		_now = now();
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
		setTime(0,0,0,0,0,0);
		difTime = _timeArr[_step-1] - now();
		randomOnce = true;
		curStarted = true;
	}

	lcd.totalTime(totTime);
	lcd.currentTemp(CurrentTemp, curTime, moreSteps);

	
	lcd.step(2, _step, 0, minute(_timeArr[_step-1]),_steps);

	if(_step < _steps)
	{
		lcd.step(3, _step+1, 0, minute(_timeArr[_step]),_steps);
	}

	if(CurrentTemp < boilingPoint && curStarted)
	{
		relay.Random(randomOnce);
		randomOnce = false;
	}
	else if (CurrentTemp < boilingPoint)
	{
		relay.ReadElements();
	}
	else if(CurrentTemp >= boilingPoint)
	{
		relay.ElementLow();
		randomOnce = true;
	}

	if(hour(totTime) <= hour(_timeArr[_step-1]) && minute(totTime) < minute(_timeArr[_step-1]) && _step < _steps && curStarted)
	{
	    _step++;
	    time_t temp = now();
	    setTime(0,0,0,0,0,0);
	    difTime = _timeArr[_step-1] - now();
	    setTime(temp);
	}

	if(hour(totTime) <= hour(_timeArr[_step-1]) && minute(totTime) < minute(_timeArr[_step-1]) && curStarted && _steps == _step)
	{
		_step++;
		moreSteps = false;
	}

	if(hour(totTime) <= 0 && minute(totTime) <= 0 && second(totTime) <= 0)
	{
		relay.AllLow();
	    return false;
	}
	return true;

}

void Boil::Unpause()
{
	setTime(_now);
}