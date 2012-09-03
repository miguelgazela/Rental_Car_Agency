/*
 * Contato.cpp
 *
 *  Created on: 1 de Out de 2011
 *      Author: migueloliveira
 */

#include "Contato.h"


Contato::Contato() : pais(NULL), morada(NULL), cidade(NULL), codigo_postal(NULL), phoneNumber(NULL), email(NULL) //Constructor por defeito da classe Contato
{ }

//Constructor da classe Contato
Contato::Contato(const string& pais_, const string& morada_, const string& cidade_, const string& codigo_p, const long& phoneNum, const string& e_mail)
{
	pais = new string(pais_);
	morada = new string (morada_);
    cidade = new string (cidade_);
    codigo_postal = new string (codigo_p);
    phoneNumber = new long (phoneNum);
    email = new string (e_mail);
}

Contato::~Contato() //Destructor da classe Contato
{
	delete pais;
	delete morada;
    delete cidade;
    delete codigo_postal;
    delete phoneNumber;
    delete email;
}

const string& Contato::getPais() const //retorna o pais do contato
{
	return *pais;
}

const string& Contato::getMorada() const //retorna a morada do contato
{
	return *morada;
}

const string& Contato::getCidade() const //retorna a cidade do contato
{
	return *cidade;
}

const string& Contato::getPostal() const //retorna o codigo postal do contato
{
	return *codigo_postal;
}

const string& Contato::getEmail() const //retorna o email do contato
{
	return *email;
}

const long& Contato::getPhoneNumber() const //retorna o numero de telefone do contato
{
	return *phoneNumber;
}

void Contato::setPais(const string& pais_) //altera o pais do contato para pais_
{
	pais = new string (pais_);
}

void Contato::setMorada(const string& morada_) //altera a morada do contato para morada_
{
	morada = new string (morada_);
}

void Contato::setCidade(const string& cidade_) //altera a cidade do contato para cidade_
{
	cidade = new string (cidade_);
}

void Contato::setPostal(const string& codigo_postal_) //altera o codigo postal do contato para codigo_postal_
{
	codigo_postal = new string (codigo_postal_);
}

void Contato::setPhoneNumber(const string& phoneNumber_) //altera o numero de telefone do contato para phoneNumber_
{
	phoneNumber =  new long ( atoi(phoneNumber_.c_str()) );
}

void Contato::setEmail(const string& email_) //altera o email do contato para email
{
	email = new string (email_);
}

void Contato::saveContato(fstream& outFile) const //grava o contato num ficheiro
{
	outFile << *pais << '\n';
	outFile << *morada << '\n';
	outFile << *cidade << '\n';
	outFile << *codigo_postal << '\n';
	outFile << *phoneNumber << '\n';
	outFile << *email << '\n';
}

void Contato::loadContato(fstream &inFile) //carrega o contato de um ficheiro
{
	string pais_, morada_, cidade_, codigo_postal_, phoneNumber_, email_;

	getline(inFile,pais_);
	getline(inFile,morada_);
	getline(inFile,cidade_);
	getline(inFile,codigo_postal_);
	getline(inFile,phoneNumber_);
	getline(inFile,email_);

	setPais(pais_);
	setMorada(morada_);
	setCidade(cidade_);
	setPostal(codigo_postal_);
	setPhoneNumber(phoneNumber_);
	setEmail(email_);
}

ostream& operator <<(ostream& os, const Contato& c) //faz o display do contato
{
	os << "Pais: " << c.getPais() << endl;
	os << "\nMorada: " << c.getMorada() << endl;
	os << "\nCidade: " << c.getCidade() << endl;
	os << "\nCodigo-postal: " << c.getPostal() << endl;
	os << "\nContato telefonico: " << c.getPhoneNumber() << endl;
	os << "\ne-mail: " << c.getEmail() << endl;
	return os;
}

