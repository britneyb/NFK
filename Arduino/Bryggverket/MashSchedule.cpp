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

	pinMode(stopButton, OUTPUT);
	pinMode(SWITCH1, OUTPUT);
	pinMode(SWITCH2, OUTPUT);
	pinMode(SWITCH3, OUTPUT);
	pinMode(SWITCH4, OUTPUT);
	pinMode(SWITCH5, OUTPUT);
	pinMode(startButton,OUTPUT);
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
			lcd.Print("Paused              ");
			lcd.Print("Mashschemed uploaded", 1);
			loaded = true;	
		}
		else
		{
			lcd.Print("Fail",1);
			loaded = false;
		}
	}

	sensors.requestTemperatures();
	CurrentTemp = sensors.getTempCByIndex(0) + Calibrator;
	lcd.getTemp(String(CurrentTemp));
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
	    
		while(loaded)
		{
			if(digitalRead(stopButton))
			{
			    running = false;
			    //digitalWrite(PUMP, LOW);
				digitalWrite(RELAY1, LOW);
				digitalWrite(RELAY2, LOW);
				digitalWrite(RELAY3, LOW);
				digitalWrite(RELAY4, LOW);
				lcd.Print("Paused              ",3);
			}

			if(running)
			{
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
	lcd.currentTemp(CurrentTemp);
	//lcd.Print("Aktuellt:", 1);
	//lcd.Print(String(CurrentTemp), 1, 9);
	//lcd.Print(String(degree), 1, 11);
	//lcd.Print("C ", 1, 12);
	//lcd.Print("  ", 1, 14); //we did this later down for minutes

	lcd.Print("Steg ", 2);
	lcd.Print(String(_step), 2, 5);
	lcd.Print(": ",2,6);
	lcd.Print(String(arr[_temp]),2,8);
	lcd.Print("C ",2,10);
	lcd.Print(String(arr[_time]),2,12);
	lcd.Print(" min",2,14);

	if(_step < _steps)
	{
		lcd.Print("Steg ", 3);
		lcd.Print(String(_step+1), 3, 5);
		lcd.Print(": ",3,6);
		lcd.Print(String(arr[_temp+2]),3,8);
		lcd.Print("C ",3,10);
		lcd.Print(String(arr[_time+2]),3,12);
		lcd.Print(" min",3,14);
	}

	if (minute(curTime) <= 0 && curStarted) //Changing between min and sec on the current step
	{
		lcd.Print(String(second(curTime)), 1, 14);
		lcd.Print(" sek", 1, 16);
	}
	else if(curStarted)
	{
		lcd.Print(" ", 1, 15);
		lcd.Print(String(minute(curTime)), 1, 14);
		lcd.Print(" min", 1, 16);
	}

	if(CurrentTemp >= arr[_temp] && curStarted) //For the relay
	{	
		TurnOff();
	}
	else if(CurrentTemp < arr[_temp] && curStarted)
	{
		Random();
	}

	else
	{
		AllOn();
	}

	// if(digitalRead(SWITCH5))
	// {
	// 	digitalWrite(PUMP, HIGH);
	// }
	// else
	// {
	// 	digitalWrite(PUMP, LOW);
	// }

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
	lcd.currentTemp(CurrentTemp);
	if(second() % 2 == 0) //Updates the temp every two seconds
	{
		sensors.requestTemperatures();
		CurrentTemp = sensors.getTempCByIndex(0) + Calibrator;
	}
	if(digitalRead(startButton))
	{
	    running = true;
	    setTime(totTime);
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

void MashSchedule::Random()
{
	if (someFlag_2)
	{
		randNumber = random(4);
		someFlag_2=false;
	}
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
	 		if(randNumber == 0)
	 		{
				digitalWrite(RELAY1,LOW);
	 			randNumber = random(4);
	 			relayOn = true;
	 		}
	 	}
	 	if(stateRelay2 == LOW)
	 	{
	 		if(randNumber == 1)
	 		{
				digitalWrite(RELAY2,LOW);
	 			randNumber = random(4);
	 			relayOn = true;
	 		}
	 	}
	 	if(stateRelay3 == LOW)
	 	{
	 		if(randNumber == 2)
	 		{
				digitalWrite(RELAY3,LOW);
	 			randNumber = random(4);
	 			relayOn = true;
	 		}
	 	}
	 	if(stateRelay4 == LOW)
	 	{
	 		if(randNumber == 3)
	 		{
				digitalWrite(RELAY4,LOW);
	 			randNumber = random(4);
	 			relayOn = true;
	 		}
	 	}
	 }
	switch (randNumber)
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

void MashSchedule::TurnOff()
{
	someFlag_2=true;
	digitalWrite(RELAY1,LOW);
	digitalWrite(RELAY2,LOW);
	digitalWrite(RELAY3,LOW);
	digitalWrite(RELAY4,LOW);
}
