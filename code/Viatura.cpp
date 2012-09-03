/*
 * Viatura.cpp
 *
 *  Created on: 1 de Out de 2011
 *      Author: migueloliveira
 */

#include "Viatura.h"

#include <iostream>
using namespace std;

unsigned int Viatura::num_viaturas = 0;

//construtor por defeito da classe Viatura
Viatura::Viatura(): marca(NULL), modelo(NULL), matricula(NULL), transmissao(NULL), combustivel(NULL), registo(NULL), nXalugado(0), precoPorDia(0), lugares(0), cv(0), cilindrada(0), disponivel(false), ar_condicionado(false)
{
	ID = 0;
}

//construtor da classe Viatura
Viatura::Viatura(const string& marca_, const string& modelo_, const string& matricula_, const string& transmissao_, const string& combustivel_, Data* registo_, unsigned int precoPorDia_, unsigned int lugares_, unsigned int cv_, unsigned int cilindrada_, bool ar_condicionado_) : ID(++num_viaturas) //construtor da classe Viatura
{
	if ( returnDataActual() - (*registo_) < 0 )
		throw DataInvalida();
	marca = new string (marca_);
	modelo = new string (modelo_);
	matricula = new string (matricula_);
	transmissao = new string (transmissao_);
	combustivel = new string (combustivel_);
	registo = registo_;
	nXalugado = 0;
	precoPorDia = precoPorDia_;
	lugares = lugares_;
	cv = cv_;
	cilindrada = cilindrada_;
	ar_condicionado = ar_condicionado_;
	disponivel = true;


}

Viatura::~Viatura()//destrutor da classe Viatura
{
	delete marca;
	delete modelo;
	delete matricula;
	delete transmissao;
	delete combustivel;
	delete registo;
}

const unsigned int& Viatura::getID() const //devolve o ID da viatura
{
	return ID;
}

const string& Viatura::getMarca() const //devolve a marca da viatura
{
	return *marca;
}


const string& Viatura::getModelo() const //devolve o modelo da viatura
{
	return *modelo;
}


const string& Viatura::getMatricula() const //devolve a matricula da viatura
{
	return *matricula;
}

const string& Viatura::getTransmissao() const //devolve a transmissao da viatura
{
	return *transmissao;
}

const string& Viatura::getCombustivel() const //devolve o combustivel da viatura
{
	return *combustivel;
}


const Data* Viatura::getRegisto() const //devolve a data de registo da viatura
{
	return registo;
}

const unsigned int& Viatura::getnXalugado() const //devolve o numero de vezes que a viatura foi alugada
{
	return nXalugado;
}

const unsigned int& Viatura::getPrecoPorDia() const //devolvee o preco diario da viatura
{
	return precoPorDia;
}

const unsigned int& Viatura::getLugares() const //devolve o numero de lugares da viatura
{
	return lugares;
}

const unsigned int& Viatura::getCV() const //devolve os cavalos da viatura
{
	return cv;
}

const unsigned int& Viatura::getCilindrada() const //devolve a cilindrada da viatura
{
	return cilindrada;
}

bool Viatura::getDisponivel() const //devolve o estado de disponibilidade da viatura
{
	return disponivel;
}

bool Viatura::getAr_condicionado() const //devolve o estado de ar condicionado da viatura
{
	return ar_condicionado;
}


void Viatura::setNumViaturas(unsigned int numViaturas) //altera o numero de viatura para numViaturas
{
	num_viaturas = numViaturas;
}

void Viatura::anularViatura() //decrementa o numero de viaturas
{
	num_viaturas--;
}

void Viatura::setID(const unsigned int& ID_) //altera o ID da viatura para ID_
{
	ID = ID_;
}

void Viatura::setMarca(const string& marca_) //altera a marca da viatura para marca_
{
	marca = new string (marca_);
}

void Viatura::setModelo(const string& modelo_) //altera o modelo da viatura para modelo_
{
	modelo = new string (modelo_);
}

void Viatura::setMatricula(const string& matricula_) //altera a matricula da viatura para matricula_
{
	matricula = new string (matricula_);
}

