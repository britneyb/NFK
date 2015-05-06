/*
   Main class to handle the mashshedule
*/

#include "Arduino.h"
#include "Mash.h"

Mash::Mash(int* arr, int arrSize)
{
		setTime(0,0,0,0,0,0);
		_steps = arrSize/2;
		tempTime = arr; //new int [arrSize];

	    _temp = 0; //temporary variable for the temperature
		_time = 1;
		difTime = 0;
		curStarted = false;
	    _step=1;

	    randNum = new int[noRandom];
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

	if(!curStarted && CurrentTemp >= tempTime[_temp]) //Starts counting when the current temp is right
	{		
		difTime = totTime;
		curTime = totTime - difTime;
		curStarted = true;
		someFlag = false;
	}

	lcd.currentTemp(CurrentTemp, curTime, curStarted);

	lcd.step(2, _step, tempTime[_temp], tempTime[_time]);

	if(_step < _steps)
	{
		lcd.step(3, _step+1, tempTime[_temp+2], tempTime[_time+2]);
	}

	if(CurrentTemp >= tempTime[_temp] && curStarted) //For the relay
	{
		someFlag_2 = true;
		Relay::ElementLow();
	}
	else if(CurrentTemp < tempTime[_temp] && curStarted)
	{
		Random();
	}

	else
	{
		Relay::ReadElements();
	}

	if(digitalRead(SWITCH5))
	{
		digitalWrite(PUMP, HIGH);
	}
	else
	{
		digitalWrite(PUMP, LOW);
	}

	if(minute(curTime) >= tempTime[_time] && (_steps) > _step && curStarted)
	{
		_step += 1;
		_temp += 2;
		_time += 2;
		someFlag=true;
		curStarted = false;
		difTime = 0;

		lcd.Print("                    ",1);
		lcd.Print("                    ",3);
	}

	if(minute(curTime) >= tempTime[_time] && (_steps) == _step && curStarted)
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

	someFlag_2 = true;
	Relay::ElementLow();
	lcd.Print("Waiting for program ",0);
	lcd.Print("                    ",1);
	lcd.Print("                    ",2);
	lcd.Print("                    ",3);
}

int Mash::Uniqe()
{
	int temp = random(4);
	int j = 0;
	boolean uniqe = true;

	while(j < noRandom)
	{
		if (temp == randNum[j])
		{
			temp = random(4);
			j = 0;
		}
		else
		{
			j++;
		}
	}

	return temp;
}

void Mash::Random()
{
	if (someFlag_2)
	{
		for (int i = 0; i < noRandom; i++)
		{
			if(i > 0)
				randNum[i] = Uniqe();
			else
				randNum[i] = random(4);
		}

		someFlag_2=false;
	}
	
	for (int i = 0; i < noRandom; i++)
	{
		boolean relayOn = true;

		while(relayOn)
		{
			stateRelay1 = digitalRead((SWITCH1));
			stateRelay2 = digitalRead((SWITCH2));
			stateRelay3 = digitalRead((SWITCH3));
			stateRelay4 = digitalRead((SWITCH4));
			relayOn = false;

			if(stateRelay1 == LOW)
			{
				if(randNum[i] == 0)
				{
					digitalWrite(ELEMENT1,LOW);
					randNum[i] = Uniqe(); //random(4);
					relayOn = true;
				}	
			}
			if(stateRelay2 == LOW)
			{
				if(randNum[i] == 1)
				{
					digitalWrite(ELEMENT2,LOW);
					randNum[i] = Uniqe(); //random(4);
					relayOn = true;
				}	
			}
			if(stateRelay3 == LOW)
			{
				if(randNum[i] == 2)
				{
					digitalWrite(ELEMENT3,LOW);
					randNum[i] = Uniqe(); //random(4);
					relayOn = true;
				}	
			}
			if(stateRelay4 == LOW)
			{
				if(randNum[i] == 3)
				{
					digitalWrite(ELEMENT4,LOW);
					randNum[i] = Uniqe(); //random(4);
					relayOn = true;
				}
			}
		}

		switch (randNum[i])
		{
			case  0:
				digitalWrite(ELEMENT1,HIGH); 
				break;
			case 1:
				digitalWrite(ELEMENT2,HIGH);           // Turns ON Relays 2				         
				break;
			case 2:
				digitalWrite(ELEMENT3,HIGH);           // Turns ON Relays 3
				break;        
			case 3:
				digitalWrite(ELEMENT4,HIGH);           // Turns ON Relays 4
				break;    
		}
	}
}
