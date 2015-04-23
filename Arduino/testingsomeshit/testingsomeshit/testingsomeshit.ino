#include <Time.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
LiquidCrystal_I2C lcd(0x27,20,4);
#define TIME_MSG_LEN  11   // time sync to PC is HEADER followed by unix time_t as ten ascii digits
#define TIME_HEADER  255


//Defines our Pin
#define ONE_WIRE_BUS A0

OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
int CurrentTemp;
int buttonInput = 2;
int total;
int aktuell;
boolean Cheak = true;
boolean Cheak_2 ;
time_t t=0;
int led = 7;
int state = LOW;



void setup()
{
	Serial.begin(9600);
	lcd.init();
	lcd.backlight();
	sensors.begin();
	pinMode(buttonInput,OUTPUT);
    pinMode(led, OUTPUT);
	lcd.print("Wait for program:");
}

void loop()


{ 
	
	setTime(0,0,0,0,0,0);
   while(Serial.available())


{	lcd.setCursor(0,0);
	lcd.print("Totalt:");lcd.print(minute()); lcd.print(" min ");lcd.print(second()); lcd.print(" sek"); lcd.print(" ");
	state  = digitalRead(buttonInput);
	if(state ==HIGH)
	{
		t = now();
		Cheak=false;
		
	}
	
	
	aktuell=now()-t;
	
	if (!Cheak)
	{	changefromSecTomin();
		if(second()%2==0)
		getTemp();
		
	}
	
	
	if (CurrentTemp == 33)
	{
		digitalWrite(led,HIGH);
	}
	else if (CurrentTemp == 27)
	{
	    digitalWrite(led,LOW);
	
	}
		
}


}




void changefromSecTomin(){
	
if (minute(aktuell)==0)
{	
	lcd.setCursor(0,1);
	lcd.print("Aktuellt:");lcd.print(CurrentTemp);lcd.print((char)223);lcd.print("C ");lcd.print(second(aktuell)); lcd.print(" sek");
	
}
else{
	lcd.setCursor(0,1);
	lcd.print("Aktuellt:");lcd.print(CurrentTemp);lcd.print((char)223); lcd.print("C ");lcd.print(minute(aktuell));lcd.print(" min");lcd.print("    ");
}




};


void getTemp(){
		
		sensors.requestTemperatures();
		CurrentTemp =sensors.getTempCByIndex(0);
		
	
};
