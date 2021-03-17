
#include "RaspberryPi.h"


#include <cstdio>

#include <ctime>

#include <utility>
#include <iostream>
#include <array>
#include "wiringPi.h"

#include "wiringSerial.h"



using namespace std;



int RaspberryPi::initComponent()
{
	printf("Reversi game has been initiated...\n");

	if (wiringPiSetup() == -1)
		return -1;

	for (int i : pinLEDRows)
	{
		pinMode(i, INPUT);
		pullUpDnControl (i, PUD_DOWN);
	}

	for (int i : pinLEDCols)
	{
		pinMode(i, INPUT);
		pullUpDnControl (i, PUD_DOWN);
	}

	for (int i : pinPadCols)
	{
		pinMode(i, INPUT);
		pullUpDnControl (i, PUD_DOWN) ;
	}

	int fd = serialOpen("/dev/ttyUSB0", 9600);
	if(fd == -1)
	{
		printf("serial connection not initialized\n");
	}
	else
	{
		printf("serial setup complete\n");
	}
	return fd;
}


pair<int, int> RaspberryPi::padInput(int fd)
{
	int x = serialGetchar(fd);
	//cout << x << " ";
	int y = -1;

	for (int i = 0; i < 8; i++)
	{
		if (digitalRead(pinPadCols[i]) == HIGH)
		{
			y = i;
		}
	}
	
	return make_pair(x, y);
}



void RaspberryPi::updateLED(const array<array<int, 8>, 8>& map)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			int t = time(NULL);
			if (map[i][j] == 1 || 
				map[i][j] == 2 && t % 2 == 0)
			{
				pinMode(pinLEDRows[i], OUTPUT);
                                pinMode(pinLEDCols[j], OUTPUT);
				digitalWrite(pinLEDRows[i], HIGH);
				digitalWrite(pinLEDCols[j], LOW);
				delay(1);
				pinMode(pinLEDRows[i], INPUT);
                                
                                pinMode(pinLEDCols[j], INPUT);
                                
			}
		}
	}


	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			int t = time(NULL);
			if (map[i][j] == -1 || 
				map[i][j] == -2 && t % 2 == 0)
			{
				pinMode(pinLEDRows[i], OUTPUT);
				pinMode(pinLEDCols[j], OUTPUT);
				digitalWrite(pinLEDCols[j], HIGH);
				digitalWrite(pinLEDRows[i], LOW);
				delay(1);
				pinMode(pinLEDRows[i], INPUT);
				
				pinMode(pinLEDCols[j], INPUT);
			}
		}
	}

}

void RaspberryPi::close(int fd) 
{ 
	 	
        for (int i : pinLEDRows)
        {
                pinMode(i, OUTPUT);
                digitalWrite(i, LOW);
        }

        for (int i : pinLEDCols)
        {
                pinMode(i, OUTPUT);
                digitalWrite(i, LOW);
        }

        for (int i : pinPadCols)
        {
                pinMode(i, OUTPUT);
                digitalWrite(i, LOW);
        }
	
	serialClose(fd);
}
