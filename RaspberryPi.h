#pragma once



#include <utility>

#include <array>



using namespace std;

namespace RaspberryPi
{
	const int pinLEDRows[] = { 29, 28, 27, 26, 31, 11, 10, 6 };
	const int pinLEDCols[] = { 8, 9, 7, 0, 2, 3, 12, 13 };
	const int pinPadCols[] = { 14, 30, 21, 22, 23, 24, 25, 1};

	int initComponent();

	pair<int, int> padInput(int fd);

	void updateLED(const array<array<int, 8>, 8> &map);

	void close(int fd);
}
