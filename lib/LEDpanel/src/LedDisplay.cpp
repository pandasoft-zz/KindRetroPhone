#include "LEDDisplay.h"
#include <Arduino.h>

LEDDisplay::LEDDisplay(char dataPin, char clockPin, char latchPin)
{
	_dataPin = dataPin;
	_clockPin = clockPin;
	_latchPin = latchPin;
	pinMode(_dataPin, OUTPUT);
	pinMode(_clockPin, OUTPUT);
	pinMode(_latchPin, OUTPUT);
}

void LEDDisplay::setScreen(LEDScreen* screen)
{
	_screen = screen;
}

void LEDDisplay::update()
{
	digitalWrite(_latchPin, LOW);
	char _rows = _screen->getNumRows();
	char* _matrix = _screen->getMatrix();
	char i;

	for (i = 0; i < _rows; i++) {
		shiftOut(_dataPin, _clockPin, LSBFIRST, _matrix[i]);
	}

	digitalWrite(_latchPin, HIGH);
}
