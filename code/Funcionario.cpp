/*
 * Funcionario.cpp
 *
 *  Created on: 2 de Out de 2011
 *      Author: migueloliveira
 */

#include "Funcionario.h"

unsigned int Funcionario::numFuncionarios = 0;

Funcionario::Funcionario() : ID(0), vencimento(0) //Construtor por defeito da classe Funcionario
{ }

//Constructor da classe Funcionario
Funcionario::Funcionario(const string& nome, const long& BI, Data* data_nascimento, Contato* contato, unsigned int vencimento) : Pessoa(nome, BI, data_nascimento, contato), vencimento(vencimento)
{
	ID = ++numFuncionarios;
}

Funcionario::~Funcionario() //Destructor da classe Funcionario
{ }

const unsigned int& Funcionario::getID() const //retorna o ID do funcionario
{
	return ID;
}

const unsigned int Funcionario::getVencimento() const //retorna o vencimento do funcionario
{
	return vencimento;
}

void Funcionario::setNumFuncionarios(unsigned int numfuncionarios) //altera o numero de funcionarios para numfuncionarios
{
	numFuncionarios = numfuncionarios;
}

void Funcionario::anularFuncionario() //decrementa o numero de funcionarios
{
	numFuncionarios--;
}

void Funcionario::setVencimento(unsigned int vencimento_) //altera o vencimento do funcionario para vencimento_
{
	vencimento = vencimento_;
}

void Funcionario::setID(unsigned int& ID_) //altera o ID do funcionario para ID_
{
	ID = ID_;
}

void Funcionario::saveInfo(fstream& outFile) const //grava o funcionario para um ficheiro
{
	outFile << ID << '\n';
	outFile << vencimento << '\n';

	Pessoa::savePessoa(outFile);
}

void Funcionario::loadInfo(fstream& inFile) //carrega o funcionario para um ficheiro
{
	inFile >> ID;
	inFile.ignore(1,'\n');

	inFile >> vencimento;
	inFile.ignore(1,'\n');

	Pessoa::loadPessoa(inFile);
}

void Funcionario::showInfo() const //mostra as informacoes do funcionario
{
	cout << "ID: " << ID << endl;
	cout << "Vencimento: " << vencimento << endl;
	cout << "Idade: " << getIdade() << endl;
	Pessoa::showInfo();
}

int Funcionario::subclasse() const //retorna a subclasse da Pessoa (1=funcionario)
{
	return 1;
}

bool Funcionario::operator < (Funcionario& f2) //verifica se o funcionario e menor que o funcionario f2
{
	if ( ID < f2.getID() )
		return true;
	return false;
}

