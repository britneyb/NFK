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
	Relay::Begin();
	lcd.Begin();
}

void Program::Receive()
{
	String content = "";

	content = serialStr.Read();

	if(content != "")
	{
		int data[maxStep]; //The results will be stored here
		int i = 0;

		while(content != "")
		{
			int index = content.indexOf(",");		//We find the next comma

			if(index < 0)
			{							//När man läst ut allt ur content så ballar index ur, och då breakar vi ur loopen och nollställer content.
				content = "";
				break;
			}

			if(i==0)
			{
				name = content.substring(0,index);
			}
			else
			{
				data[i] = atol(content.substring(0,index).c_str()); //Extract the number
			}

			content = content.substring(index+1); //Remove the number from the string
			i++;
		}

		arrSize = i-2;
		arr = new int [arrSize];
		int check = name.length();
		int checkSum = data[i-1];

		for(int j=0; j < arrSize; j++)
		{
		    arr[j] = data[j+1];
		    check += arr[j];
		}

		if(check == checkSum)
		{
			lcd.loaded();
			loaded = true;	
		}
		else
		{
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
	    Mash mSchedule(arr,arrSize);

		while(loaded)
		{
			if(digitalRead(stopButton))
			{
			    running = false;
			    Relay::AllLow();
				lcd.Print("Paused              ",3);
			}

			if(running)
			{
				loaded = mSchedule.Start();
			}
			else
			{
				if(!digitalRead((stopButton)))
				{
					Pause(mSchedule);
				}
			}
		}
	}

}

void Program::Pause(Mash mash)
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
	    mash.Unpause();
	}

	if (digitalRead(stopButton))
	{
		//digitalWrite(PUMP,LOW);
		//TurnOff();
		loaded=false;
		
		//someFlag_3=false;
		mash.ProgramFinshed();
		
	}
}


void Program::Start()
{

}


