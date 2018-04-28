
#include "LEDScreen.h";

LEDScreen::LEDScreen(byte rows, byte cols = 8 ) {
	_cols = 8; //now not support custom cols
	_rows = rows;
	_size = (rows*cols+8-1)/8;
	_matrix = (byte*) new byte[_rows];
}

LEDScreen::~LEDScreen() {
	free(_matrix);
}

void LEDScreen::setLed(bool state, byte col, byte row){
	byte _tmp = 0x01;

	if (state ) {
		_matrix[row] = (_matrix[row] | (_tmp << col));
	} else {
		_matrix[row] = (_matrix[row] & ~ (_tmp << col));
	}
}

 bool LEDScreen::getLed(byte col, byte row) {
	 return (_matrix[row] >> col) & 1;
 }

void LEDScreen::toggleLed(byte col, byte row){
	byte _tmp = 0x01;

	_matrix[row] = (_matrix[row] ^ (_tmp << col));
}

void LEDScreen::toggle(){
	for ( byte x = 0; x < _rows; x++) {
		toggleRow(x);
	}
}

  void LEDScreen::toggleRow(byte row){
	_matrix[row] = ~_matrix[row];
  }
  void LEDScreen::toggleCol(byte col){
	for ( byte x = 0; x < _rows; x++) {
		toggleLed(col, x);
	}
  }
  void LEDScreen::clearRow(byte row){
	  _matrix[row] = 0;
  }
  void LEDScreen::clearCol(byte col){
	for ( byte x = 0; x < _rows; x++) {
		setLed(false, col, x);
	}
  }
  void LEDScreen::swapRow(byte srcRow, byte destRow){
	  byte tmp = _matrix[destRow];
	  _matrix[destRow] = _matrix[srcRow];
	  _matrix[srcRow] = tmp;

  }
  void LEDScreen::copyRow(byte srcRow, byte destRow){
	  _matrix[destRow] = _matrix[srcRow];
  }

  void LEDScreen::copyCol(byte srcCol, byte destCol) {
	bool tmp;
	for (byte x = 0; x < _rows; x++) {
		tmp = getLed(srcCol, x);
		setLed(tmp, destCol, x);
	}
  }

  void LEDScreen::swapCol(byte srcCol, byte destCol) {
	bool tmp;
	for ( byte x = 0; x < _rows; x++) {
		tmp = getLed(srcCol, x);
		setLed(getLed(destCol, x), srcCol, x);
		setLed(tmp, destCol, x);
	}
  }



	void LEDScreen::shiftRowLeft(byte row, byte count = 1){
		byte tmp = _matrix[row];
		_matrix[row] = tmp >> count | tmp << (8-count);
	}
	void LEDScreen::shiftRowRight(byte row, byte count = 1) {
		byte tmp = _matrix[row];
		_matrix[row]  = tmp << count | tmp >> (8-count);
	}

	void LEDScreen::shiftRight(byte count = 1){
		for ( byte x = 0; x < _rows; x++) {
			shiftRowRight(x, count);
		}
	}
	void LEDScreen::shiftLeft(byte count = 1) {
		for ( byte x = 0; x < _rows; x++) {
			shiftRowLeft(x, count);
		}
	}
	void LEDScreen::shiftTop(){
		byte x = _rows - 1;
		byte tmp = _matrix[x--];

		for ( ; x >= 0 && x < _rows ; x--) {
			_matrix[x + 1] = _matrix[x];
		}

		_matrix[0] = tmp;
	}
	void LEDScreen::shiftBottom() {
		byte x = 0;
		byte tmp = _matrix[x++];

		for (; x < _rows; x++) {
			_matrix[x - 1] = _matrix[x];
		}
		_matrix[x -1] = tmp;
	}

byte * LEDScreen::getMatrix(){
	return _matrix;
}

byte LEDScreen::getNumCols(){
	return _cols;
}

byte LEDScreen::getNumRows(){
	return _rows;
}

void LEDScreen::clear(){
	memset(_matrix, 0, _size);
}