/*
 * display.h
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <conio.h>
#include <windows.h>
#include <iostream>
#include "Data.h"

using namespace std;

void gotoxy(int x, int y); //funcao que serve para deslocar o cursor da janela de consola para determinadas coordenadas
void clearScreen(void); //funcao que apaga a consola de comandos
void setcolor(unsigned int color);
void showFrames();
void clrln(int y); // limpa uma determinada linha
void maximizeScreenBufferAndConsole(); //funcao que aumenta o tamanho do buffer e da consola

#endif /* DISPLAY_H_ */
