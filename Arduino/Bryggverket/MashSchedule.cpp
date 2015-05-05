/*
   Main class to handle the mashshedule
*/

#include "Arduino.h"
#include "MashSchedule.h"


void MashSchedule::Default()
{
	 //  _temp = 0; //temporary variable for the temperature
		// _time = 1;
		// //_steps = arrSize/2;
		// difTime = 0;
		// curStarted = false;
		
	
	sensors.begin();
	pinMode(RELAY1, OUTPUT);
	pinMode(RELAY2, OUTPUT);
	pinMode(RELAY3, OUTPUT);
	pinMode(RELAY4, OUTPUT);
	pinMode(PUMP, OUTPUT);
	//Send request to get Temperature
	//sensors.requestTemperatures();
	//CurrentTemp = sensors.getTempCByIndex(0);

	pinMode(stopButton, INPUT);
	pinMode(SWITCH1, INPUT);
	pinMode(SWITCH2, INPUT);
	pinMode(SWITCH3, INPUT);
	pinMode(SWITCH4, INPUT);
	pinMode(SWITCH5, INPUT);
	pinMode(startButton,INPUT);
    //pinMode(led, OUTPUT);
    
	lcd.Begin();
	//lcd.Print("Waiting for program");
	//lcd.Print("Current Temp: ", 1); //Bortkommenterad pågrund av att den redan gör detta i funktionen receive()
	//lcd.Print(String(CurrentTemp));	
}

void MashSchedule::Receive()
{
	String content = "";

	/*while (Serial.available()){ 
		content = Serial.readString();
	}*/
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
		_steps = arrSize/2;
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
			//lcd.Print("Paused              ");
			//lcd.Print("Mashschemed uploaded", 1);
			lcd.loaded();
			loaded = true;	
		}
		else
		{
			//lcd.Print("Fail",1);
			lcd.failed();
			loaded = false;
		}
	}

	sensors.requestTemperatures();
	CurrentTemp = sensors.getTempCByIndex(0) + Calibrator;
	lcd.getTemp(2,CurrentTemp);
	//lcd.Print("Current temp: ", 2);
	//lcd.Print(String(CurrentTemp), 2, 14);
	//lcd.Print(String(degree), 2, 16);
	//lcd.Print("C", 2, 17);

	state  = digitalRead(startButton);

	if(loaded && state == HIGH)
	{
		setTime(0,0,0,0,0,0);
		lcd.Print("                    ", 0); //Just temporary, will instead implement a function clear() on the display class
		lcd.Print("                    ", 1);
		lcd.Print("                    ", 2);

	    _temp = 0; //temporary variable for the temperature
		_time = 1;
		//_steps = arrSize/2;
		difTime = 0;
		curStarted = false;
	    _step=1;
	    running = true;
	    randNum = new int[noRandom];
	    
		while(loaded)
		{
			if(digitalRead(stopButton))
			{	
			    running = false;
			    digitalWrite(PUMP, LOW);
				digitalWrite(RELAY1, LOW);
				digitalWrite(RELAY2, LOW);
				digitalWrite(RELAY3, LOW);
				digitalWrite(RELAY4, LOW);
				lcd.Print("Paused              ",3);
			
			}

			if(running)
			{	someFlag_3=true;
				Start();
			}
			else
			{
				if(!digitalRead((stopButton)))
				{
					Pause();
					
				}
			}
		}
	}
}

void MashSchedule::Start()
{	
	totTime = now();
	curTime = totTime - difTime;

	if(second() % 2 == 0) //Updates the temp every two seconds
	{
		sensors.requestTemperatures();
		CurrentTemp = sensors.getTempCByIndex(0) + Calibrator;
	}

	lcd.totalTime(totTime);
	//lcd.Print("Totalt:");
	//lcd.Print(String(minute(totTime)), 0, 7);
	//lcd.Print("min ", 0, 9);
	//lcd.Print("  ", 0, 14);
	//lcd.Print(String(second(totTime)), 0, 14);
	//lcd.Print(" sek", 0, 16);

	if(!curStarted && CurrentTemp >= arr[_temp]) //Starts counting when the current temp is right
	{		
		difTime = totTime;
		curTime = totTime - difTime;
		curStarted = true;
		someFlag = false;
	}
	lcd.currentTemp(CurrentTemp, curTime, curStarted);
	//lcd.Print("Aktuellt:", 1);
	//lcd.Print(String(CurrentTemp), 1, 9);
	//lcd.Print(String(degree), 1, 11);
	//lcd.Print("C ", 1, 12);
	//lcd.Print("  ", 1, 14); //we did this later down for minutes

	lcd.step(2, _step, arr[_temp], arr[_time]);
	// lcd.Print("Steg ", 2);
	// lcd.Print(String(_step), 2, 5);
	// lcd.Print(": ",2,6);
	// lcd.Print(String(arr[_temp]),2,8);
	// lcd.Print("C ",2,10);
	// lcd.Print(String(arr[_time]),2,12);
	// lcd.Print(" min",2,14);

	if(_step < _steps)
	{
		lcd.step(3, _step+1, arr[_temp+2], arr[_time+2]);
		
		// lcd.Print("Steg ", 3);
		// lcd.Print(String(_step+1), 3, 5);
		// lcd.Print(": ",3,6);
		// lcd.Print(String(arr[_temp+2]),3,8);
		// lcd.Print("C ",3,10);
		// lcd.Print(String(arr[_time+2]),3,12);
		// lcd.Print(" min",3,14);
	}
	if(minute(curTime) >= arr[_time] && (_steps) == _step && curStarted)
	{	
		digitalWrite(PUMP,LOW);
		TurnOff();
		loaded=false;
		someFlag_3=false;
		ProgramFinshed();
		
	}

	

	// if (minute(curTime) <= 0 && curStarted) //Changing between min and sec on the current step
	// {
	// 	lcd.Print(String(second(curTime)), 1, 14);
	// 	lcd.Print(" sek", 1, 16);
	// }
	// else if(curStarted)
	// {
	// 	lcd.Print(" ", 1, 15);
	// 	lcd.Print(String(minute(curTime)), 1, 14);
	// 	lcd.Print(" min", 1, 16);
	// }

	if(CurrentTemp >= arr[_temp] && curStarted) //For the relay
	{	
		TurnOff();
	}
	else if(CurrentTemp < arr[_temp] && curStarted && someFlag_3)
	{
		Random();
	}

	else if(someFlag_3)
	{
		AllOn();
	}

	if(digitalRead(SWITCH5) && someFlag_3)
	{
		digitalWrite(PUMP, HIGH);
	}
	else
	{
		digitalWrite(PUMP, LOW);
	}

	if(minute(curTime) >= arr[_time] && (_steps) > _step && curStarted)
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

}

