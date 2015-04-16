#include <Wire.h>
#include <LiquidCrystal_I2C.h>
/*
 * Sketch1.ino
 *
 * Created: 4/14/2015 8:25:40 AM
 * Author: Sebastian
 */ 

LiquidCrystal_I2C lcd(0x27,20,4);

void setup()
{
	  /* add setup code here, setup code runs once when the processor starts */
	lcd.init();
	lcd.backlight();
	lcd.setCursor(0,0);
	lcd.print("Hello World");
}

void loop()
{
	  /* add main program code here, this code starts again each time it ends */
}
