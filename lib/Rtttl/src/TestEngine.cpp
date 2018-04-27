#include <Arduino.h>
#include "TestEngine.h"

TestEngine::TestEngine()
{

}

void TestEngine::playTone(unsigned int frequency, unsigned long duration)
{
	Serial.print("frequency=");
	Serial.print(frequency);
	Serial.print(", duration=");
	Serial.println(duration);
}
void TestEngine::stopTone()
{
	Serial.println("Stop tone");
}

