#include "Arduino.h"

#define ONE_WIRE_BUS A0
#define RELAY1 6//the pin where the relay is connected
#define RELAY2 5//the pin where the relay is connected
#define RELAY3 4//the pin where the relay is connected
#define RELAY4 3//the pin where the relay is connected
#define PUMP 7
#define SWITCH1 8
#define SWITCH2 9
#define SWITCH3 10
#define SWITCH4 11
#define SWITCH5 12

#define startButton 2 //The pin where the button is connected
#define stopButton 13

#define maxStep 32 //The max number of steps that can be received
#define degree char(223) //To get the right Celcius-symbol

#define Calibrator 0 //Calibration for the temp-sensor