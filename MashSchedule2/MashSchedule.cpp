/*
Main class to handle the mashshedule
*/

#include "Arduino.h"
#include "MashSchedule.h"

void MashSchedule::Default()
{
	sensors.begin();
	//Send request to get Temperature
	//sensors.requestTemperatures();
	//CurrentTemp = sensors.getTempCByIndex(0);

	pinMode(buttonInput,OUTPUT);
	pinMode(led, OUTPUT);

	lcd.Begin();
	lcd.Print("Waiting for program");
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
			lcd.Print("Paused             ");
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
	CurrentTemp = sensors.getTempCByIndex(0);
	lcd.Print("Current temp: ", 2);
	lcd.Print(String(CurrentTemp), 2, 14);
	lcd.Print(String(degree), 2, 16);
	lcd.Print("C", 2, 17);
	setTime(0,0,0,0,0,0);
	
	state  = digitalRead(buttonInput);

	if(loaded && state == HIGH)
	{
		lcd.Print("                              ", 2);
		

		while(loaded)
		{
			Start();
			
		}
	}
}

void MashSchedule::Start()
{
	
	//sensors.begin(); //Kan kanske bortkommenteras
	
	sensors.requestTemperatures();
	CurrentTemp = sensors.getTempCByIndex(0);
	
	//lcd.Begin();

	

	lcd.Print("Totalt:            ");
	lcd.Print(String(minute()), 0, 7);
	lcd.Print(" min ", 0, 9);
	lcd.Print(String(second()), 0, 14);
	lcd.Print("sek", 0, 16);
	state  = digitalRead(buttonInput);
	
	lcd.Print(String(degree), 1, 11);
	lcd.Print("C ", 1, 0);
	lcd.Print(String(CurrentTemp), 1, 3);
	
	if(flag && CurrentTemp>= 27){
		
		
		t = now();
		digitalWrite(led,LOW);
		flag=false;
	}
	if(CurrentTemp<= 27){
		digitalWrite(led,HIGH);
	
	}
	else{
		digitalWrite(led,LOW);
		
	}
	
	
	aktuell = now()-t;
	
	if (minute(aktuell)==0 && !flag )
	{	
		lcd.Print("Aktuellt:",1);
		lcd.Print(String(CurrentTemp), 1, 9);
		lcd.Print(String(degree), 1, 11);
		lcd.Print("C ", 1, 12);
		lcd.Print(String(second(aktuell)), 1, 14);
		lcd.Print(" sek ", 0, 16);
		
		//if (!flag && CurrentTemp>=27 ){
			//lcd.Print(String(second(aktuell)), 1, 14);
			//lcd.Print("sek", 1, 16);
		//}
		
		if(second()%2==0)
		{
			sensors.requestTemperatures();
			CurrentTemp =sensors.getTempCByIndex(0);
		}
	}
	else if(!flag)
	{	
		lcd.Print("Aktuellt:", 1);
		lcd.Print(String(CurrentTemp), 1, 9);
		lcd.Print(String(degree), 1, 11);
		lcd.Print("C ", 1, 12);
		lcd.Print(String(minute(aktuell)), 1, 14);
		lcd.Print(" min    ", 1, 15);
	if(minute(aktuell)==1 && second(aktuell)==4)
	{
		if(flag_1){
			
			lcd.Print(" test",2);
			t=now();
			flag_1=false;
			//counter++;
		}
	}

	
	
	}
	
	
}
