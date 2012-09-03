/*
 * Data.h
 */

#ifndef DATA_H_
#define DATA_H_
#include <fstream>
#include <ctime>
#include <iomanip>

using namespace std;

/**
 * @brief Classe que representa os objectos do tipo Data
 */

class Data {
	int dia, mes, ano, hora;
public:
	/**
	 * Construtor que cria um objecto Data com uma data pre-definida a 1/1/1970 e hora a 0
	 */
	Data();

	/**
	 * @brief Construtor de objecto data
	 *
	 * Construtor de Data que recebe 3 parametros
	 *
	 * @param int dia da data
	 * @param int mes da data
	 * @param int ano da data
	 * @param int hora da data
	 */
	Data(int dia, int mes, int ano, int hora = 0);

	/**
	 * @brief Retorna o dia da data
	 * @return int dia
	 */
	int getDia() const;

	/**
	 * @brief Retorna o mes da data
	 * @return int mes
	 */
	int getMes() const;

	/**
	 * @brief Retorna o ano da data
	 * @return int ano
	 */
	int getAno() const;

	/**
	 * @brief Retorna a hora da data
	 * @return int hora
	 */
	int getHora() const;

	/**
	 * @brief Define o ano da Data
	 * @param int ano
	 */
	void setAno(int ano);

	/**
	 * @brief Define o mes da Data
	 * @param int mes
	 */
	void setMes(int mes);

	/**
	 * @brief Define o dia da Data
	 * @param int dia
	 */
	void setDia(int dia);

	/**
	 * @brief Define a hora da Data
	 * @param int hora
	 */
	void setHora(int hora);

	/**
	 * @brief Verifica se ano em questao e bissexto
	 * @return bool verdadeiro se for bissexto, falso se nao
	 */
	bool isAnoBissexto() const;

	/**
	 * @brief Verifica se dia escolhido e valido
	 *
	 * Verifica se o dia passado ao construtor e valido para o mes escolhido (tem em conta anos bissextos)
	 *
	 * @return bool verdadeiro se for valido, falso se nao
	 */
	bool checkDay(int& testDay) const;

	/**
	 * @brief Verifica se uma Data e menor que outra
	 *
	 * Overload do operador '<' para verificar se uma Data e menor que outra
	 *
	 * @return bool verdadeiro se for menor, falso se nao
	 */
	bool operator < (const Data& data);

	/**
	 * @brief Verifica se uma Data e igual a outra
	 *
	 * Overload do operador '==' para verificar se uma Data e a mesma que outra
	 *
	 * @return bool verdadeiro se for igual, falso se nao
	 */
	bool operator == (const Data& data2);

	/**
	 * @brief Faz a subtraccao de duas Datas
	 *
	 * Devolve o numero de dias que separa duas Datas (tem em conta anos bissextos)
	 *
	 * @return double valor da diferenca em dias
	 */
	double operator - (const Data& data);

	/**
	 * @brief grava uma Data num ficheiro
	 * @param fstream ficheiro para o qual deve guardar os seus atributos
	 */
	void saveData(fstream &outFile) const;

	/**
	 * @brief carrega uma Data de um ficheiro
	 * @param fstream ficheiro do qual deve carregar os atributos
	 */
	void loadData(fstream &inFile);
};

ostream& operator << (ostream& o, const Data& d);

class DataInvalida {
public:
};

Data returnDataActual();

#endif /* DATA_H_ */
