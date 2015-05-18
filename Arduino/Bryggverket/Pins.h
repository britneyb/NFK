#include "Arduino.h"

#define ONE_WIRE_BUS A0

#define PUMP A1
#define COOLINGPUMP A2 //Not yet implemented
#define BUZZER A3

#define startButton 2 //The pin where the button is connected
#define stopButton 3

#define SWITCH1 4
#define SWITCH2 5
#define SWITCH3 6
#define SWITCH4 7
#define SWITCHMODE 8

#define ELEMENT1 9//the pin where the relay is connected
#define ELEMENT2 10//the pin where the relay is connected
#define ELEMENT3 11//the pin where the relay is connected
#define ELEMENT4 12//the pin where the relay is connected



#define boilingPoint 25
//#define maxStep 32 //The max number of steps that can be received
#define degree char(223) //To get the right Celcius-symbol

#define Calibrator 0 //Calibration for the temp-sensor
//#define noRandom 2