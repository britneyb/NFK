#include "Program.h"
#include "Mash.h"
#include "Boil.h"
#include "Cooling.h"
#include "Button.h"
#include "Relay.h"
#include "Switch.h"
#include <Time.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include "Display.h"
#include "SerialString.h"
#include "Pins.h"

Program test1;

void setup()
{
  
  	Serial.begin(9600);
	test1.Default();
}

void loop()
{
  	test1.Receive(); 

}
