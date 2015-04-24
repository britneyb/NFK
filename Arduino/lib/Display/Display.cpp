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

