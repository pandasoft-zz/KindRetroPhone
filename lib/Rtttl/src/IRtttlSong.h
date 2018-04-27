#ifndef RTTT_ISong_H_
#define RTTT_ISong_H_

#include <Arduino.h>

class IRtttlSong {
public:
  virtual char get();
  virtual char next();
  virtual void reset();
};

#endif