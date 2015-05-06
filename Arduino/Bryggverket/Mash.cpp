/*
   Main class to handle the mashshedule
*/

#include "Arduino.h"
#include "Mash.h"

Mash::Mash(int* tempArr, int* timeArr, int arrSize)
{
		setTime(0,0,0,0,0,0);
		_steps = arrSize;
		_tempArr = tempArr; //new int [arrSize];
		_timeArr = timeArr;

	    //_temp = 0; //temporary variable for the temperature
		//_time = 1;
		difTime = 0;
		curStarted = false;
	    _step=1;
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

	lcd.step(2, _step, _tempArr[_step-1], _timeArr[_step-1]);

	if(_step < _steps)
	{
		lcd.step(3, _step+1, _tempArr[_step], _timeArr[_step]);
	}

	if(CurrentTemp >= _tempArr[_step-1] && curStarted) //For the relay
	{
		someFlag_2 = true;
		relay.ElementLow();
	}
	else if(CurrentTemp < _tempArr[_step-1] && curStarted)
	{
		relay.Random(someFlag_2);
		someFlag_2 = false;
	}
	else
	{
		relay.ReadElements();
	}

	if(digitalRead(SWITCH5))
	{
		digitalWrite(PUMP, HIGH);
	}
	else
	{
		digitalWrite(PUMP, LOW);
	}

	if(minute(curTime) >= _timeArr[_step-1] && (_steps) > _step && curStarted)
	{
		_step += 1;
		//_temp += 2;
		//_time += 2;
		curStarted = false;
		difTime = 0;

		lcd.Print("                    ",1);
		lcd.Print("                    ",3);
	}

	if(minute(curTime) >= _timeArr[_step-1] && (_steps) == _step && curStarted)
	{	
		ProgramFinshed();
		return false;
	}

	return true;
}

void Mash::Unpause()
{
	Serial.print(String(minute(totTime)));
	Serial.print(String(second(totTime)));
	setTime(totTime);
}

void Mash::ProgramFinshed()
{
	digitalWrite(PUMP,LOW);

	//someFlag_2 = true;
	relay.ElementLow();
	lcd.Print("Waiting for program ",0);
	lcd.Print("                    ",1);
	lcd.Print("                    ",2);
	lcd.Print("                    ",3);
}


