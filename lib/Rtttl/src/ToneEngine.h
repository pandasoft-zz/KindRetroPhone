#ifndef RTTTL_TE_H_
#define RTTTL_TE_H_

#include <Arduino.h>
#include "IToneEngine.h"

class ToneEngine : public IToneEngine {
public:
  ToneEngine(byte pin);
  virtual void playTone(unsigned int frequency, unsigned long duration);
  virtual void stopTone();

private:
  byte _pin;
};

#endif