#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//Defines our Pin
#define ONE_WIRE_BUS A0
//0x27 is the address for the display controller and 20,4 is the number of characters and rows on the display
LiquidCrystal_I2C lcd(0x27,20,4);
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
float CurrentTemp;
int buttonInput = 2;
int state = LOW; 
// 
const int Calibrator = 3.5;

void setup()
{
	//sets the serial communication
	Serial.begin(9600);
	
	lcd.init();
	lcd.backlight();
	lcd.setCursor(0, 0);
	
	pinMode(buttonInput,OUTPUT);
	sensors.begin();
}

void loop()
{	
	//Send request to get Temperature
	sensors.requestTemperatures();
	state  = digitalRead(buttonInput);
	//clear the screen
	lcd.clear();
	CurrentTemp =sensors.getTempCByIndex(0);
	//CurrentTemp = CurrentTemp -Calibrator;
	
	if(Serial.available())
	{
		lcd.print("Program paused:");
		lcd.setCursor(0,2);
		lcd.print("Program engaged:");
		lcd.setCursor(0,1);
		lcd.print("Current Temp: "); 
		lcd.print(CurrentTemp );
		lcd.print("C");
		
		if (state==HIGH)
		{ 
			lcd.print("Program started");
			delay(2000);			
		}		
	}
	else {
		
		lcd.print("Waiting for program");
		lcd.setCursor(0,1);
		lcd.print("Current Temp: "); 
		lcd.print(CurrentTemp);
	}
}
