// ---------------------------------------------------------------------------
// Created by Antoine Beauchamp based on the code from the ToneLibrary
//
// See "NonBlockingRtttl.h" for purpose, syntax, version history, links, and more.
// ---------------------------------------------------------------------------

#include "Rtttl.h"

/*********************************************************
 * RTTTL Library data
 *********************************************************/

//#define isdigit(n) (n >= '0' && n <= '9')
#define OCTAVE_OFFSET 0

const int Rtttl::_NOTES[] = {0,
							 NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4,
							 NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5,
							 NOTE_C6, NOTE_CS6, NOTE_D6, NOTE_DS6, NOTE_E6, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_GS6, NOTE_A6, NOTE_AS6, NOTE_B6,
							 NOTE_C7, NOTE_CS7, NOTE_D7, NOTE_DS7, NOTE_E7, NOTE_F7, NOTE_FS7, NOTE_G7, NOTE_GS7, NOTE_A7, NOTE_AS7, NOTE_B7};

Rtttl::Rtttl(IToneEngine *engine)
{
	_engine = engine;
	_state = NOT_INIT;
	_default_dur = 4;
	_default_oct = 6;
	_bpm = 63;

	_state = PlaingState::NOT_INIT;
	_engine->stopTone();
}

void Rtttl::load(IRtttlSong *song)
{
	_songBuffer = song;
}

void Rtttl::onEnd (void (*callback)()) {
	_onEndcallback = callback;
}

void Rtttl::play()
{
	//TODO musi byt inicializoavy zdroj
	_state = PlaingState::PLAYING;

	_engine->stopTone();

	//read buffer until first note
	int num;

	// format: d=N,o=N,b=NNN:
	// find the start (skip name, etc)

	while (_songBuffer->get() != ':') {
		_songBuffer->next(); // ignore name
	}
	_songBuffer->next();	 // skip ':'

	// get default duration
	if (_songBuffer->get() == 'd')
	{
		_songBuffer->next();
		_songBuffer->next(); // skip "d="
		num = 0;
		while (isdigit(_songBuffer->get()))
		{
			num = (num * 10) + (_songBuffer->next() - '0');
		}
		if (num > 0)
		{
			_default_dur = num;
		}
		_songBuffer->next(); // skip comma
	}

	// get default octave
	if (_songBuffer->get() == 'o')
	{
		_songBuffer->next();
		_songBuffer->next(); // skip "o="

		num = _songBuffer->next() - '0';

		if (num >= 3 && num <= 7)
		{
			_default_oct = num;
		}

		_songBuffer->next(); // skip comma
	}

	// get BPM
	if (_songBuffer->get() == 'b')
	{
		_songBuffer->next();
		_songBuffer->next(); // skip "b="
		num = 0;
		while (isdigit(_songBuffer->get() ))
		{
			num = (num * 10) + (_songBuffer->get() - '0');
			_songBuffer->next();
		}
		_bpm = num;
		_songBuffer->next(); // skip colon
	}

	// BPM usually expresses the number of quarter notes per minute
	_wholenote = (60 * 1000L / _bpm) * 4; // this is the time for whole note (in milliseconds)
}

void Rtttl::stop()
{
}

void Rtttl::pause()
{
}

PlaingState Rtttl::getState()
{
	return this->_state;
}

void Rtttl::update() {
	//if done playing the song, return
	if ( _state != PlaingState::PLAYING )
	{

		return;
	}

	//are we still playing a note ?
	unsigned long m = millis();
	if (m < _noteDelay)
	{
		//wait until the note is completed
		return;
	}

	//ready to play the next note
	if (_songBuffer->get() == '\0')
	{
		_state != PlaingState::END;
		 
		 if ( _onEndcallback != NULL ) {
			 (*_onEndcallback)();
		 }

		return; //end of the song
	}
	else
	{

		Rtttl::_nextnote();
	}
}

void Rtttl::_nextnote()
{
	long duration;
	byte note;
	byte scale;

	//stop current note
	_engine->stopTone();

	// first, get note duration, if available
	int num = 0;

	while (isdigit(_songBuffer->get()))
	{
		num = (num * 10) + (_songBuffer->get() - '0');
		_songBuffer->next();
	}

	if (num)
		duration = _wholenote / num;
	else
		duration = _wholenote / _default_dur; // we will need to check if we are a dotted note after

	// now get the note
	note = 0;

	switch (_songBuffer->get())
	{
	case 'c':
		note = 1;
		break;
	case 'd':
		note = 3;
		break;
	case 'e':
		note = 5;
		break;
	case 'f':
		note = 6;
		break;
	case 'g':
		note = 8;
		break;
	case 'a':
		note = 10;
		break;
	case 'b':
		note = 12;
		break;
	case 'p':
	default:
		note = 0;
	}
	_songBuffer->next();

	// now, get optional '#' sharp
	if (_songBuffer->get() == '#')
	{
		note++;
		_songBuffer->next();
	}

	// now, get optional '.' dotted note
	if (_songBuffer->get() == '.')
	{
		duration += duration / 2;
		_songBuffer->next();
	}

	// now, get scale
	if (isdigit(_songBuffer->get()))
	{
		scale = _songBuffer->get() - '0';
		_songBuffer->next();
	}
	else
	{
		scale = _default_oct;
	}

	scale += OCTAVE_OFFSET;

	if (_songBuffer->get() == ',')
	{
		_songBuffer->next(); // skip comma for next note (or we may be at the end)
	}
	// now play the note

	if (note)
	{
		_engine->playTone(_NOTES[(scale - 4) * 12 + note], duration);

		_noteDelay = millis() + (duration + 1);
	}
	else
	{
		_noteDelay = millis() + (duration);
	}
}