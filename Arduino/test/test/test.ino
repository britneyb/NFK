#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27,20,4); 

    // the number of the pushbutton pin
// the number of Button pin
int buttonInput = 2;
// variables will change:
volatile int state = LOW;      // variable for reading the pushbutton status

void setup() {
	Serial.begin(9600);
	// initialize the pushbutton pin as an input:
	
	pinMode(buttonInput,OUTPUT);

	lcd.init();
	lcd.backlight();
	lcd.setCursor(0, 0);
}

void loop(){
	
	lcd.clear();
	
	// read the state of the pushbutton value:
	
	state  = digitalRead(buttonInput);
	
	// check if the pushbutton is pressed.
	// if it is, the buttonState is HIGH:
	if (state == HIGH) {
		// turn LED on:
		lcd.print("on");
		
	}
	else {
		// turn LED off:in
		lcd.print("off");
		
		
	}
}