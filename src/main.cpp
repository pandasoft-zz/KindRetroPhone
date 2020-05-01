#include <Arduino.h>
#include <ArduinoLog.h>
#include <Keypad.h>
#include <Rtttl.h>
#include <ToneEngine.h>
#include <ProgmemRTTTSong.h>
#include <LEDDisplay.h>
#include <LEDAnimation.h>
#include "keycodes.h"
#include "music.h"
#include "animation.h"

byte rowPins[] = {A1, A2, A3, A4};
const int rowCount = 4;

byte colsPins[] = {6, 7, 8, 9, 10, 11, 12, A5, A0};
const int colCount = 9;

// pin připojen na RCLK registru (12)
const byte latchPin = 4;
//Pin connected to SRCLK registru (11)
const byte clockPin = 3;
//Pin připojen na Data pin registu (14)
const byte dataPin = 2;

const byte mainSpeakerPin = 5;

byte album = 0;

const char phoneKeyboard[rowCount][colCount] = {
	{KEY_STAR, KEY_0, KEY_HASH, KEY_ALOUD, KEY_OPTION, KEY_NONE, KEY_M1, KEY_M5, KEY_NONE},
	{KEY_7, KEY_8, KEY_9, KEY_BACK, KEY_DEL, KEY_SEARCH, KEY_M2, KEY_M6, KEY_NONE},
	{KEY_4, KEY_5, KEY_6, KEY_LIST, KEY_UP, KEY_MENU, KEY_M3, KEY_N1, KEY_NONE},
	{KEY_1, KEY_2, KEY_3, KEY_REPETE, KEY_DOWN, KEY_MUTE, KEY_M4, KEY_N2, KEY_VOLUME}
};

const unsigned int pianoNotes[] = {
	NOTE_A6, //1
	NOTE_B6, //2
	NOTE_C6, //3
	NOTE_D6, //4
	NOTE_E6, //5
	NOTE_F6, //6
	NOTE_G6, //7
	NOTE_GS6, //8
	NOTE_AS7, //1
};

Keypad phoneKeypad = Keypad(makeKeymap(phoneKeyboard), rowPins, colsPins, rowCount, colCount);

LEDScreen *screen = new LEDScreen(3);

LEDDisplay ledDisplay = LEDDisplay(dataPin, clockPin, latchPin);
LEDAnimation animation = LEDAnimation(screen);

IToneEngine *engine = new ToneEngine(mainSpeakerPin);
Rtttl sound = Rtttl(engine);


// Taking care of some special events.
void keypadCheck()
{
	if (phoneKeypad.getKeys())
	{
		for (int i = 0; i < LIST_MAX; i++) // Scan the whole key list.
		{
			if (phoneKeypad.key[i].stateChanged) // Only find keys that have changed state.
			{
				byte pos = 0;
				const char * song = NULL;
				
				Animation adnimation = animations1;

				switch (phoneKeypad.key[i].kstate)
				{ // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
					case PRESSED:
						switch (phoneKeypad.key[i].kchar)
						{
							case KEY_1:
							case KEY_2:
							case KEY_3:
							case KEY_4:
							case KEY_5:
							case KEY_6:
							case KEY_7:
							case KEY_8:
							case KEY_9:
								animation.stop();
								pos = phoneKeypad.key[i].kchar - KEY_1;
								screen->toggleLed(pos, 0);
								sound.stop();
								engine->playTone(pianoNotes[pos], 1000);
								break;
							case KEY_0:
								screen->clearRow(0);
								break;
							case KEY_HASH:
								screen->copyRow(1, 2);
								screen->copyRow(0, 1);
								screen->clearRow(0);
								break;
							case KEY_STAR:
								screen->toggle();
								break;
							case KEY_NONE:
								song = song1;
								break;
							case KEY_MENU:
								song = song2;
								adnimation = animations2;
								break;
							case KEY_SEARCH:
								song = song3;
								break;
							case KEY_UP:
								song = song4;
								break;
							case KEY_DOWN:
								song = song5;
								break;
							case KEY_DEL:
								song = song6;
								break;
							case KEY_LIST:
								song = song7;
								break;
							case KEY_OPTION:
								song = song8;
								break;
							case KEY_MUTE:
								song = song11;
								break;
							case KEY_VOLUME:
								song = song12;
								break;
							case KEY_ALOUD:
								song = song24;
								break;
							case KEY_BACK:
								song = song14;
								break;
							case KEY_REPETE:
								song = song15;
								break;
							case KEY_M1:
								song = song16;
								break;
							case KEY_M2:
								song = song17;
								break;
							case KEY_M3:
								song = song18;
								break;
							case KEY_M4:
								song = song19;
								break;
							case KEY_M5:
								song = song20;
								break;
							case KEY_M6:
								song = song21;
								break;
							case KEY_N1:
								song = song22;
								break;
							case KEY_N2 :
								song = song23;
								break;
						}
						break;
					case HOLD:
						break;
					case RELEASED:
						break;
					case IDLE:
						break;
					}

				if ( song != NULL) {
					animation.start(adnimation);

					sound.load(new ProgmemRTTTSong(song));
					sound.play();
				}
			}
		}
	}
}

void stopAnimation() {
	Log.trace("Stop animation after stop song");
	animation.stop();
}

void setup()
{
	Serial.begin(9600);
	Log.begin(LOG_LEVEL_VERBOSE, &Serial);

	screen->clear();
	ledDisplay.setScreen(screen);

	sound.onEnd(stopAnimation);
}

void loop()
{
	keypadCheck();

	sound.update();

	animation.update();

	ledDisplay.update();
}
