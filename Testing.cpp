#include "wiringPi.h"
#include "RaspberryPi.h"
#include <array>
using namespace std;
using namespace RaspberryPi;

int main(void)
{
	array<array<int, 8>, 8> map1;
	array<array<int, 8>, 8> map2;
	for(int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			map1[i][j] = 1;
			map2[i][j] = -1;
		}
	}
	printf("begining to initialize component\n");
	initComponent();
	while(true)
	{
		updateLED(map1);
		updateLED(map2);
	}
	return 0;
}
