/*
 * Aluguer.cpp
 *
 *  Created on: 1 de Out de 2011
 *      Author: migueloliveira
 */

#include "Aluguer.h"

unsigned int Aluguer::numAlugueres = 0;

Aluguer::Aluguer() //Constructor por defeito da classe Aluguer
{
	ID = 0;
	custo_total = 0;
	pontos_atribuidos = 0;
	com_desconto = false;

	// apontadores nulos
	viatura_alugada = NULL;
	inicio_aluguer = NULL;
	fim_aluguer = NULL;
}

Aluguer::Aluguer(Viatura* veiculo, Data* inicio, Data* fim, bool desconto) //Constructor da classe Aluguer
: viatura_alugada(veiculo), inicio_aluguer(inicio), fim_aluguer(fim), com_desconto (desconto)
{
	if ( ((*fim_aluguer) - (*inicio_aluguer)) > 0 )
	{
		ID = ++numAlugueres;
		setCustoTotal(0);
		setPontos(0);
	}
	else
		throw invalidAluguer();
}

Aluguer::~Aluguer() //Destructor da classe Aluguer
{
}

unsigned int Aluguer::getID() const //retorna o ID do aluguer
{
	return ID;
}

Viatura* Aluguer::getViaturaAlugada() const //retorna a viatura alugada
{
	return viatura_alugada;
}

Data* Aluguer::getDataFim() const //retorna a data do fim do aluguer
{
	return fim_aluguer;
}

Data* Aluguer::getDataInicio() const //retorna a data do inicio do aluguer
{
	return inicio_aluguer;
}

unsigned int Aluguer::getPontos() const //retorna os pontos que o aluguer vale
{
	return pontos_atribuidos;
}

float Aluguer::getCustoTotal() const //retorna o custo total do aluguer
{
	return custo_total;
}

bool Aluguer::getDesconto() const //verifica se o aluguer tem desconto
{
	return com_desconto;
}

int Aluguer::getDiasParaAcabar() const //retorna o numero de dias para o aluguer acabar
{
	return ((*fim_aluguer) - returnDataActual());
}

void Aluguer::setViaturaAlugada(Viatura* v) //altera a viatura alugada para v
{
	viatura_alugada = v;
}

void Aluguer::setNumAlugueres(unsigned int numalugueres) //altera o numero de alugueres para numalugueres
{
	numAlugueres = numalugueres;
}

void Aluguer::setID(const unsigned int& ID_) //altera o ID do aluguer para ID_
{
	ID = ID_;
}

void Aluguer::setPontos(unsigned int pontos) //altera os pontos que o aluguer vale
{
	if (pontos == 0)
		pontos_atribuidos = custo_total*2; // 2 pontos por cada euro gasto
	else
		pontos_atribuidos = pontos;
}

void Aluguer::setCustoTotal(float custo) //calcula o custo total do aluguer
{
	if (custo == 0)
		if (!com_desconto)
			custo_total = ( (viatura_alugada)->getPrecoPorDia() * ((*fim_aluguer)-(*inicio_aluguer)) );// preco por dia da viatura * o numero de dias do aluguer
		else
			custo_total = ((((viatura_alugada)->getPrecoPorDia() * ((*fim_aluguer)-(*inicio_aluguer))))-(((viatura_alugada)->getPrecoPorDia() * ((*fim_aluguer)-(*inicio_aluguer))) * 0.05));
	else
		custo_total = custo;
}

void Aluguer::setDataFim(Data* d) //altera a data do fim do aluguer para d
{
	fim_aluguer = d;
}

void Aluguer::showInfo() const //mostra as informacoes do aluguer
{
	cout << "Id: " << ID;
	cout << " - Marca viatura: " << viatura_alugada->getMarca();
	cout << " - Data inicio: " << inicio_aluguer->getDia() << '/' << inicio_aluguer->getMes() << '/' << inicio_aluguer->getAno();
	cout << " - Data fim: " << fim_aluguer->getDia() << '/' << fim_aluguer->getMes() << '/' << fim_aluguer->getAno() << '\n';
}

bool Aluguer::operator < (const Aluguer& a2) const //verifica se o aluguer e menor que o aluguer a2
{
	if ( ID < a2.getID() )
		return true;
	return false;
}

void Aluguer::saveInfo(fstream& outFile) const //grava o aluguer para um ficheiro
{
	outFile << ID << '\n';
	outFile << viatura_alugada->getID() << '\n';
	inicio_aluguer->saveData(outFile);
	fim_aluguer->saveData(outFile);
}

void Aluguer::loadInfo(fstream& inFile) //carrega o aluguer para um ficheiro
{
	string aluguer_ID, viatura_ID;

	getline(inFile,aluguer_ID); ID = atoi(aluguer_ID.c_str());

	// mete um veiculo "vazio", apenas com o ID do original para depois fazer o match
	Viatura* v = new Viatura;
	getline(inFile,viatura_ID); v->setID(atoi(viatura_ID.c_str()));
	viatura_alugada = v;

	// datas do aluguer
	Data* di = new Data;
	di->loadData(inFile);
	inicio_aluguer = di;

	Data* df = new Data;
	df->loadData(inFile);
	fim_aluguer = df;
}
