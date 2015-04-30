#include "MashSchedule.h"
#include <Time.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include "Display.h"
#include "SerialString.h"
#include "Pins.h"

MashSchedule test1;

void setup()
{
  
  	Serial.begin(9600);
	test1.Default();
}

void loop()
{
  	test1.Receive(); 

}
