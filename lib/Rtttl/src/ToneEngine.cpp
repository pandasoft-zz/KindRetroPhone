#include "ToneEngine.h"


ToneEngine::ToneEngine(byte pin)
{
	_pin = pin;
	pinMode(pin, OUTPUT);
}
void ToneEngine::playTone(unsigned int frequency, unsigned long duration)
{
	tone(_pin, frequency, duration);
}
void ToneEngine::stopTone()
{
	noTone(this->_pin);
}