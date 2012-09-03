/*
 * mouse.h
 * Created on: 17 de Dez de 2011
 * Author: migueloliveira
 */

#ifndef MOUSE_H_
#define MOUSE_H_

#include <conio.h>
#include <windows.h>

HANDLE hStdin;
DWORD fdwSaveOldMode;

VOID ErrorExit(LPSTR);
VOID MouseEventProc(MOUSE_EVENT_RECORD, int&, int&);

int mouseDoubleClick()
{
    DWORD cNumRead, fdwMode, i;
    INPUT_RECORD irInBuf[128];
    int X = -1, Y = -1;

    // Get the standard input handle.
    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if (hStdin == INVALID_HANDLE_VALUE)
        ErrorExit("GetStdHandle");

    // Save the current input mode, to be restored on exit.
    if (! GetConsoleMode(hStdin, &fdwSaveOldMode) )
        ErrorExit("GetConsoleMode");

    // Enable the window and mouse input events.
    fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    if (! SetConsoleMode(hStdin, fdwMode) )
        ErrorExit("SetConsoleMode");

    do {
		// Wait for the events.
        if (! ReadConsoleInput(
                hStdin,      // input buffer handle
                irInBuf,     // buffer to read into
                128,         // size of read buffer
                &cNumRead) ) // number of records read
            ErrorExit("ReadConsoleInput");

        // Dispatch the events to the appropriate handler.
        for (i = 0; i < cNumRead; i++)
        {
            switch(irInBuf[i].EventType)
            {
                case MOUSE_EVENT: // mouse input
                	MouseEventProc(irInBuf[i].Event.MouseEvent, X, Y);
                    break;
            }
        }
    } while (X == -1 && Y == -1);

    // Restore input mode on exit.
    SetConsoleMode(hStdin, fdwSaveOldMode);

    // calcula o butao em que clicou de acordo com as coordenadas
    if (X >= 73 && X <= 101)
	{
		if (Y > 24 && Y < 28)
			return 0;
		else if (Y > 28 && Y < 32)
			return 1;
		else if (Y > 32 && Y < 36)
			return 2;
		else if (Y > 36 && Y < 40)
			return 3;
		else if (Y > 40 && Y < 44)
			return 4;
		else
			return 100;
	}
	else
		return 100;
}

VOID ErrorExit (LPSTR lpszMessage)
{
    fprintf(stderr, "%s\n", lpszMessage);

    // Restore input mode on exit.
    SetConsoleMode(hStdin, fdwSaveOldMode);

    ExitProcess(0);
}

void MouseEventProc(MOUSE_EVENT_RECORD mer, int& X, int& Y)
{
	if (mer.dwEventFlags == DOUBLE_CLICK)
	{
		X = mer.dwMousePosition.X;
		Y = mer.dwMousePosition.Y;
	}
}

#endif /* MOUSE_H_ */
