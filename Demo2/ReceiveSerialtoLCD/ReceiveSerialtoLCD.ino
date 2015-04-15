#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//0x27 is the adress for the display controller and 20,4 is the number of characters and rows on the display
LiquidCrystal_I2C lcd(0x27,20,4); 

//serial input
int incomingByte = 0; 

void setup()
{
    //sets the serial communication
    Serial.begin(9600); 
    lcd.init(); 
    lcd.backlight();
    lcd.setCursor(0, 0);
}

void loop()
{
   if (Serial.available()) {
    // wait a bit for the entire message to arrive
    delay(100);
    // clear the screen
    lcd.clear();
    // read all the available characters
    while (Serial.available() > 0) {
      // display each character to the LCD
      lcd.write(Serial.read());
    }
  }
}
