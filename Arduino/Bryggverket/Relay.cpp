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
	pinMode(COOLINGPUMP, OUTPUT);
}

void Relay::AllLow()
{
	digitalWrite(PUMP, LOW);
	digitalWrite(COOLINGPUMP,LOW);
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

void Relay::ReadElements(int noElements)
{
	int stateRelay1 = digitalRead(SWITCH1);
	int stateRelay2 = digitalRead(SWITCH2);
	int stateRelay3 = digitalRead(SWITCH3);
	int stateRelay4 = digitalRead(SWITCH4);
	int elementsOn = 0;
	if(stateRelay1 == HIGH && elementsOn < noElements)
	{
		digitalWrite(ELEMENT1,HIGH);
		elementsOn++;
	}
	else
		digitalWrite(ELEMENT1,LOW);
	if(stateRelay2 == HIGH && elementsOn < noElements)
	{
		digitalWrite(ELEMENT2,HIGH);
		elementsOn++;
	}
	else
		digitalWrite(ELEMENT2,LOW);
	if(stateRelay3 == HIGH && elementsOn < noElements)
	{
		digitalWrite(ELEMENT3,HIGH);
		elementsOn++;
	}
	else
		digitalWrite(ELEMENT3,LOW);
	if(stateRelay4 == HIGH && elementsOn < noElements)
	{
		digitalWrite(ELEMENT4,HIGH);
		elementsOn++;
	}
	else
		digitalWrite(ELEMENT4,LOW);
}

void Relay::SetRandom(int noRandom)
{
	randNum = new int[noRandom];
}

void Relay::Random(boolean firstRun, int noRandom)
{
	if (firstRun)
	{
		for (int i = 0; i < noRandom; i++)
		{
			if(i > 0)
				randNum[i] = Unique(noRandom);
			else
				randNum[i] = random(4);
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
					randNum[i] = Unique(noRandom); //random(4);
					relayOn = true;
				}	
			}
			if(stateRelay2 == LOW)
			{
				if(randNum[i] == 1)
				{
					digitalWrite(ELEMENT2,LOW);
					randNum[i] = Unique(noRandom); //random(4);
					relayOn = true;
				}	
			}
			if(stateRelay3 == LOW)
			{
				if(randNum[i] == 2)
				{
					digitalWrite(ELEMENT3,LOW);
					randNum[i] = Unique(noRandom); //random(4);
					relayOn = true;
				}	
			}
			if(stateRelay4 == LOW)
			{
				if(randNum[i] == 3)
				{
					digitalWrite(ELEMENT4,LOW);
					randNum[i] = Unique(noRandom); //random(4);
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

int Relay::Unique(int noRandom)
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
