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
			lcd.print("Mashscheme uploaded ");
		else if(type == "boil")
			lcd.print("Boilscheme uploaded ");
		else if(type == "cooling")
			lcd.print("Coolscheme uploaded ");
	}
	else
	{
		lcd.setCursor(0,0);
		lcd.print("Waiting for program ");
		lcd.setCursor(0,1);
		lcd.print("                    ");
	}
	lcd.setCursor(0,3);
	if(ip != "")
		lcd.print(ip);
	else
		lcd.print("                    ");
	getTemp(2,temp,true);
}

void Display::getTemp(int row, int temp, boolean clear)
{
	lcd.setCursor(0,row);
	lcd.print("Current: ");
 lcd.setCursor(9,row);
 if(temp<10 && temp >-1)
    {lcd.print(" "+String(temp));}
	else
    {lcd.print(String(temp));}
	
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

void Display::programFinished()
{
	lcd.setCursor(0,1);
	lcd.print("Program Finished    ");
	lcd.setCursor(0,2);
	lcd.print("                    ");
	lcd.setCursor(0,3);
	lcd.print("Paused              ");
}

void Display::totalTime(time_t t)
{
	lcd.setCursor(0,0);
	lcd.print("Total: ");

 /*
  * Hour
  */

  if(hour(t)>9)
	{lcd.setCursor(6,0);}
  else
	{lcd.setCursor(7,0);}
 
	lcd.print(String(hour(t)));
	lcd.setCursor(8,0);
	lcd.print(":0 ");
 /*
  * Min
  */
  if(minute(t)>9)
	{lcd.setCursor(9,0);}
  else
  {lcd.setCursor(10,0);}
  
	lcd.print(String(minute(t)));
	lcd.setCursor(11,0);
	lcd.print(":0 ");
 /*
  * Sec
  */
	
	if(second(t)>9)
	{lcd.setCursor(12,0);}
  else
  {lcd.setCursor(13,0);}
  
	lcd.print(String(second(t)));
	lcd.setCursor(14,0);
	lcd.print("       ");
}

void Display::currentTemp(int temp, time_t curTime, boolean started)
{
	getTemp(1,temp,true);

	if(hour(curTime) > 0 && started)
	{
		lcd.setCursor(14,1);
		lcd.print(String(hour(curTime)));
		lcd.setCursor(15,1);
		lcd.print(":");
		lcd.setCursor(17,1);
		lcd.print(" ");
		lcd.setCursor(16,1);
		lcd.print(String(minute(curTime)));
		lcd.setCursor(18,1);
		lcd.print("  ");
	}
	else if(hour(curTime) <= 0 && minute(curTime) > 0 && started) //Changing between min and sec on the current step
	{

     if(minute(curTime)>9)
    {lcd.setCursor(14,1);}
    else
    {
      lcd.setCursor(14,1);
      lcd.print("0");
      lcd.setCursor(15,1);
     }

		lcd.print(String(minute(curTime)));
		lcd.setCursor(16,1);
		lcd.print(" min");
	}
	else if(minute(curTime) <= 0 && started)
	{
     if(second(curTime)>9)
    {lcd.setCursor(14,1);}
    else
    {
      lcd.setCursor(14,1);
      lcd.print("0");
      lcd.setCursor(15,1);
     }
		lcd.print(String(second(curTime)));
		lcd.setCursor(16,1);
		lcd.print(" sek");
	}
}

void Display::cooling(time_t t, int cTemp, int temp)
{
	totalTime(t);
	getTemp(1, cTemp, true);
	lcd.setCursor(0,2);
	lcd.print("Target temp: ");
	lcd.setCursor(13,2);
	lcd.print(temp);
	lcd.setCursor(15,2);
	lcd.print(String(char(223)));//String(degree), 2, 16);
	lcd.setCursor(16,2);
	lcd.print("C   ");
	lcd.setCursor(0,3);
	lcd.print("                    ");
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
		lcd.setCursor(7,row);
		lcd.print(": ");
		if(cTemp != 0)
		{
			lcd.setCursor(9,row);
			lcd.print(String(cTemp));
			lcd.setCursor(11,row);
			lcd.print(String(char(223)));
			lcd.setCursor(12,row);
			lcd.print("C ");


/*
 * Sätt ut tiden
 */
      lcd.setCursor(13,row);    
			if(cTime <= 9)
      {
        
        lcd.print(" 0"+String(cTime));
        lcd.setCursor(16,row);
        lcd.print(" min");
      }
			else if(cTime <= 99)
			{
        lcd.print(" "+String(cTime));
				lcd.setCursor(16,row);
				lcd.print(" min");
			}
			else if(cTime > 99)
			{
        lcd.print(String(cTime));
				lcd.setCursor(16,row);
				lcd.print("min");
			}
		}
		else
		{
			lcd.setCursor(9,row);
			lcd.print(String(cTime));
			lcd.setCursor(11,row);
			lcd.print(" min");
		}
		if(cStep == steps && row == 2)
		{
			lcd.setCursor(0,3);
			lcd.print("                    ");
		}
	}
}
void Display::BootingUp()
{
  lcd.setCursor(2,1);
  lcd.print("Booting up..");
  delay(500);
  lcd.setCursor(2,2); 
  lcd.print("the brewery");
  delay(1000);
}
