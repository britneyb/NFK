#include <Time.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "Program.h"
#include "Mash.h"
#include "Boil.h"
#include "Cooling.h"
#include "Display.h"
#include "SerialString.h"
#include "Pins.h"
#include "Button.h"
#include "Relay.h"
#include "Switch.h"

Program schedule;

void setup()
{
  	Serial.begin(9600);
	schedule.Default();
}

void loop()
{
  	schedule.Receive(); 
}
