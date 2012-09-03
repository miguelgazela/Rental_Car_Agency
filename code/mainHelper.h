/*
 * mainHelper.h
 *
 *  Created on: 22 de Out de 2011
 *      Author: migueloliveira
 */

#ifndef MAINHELPER_H_
#define MAINHELPER_H_
#include "Agencia.h"
#include <sstream>
#include <string>
#include <iostream>

#define ENTER	13
#define ESC		27
#define UP		72
#define DOWN	80

using namespace std;

/* ********************************************************
 *
 * PROTÓTIPOS DAS FUNCOES
 *
 * ********************************************************
 */

/* Area de Funcionarios */
bool addNovoFuncionario(Agencia& a);
Funcionario* searchFuncionario(Agencia& a, bool& proceed, bool& didSearch);
void ModifyRemoveFuncionario(Agencia& a, bool& proceed, unsigned int mr);

/* Area de Clientes */
bool addNovoCliente(Agencia& a);
Cliente* searchCliente(Agencia& a, bool& proceed, bool& didSearch, bool atividade);
void ModifyRemoveCliente(Agencia& a, bool& proceed, unsigned int mr);
void reativarCliente(Agencia& a, bool& proceed);
void ModifyRemoveClienteInativo(Agencia& a, bool& proceed, unsigned int mr);


/* Area de Viaturas */
bool addNovaViatura(Agencia& a, int opt);
Viatura* searchViatura(Agencia& a, bool& proceed, int opt, bool& didSearch);
void ModifyRemoveViatura(Agencia& a, bool& proceed, unsigned int mr);
void modifyViatura(Agencia& a, Viatura* v, bool& proceed);

/* Area de Alugueres */
bool addNovoAluguer(Agencia& a);
Aluguer* searchAluguer(Agencia& a, bool& proceed, bool& didSearch);
void ModifyCancelFinishAluguer(Agencia& a, bool& proceed, unsigned int mr);
void modifyAluguer(Agencia& a, Aluguer* al, bool& proceed);

/* Area de Oficinas */
bool addNovaOficina(Agencia& a);
void sendCarToShop(Agencia& a);
void ModifyRemoveOficina(Agencia& a, bool& proceed, int modRem);
void modifyOficina(Agencia& a, bool& proceed, Oficina& of);
Oficina searchOficina (Agencia& a, bool& proceed);
void removeReparacao(Agencia& a, bool& proceed);

/* Outras Funcoes */
void displayMenuPlusArrows(int x, int x_inc, int y, int menu, int& input, int& state, int numStates);
int stateMachine (int numStates, int input, int currentState);
int getArrowKeys();
void pressEnter();
bool isNumber (const string& option);
bool hasNumber (const string& name);
bool validNoum (const string& stringTeste);
bool validateOption (const string& option, const int& op,int escolhas, int x, int y);
bool testProceed(const string& str, bool& proceed);
bool validMail(const string& mail);
bool validMatricula(const string& matricula);
void lerString(string& str, unsigned int op, bool& proceed);
void lerData(int& dia, int& mes, int& ano, bool& proceed);
void readOption(string& option, int& op);
string convertNum(long& num);
template <class T>
void lerNumero(T& num, bool& proceed, unsigned int op);
template <class T>
void showCF(const T* cf);
template <class T>
void modify(Agencia& a, T* cf, bool& proceed);
template <class T>
void searchIt(Agencia& a, vector<T*>& resultados, bool& proceed, int classe, bool& didSearch);

/*Funcoes relacionadas com o display*/
void showMenu(int option); //mostra menus especificos

#endif /* MAINHELPER_H_ */
