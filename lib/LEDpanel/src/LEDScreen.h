#ifndef LEDSCREEN_H_
#define LEDSCREEN_H_

#include <Arduino.h>

class LEDScreen
{
public:
	LEDScreen(byte rows, byte cols = 8);
	~LEDScreen();
	void setLed(bool state, byte col, byte row);
	bool getLed(byte col, byte row);
	void toggleLed(byte col, byte row);

	void toggle();
	void toggleRow(byte row);
	void toggleCol(byte col);

	void clear();
	void clearRow(byte row);
	void clearCol(byte col);

	void swapRow(byte srcRow, byte destRow);
	void swapCol(byte srcCol, byte destCol);

	void copyRow(byte srcRow, byte destRow);
	void copyCol(byte srcCol, byte destCol);

	void shiftRowLeft(byte row, byte count = 1);
	void shiftRowRight(byte row, byte count = 1);
	void shiftRight(byte count = 1);
	void shiftLeft(byte count = 1);
	void shiftBottom();
	void shiftTop();

	byte * getMatrix();
	byte getNumCols();
	byte getNumRows();

private:
	byte _cols;
	byte _rows;
	size_t _size;
	byte* _matrix;
};

#endif