void MashSchedule::Pause()
{
	// lcd.Print("Aktuellt:", 1);
	// lcd.Print(String(CurrentTemp), 1, 9);
	// lcd.Print(String(degree), 1, 11);
	// lcd.Print("C ", 1, 12);
	
	lcd.getTemp(1, CurrentTemp);
	if(second() % 2 == 0) //Updates the temp every two seconds
	{
		sensors.requestTemperatures();
		CurrentTemp = sensors.getTempCByIndex(0) + Calibrator;
	}
	if(digitalRead(startButton))
	{	lcd.Print("           ",3,0);
	    running = true;
	    setTime(totTime);
	}
	else if (digitalRead(stopButton))
	{ digitalWrite(PUMP,LOW);
		TurnOff();
		loaded=false;
		
		someFlag_3=false;
		ProgramFinshed();
		
	}
	
	
}

void MashSchedule::AllOn()
{
	stateRelay1 = digitalRead(SWITCH1);
	stateRelay2 = digitalRead(SWITCH2);
	stateRelay3 = digitalRead(SWITCH3);
	stateRelay4 = digitalRead(SWITCH4);
	if(stateRelay1 == HIGH)
		digitalWrite(RELAY1,HIGH);
	else
		digitalWrite(RELAY1,LOW);
	if(stateRelay2 == HIGH)
		digitalWrite(RELAY2,HIGH);
	else
		digitalWrite(RELAY2,LOW);
	if(stateRelay3 == HIGH)
		digitalWrite(RELAY3,HIGH);
	else
		digitalWrite(RELAY3,LOW);
	if(stateRelay4 == HIGH)
		digitalWrite(RELAY4,HIGH);
	else
		digitalWrite(RELAY4,LOW);
}

int MashSchedule::Uniqe()
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

void MashSchedule::Random()
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
					digitalWrite(RELAY1,LOW);
					randNum[i] = Uniqe(); //random(4);
					relayOn = true;
				}	
			}
			if(stateRelay2 == LOW)
			{
				if(randNum[i] == 1)
				{
					digitalWrite(RELAY2,LOW);
					randNum[i] = Uniqe(); //random(4);
					relayOn = true;
				}	
			}
			if(stateRelay3 == LOW)
			{
				if(randNum[i] == 2)
				{
					digitalWrite(RELAY3,LOW);
					randNum[i] = Uniqe(); //random(4);
					relayOn = true;
				}	
			}
			if(stateRelay4 == LOW)
			{
				if(randNum[i] == 3)
				{
					digitalWrite(RELAY4,LOW);
					randNum[i] = Uniqe(); //random(4);
					relayOn = true;
				}
			}
		}
		switch (randNum[i])
		{
			case  0:
				digitalWrite(RELAY1,HIGH); 
				break;
			case 1:
				digitalWrite(RELAY2,HIGH);           // Turns ON Relays 2				         
				break;
			case 2:
				digitalWrite(RELAY3,HIGH);           // Turns ON Relays 3
				break;        
			case 3:
				digitalWrite(RELAY4,HIGH);           // Turns ON Relays 4
				break;    
		}
	}
}

void MashSchedule::TurnOff()
{
	someFlag_2=true;
	digitalWrite(RELAY1,LOW);
	digitalWrite(RELAY2,LOW);
	digitalWrite(RELAY3,LOW);
	digitalWrite(RELAY4,LOW);
}


void MashSchedule::ProgramFinshed()
{	
	lcd.Print("                    ", 0); //Just temporary, will instead implement a function clear() on the display class
	lcd.Print("                    ", 2);
	lcd.Print("                    ", 1);
	lcd.Print("                    ", 3);
	
	lcd.Print("Whaiting for program",0,0);
	lcd.getTemp(2,_temp);
	
	
	
}