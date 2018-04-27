
#include "Screen.h";

Screen::Screen(char rows, char cols = 8 ) {
	_cols = cols;
	_rows = rows;
	_size = (rows*cols+8-1)/8;
	_matrix = (char*) calloc(_size, 0);
}

Screen::~Screen() {
	free(_matrix);
}

void Screen::setLed(bool state, char row, char col){
	char _tmp = 0x01;

	if (state ) {
		_matrix[row] = (_matrix[row] | (_tmp << col));
	} else {
		_matrix[row] = (_matrix[row] & ~ (_tmp << col));
	}
}

void Screen::toggleLed(char row, char col){
	char _tmp = 0x01;

	_matrix[row] = (_matrix[row] ^ (_tmp << col));
}

void Screen::toggle(){
	char x;
	for ( x = 0; x < _rows; x++) {
		_matrix[x] = ~_matrix[x];
	}
}

char * Screen::getMatrix(){
	return _matrix;
}

char Screen::getNumCols(){
	return _cols;
}

char Screen::getNumRows(){
	return _rows;
}


void Screen::clear(){
	memset(_matrix, 0, _size);
}