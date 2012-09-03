/*
 * Data.cpp
 *
 *  Created on: 1 de Out de 2011
 *      Author: migueloliveira
 */

#include "Data.h"

Data::Data() : dia(1), mes(1), ano(1970), hora(0)
{ }

Data::Data(int d, int m, int a, int hora) : hora(hora)
{
	if (d > 0 && d <= 31 && m > 0 && m <= 12 && a > 0)	// verifica se os argumentos sao numeros validos
	{
		mes = m;
		ano = a;
		if (ano < 1860) // margem de 150 para as idades
			throw DataInvalida();
	}
	else
		throw DataInvalida();

	if (checkDay(d))	// verifica se o dia e valido para o mes escolhido usando a funcao checkDay
	{
		dia = d;
	}
	else
		throw DataInvalida();	// se a data nao e valida, lanca uma excepcao DataInvalida
}

int Data::getDia() const
{
	return dia;
}

int Data::getMes() const
{
	return mes;
}

int Data::getAno() const
{
	return ano;
}

int Data::getHora() const
{
	return hora;
}

void Data::setAno(int ano_)
{
	ano = ano_;
}

void Data::setMes(int mes_)
{
	mes = mes_;
}

void Data::setDia(int dia_)
{
	dia = dia_;
}

void Data::setHora(int hora_)
{
	hora = hora_;
}

bool Data::isAnoBissexto() const
{
	if ( ano % 400 == 0 || ( ano % 4 == 0 && ano % 100 != 0 ) )	// algoritmo para verificar se ano e bissexto
		return true;
	else
		return false;
}

bool Data::checkDay(int& testDay) const
{
	static const int diasPorMes [13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if ( testDay > 0 && testDay <= diasPorMes[mes] )	// verifica se o dia e valido para o mes escolhido
		return true;

	if ( mes == 2 && testDay == 29 && isAnoBissexto() )	// verificar dia 29 de Fevereiro para anos bissextos
		return true;

	return false;	// dia nao e valido
}

bool Data::operator < (const Data& data)
{
	if ( ano < data.getAno() ) // se o ano for menor
		return true;
	else if ( ano > data.getAno() ) // se o ano for maior
		return false;
	else // os anos sao o mesmo
	{
		if ( mes < data.getMes() ) // se mes for menor
			return true;
		else if ( mes > data.getMes() ) // se mes for maior
			return false;
		else
		{
			if ( dia < data.getDia() ) // se dia e menor
				return true;
			else // ou o dia e maior, ou sao o mesmo dia
				return false;
		}
	}
}

bool Data::operator == (const Data& data2)
{
	return (dia == data2.getDia() && mes == data2.getMes() && ano == data2.getAno() );
}

double Data::operator - (const Data& data)
{
	struct tm data1 = {0,0,0,dia,mes-1,ano-1900}; // cria uma estrutura tm com a data do objecto
	struct tm data2 = {0,0,0,data.getDia(),data.getMes()-1,data.getAno()-1900}; // cria uma estrutura tm com a data a subtrair

	time_t x = mktime(&data1); // devolve para x o tempo da data passada na estrutura (em segundos)
	time_t y = mktime(&data2);	// faz o mesmo para y

	if ( x != (time_t)(-1) && y != (time_t)(-1) )
		return ( difftime(x,y) / (60 * 60 * 24) ); // calcula a diferena entre as duas datas, devolve em dias
	return 0.0;
}

void Data::saveData(fstream &outFile) const
{
	outFile << dia << ' ' << mes << ' ' << ano << ' ' << hora << '\n'; // guarda os atributos do objecto na mesma linha do ficheiro
}

void Data::loadData(fstream &inFile)
{
	inFile >> dia >> mes >> ano >> hora; // carrega os atributos do objecto do ficheiro
	inFile.ignore(1,'\n');
}

Data returnDataActual() // calcula a data actual em que o programa esta a correr
{
	time_t rawtime;
	struct tm *timeinfo;

	time (&rawtime);
	timeinfo = localtime (&rawtime);

	int dia = timeinfo->tm_mday;
	int mes = timeinfo->tm_mon+1;
	int ano = timeinfo->tm_year+1900;
	int hora = timeinfo->tm_hour;

	Data d(dia, mes, ano, hora);

	return d;
}

ostream& operator << (ostream& o, const Data& d)
{
	o << right << setfill('0') << setw(2) << d.getDia() << '/' << setw(2) << d.getMes() << '/' << setw(4) << d.getAno() << setfill(' ') << setw(2) << left << ' '; // faz o display da Data no formato DD/MM/AA
	return o;
}


