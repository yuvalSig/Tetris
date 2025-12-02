#include "General.h"


void gotoxy(int x, int y) {
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;		// Coords of the cursor's position
	cout.flush();				// Flushes the buffer
	dwCursorPosition.X = x;		// Set the cursor's x position to given x
	dwCursorPosition.Y = y;		// Set the cursor's y position to given y
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);		// Sets the output's cursor position to given dwCursorPosition
}

void clrscr() {
	system("cls");	// System allows us to activate windows commands, "cls" command is the clear screen command
}
