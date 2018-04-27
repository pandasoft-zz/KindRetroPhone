#ifndef RTTTL_ITE_H_
#define RTTTL_ITE_H_

#include <Arduino.h>

class IToneEngine {
public:
  virtual void playTone(unsigned int frequency, unsigned long duration);
  virtual void stopTone();
};

#endif