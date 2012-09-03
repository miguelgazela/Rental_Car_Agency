/*
 * display.cpp
 */

#include "display.h"

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clearScreen(void)
{
	COORD upperLeftCorner = {0,0};
	DWORD charsWritten;
	DWORD conSize;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO  csbi;

	GetConsoleScreenBufferInfo(hCon, &csbi);
	conSize = csbi.dwSize.X * csbi.dwSize.Y;

	// fill with spaces
	FillConsoleOutputCharacter(hCon, TEXT(' '), conSize, upperLeftCorner, &charsWritten);
	GetConsoleScreenBufferInfo(hCon, &csbi);
	FillConsoleOutputAttribute(hCon, csbi.wAttributes, conSize, upperLeftCorner, &charsWritten);

	// cursor to upper left corner
	SetConsoleCursorPosition(hCon, upperLeftCorner);
}

void showFrames()
{
	int x = 0; //coordenada x
	int y = 0; //coordenada y

	// caixa superior
	for (x = 54, y = 1; x < 125; x++)
	{
		gotoxy(x,5); cout << '-';
	}

	// info do projeto
	gotoxy(1,66); cout << "      |   Projeto 1 - AEDA - AGENCIA DE ALUGUER DE VIATURAS FEUP - Produzido por Miguel Oliveira (ei10076@fe.up.pt) e Afonso Caldas (ei10051@fe.up.pt) - " << returnDataActual() << " |";
}

void clrln(int y)
{
	for (int x = 1; x < 176; x++)
	{
		gotoxy(x,y);
		cout << ' ';
	}
}

void setcolor(unsigned int color)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon,color);
}

void maximizeScreenBufferAndConsole()
{
	HANDLE hOut;
	COORD NewSize;
	SMALL_RECT DisplayArea = {0, 0, 0, 0};

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	//buffer
	NewSize.X = 196;
	NewSize.Y = 250;
	SetConsoleScreenBufferSize(hOut, NewSize);

	//Consola
	NewSize = GetLargestConsoleWindowSize(hOut);
	DisplayArea.Right = NewSize.X - 1;
	DisplayArea.Bottom = NewSize.Y - 1;

	SetConsoleWindowInfo(hOut, TRUE, &DisplayArea);
}




