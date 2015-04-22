/*
   Library to have a basic communication with a Serial device.
*/

#include "Arduino.h"
#include "SerialString.h"

// SerialString::SerialString(i) 
// {
	
// }

void SerialString::Print(String str)
{
	Serial.print(str);	
}

String SerialString::Read()
{
	if(Serial.available())
	{
		delay(100);
		String str = Serial.readString();
		return str;
	}
	else
	{
		return "NoSignal";
	}

}