void Viatura::setTransmissao(const string& transmissao_) //altera a transmissao da viatura para transmissao_
{
	transmissao = new string (transmissao_);
}

void Viatura::setCombustivel(const string& combustivel_) //altera o combustivel da viatura para combustivel_
{
	combustivel = new string (combustivel_);
}

void Viatura::setRegisto(Data* registo_) //altera a data de registo da viatura para registo_
{
	registo = registo_;
}

void Viatura::incnXalugado() //incrementa o numero de vezes que a viatura foi alugada
{
	nXalugado++;
}

void Viatura::setPrecoPorDia(const string& precoPorDia_) //altera o preco diario da viatura para precoPorDia_
{
	precoPorDia = atoi(precoPorDia_.c_str());
}

void Viatura::setLugares(const string& lugares_) //altera o numero de lugares da viatura para lugares_
{
	lugares = atoi(lugares_.c_str());
}

void Viatura::setCV(const string& cv_) //altera os cavalos da viatura para cv_
{
	cv = atoi(cv_.c_str());
}

void Viatura::setCilindrada(const string& cilindrada_) //altera a cilindrada da viatura para cilindrada_
{
	cilindrada = atoi(cilindrada_.c_str());
}

void Viatura::setDisponivel(bool disponivel_) //altera o estado de disponibilidade da viatura para disponivel_
{
	disponivel = disponivel_;
}

void Viatura::setAr_condicionado(const string& ar_condicionado_) //altera o estado de ar condicionado para ar_condicionado_
{
	if(atoi(ar_condicionado_.c_str()) == 1)
		ar_condicionado = true;
	else
		ar_condicionado = false;
}

void Viatura::saveInfo(fstream& outFile) const //grava a viatura num ficheiro
{
	outFile << ID << '\n';
	outFile << *marca << '\n';
	outFile << *modelo << '\n';
	outFile << *matricula << '\n';
	outFile << *transmissao << '\n';
	outFile << *combustivel << '\n';
	registo->saveData(outFile);
	outFile << nXalugado << ' ' << precoPorDia << ' ' << lugares << ' ' << cv << ' ' << cilindrada << '\n';
	outFile << disponivel << ' ' << ar_condicionado << '\n';
}

void Viatura::loadInfo(fstream& inFile) //carrega a viatura de um ficheiro
{
	string marca_, modelo_, matricula_, transmissao_, combustivel_;

	inFile >> ID;
	inFile.ignore(1,'\n');

	getline(inFile,marca_); setMarca(marca_);
	getline(inFile,modelo_); setModelo(modelo_);
	getline(inFile,matricula_); setMatricula(matricula_);
	getline(inFile,transmissao_); setTransmissao(transmissao_);
	getline(inFile,combustivel_); setCombustivel(combustivel_);

	Data* r = new Data();
	r->loadData(inFile);
	setRegisto(r);

	inFile >> nXalugado >> precoPorDia >> lugares >> cv >> cilindrada;
	inFile.ignore(1,'\n');
	inFile >> disponivel >> ar_condicionado;
	inFile.ignore(1,'\n');
}

void Viatura::showInfo() const //mostra as informacoes da viatura
{
	cout << "Marca: " << *marca << endl << endl;
	cout << "Modelo: " << *modelo << endl << endl;
	cout << "Matricula: " << *matricula << endl << endl;
	cout << "Transmissao: " << *transmissao << endl << endl;
	cout << "Combustivel: " << *combustivel << endl << endl;
	cout << "Data de registo: " << *registo << endl << endl;
	cout << "Numero de vezes alugado: " << nXalugado << endl << endl;
	cout << "Preco diario: " << precoPorDia << " euros"<< endl << endl;
	cout << "Lugares: " << lugares << endl << endl;
	cout << "Cavalos: " << cv << endl << endl;
	cout << "Cilindrada: " << cilindrada << endl << endl;
	cout << "Disponivel: ";
		if(disponivel)
			cout << "Sim\n" << endl;
		else
			cout << "Nao\n" << endl;
	cout << "Ar condicionado: ";
	if(ar_condicionado)
		cout << "Sim\n" << endl;
	else
		cout << "Nao\n" << endl;
}
