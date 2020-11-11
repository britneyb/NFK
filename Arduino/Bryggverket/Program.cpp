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
	pinMode(BUZZER, OUTPUT);
  lcd.BootingUp();
}

void Program::Receive()
{

	String content = "";

	content = serialStr.Read();

	if(content != "")
	{
		type = content.substring(0,content.indexOf(","));
		content = content.substring(content.indexOf(",")+1); //Remove the number from the string
		
		if(type == "ip")
		{
			ip = content.substring(0,content.indexOf(","));
			content = "";
		}
		else if(type == "cooling")
		{
			name = content.substring(0,content.indexOf(","));
			content = content.substring(content.indexOf(",")+1);
			check = name.length();

			id = atol(content.substring(0,content.indexOf(",")).c_str());
			content = content.substring(content.indexOf(",")+1);

			checkSum = atol(content.substring(0,content.indexOf(",")).c_str());
			content = content.substring(content.indexOf(",")+1);

			coolingTemp = atol(content.substring(0,content.indexOf(",")).c_str());
			content = content.substring(content.indexOf(",")+1);
			check += coolingTemp;

			if(check == checkSum)
			{
				loaded = true;
			}
			else
			{
				lcd.failed();
				loaded = false;
			}
		}
		else
		{

			name = content.substring(0,content.indexOf(","));
			content = content.substring(content.indexOf(",")+1);
			check = name.length();

			id = atol(content.substring(0,content.indexOf(",")).c_str());
			content = content.substring(content.indexOf(",")+1);

			elHeating = atol(content.substring(0,content.indexOf(",")).c_str());
			content = content.substring(content.indexOf(",")+1);

			elRandom = atol(content.substring(0,content.indexOf(",")).c_str());
			content = content.substring(content.indexOf(",")+1);
			
			checkSum = atol(content.substring(0,content.indexOf(",")).c_str());
			content = content.substring(content.indexOf(",")+1);
			
			noSteps = atol(content.substring(0,content.indexOf(",")).c_str());
			content = content.substring(content.indexOf(",")+1);
			check += noSteps;

			if(type == "boil")
			{
				boilTemp = atol(content.substring(0,content.indexOf(",")).c_str());
				content = content.substring(content.indexOf(",")+1);
				check += boilTemp;

				totalTime = atol(content.substring(0,content.indexOf(",")).c_str());
				content = content.substring(content.indexOf(",")+1);
				check += totalTime;
			}

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
			}

			if(check == checkSum)
			{
				loaded = true;
			}
			else
			{
				lcd.failed();
				loaded = false;
			}
		}
	}

	if(digitalRead(SWITCHMODE))
	{
		relay.ReadElements();
		digitalWrite(PUMP, HIGH);
		digitalWrite(COOLINGPUMP, HIGH);
	}
	else
	{
		relay.AllLow();
	}

	sensors.requestTemperatures();
	CurrentTemp = sensors.getTempCByIndex(0) + Calibrator;
	lcd.Default(loaded,CurrentTemp,type,ip);

	state = digitalRead(startButton);

	if(loaded && state == HIGH && !digitalRead(SWITCHMODE))
	{
	    running = true;
	    Boil bSchedule(id, hopsArr, timeArr, boilTemp, totalTime, noSteps, elHeating, elRandom);
    	Mash mSchedule(id, tempArr,timeArr,noSteps, elHeating, elRandom); //fyi should be a selection 
    	Cooling cSchedule(id, coolingTemp);
	
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
				else if(type == "cooling")
				{
					loaded = cSchedule.Start();
				}
			}
			else
			{
				if(!digitalRead(stopButton))
				{
					Pause(mSchedule, bSchedule, cSchedule);
				}
			}
		}
		if(running)
		{
			ProgramFinished();
		}
	}
}

void Program::Pause(Mash mSchedule, Boil bSchedule, Cooling cSchedule)
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
		digitalWrite(COOLINGPUMP, HIGH);
	}
	else
	{
		relay.AllLow();
	}

	if(digitalRead(startButton) && !digitalRead(SWITCHMODE))
	{
	    running = true;
	    if(type == "mash")
	    	mSchedule.Unpause();
	    else if(type == "boil")
	    	bSchedule.Unpause();
	    else if(type == "cooling")
	    	cSchedule.Unpause();
	}
	if (digitalRead(stopButton))
	{
		loaded=false;
		relay.AllLow();
	}
}

void Program::ProgramFinished()
{
	while(!digitalRead(stopButton))
	{
		lcd.programFinished();
	}
}
