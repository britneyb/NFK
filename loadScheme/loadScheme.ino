#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//loadScheme.ino

LiquidCrystal_I2C lcd(0x27,20,4);

void getData(){
	String content = "";
	if (Serial.available()){
		while (Serial.available()){
			content = Serial.readString();
		}
	}

	if(content != ""){
		int data[22]; //The results will be stored here
		String name = "";
		int* arr = 0;
		int i = 0;
		while(content != ""){
			int index = content.indexOf(",");		//We find the next comma
			if(index < 0){							//När man läst ut allt ur content så ballar index ur, och då breakar vi ur loppen och nollställer content.
				content = "";
				break;
			}
			if(i==0){
				name = content.substring(0,index);
			}
			else{
				data[i] = atol(content.substring(0,index).c_str()); //Extract the number
			}
			content = content.substring(index+1); //Remove the number from the string
			i++;
		}
		int arrSize = i-2;
		arr = new int [arrSize];
		int check = name.length();
		int checkSum = data[i-1];
		for(int j=0; j < arrSize; j++){
		    arr[j] = data[j+1];
		    check += arr[j];
		}
		if(check == checkSum){
			Serial.print("Checksumman stämmer");
		}
		else{
			Serial.print("Fail");
		}
	}
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
}

void loop() {
  // put your main code here, to run repeatedly:
  	getData();
}
