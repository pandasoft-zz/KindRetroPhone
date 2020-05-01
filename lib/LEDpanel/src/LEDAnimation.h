#ifndef LEDANIMATION_H_
#define LEDANIMATION_H_

#include <Arduino.h>
#include "Animate.h"
#include <LEDScreen.h>

struct Frame
{
    byte * efects;
    unsigned long duration;
};

struct Animation
{
    Frame * frames;
    int count;
};


class LEDAnimation
{
public:
	LEDAnimation(LEDScreen *screen);
	void start(Animation frames);
	void stop();
	bool isPlayed();
	void setLoop(bool state);
	void update();

private:
	LEDScreen *_screen;
	int _actualIndex;
	bool _played = false;
	Animation * _actualAnimation;
	bool _infiniteLoop = true;
	unsigned long _lastTime;
};

#endif //LEDANIMATION_H_
