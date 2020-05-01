#ifndef LEDDISPLAY_H_
#define LEDDISPLAY_H_

#include <Arduino.h>
#include "LEDScreen.h"

class LEDDisplay {
public:
  LEDDisplay(char dataPin, char clockPin, char latchPin);
  void setScreen(LEDScreen * screen);
  void update();
private:
	char _dataPin;
	char _clockPin;
	char _latchPin;
	LEDScreen * _screen;
};

#endif //LEDDISPLAY_H_