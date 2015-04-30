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

