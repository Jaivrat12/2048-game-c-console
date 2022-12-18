#include "windows.h"
#include "time.h"

#define ROWS 4
#define COLS 4

#define EASY 1
#define HARD 2

#define GRAY 8
#define BLUE 9
#define GREEN 10
#define CYAN 11
#define RED 12
#define PINK 13
#define YELLOW 14
#define WHITE 15

#define CLS system("CLS")
#define PAUSE system("PAUSE")
#define wait(n) _sleep(1 * n * 1000)

int getRandomPos(int upper) {

    return rand() % (upper + 1);
}

// IMP NOTE: This "gotoxy()" needs "windows.h" library!!!
static const COORD startCoords = {0,0};

void gotoxy(int x,int y) {

    COORD coord = {x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(int color) {

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void resetColor() {

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

int getConsoleWidth() {

	CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

int getConsoleHeight() {

	CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

/*

// THERE IS CONSOLE_FONT_INFOEX, etc to change font size...

inline void setFontSize(int a, int b) {

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();

    lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(hStdOut, 0, lpConsoleCurrentFontEx);
    lpConsoleCurrentFontEx->dwFontSize.X = a;
    lpConsoleCurrentFontEx->dwFontSize.Y = b;
    SetCurrentConsoleFontEx(hStdOut, 0, lpConsoleCurrentFontEx);
}
*/

/*
Alternative gotoxy()...

// IMP NOTE: This "gotoxy()" needs "windows.h" library!!!
void gotoxy(int x, int y) {

    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD new = {x, y};
    SetConsoleCursorPosition(out, new);
}
*/
