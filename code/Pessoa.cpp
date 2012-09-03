/*
 * Pessoa.cpp
 *
 *  Created on: 1 de Out de 2011
 *      Author: migueloliveira
 */

#include "Pessoa.h"

//Constructor por defeito da classe Pessoa
Pessoa::Pessoa() : nome(NULL), data_nascimento(NULL), contato(NULL), BI(NULL)
{ }

//Constructor da classe Pessoa
Pessoa::Pessoa(const string& nome_, const long& BI_, Data* data_nasc, Contato* contato_) : data_nascimento (data_nasc), alugueres_realizados(0)
{
	nome = new string (nome_);
	contato = contato_;
	BI = new long (BI_);
	if (data_nasc->getAno() > 1970) // o mktime usado na subtracao de datas nao suporta datas anteriores a 1970 em Windows
	{
		double idade = (returnDataActual()-(*data_nascimento))/365.25; // calcula idade da pessoa
		if ( idade < 18 ) // se menor que 18 anos
		{
			throw menorIdade(nome_);
		}
	}
}

//Destructor da classe Pessoa
Pessoa::~Pessoa()
{
	delete nome;
	delete data_nascimento;
	delete contato;
	delete BI;
}

const string& Pessoa::getNome() const //retorna o nome da pessoa
{
	return *nome;
}

int Pessoa::getIdade() const //retorna a idade da pessoa
{
	if (data_nascimento->getAno() > 1970)
		return (returnDataActual()-(*data_nascimento))/365.25;
	else // necessario novamente porque a funcao mktime nao suporta datas anteriores a 1970 em Windows
	{
		Data d = *data_nascimento;
		d.setAno(1971);
		int idade = (returnDataActual() - d)/365.25;
		idade += (1971-(data_nascimento->getAno()));
		return idade;
	}
}

const long& Pessoa::getBI() const //retorna o BI da pessoa
{
	return *BI;
}

const Data* Pessoa::getData() const //retorna a data de nascimento da pessoa
{
	return data_nascimento;
}

Contato* Pessoa::getContato() //retorna o contato da pessoa
{
	return contato;
}

const long* Pessoa::getNIF() const //retorna o NIF da pessoa
{
	long* l = NULL;
	return l;
}

const unsigned int Pessoa::getVencimento() const //retorna o vencimento da pessoa
{
	return 0;
}

unsigned int Pessoa::getNumAlugueresRealizados() const //retorna o numero de alugueres realizados
{
	return alugueres_realizados;
}

const vector<Aluguer*>& Pessoa::getAlugueresActivos() const //retorna os alugueres activos da pessoa
{
	return alugueres;
}

const vector<int>& Pessoa::getIDalugueresActivos() const //retorna os IDs dos alugueres activos da pessoa
{
	return IDs_alugueres;
}

bool Pessoa::hasAluguer(Aluguer* al) //verifica se a pessoa tem o aluguer al activo
{
	int pos = BinarySearch(alugueres, *al);

	if (pos != -1)
		return true;
	return false;
}

void Pessoa::addAluguer(Aluguer* novo_aluguer) //adiciona o aluguer novo_aluguer a pessoa
{
	alugueres.push_back(novo_aluguer);
}

void Pessoa::showAlugueresActivos() const //mostra os alugueres activos da pessoa
{
	for (unsigned int i = 0; i < alugueres.size(); i++)
	{
		alugueres.at(i)->showInfo();
	}
}

void Pessoa::finishAluguer(Aluguer* al) //termina o aluguer al da pessoa
{
	alugueres_realizados++;
	cancelAluguer(al);
}

void Pessoa::cancelAluguer(Aluguer* al) //cancela o aluguer al da pessoa
{
	int pos = BinarySearch(alugueres, *al);
	alugueres.erase(alugueres.begin()+pos);
}

bool Pessoa::hasAlugueresActivos() const //verifica se a pessoa tem alugueres activos
{
	return (!alugueres.empty());
}

void Pessoa::showInfo() const //mostra as informacoes da pessoa
{
	cout << "\nNome: " << *nome << endl; // fazer uma funcao para mostrar so o primeiro e ultimo nome
	cout << "\nData de nascimento: " << *data_nascimento << endl;
	cout << endl << (*contato);
	cout << "\nBI: " << *BI << endl;
}

void Pessoa::setNome(const string& nome_) //altera o nome da pessoa para nome_
{
	nome = new string (nome_);
}

void Pessoa::setBI(const string& BI_) //altera o BI da pessoa para BI_
{
	BI = new long ( atoi(BI_.c_str()) );
}

void Pessoa::setData(Data* data_n) //altera a data de nascimento da pessoa para data_n
{
	data_nascimento = data_n;
}

void Pessoa::setContato(Contato* cont) //altera o contato da pessoa para cont
{
	contato = cont;
}

void Pessoa::savePessoa(fstream& outFile) const //grava a viatura num ficheiro
{
	outFile << *nome << '\n';
	outFile << *BI << '\n';

	data_nascimento->saveData(outFile);
	contato->saveContato(outFile);

	outFile << alugueres_realizados << '\n';

	outFile << alugueres.size() << ' ';
	for(vector<Aluguer*>::const_iterator it = alugueres.begin(); it != alugueres.end(); it++)
		outFile << (*it)->getID() << ' ';

	outFile << '\n';
}

void Pessoa::loadPessoa(fstream& inFile) //carrega a pessoa de um ficheiro
{
	string nome_, BI_;
	unsigned int numAlugueresON, aluguerID;

	getline(inFile,nome_);
	getline(inFile,BI_);
	setNome(nome_);
	setBI(BI_);
	Data* d = new Data();
	d->loadData(inFile);
	setData(d);

	Contato* c = new Contato();
	c->loadContato(inFile);
	setContato(c);

	inFile >> alugueres_realizados;
	inFile.ignore(1,'\n');

	inFile >> numAlugueresON;
	while ( numAlugueresON > 0 )
	{
		inFile >> aluguerID;
		IDs_alugueres.push_back(aluguerID);
		numAlugueresON--;
	}
	inFile.ignore(10,'\n');
}


