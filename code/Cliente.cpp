/*
 * Cliente.cpp
 *
 *  Created on: 2 de Out de 2011
 *      Author: migueloliveira
 */

#include "Cliente.h"

unsigned int Cliente::numClientes = 0;

Cliente::Cliente() : ID(0), NIF(NULL), pontos(0) //Constructor por defeito da classe Cliente
{ }

//Constructor da classe Cliente
Cliente::Cliente(const string& nome, const long& BI,Data* data_nascimento, Contato* contato, const long& NIF_) : Pessoa(nome, BI, data_nascimento, contato)
{
	ID = ++numClientes;
	pontos = 0;
	ultimo_aluguer = new Data(returnDataActual().getDia(),returnDataActual().getMes(),returnDataActual().getAno());
	ativo = true;
	NIF = new long (NIF_);
}

Cliente::~Cliente() //Destructor da classe Cliente
{
	delete NIF;
}

const unsigned int& Cliente::getID() const //retorna o ID do cliente
{
	return ID;
}

const long* Cliente::getNIF() const //retorna o NIF do cliente
{
	return NIF;
}
const unsigned int& Cliente::getPontos() const //retorna os pontos do cliente
{
	return pontos;
}

const Data* Cliente::getUltimoAluguer() const //retorna a data do ultimo aluguer do cliente
{
	return ultimo_aluguer;
}

const bool Cliente::getAtivo() const
{
	return ativo;
}

void Cliente::addAluguer(Aluguer* novoAluguer) //adiciona o aluguer novoAluger ao cliente
{
	Pessoa::addAluguer(novoAluguer);
	addPontos(novoAluguer->getPontos());
}

void Cliente::cancelAluguer(Aluguer* al) //cancela o aluguer al do cliente
{
	addPontos(0- (al->getPontos()) );
	Pessoa::cancelAluguer(al);
}

void Cliente::addPontos(int pontos_novos) //adiciona pontos_novos aos pontos do Cliente
{
	pontos += pontos_novos;
}

bool Cliente::hasAluguerAtrasados() const //verifica se o cliente tem alugueres em atraso
{
	for (vector<Aluguer*>::const_iterator it = alugueres.begin(); it != alugueres.end(); it++)
		if ((*it)->getDiasParaAcabar() < 0)
			return true;
	return false;
}

bool Cliente::descontoCandidate() const //verifica se o cliente tem direito a um desconto
{
	if ( pontos >= 5000 )
		return true;
	return false;
}

unsigned int Cliente::getNumClientes() //retorna o numero de clientes existentes
{
	return numClientes;
}

void Cliente::setNumClientes(unsigned int numclientes) //altera o numero de clientes existentes para numclientes
{
	numClientes = numclientes;
}

void Cliente::anularCliente() //decrementa o numero de clientes
{
	numClientes--;
}

void Cliente::setID(unsigned int& ID_) //altera o ID do cliente para ID_
{
	ID = ID_;
}

void Cliente::setUltimoAluguer(Data* ultimo_aluguer_)
{
	ultimo_aluguer = ultimo_aluguer_;
}

void Cliente::setAtivo(bool ativo_)
{
	ativo = ativo_;
}

void Cliente::setNIF(const string& NIF_) //altera o NIF do cliente para NIF_
{
	NIF = new long ( atoi(NIF_.c_str()) );
}

void Cliente::saveInfo(fstream& outFile) const //grava o cliente para um ficheiro
{
	outFile << ID << '\n';
	outFile << *NIF << '\n';
	ultimo_aluguer->saveData(outFile);
	outFile << ativo << '\n';

	Pessoa::savePessoa(outFile);
}

void Cliente::loadInfo(fstream& inFile) //carrega o cliente de um ficheiro
{
	string NIF_;

	inFile >> ID;
	inFile.ignore(1,'\n');

	getline(inFile,NIF_);
	setNIF(NIF_);
		
	Data* d = new Data();
	d->loadData(inFile);
	setUltimoAluguer(d);

	inFile >> ativo;
	inFile.ignore(1,'\n');

	Pessoa::loadPessoa(inFile);
}

void Cliente::showInfo() const //mostra as informacoes do cliente
{
	cout << "\nID: " << ID << endl;
	cout << "\nIdade: " << getIdade() << endl;
	Pessoa::showInfo();
	cout << "\nNIF: " << *NIF << endl;
	cout << "\nUltimo aluguer: " << *ultimo_aluguer << endl;
}

int Cliente::subclasse() const //retorna a subclasse da Pessoa(2=Cliente)
{
	return 2;
}

bool Cliente::operator < (const Cliente& cliente2) const //verifica se o cliente e menor que o cliente2
{
	return ( ID < cliente2.getID() );
}

