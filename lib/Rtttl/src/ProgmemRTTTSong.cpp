
#include "ProgmemRTTTSong.h"

ProgmemRTTTSong::ProgmemRTTTSong(char * song) {
	_buffer = song;

	reset();
}
char ProgmemRTTTSong::next() {
	//TODO osetrit konec pameti
	return pgm_read_byte_near(_buffer + _pos++);
}

char ProgmemRTTTSong::get() {
	return pgm_read_byte_near(_buffer + _pos);
}

void ProgmemRTTTSong::reset(){
	_pos = 0;
}
