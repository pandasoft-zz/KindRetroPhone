#ifndef LEDSCREEN_H_
#define LEDSCREEN_H_

#include <Arduino.h>

class Screen {
public:
  Screen(char rows, char cols = 8);
  ~ Screen();
  void setLed(bool state, char row, char col);
  char getLed(char row, char col);
  void toggleLed(char row, char col);
  void toggle();
  void clear();
  char * getMatrix();
  char getNumCols();
  char getNumRows();
private:
	char _cols;
	char _rows;
	size_t _size;
	char *_matrix;
};

#endif

