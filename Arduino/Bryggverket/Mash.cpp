/*
   Main class to handle the mashshedule
*/

#include "Arduino.h"
#include "Mash.h"

Mash::Mash(int id, int* tempArr, int* timeArr, int arrSize, int elHeating, int elRandom)
{
	setTime(0,0,0,0,0,0);
	_steps = arrSize;
	_tempArr = tempArr; //new int [arrSize];
	_timeArr = timeArr;
	_id = id;
	difTime = 0;
	curStarted = false;
    _step=1;
    lcd.Begin();
    sensors.requestTemperatures();
	CurrentTemp = sensors.getTempCByIndex(0) + Calibrator;

	_elHeating = elHeating;
	_elRandom = elRandom;
	relay.SetRandom(_elRandom);
        elementDelay=now();
      
}

boolean Mash::Start()
{	
	totTime = now();
	curTime = totTime - difTime;

	if(second() % 2 == 0) //Updates the temp every two seconds
	{
		sensors.requestTemperatures();
		CurrentTemp = sensors.getTempCByIndex(0) + Calibrator;
	}

	lcd.totalTime(totTime);

	if(!curStarted && CurrentTemp >= _tempArr[_step-1]) //Starts counting when the current temp is right
	{
		difTime = totTime;
		curTime = totTime - difTime;
		curStarted = true;
	}

	lcd.currentTemp(CurrentTemp, curTime, curStarted);

	lcd.step(2, _step, _tempArr[_step-1], _timeArr[_step-1],_steps);

	if(_step < _steps)
	{
		lcd.step(3, _step+1, _tempArr[_step], _timeArr[_step],0);
	}
	if(CurrentTemp >= _tempArr[_step-1] && curStarted)//For the relay
	{
		randomOnce = true;
                if((elementDelay + 30) <= now()) //the element must not turn on and off if the temp is around the goaltemp. make a delay on 30 sec.
		  relay.ElementLow();
                
	}
	else if(CurrentTemp < _tempArr[_step-1] && curStarted)
	{
		relay.Random(randomOnce, _elRandom);
		randomOnce = false;
                elementDelay = now();
                
	}
	else
	{
		relay.ReadElements(_elHeating);
	}

	digitalWrite(PUMP, HIGH);

	if(second() == 1)
	{
		int check = _id+minute(totTime)+hour(totTime)*60+CurrentTemp;
		Serial.print("mash,"+String(_id)+",0,"+String(minute(totTime)+hour(totTime)*60)+","+CurrentTemp+","+String(check)+"/");
	}

	if(minute(curTime) >= _timeArr[_step-1] && (_steps) > _step && curStarted)
	{
		_step += 1;
		curStarted = false;
		difTime = 0;
	}

	if(minute(curTime) >= _timeArr[_step-1] && (_steps) == _step && curStarted)
	{
		relay.AllLow();
		digitalWrite(BUZZER, HIGH);
		delay(500);
		digitalWrite(BUZZER, LOW);
		int check = _id+minute(totTime)+hour(totTime)*60+CurrentTemp;
		Serial.print("mash,"+String(_id)+",0,"+String(minute(totTime)+hour(totTime)*60)+","+CurrentTemp+","+String(check)+"/");
		return false;
	}

	return true;
}

void Mash::Unpause()
{
	setTime(totTime);
}
