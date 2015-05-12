#include "Arduino.h"

#define ONE_WIRE_BUS A0
#define ELEMENT1 A1//the pin where the relay is connected
#define ELEMENT2 A2//the pin where the relay is connected
#define ELEMENT3 A3//the pin where the relay is connected
#define ELEMENT4 9//the pin where the relay is connected

#define startButton 2 //The pin where the button is connected
#define stopButton 3

#define SWITCHMODE 4
#define SWITCH1 5
#define SWITCH2 6
#define SWITCH3 7
#define SWITCH4 8
//#define SWITCH5 9
#define PUMP 10
#define COOLINGPUMP 11 //Not yet implemented

#define BUZZER 12

#define boilingPoint 25
#define maxStep 32 //The max number of steps that can be received
#define degree char(223) //To get the right Celcius-symbol

#define Calibrator 0 //Calibration for the temp-sensor
#define noRandom 2