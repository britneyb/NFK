/*
 Class to handle all the Relays
*/

#include "Arduino.h"
#include "Relay.h"

void Relay::Begin()
{
	pinMode(ELEMENT1, OUTPUT);
	pinMode(ELEMENT2, OUTPUT);
	pinMode(ELEMENT3, OUTPUT);
	pinMode(ELEMENT4, OUTPUT);
	pinMode(PUMP, OUTPUT);
	
	//randNum = new int[noRandom];
}

void Relay::AllLow()
{
	digitalWrite(PUMP, LOW);
	digitalWrite(ELEMENT1, LOW);
	digitalWrite(ELEMENT2, LOW);
	digitalWrite(ELEMENT3, LOW);
	digitalWrite(ELEMENT4, LOW);
}

void Relay::ElementLow()
{
	digitalWrite(ELEMENT1, LOW);
	digitalWrite(ELEMENT2, LOW);
	digitalWrite(ELEMENT3, LOW);
	digitalWrite(ELEMENT4, LOW);
}

void Relay::ReadElements()
{
	int stateRelay1 = digitalRead(SWITCH1);
	int stateRelay2 = digitalRead(SWITCH2);
	int stateRelay3 = digitalRead(SWITCH3);
	int stateRelay4 = digitalRead(SWITCH4);

	if(stateRelay1 == HIGH)
		digitalWrite(ELEMENT1,HIGH);
	else
		digitalWrite(ELEMENT1,LOW);
	if(stateRelay2 == HIGH)
		digitalWrite(ELEMENT2,HIGH);
	else
		digitalWrite(ELEMENT2,LOW);
	if(stateRelay3 == HIGH)
		digitalWrite(ELEMENT3,HIGH);
	else
		digitalWrite(ELEMENT3,LOW);
	if(stateRelay4 == HIGH)
		digitalWrite(ELEMENT4,HIGH);
	else
		digitalWrite(ELEMENT4,LOW);
}

void Relay::Random(boolean firstRun)
{
	if (firstRun)
	{
		for (int i = 0; i < noRandom; i++)
		{
			if(i > 0)
				randNum[i] = Unique();
			else
				randNum[i] = random(4);

			Serial.print(String(randNum[i]));
		}
	}

	for (int i = 0; i < noRandom; i++)
	{
		boolean relayOn = true;

		while(relayOn)
		{
			int stateRelay1 = digitalRead((SWITCH1));
			int stateRelay2 = digitalRead((SWITCH2));
			int stateRelay3 = digitalRead((SWITCH3));
			int stateRelay4 = digitalRead((SWITCH4));
			relayOn = false;

			if(stateRelay1 == LOW)
			{
				if(randNum[i] == 0)
				{
					digitalWrite(ELEMENT1,LOW);
					randNum[i] = Unique(); //random(4);
					relayOn = true;
				}	
			}
			if(stateRelay2 == LOW)
			{
				if(randNum[i] == 1)
				{
					digitalWrite(ELEMENT2,LOW);
					randNum[i] = Unique(); //random(4);
					relayOn = true;
				}	
			}
			if(stateRelay3 == LOW)
			{
				if(randNum[i] == 2)
				{
					digitalWrite(ELEMENT3,LOW);
					randNum[i] = Unique(); //random(4);
					relayOn = true;
				}	
			}
			if(stateRelay4 == LOW)
			{
				if(randNum[i] == 3)
				{
					digitalWrite(ELEMENT4,LOW);
					randNum[i] = Unique(); //random(4);
					relayOn = true;
				}
			}
		}

		switch (randNum[i])
		{
			case  0:
				digitalWrite(ELEMENT1,HIGH); 
				break;
			case 1:
				digitalWrite(ELEMENT2,HIGH);           // Turns ON Element 2				         
				break;
			case 2:
				digitalWrite(ELEMENT3,HIGH);           // Turns ON Element 3
				break;        
			case 3:
				digitalWrite(ELEMENT4,HIGH);           // Turns ON Element 4
				break;    
		}
	}
}

int Relay::Unique()
{
	int temp = random(4);
	int j = 0;

	while(j < noRandom)
	{
		if (temp == randNum[j])
		{
			temp = random(4);
			j = 0;
		}
		else
		{
			j++;
		}
	}

	return temp;	
}
