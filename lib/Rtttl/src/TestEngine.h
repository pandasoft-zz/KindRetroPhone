#ifndef RTTTL_TEE_H_
#define RTTTL_TEE_H_

#include <Arduino.h>
#include "IToneEngine.h"

class TestEngine : public IToneEngine {
public:
  TestEngine();
  virtual void playTone(unsigned int frequency, unsigned long duration);
  virtual void stopTone();
};

#endif
