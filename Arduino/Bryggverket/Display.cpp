/*
   Library to print a string to a 20x4 Display and a Display-controller with an address of 0x27
*/

#include "Arduino.h"
#include "Display.h"

Display::Display() 
{
 	
}

void Display::Print(String str, int row, int column)
{
	lcd.setCursor(column, row);
	lcd.print(str);
}

void Display::Begin()
{
	lcd.init(); 
	lcd.backlight();
	lcd.setCursor(0, 0); 
	lcd.clear(); 
}

void Display::Default(boolean loaded, int temp, String type, String ip)
{
	if(loaded)
	{
		lcd.setCursor(0,0);
		lcd.print("Paused              ");
		lcd.setCursor(0,1);
		if(type == "mash")
			lcd.print("Mashschemed uploaded");
		else if(type == "boil")
			lcd.print("Boilschemed uploaded");
	}
	else
	{
		lcd.setCursor(0,0);
		lcd.print("Waiting for program ");
		lcd.setCursor(0,1);
		lcd.print("                    ");
	}
	lcd.setCursor(0,3);
	lcd.print(ip);
	getTemp(2,temp,true);
}

void Display::getTemp(int row, int temp, boolean clear)
{
	lcd.setCursor(0,row);
	lcd.print("Current: ");
	lcd.setCursor(9,row);
	lcd.print(String(temp));
	lcd.setCursor(11,row);
	lcd.print(String(char(223)));//String(degree), 2, 16);
	lcd.setCursor(12,row);
	lcd.print("C");
	if(clear)
	{
		lcd.setCursor(13,row);
		lcd.print("       ");
	}
}

void Display::failed()
{
	lcd.setCursor(0,1);
	lcd.print("Fail                ");
}

void Display::paused(int temp)
{
	getTemp(1,temp);
	lcd.setCursor(0,3);
	lcd.print("Paused              ");
}

void Display::totalTime(time_t t)
{
	lcd.setCursor(0,0);
	lcd.print("Total: ");
	lcd.setCursor(7,0);
	lcd.print(String(minute(t)));
	lcd.setCursor(10,0);
	lcd.print("min   ");
	lcd.setCursor(14,0);
	lcd.print(String(second(t)));
	lcd.setCursor(16,0);
	lcd.print(" sek");
}

void Display::currentTemp(int temp, time_t curTime, boolean started)
{
	getTemp(1,temp,true);

	if (minute(curTime) <= 0 && started) //Changing between min and sec on the current step
	{
		lcd.setCursor(14,1);
		lcd.print(String(second(curTime)));
		lcd.setCursor(16,1);
		lcd.print(" sek");
	}
	else if(started)
	{
		lcd.setCursor(15,1);
		lcd.print(" ");
		lcd.setCursor(14,1);
		lcd.print(String(minute(curTime)));
		lcd.setCursor(16,1);
		lcd.print(" min");
	}
}

void Display::step(int row, int cStep, int cTemp, int cTime, int steps)
{
	if(cTemp == 0 && cStep > steps)
	{
		lcd.setCursor(0,2);
		lcd.print("                    ");
		lcd.setCursor(0,3);
		lcd.print("                    ");
	}
	else
	{
		lcd.setCursor(0,row);
		lcd.print("Step ");
		lcd.setCursor(5,row);
		lcd.print(String(cStep));
		lcd.setCursor(6,row);
		lcd.print(": ");
		if(cTemp != 0)
		{
			lcd.setCursor(8,row);
			lcd.print(String(cTemp));
			lcd.setCursor(10,row);
			lcd.print(String(char(223)));
			lcd.setCursor(11,row);
			lcd.print("C ");
			lcd.setCursor(13,row);
			lcd.print(String(cTime));
			lcd.setCursor(15,row);
			lcd.print(" min");
		}
		else
		{
			lcd.setCursor(8,row);
			lcd.print(String(cTime));
			lcd.setCursor(10,row);
			lcd.print(" min");
		}
		if(cStep == steps && row == 2)
		{
			lcd.setCursor(0,3);
			lcd.print("                    ");
		}
	}
}