/*
 * structs.cpp
 *
 *  Created on: 26 de Out de 2011
 *      Author: migueloliveira
 */

#include "structs.h"

void nulificarOficina(pesquisaOficina& p)
{
	p.cidade = "null";
	p.nome = "null";
	p.distancia_inf = -1;
	p.distancia_sup = 2147483646;
	p.numFuncionarios_inf = -1;
	p.numFuncionarios_sup = 2147483646;
}

int numCriteriosOficina(pesquisaOficina& p)
{
	int num = 0;

	if (p.cidade != "null")
		num++;
	if (p.nome != "null")
		num++;
	if (p.distancia_inf != -1)
		num++;
	if (p.numFuncionarios_inf != -1)
		num++;

	return num;
}

void nulificarCF(pesquisaCF& p)
{
	p.nome = "null";
	p.BI = 0;
	p.pais = "null";
	p.morada = "null";
	p.cidade = "null";
	p.codigopostal = "null";
	p.phone = 0;
	p.email = "null";
	p.idade_inf = 0;
	p.idade_sup = 199;
	p.NIF = 0;
	p.vencimento_inf = -1;
	p.vencimento_sup = 2147483646;
}

int numCriteriosCF(pesquisaCF& p)
{
	int num = 0;

	if (p.nome != "null")
		num++;
	if (p.BI != 0)
		num++;
	if (p.pais != "null")
		num++;
	if (p.morada != "null")
		num++;
	if (p.cidade != "null")
		num++;
	if (p.codigopostal != "null")
		num++;
	if (p.phone != 0)
		num++;
	if (p.email != "null")
		num++;
	if (p.idade_inf != 0)
		num++;
	if (p.NIF != 0)
		num++;
	if (p.vencimento_inf != -1)
		num++;

	return num;
}

void nulificarAluguer(pesquisaAluguer& p)
{
	p.nomeCliente = "null";
	p.nomeFuncionario = "null";
	p.marcaViatura = "null";
	p.valor = 0;
	p.dias = 0;
}

int numCriteriosAluguer(pesquisaAluguer& p)
{
	int num = 0;

	if ( p.valor != 0 )
		num++;
	if (p.dias != 0)
		num++;
	if (p.nomeCliente != "null")
		num++;
	if (p.nomeFuncionario != "null")
		num++;
	if (p.marcaViatura != "null")
		num++;

	return num;
}

void nulificarViatura(pesquisaViatura& p)
{
	p.marca = "null";
	p.modelo = "null";
	p.matricula = "null";
	p.transmissao = "null";
	p.combustivel = "null";
	p.ano = 0;
	p.nXalugado = -1;
	p.precoPorDia_inf = -1;
	p.precoPorDia_sup = 2147483646;
	p.cv = 0;
	p.cilindrada = 0;
}

int numCriteriosViatura(pesquisaViatura& p)
{
	int num = 0;

	if (p.marca != "null")
		num++;
	if (p.modelo != "null")
		num++;
	if (p.matricula != "null")
		num++;
	if (p.transmissao != "null")
		num++;
	if (p.combustivel != "null")
		num++;
	if (p.ano != 0)
		num++;
	if (p.nXalugado != -1)
		num++;
	if (p.precoPorDia_inf != -1)
		num++;
	if (p.cv != 0)
		num++;
	if (p.cilindrada != 0)
		num++;

	return num;
}

