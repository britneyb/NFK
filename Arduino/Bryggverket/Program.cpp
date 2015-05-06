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
	//if(Serial.available())
	//{
		//content = Serial.readString();
	//}


	if(content != "")
	{
		type = content.substring(0,content.indexOf(","));
		content = content.substring(content.indexOf(",")+1); //Remove the number from the string
		
		name = content.substring(0,content.indexOf(","));
		content = content.substring(content.indexOf(",")+1);
		check = name.length();
		
		checkSum = atol(content.substring(0,content.indexOf(",")).c_str());
		content = content.substring(content.indexOf(",")+1);
		
		noSteps = atol(content.substring(0,content.indexOf(",")).c_str());
		content = content.substring(content.indexOf(",")+1);

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
			Serial.print("Success "+type);
			lcd.loaded();
			loaded = true;	
		}
		else
		{
			Serial.print("Fail");
			lcd.failed();
			loaded = false;
		}
	}

	sensors.requestTemperatures();
	CurrentTemp = sensors.getTempCByIndex(0) + Calibrator;
	lcd.getTemp(2,CurrentTemp);

	state = digitalRead(startButton);

	if(loaded && state == HIGH)
	{
		lcd.Print("                    ", 0); //Just temporary, will instead implement a function clear() on the display class
		lcd.Print("                    ", 1);
		lcd.Print("                    ", 2);

	    running = true;
	    
    	Mash mSchedule(tempArr,timeArr,noSteps); //fyi should be a selection 
    	Boil bSchedule(hopsArr, timeArr, totalTime, noSteps);
	

		while(loaded)
		{
			if(digitalRead(stopButton))
			{
			    running = false;
			    relay.AllLow();
				lcd.Print("Paused              ",3);
			}

			if(running)
			{
				if(type == "mash")
				{
					loaded = mSchedule.Start();
				}
				else if(type == "boil")
				{
					lcd.Print("Hahahahahahahahahaha",0);
					lcd.Print("Det trodde du allt!!",1);
				}
			}
			else
			{
				if(!digitalRead(stopButton))
				{
					Pause(mSchedule);
				}
			}
		}
	}

}

void Program::Pause(Mash mSchedule)
{
	lcd.getTemp(1, CurrentTemp);

	if(second() % 2 == 0) //Updates the temp every two seconds
	{
		sensors.requestTemperatures();
		CurrentTemp = sensors.getTempCByIndex(0) + Calibrator;
	}
	
	if(digitalRead(startButton))
	{
	    running = true;
	    mSchedule.Unpause();
	}
	if (digitalRead(stopButton))
	{
		loaded=false;
		mSchedule.ProgramFinshed();
	}
}



