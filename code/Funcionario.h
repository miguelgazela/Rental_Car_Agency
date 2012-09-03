/*
 * Funcionario.h
 *
 *  Created on: 2 de Out de 2011
 *      Author: migueloliveira
 */

#ifndef FUNCIONARIO_H_
#define FUNCIONARIO_H_

#include "Pessoa.h"

/**
 * @brief Classe que representa os objectos do tipo Funcionario
 */

class Funcionario: public Pessoa {
	static unsigned int numFuncionarios;
	unsigned int ID;
	unsigned int vencimento;
public:
	/**
	 * Construtor que cria um objecto Funcionario com atributos nulos
	 */
	Funcionario();
	/**
	 * @brief Construtor de objecto Funcionario
	 *
	 * Construtor de Funcionario que recebe 5 parametros
	 *
	 * @param const string nome do funcionario
	 * @param const long numero de bilhete de identidade do funcionario
	 * @param Data data de nascimento do funcionario
	 * @param Contato contato do funcionario
	 * @param unsigned int vencimento do funcionario
	 */
	Funcionario(const string& nome, const long& BI, Data* data_nascimento, Contato* contato, unsigned int vencimento);
	/**
	 * Destrutor de objecto Funcionario
	 */
	~Funcionario();

	/**
	 * @brief Retorna o ID do funcionario
	 * @return unsigned int ID
	 */
	const unsigned int& getID() const;
	/**
	 * @brief Retorna o vencimento do funcionario
	 * @return unsigned int vencimento
	 */
	const unsigned int getVencimento() const;

	/**
	 * @brief Altera o numero de funcionarios
	 * @param unsigned int numero de funcionarios que deve ser utilizado
	 */
	static void setNumFuncionarios(unsigned int numfuncionarios);
	/**
	 * @brief Decrementa o numero de funcionarios existentes
	 */
	static void anularFuncionario();

	/**
	 * @brief Altera o vencimento do funcionario
	 * @param unsigned int vencimento que deve ser utilizado
	 */
	void setVencimento(unsigned int vencimento_);
	/**
	 * @brief Altera o ID do funcionario
	 * @param unsigned int ID que deve ser utilizado
	 */
	void setID(unsigned int& ID);

	/**
	 * @brief Grava um Funcionario num ficheiro
	 * @param fstream ficheiro para o qual deve guardar os seus atributos
	 */
	void saveInfo(fstream& outFile) const;
	/**
	 * @brief Carrega um Funcionario de um ficheiro
	 * @param fstream ficheiro para o qual deve guardar os seus atributos
	 */
	void loadInfo(fstream& inFile);
	
	/**
	 * @brief Mostra as informacoes de um funcionario
	 */
	void showInfo() const;
	/**
	 * @brief Retorna a categoria da Pessoa
	 * @return int numero 1 que identifica a subclasse Funcionario
	 */
	int subclasse() const;

	/**
	 * @brief Verifica se um funcionario e menor que outro
	 *
	 * Overload do operador '<' para verificar se um funcionario e menor que outro
	 *
	 * @return bool verdadeiro se for menor, falso se nao
	 */
	bool operator < (Funcionario& f2);
};

#endif /* FUNCIONARIO_H_ */
