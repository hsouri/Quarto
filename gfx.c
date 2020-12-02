//Rev.2.1

#include "gfx.h"

#define MIN_LOG 20
#define MAX_LOG 100

#define MAX_H FIRST_LOG_LINE+((LOG_SIZE<MIN_LOG) ? MIN_LOG :((LOG_SIZE>MAX_LOG) ? MAX_LOG : LOG_SIZE))
#define MAX_L 4*(SIZE_RATIO+5)+2

void initScreen()
{
	HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX fontInfo;
	COORD requiredSize;
	COORD maxSize = GetLargestConsoleWindowSize(stdHandle);
	SMALL_RECT frame;

	fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	requiredSize.X = MAX_L;
	requiredSize.Y = MAX_H;
	frame.Left = 0;
	frame.Top = 0;
	frame.Right = (maxSize.X < requiredSize.X)? maxSize.X : requiredSize.X-1;
	frame.Bottom = (maxSize.Y < requiredSize.Y)? maxSize.X : requiredSize.Y-1;

	
	SetConsoleScreenBufferSize(stdHandle, requiredSize);
	GetCurrentConsoleFontEx(stdHandle, 0, &fontInfo);
	fontInfo.dwFontSize.X = 8;
	fontInfo.dwFontSize.Y = 8;
	SetCurrentConsoleFontEx(stdHandle,	0, &fontInfo);	
	SetConsoleWindowInfo(stdHandle, 1, &frame);
}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = (x < 0) ? 0 : ((x > MAX_L-1 ) ? MAX_L-1 : x);
	coord.Y = (y < 0) ? 0 : ((y > MAX_H-1 ) ? MAX_H-1 : y);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
int getCursorXPos(){
	CONSOLE_SCREEN_BUFFER_INFO inf;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &inf);
	return inf.dwCursorPosition.X;
}

int getCursorYPos(){
	CONSOLE_SCREEN_BUFFER_INFO inf;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &inf);
	return inf.dwCursorPosition.Y;
}

int getLineSize(){
	CONSOLE_SCREEN_BUFFER_INFO inf;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &inf);
	return inf.dwSize.X;
}

void clearLine(int offset)
{
	int lineSize = getLineSize();
	int y = getCursorYPos();
	int numOfLines = (offset < 0 ) ? 0 : (((y + offset) > MAX_H-1) ? MAX_H-1-y-1 : offset);
	int i = 0;
	for(i = 0; i <= numOfLines; i++){
		int len = lineSize;
		gotoxy(0, y+i);
		while(len){
			putchar(' ');
			len--;
		}
	}
	gotoxy(0, y);
}


#define MIN_SIZE 17 //Minimum size allowd

void drawTable(int originX, int originY, int cellSize)
{
	int y, x;
	
	if(cellSize < MIN_SIZE)
		return;

	//4 cells(size+4+1) [+1 considering left seperator of each cell]
	//+ 1 [for one last seperator]
	// thus 4(cellSize+5)+1

	for(y = originY; y < originY+4*(cellSize+5)+1; y++) {
		x = originX;
		for(x = originX; x < originX+4*(cellSize+5)+1; x++){
			if(y%(cellSize+5) == originY ) {
				gotoxy(x, y);
				putchar('-');
			}
			else if(x%(cellSize+5) == originX ) {
				gotoxy(x, y);
				putchar('|');
			}
		}
	}
	putchar('\n');
}


//shape draw functions forward declarations
void drawRect(int xOrig, int yOrig, int rect, int size);
void drawCircle(int xOrig, int yOrig, int circle, int size);

void drawPiece(int x, int y, int shape, int size) {
	
	if(size < MIN_SIZE) return;

    if(shape & SHAPE_BIT_MASK) {
        drawRect(x,y,shape, size);
    }
    else {
        drawCircle(x,y,shape, size);
    }
}


void drawRect(int xOrig, int yOrig, int rect, int size) {
	int rectLen = 0;
	int shapeLowerBoundY = 0, shapeUpperBoundY = 0;
	int shapeLowerBoundX = 0, shapeUpperBoundX = 0;
	int fill = 0;
	char color = ' ';
	int x,y;

	rectLen = (rect & SIZE_BIT_MASK)? size : size/2;
	rectLen--;
	fill = (rect & FILL_BIT_MASK)? TRUE : FALSE;
	color = (rect & COLOR_BIT_MASK)? BLACK : WHITE;
    
	shapeLowerBoundY = yOrig+(size-rectLen)/2;
	shapeUpperBoundY = rectLen+shapeLowerBoundY;
	shapeLowerBoundX = xOrig+(size-rectLen)/2;
	shapeUpperBoundX = rectLen+shapeLowerBoundX;    
    
	for (y = yOrig; y < yOrig+size; y++) {
		for (x = xOrig; x < xOrig+size; x++) {
			
			if(x < 0 || y < 0 ) continue;

			//Check if inside rectangular area
			if((shapeLowerBoundY <= y &&  y <= shapeUpperBoundY) &&
				(shapeLowerBoundX <= x &&  x <= shapeUpperBoundX)) {

				//Print color character if on the edge anyway
				if((shapeLowerBoundY == y ||  y == shapeUpperBoundY) || 
					(shapeLowerBoundX == x ||  x == shapeUpperBoundX)) {
					gotoxy(x,y);
					putchar(color);
				}
				//If inside, print only if shape is filled
				else if(fill){
					gotoxy(x,y);
					putchar(color);
				}
			}
		}
	}
}

void drawCircle(int xOrig, int yOrig, int circle, int size) {
	double centerY = yOrig+size/2.0;
	double centerX = xOrig+size/2.0;
	int circleRadius = 0;
	int fill = 0;
	char color = ' ';
	int x,y;

	circleRadius = (circle & SIZE_BIT_MASK)? size/2 : size/4;
	fill = (circle & FILL_BIT_MASK)? TRUE : FALSE;
	color = (circle & COLOR_BIT_MASK)? BLACK : WHITE;
    
	for (y = yOrig; y < yOrig+size; y++) {
		for (x = xOrig; x < xOrig+size; x++) {

			//circle formula: sqrt((x-size/2)^2 + (y-size/2)^2) = r
			double val = sqrt(pow(x-centerX, 2)+pow(y-centerY,2.0));
			if(x < 0 || y < 0 ) continue;
			
			if (fill) {
				if(val <= circleRadius ) {
					gotoxy(x,y);
					putchar(color);
				}
			}
			else if (circleRadius-1 <= val && val <= circleRadius) {
				gotoxy(x,y);
				putchar(color);
			}
		}
	}
}