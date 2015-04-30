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
	lcd.print("Waiting for program");
}

void Display::getTemp(String temp)
{
	lcd.setCursor(0,2);
	lcd.print("Current temp: ");
	lcd.setCursor(14,2);
	lcd.print(temp);
	lcd.setCursor(16,2);
	lcd.print(String(char(223)));//String(degree), 2, 16);
	lcd.setCursor(17,2);
	lcd.print("C");
}

void Display::loaded()
{
	lcd.print("Paused              ");
	lcd.setCursor(0,1);
	lcd.print("Mashschemed uploaded");
}

void Display::failed()
{
	lcd.setCursor(0,1);
	lcd.print("Fail                ");
}

void Display::totalTime(time_t t)
{
	lcd.setCursor(0,0);
	lcd.print("Totalt:");
	lcd.setCursor(7,0);
	lcd.print(String(minute(t)));
	lcd.setCursor(9,0);
	lcd.print("min   ");
	lcd.setCursor(14,0);
	lcd.print(String(second(t)));
	lcd.setCursor(16,0);
	lcd.print(" sek");
}

void Display::currentTemp(int temp)
{
	lcd.setCursor(0,1);
	lcd.print("Aktuellt:");
	lcd.setCursor(9,1);
	lcd.print(String(temp));
	lcd.setCursor(11,1);
	lcd.print(String(char(223)));
	lcd.setCursor(12,1);
	lcd.print("C ");
}