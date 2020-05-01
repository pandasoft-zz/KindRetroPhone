

#ifndef RTTTlib_H_
#define RTTTLib_H_

#include "notes.h"
#include <Arduino.h>
#include <avr/pgmspace.h>

#include "IToneEngine.h"
#include "IRtttlSong.h"

typedef enum { NOT_INIT, INIT, PLAYING, PAUSE, END } PlaingState;


class Rtttl {
public:
  // methods
  Rtttl(IToneEngine *engine);
  void load(IRtttlSong *song);
  void play();
  void stop();
  void pause();
  PlaingState getState();
  void update();
  void onEnd (void (*callback)());

private:
  void _nextnote();

  IToneEngine *_engine;
  IRtttlSong * _songBuffer;
  PlaingState _state;
  void (*_onEndcallback)() = NULL;
  byte _default_dur = 4;
  byte _default_oct = 5;
  int _bpm = 63;
  long _wholenote;
  unsigned long _noteDelay = 0;
  const static int _NOTES[];
};

#endif
