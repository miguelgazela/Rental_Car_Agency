/*
 * Cliente.h
 *
 *  Created on: 2 de Out de 2011
 *      Author: migueloliveira
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_

#include "Pessoa.h"

/**
 * @brief Classe que representa os objectos do tipo Cliente
 */

class Cliente: public Pessoa {
	static unsigned int numClientes;
	unsigned int ID;
	long* NIF;
	Data* ultimo_aluguer;
	unsigned int pontos;
	bool ativo;
public:
	/**
	 * Construtor que cria um objecto Cliente com atributos nulos
	 */
	Cliente();
	/**
	 * @brief Construtor de objecto Cliente
	 *
	 * Construtor de Cliente que recebe 5 parametros
	 *
	 * @param const string nome do cliente
	 * @param const long numero de bilhete de identidade do cliente
	 * @param Data data de nascimento do cliente
	 * @param Contato contato do cliente
	 * @param unsigned int NIF do cliente
	 */
	Cliente(const string& nome, const long& BI, Data* data_nascimento, Contato* contato, const long& NIF);
	/**
	 * Destrutor de objecto Cliente
	 */
	~Cliente();

	/**
	 * @brief Retorna o ID do Cliente
	 * @return unsigned int ID
	 */
	const unsigned int& getID() const;
	/**
	 * @brief Retorna o NIF do Cliente
	 * @return const NIF
	 */
	const long* getNIF() const;
	/**
	 * @brief Retorna os pontos do Cliente
	 * @return unsigned int pontos
	 */
	const unsigned int& getPontos() const;

	/**
	 * @brief Retorna a data do ultimo aluguer do Cliente
	 * @return Data* apontador para a data do ultimo aluguer do Cliente
	 */
	const Data* getUltimoAluguer() const;

	/**
	 * @brief Retorna estado de atividade do Cliente
	 * @return bool estado de atividade do Cliente
	 */
	const bool getAtivo() const;

	/**
	 * @brief Adiciona um aluguer ao cliente
	 * @param Aluguer* apontador para o aluguer que deve ser adicionado
	 */
	void addAluguer(Aluguer* novoAluguer);
	/**
	 * @brief Cancela um aluguer ao cliente
	 * @param Aluguer* apontador para o aluguer que deve ser cancelado
	 */
	void cancelAluguer(Aluguer* al);
	/**
	 * @brief Adiciona um aluguer ao cliente
	 * @param Aluguer* apontador para o aluguer que deve ser adicionado
	 */
	void addPontos(int pontos_novos);
	/**
	 * @brief Verifica se o cliente tem algum aluguer em atraso
	 * @return bool verdadeiro se o cliente tiver algum aluguer em atraso, falso se nao tiver
	 */
	bool hasAluguerAtrasados() const;
	/**
	 * @brief Verifica se o cliente ja pode usufruir de desconto num aluguer
	 * @return bool verdadeiro se a pessoa ja puder usufruir de desconto num alugue, falso se nao tiver
	 */
	bool descontoCandidate() const;

	/**
	 * @brief Retorna o numero de clientes existentes
	 * @return unsigned int pontos
	 */
	static unsigned int getNumClientes();
	/**
	 * @brief Altera o numero de clientes
	 * @param unsigned int numero de clientes que deve ser utilizado
	 */
	static void setNumClientes(unsigned int numclientes);
	/**
	 * @brief Decrementa o numero de clientes
	 */
	static void anularCliente();

	/**
	 * @brief Altera o ID do cliente
	 * @param unsigned int ID que deve ser utilizado
	 */
	void setID(unsigned int& ID_);

	/**
	 * @brief Altera o data do ultimo aluguer do cliente
	 * @param Data* ultimo_aluguer_  apontador para a data que deve ser utilizada
	 */
	void setUltimoAluguer(Data* ultimo_aluguer_);

	/**
	 * @brief Altera o estado de atividade do cliente
	 * @param bool ativo_  booleano que deve ser utilizada
	 */
	void setAtivo(bool ativo_);

	/**
	 * @brief Altera o NIF do cliente
	 * @param const string NIF que deve ser utilizado
	 */
	void setNIF(const string& NIF);

	/**
	 * @brief Grava um Cliente num ficheiro
	 * @param fstream ficheiro para o qual deve guardar os seus atributos
	 */
	void saveInfo(fstream& outFile) const;
	/**
	 * @brief Carrega um Cliente de um ficheiro
	 * @param fstream ficheiro para o qual deve guardar os seus atributos
	 */
	void loadInfo(fstream& inFile);
	/**
	 * @brief Mostra as informacoes de um cliente
	 */
	void showInfo() const;

	/**
	 * @brief Retorna a categoria da Pessoa
	 * @return int numero 2 que identifica a subclasse Cliente
	 */
	int subclasse() const;
	/**
	 * @brief Verifica se um cliente e menor que outro
	 *
	 * Overload do operador '<' para verificar se um cliente e menor que outro
	 *
	 * @return bool verdadeiro se for menor, falso se nao
	 */
	bool operator < (const Cliente& cliente2) const;
};

#endif /* CLIENTE_H_ */
