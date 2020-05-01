#ifndef LEDPANEL_EFECTS_H_
#define LEDPANEL_EFECTS_H_

const byte efects [][3]= {
    {B00000000, B00000000, B00000000}, //0  blank
	{B11111111, B11111111, B11111111}, //1  full
	{B11111111, B10000001, B11111111}, //2  big rectangle
	{B00000000, B01111110, B00000000}, //3  small rectangle
	{B11110000, B11110000, B11110000}, //4  left box
	{B00001111, B00001111, B00001111}, //5  right box
    {B11111111, B01111110, B00111100}, //6  top triangle
    {B00111100, B01111110, B11111111}, //7  bottom triangle
    {B11111111, B00000000, B00000000}, //8  top line
    {B00000000, B11111111, B00000000}, //9  middle line
    {B00000000, B00000000, B11111111}, //10  bottom line
    {B10000000, B10000000, B10000000}, //11  1 first col
    {B01000000, B01000000, B01000000}, //12  2 first col
    {B00100000, B00100000, B00100000}, //13  3 first col
    {B00010000, B00010000, B00010000}, //14  4 first col
    {B00001000, B00001000, B00001000}, //15  5 first col
    {B00000100, B00000100, B00000100}, //16  6 first col
    {B00000010, B00000010, B00000010}, //17  7 first col
    {B00000001, B00000001, B00000001}, //18  8 first col
    {B10000001, B10000001, B10000001}, //19  1 1 a 8 cols
    {B01000010, B01000010, B01000010}, //20  2 2 a 7 cols
    {B00100100, B00100100, B00100100}, //21  3 3 a 6 cols
    {B00011000, B00011000, B00011000}, //22  4 4 a 5 cols
};
#endif //LEDPANEL_EFECTS_H_