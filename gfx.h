//Rev.2.1
#ifndef __GFX___
#define __GFX___

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

//Size argument used draw shapes
#define SIZE_RATIO 19

//Table dimensions, DO NOT CHANGE THESE
//You may need to use them for indexing purposes
#define CELLS_PER_ROW 4
#define ROWS_PER_TABLE 4

//Color characters
#define BLACK '+'
#define WHITE '-'

//Line number of first empty line after table in console
#define FIRST_LOG_LINE ROWS_PER_TABLE*(SIZE_RATIO+5)+1

//Number of lines used after table to propmt user or log program events
#define LOG_SIZE 20

//You can use these bit masks to compose or decompoes shape descriptors
#define SHAPE_BIT_MASK 0xFF000000
#define COLOR_BIT_MASK 0x00FF0000
#define FILL_BIT_MASK 0x0000FF00
#define SIZE_BIT_MASK 0x000000FF

#if defined _WIN64 || defined _WIN32
#include <windows.h>

//x and y are upper left corners of table
void drawTable(int x, int y, int cellSize);

//x and y are upper left corners of the rectangular space occupied by shape.
// this space is equal for all shapes, actual shape is drawn at the center
void drawPiece(int x, int y, int shape, int size);
/*
shape is the integer that describes the selected piece.
(e.g 0x00FF00FF which is the same as CBHL. Refer to phase 1 description.)
*/

//Sets console buffer and font size for opmtimum diplay
void initScreen();
//You may need to press window maximize button to see effects
//This is usally called when initializing application in the main function 
/* Usage:
int main() {
	
	do variable declarations here
	
	initScreen();
	
	rest of main function

	return 0;
}
*/

//The following function manipulates cursor position
void gotoxy(int x, int y);
//Clears the line the cursor is currently in + next offset lines
void clearLine(int offset);

/*
EXAMPLE: Following code snippet clears first three log lines:

	gotoxy(0, FIRST_LOG_LINE);
	clearLine(3);

*/

//Get cursor position

int getCursorYPos();
int getCursorXPos();

#endif
#endif