/*
 Main class to handle the whole program.
*/

#include "Arduino.h"
#include "Program.h"


void Program::Default()
{
	sensors.begin(); //Should be named like tempSonsor or something like that
	Switch::Begin();
	Button::Begin();
	relay.Begin();
	lcd.Begin();
}

void Program::Receive()
{
	String content = "";

	content = serialStr.Read();
	//Serial.print(content);

	if(content != "")
	{
		type = content.substring(0,content.indexOf(","));
		content = content.substring(content.indexOf(",")+1); //Remove the number from the string
		
		if(type == "ip")
		{
			ip = content.substring(0,content.indexOf(","));
			content = "";
		}
		else
		{

			name = content.substring(0,content.indexOf(","));
			content = content.substring(content.indexOf(",")+1);
			check = name.length();
			//Serial.print(name);
			
			checkSum = atol(content.substring(0,content.indexOf(",")).c_str());
			content = content.substring(content.indexOf(",")+1);
			//Serial.print(checkSum);
			
			noSteps = atol(content.substring(0,content.indexOf(",")).c_str());
			content = content.substring(content.indexOf(",")+1);
			//Serial.print(noSteps);

			if(type == "boil")
			{
				totalTime = atol(content.substring(0,content.indexOf(",")).c_str());
				content = content.substring(content.indexOf(",")+1);
				check += totalTime;
			}

			check += noSteps;
			if(type == "mash")
				tempArr = new int[noSteps];
			if(type == "boil")
				hopsArr = new String[noSteps];

			timeArr = new int[noSteps];
			
			for(int j = 0; j < noSteps; j++)
			{
				if(type == "mash")
				{
					tempArr[j] = atol(content.substring(0,content.indexOf(",")).c_str());
					content = content.substring(content.indexOf(",")+1);
					check += tempArr[j];
					//Serial.print(tempArr[j]);
				}
				else if(type == "boil")
			    {
			    	hopsArr[j] = content.substring(0,content.indexOf(","));
				    content = content.substring(content.indexOf(",")+1);
				    check += (hopsArr[j]).length();
			    }

			    timeArr[j] = atol(content.substring(0,content.indexOf(",")).c_str());
			    content = content.substring(content.indexOf(",")+1);
			    check += timeArr[j];
			    //Serial.print(timeArr[j]);
			}
			//Serial.print(check);

			if(check == checkSum)
			{
				loaded = true;	
				Serial.print("Success");
			}
			else
			{
				lcd.failed();
				loaded = false;
				Serial.print("Fail");
			}
		}
	}

	//Serial.print(digitalRead(SWITCHMODE));
	if(digitalRead(SWITCHMODE))
	{
		relay.ReadElements();
		digitalWrite(PUMP, HIGH);
		//digitalWrite(BUZZER, HIGH);
	}
	else
	{
		relay.AllLow();
		//digitalWrite(BUZZER, LOW);
	}

	sensors.requestTemperatures();
	CurrentTemp = sensors.getTempCByIndex(0) + Calibrator;
	lcd.Default(loaded,CurrentTemp,type,ip);

	state = digitalRead(startButton);

	if(loaded && state == HIGH && !digitalRead(SWITCHMODE))
	{
	    running = true;
	    Boil bSchedule(hopsArr, timeArr, totalTime, noSteps);
    	Mash mSchedule(tempArr,timeArr,noSteps); //fyi should be a selection 
    	
	
		while(loaded)
		{
			if(digitalRead(stopButton))
			{
			    running = false;
			    relay.AllLow();
			}

			if(digitalRead(SWITCHMODE))
			{
				running = false;
			}

			if(running)
			{
				if(type == "mash")
				{
					loaded = mSchedule.Start();
				}
				else if(type == "boil")
				{
					loaded = bSchedule.Start();
				}
			}
			else
			{
				if(!digitalRead(stopButton))
				{
					Pause(mSchedule, bSchedule);
				}
			}
		}
	}
}

void Program::Pause(Mash mSchedule, Boil bSchedule)
{
	lcd.paused(CurrentTemp);
	if(second() % 2 == 0) //Updates the temp every two seconds
	{
		sensors.requestTemperatures();
		CurrentTemp = sensors.getTempCByIndex(0) + Calibrator;
	}
	
	if(digitalRead(SWITCHMODE))
	{
		relay.ReadElements();
		digitalWrite(PUMP, HIGH);
		//digitalWrite(BUZZER, HIGH);
	}
	else
	{
		relay.AllLow();
		//digitalWrite(BUZZER, LOW);
	}

	if(digitalRead(startButton) && !digitalRead(SWITCHMODE))
	{
	    running = true;
	    if(type == "mash")
	    	mSchedule.Unpause();
	    else if(type == "boil")
	    	bSchedule.Unpause();
	}
	if (digitalRead(stopButton))
	{
		loaded=false;
		relay.AllLow();
	}
}



