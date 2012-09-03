/*
 * Aluguer.h
 *
 *  Created on: 1 de Out de 2011
 *      Author: migueloliveira
 */

#ifndef ALUGUER_H_
#define ALUGUER_H_
#include <iostream>
#include "Viatura.h"
#include "Data.h"

using namespace std;

/**
 * @brief Classe que representa os objectos do tipo Aluguer.
 */

class Aluguer {
	static unsigned int numAlugueres;
	unsigned int ID;
	Viatura* viatura_alugada;
	Data* inicio_aluguer;
	Data* fim_aluguer;
	float custo_total;
	unsigned int pontos_atribuidos;
	bool com_desconto;
public:
	/**
	 * Construtor que cria um objecto Aluguer com atributos nulos
	 */
	Aluguer();
	/**
	 * @brief Construtor de objecto aluguer
	 *
	 * Construtor de Aluguer que recebe 4 parametros
	 *
	 * @param Viatura* viatura do aluguer
	 * @param Data* data de inicio do aluguer
	 * @param Data* data de fim do aluguer
	 * @param bool se ha ou nao desconto
	 */
	Aluguer(Viatura* veiculo, Data* inicio, Data* fim, bool desconto);
	/**
	 * Destrutor de objecto Aluguer
	 */
	~Aluguer();

	/**
	 * @brief Retorna o ID do aluguer
	 * @return int ID
	 */
	unsigned int getID() const;
	/**
	 * @brief Retorna a viatura alugada
	 * @return Viatura* apontador para a viatura alugada
	 */
	Viatura* getViaturaAlugada() const;
	/**
	 * @brief Retorna a data de fim do aluguer
	 * @return Data* apontador para a data de fim do aluguer
	 */
	Data* getDataFim() const;
	/**
	 * @brief Retorna a data de inicio do aluguer
	 * @return Data* apontador para a data de inicio do aluguer
	 */
	Data* getDataInicio() const;
	/**
	 * @brief Retorna o numero de pontos do aluguer
	 * @return int pontos
	 */
	unsigned int getPontos() const;
	/**
	 * @brief Retorna o custo total do aluguer
	 * @return float custo total
	 */
	float getCustoTotal() const;
	/**
	 * @brief Verifica se o custo do aluguer tem desconto
	 * @return bool verdadeiro se o custo do aluguer tiver desconto, falso se nao tiver
	 */
	bool getDesconto() const;
	/**
	 * @brief Retorna o numero de dias restantes para o fim do aluguer
	 * @return int numero de  dias
	 */
	int getDiasParaAcabar() const;

	/**
	 * @brief Altera a viatura alugada
	 * @param Viatura* apontador para a viatura que deve ser utilizado
	 */
	void setViaturaAlugada(Viatura* v);
	/**
	 * @brief Altera o numero de alugueres
	 * @param unsigned int numero que deve ser utilizado
	 */
	static void setNumAlugueres(unsigned int numalugueres);
	/**
	 * @brief Altera o ID da viatura alugada
	 * @param const unsigned int ID que deve ser utilizado
	 */
	void setID(const unsigned int& ID_);
	/**
	 * @brief Altera os pontos do aluguer
	 * @param unsigned int numero de pontos que deve ser utilizado
	 */
	void setPontos(unsigned int pontos);
	/**
	 * @brief Altera o custo total do aluguer
	 * @param float custo que deve ser utilizado
	 */
	void setCustoTotal(float custo);
	/**
	 * @brief Altera a data de fim do aluguer
	 * @param Data* apontador para a data que deve ser utilizada
	 */
	void setDataFim(Data* d);

	/**
	 * @brief Mostra as informacoes de um aluguer
	 */
	void showInfo() const;

	/**
	 * @brief Verifica se um aluguer e menor que outro
	 *
	 * Overload do operador '<' para verificar se o ID de um aluger e menor que o de outro
	 *
	 * @return bool verdadeiro se for menor, falso se nao
	 */
	bool operator < (const Aluguer& a2) const;

	/**
	 * @brief Grava um Aluguer num ficheiro
	 * @param fstream ficheiro para o qual deve guardar os seus atributos
	 */
	void saveInfo(fstream& outFile) const;
	/**
	 * @brief Carrega um Aluguer de um ficheiro
	 * @param fstream ficheiro para o qual deve guardar os seus atributos
	 */
	void loadInfo(fstream& inFile);
};

class invalidAluguer {
public:
	invalidAluguer() {}
};

#endif /* ALUGUER_H_ */
