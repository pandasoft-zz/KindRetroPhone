#include "LEDAnimation.h"
#include <Arduino.h>
#include <ArduinoLog.h>

LEDAnimation::LEDAnimation(LEDScreen *scre en)
{
	_screen = screen;
	_played = false;
	_actualAnimation = NULL;
	_actualIndex = 0;
}
void LEDAnimation::start(Animation frames)
{

	if (frames.count > 0)
	{
		_actualAnimation = &frames;
		_actualIndex = 0;
		_played = true;
		_lastTime = millis();

		_screen->load((byte *)(*_actualAnimation).frames[_actualIndex].efects);
	}
}

void LEDAnimation::stop()
{
	_screen->clear();
	_played = false;
	_actualIndex = 0;
	_actualAnimation = NULL;
}
bool LEDAnimation::isPlayed()
{
	return _played;
}
void LEDAnimation::setLoop(bool state)
{
	_infiniteLoop = state;
}
void LEDAnimation::update()
{
	if (_played && _actualAnimation != NULL)
	{
		
		unsigned long now = millis();

		if ((*_actualAnimation).count > _actualIndex)
		{
			if ((now - _lastTime) > (*_actualAnimation).frames[_actualIndex].duration)
			{

				Log.trace("LEDAnimation::Update: %d, %d"CR, _actualIndex, (*_actualAnimation).count );

				_lastTime = now;

				if ((*_actualAnimation).count > _actualIndex)
				{
					_screen->load((byte *)(*_actualAnimation).frames[++_actualIndex].efects);
					Log.trace("LEDAnimation::Update:Next: %d, %d"CR, _actualIndex, (*_actualAnimation).count );
				}
			}
		}
		else
		{
			Log.trace("LEDAnimation::Update:End: %d, %d"CR, _actualIndex, (*_actualAnimation).count );
			_actualIndex = 0;
			if (!_infiniteLoop)
			{
				Log.trace("LEDAnimation::Update:No Infinity: %d, %d"CR, _actualIndex, (*_actualAnimation).count );
				stop();
			}
		}
	}
}
