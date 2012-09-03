/*
 * structs.h
 *
 *  Created on: 26 de Out de 2011
 *      Author: migueloliveira
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_

#include <string>
using namespace std;

struct pesquisaOficina {
	string nome;
	string cidade;
	int distancia_inf;
	int distancia_sup;
	int numFuncionarios_inf;
	int numFuncionarios_sup;
};

struct pesquisaCF {
	string nome;
	long BI;
	string pais;
	string morada;
	string cidade;
	string codigopostal;
	long phone;
	string email;
	int idade_inf;
	int idade_sup;
	long NIF;
	int vencimento_inf;
	int vencimento_sup;
};

struct pesquisaAluguer {
	string nomeCliente;
	string nomeFuncionario;
	string marcaViatura;
	int valor;
	int valorOp;
	int dias;
	int diasOp;
};

struct pesquisaViatura {
	string marca;
	string modelo;
	string matricula;
	string transmissao;
	string combustivel;
	int ano;
	int anoOp;
	int nXalugado;
	int nXalugadoOp;
	int precoPorDia_inf;
	int precoPorDia_sup;
	int cv;
	int cvOp;
	int cilindrada;
	int cilindradaOp;
};

void nulificarOficina(pesquisaOficina& p);
int numCriteriosOficina(pesquisaOficina& p);

void nulificarCF(pesquisaCF& p);
int numCriteriosCF(pesquisaCF& p);

void nulificarAluguer(pesquisaAluguer& p);
int numCriteriosAluguer(pesquisaAluguer& p);

void nulificarViatura(pesquisaViatura& p);
int numCriteriosViatura(pesquisaViatura& p);


#endif /* STRUCTS_H_ */
