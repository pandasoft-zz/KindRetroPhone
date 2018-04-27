#ifndef LEDDISPLAY_H_
#define LEDDISPLAY_H_

#include <Arduino.h>
#include "Screen.h"

class LedDisplay {
public:
  LedDisplay(char dataPin, char clockPin, char latchPin);
  void setScreen(Screen * screen);
  void update();
private:
	char _dataPin;
	char _clockPin;
	char _latchPin;
	Screen * _screen;
};

#endif