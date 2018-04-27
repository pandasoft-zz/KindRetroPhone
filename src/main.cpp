#include <Arduino.h>
#include <Keypad.h>
#include <Rtttl.h>
//#include <TestEngine.h>
#include <ToneEngine.h>
#include <ProgmemRTTTSong.h>
#include <LedDisplay.h>
#include "keycodes.h"
#include "music.h"


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
    {KEY_1, KEY_2, KEY_3, KEY_REPETE, KEY_DOWN, KEY_MUTE, KEY_M4, KEY_N2, KEY_VOLUME}};

Keypad phoneKeypad = Keypad(makeKeymap(phoneKeyboard), rowPins, colsPins, rowCount, colCount);

Screen *screen = new Screen(3);

LedDisplay ledDisplay = LedDisplay(dataPin, clockPin, latchPin);

IToneEngine *engine = new ToneEngine(mainSpeakerPin);
Rtttl sound = Rtttl(engine);

byte normalize(char in)
{
    return round((255.0) * ((in) / (32.0)));
}

// Taking care of some special events.
void keypadCheck()
{
    if (phoneKeypad.getKeys())
    {
        for (int i = 0; i < LIST_MAX; i++) // Scan the whole key list.
        {
            if (phoneKeypad.key[i].stateChanged) // Only find keys that have changed state.
            {
				screen->setLed(true, 1, 1);
                byte pos = 0;
                switch (phoneKeypad.key[i].kstate)
                { // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
                case PRESSED:
                    switch (phoneKeypad.key[i].kchar)
                    {
                        case KEY_OPTION:
							album = ++album % 3;
							break;
                        case KEY_1:
                        case KEY_2:
                        case KEY_3:
                        case KEY_4:
                        case KEY_5:
                        case KEY_6:
                        case KEY_7:
                        case KEY_8:
                            pos = phoneKeypad.key[i].kchar - KEY_1;
							screen->setLed(true, pos, 2);
                            break;
                        case KEY_M1:
                        case KEY_M2:
                        case KEY_M3:
                        case KEY_M4:
                        case KEY_M5:
                        case KEY_M6:
                        case KEY_N1:
                        case KEY_N2:
                            pos = phoneKeypad.key[i].kchar - KEY_M1 + (album * 8);
                            sound.load( new ProgmemRTTTSong( (const char *) pgm_read_word (&song[pos]) ) );
                            sound.play();
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
            }
        }
    }
}

void setup()
{
    Serial.begin(9600);

	ledDisplay.setScreen(screen);
}

void loop()
{
    keypadCheck();

    sound.update();

    ledDisplay.update();
}