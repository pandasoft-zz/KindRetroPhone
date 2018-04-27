#include "LedDisplay.h"
#include <Arduino.h>

LedDisplay::LedDisplay(char dataPin, char clockPin, char latchPin)
{
	_dataPin = dataPin;
	_clockPin = clockPin;
	_latchPin = latchPin;
	pinMode(_dataPin, OUTPUT);
	pinMode(_clockPin, OUTPUT);
	pinMode(_latchPin, OUTPUT);
}

void LedDisplay::setScreen(Screen* screen)
{
	_screen = screen;
}

void LedDisplay::update()
{
	digitalWrite(_latchPin, LOW);
	char* _matrix = _screen->getMatrix();
	char _cols = _screen->getNumCols();
	char i = 0;

	for (i = 0; i < _cols; i++) {
		shiftOut(_dataPin, _clockPin, MSBFIRST, _matrix[i]);
	}

	digitalWrite(_latchPin, HIGH);
}
