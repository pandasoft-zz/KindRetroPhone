#ifndef RTTTL_PRS_H_
#define RTTTL_PRS_H_

#include "IRtttlSong.h"

class ProgmemRTTTSong: public IRtttlSong {
public:
  ProgmemRTTTSong(char * _song);
  virtual char get();
  virtual char next();
  virtual void reset();

private:
   const char *_buffer = "";
  int _pos;
};

#endif