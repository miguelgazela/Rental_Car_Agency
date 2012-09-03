/*
 * Pessoa.h
 *
 *  Created on: 1 de Out de 2011
 *      Author: migueloliveira
 */

#ifndef PESSOA_H_
#define PESSOA_H_
#include "Contato.h"
#include "Aluguer.h"
#include "binarySearch.h"
#include "Data.h"
#include <vector>
#include <string>

using namespace std;

/**
 * @brief Classe que representa os objectos do tipo Pessoa
 */

class Pessoa {
protected:
	string* nome;
	Data* data_nascimento;
	Contato* contato;
	long* BI;
	vector<Aluguer*> alugueres;
	vector<int> IDs_alugueres;
	unsigned int alugueres_realizados;
public:
	/**
	 * Construtor que cria um objecto Pessoa com atributos nulos
	 */
	Pessoa();
	/**
	 * @brief Construtor de objecto Pessoa
	 *
	 * Construtor de Pessoa que recebe 4 parametros
	 *
	 * @param const string nome da pessoa
	 * @param const long numero de bilhete de identidade da pessoa
	 * @param Data data de nascimento da pessoa
	 * @param Contato contato da pessoa
	 */
	Pessoa(const string& nome, const long& BI_,Data* data_nascimento, Contato* contato);
	/**
	 * Destrutor de objecto Pessoa
	 */
	virtual ~Pessoa();

	/**
	 * @brief Retorna o nome da Pessoa
	 * @return const string nome
	 */
	const string& getNome() const;
	/**
	 * @brief Retorna a idade da Pessoa
	 * @return int idade
	 */
	int getIdade() const;
	/**
	 * @brief Retorna o BI da pessoa
	 * @return const long BI
	 */
	const long& getBI() const;
	/**
	 * @brief Retorna a data de nascimento da pessoa
	 * @return const Data data de nascimento
	 */
	const Data* getData() const;
	/**
	 * @brief Retorna o contato da pessoa
	 * @return Contato contato
	 */
	Contato* getContato();
	/**
	 * @brief Retorna o NIF da pessoa
	 * @return const long NIF
	 */
	virtual const long* getNIF() const;
	/**
	 * @brief Retorna o vencimento da pessoa
	 * @return const unsigned int vencimento
	 */
	virtual const unsigned int getVencimento() const;
	/**
	 * @brief Retorna o numero de alugueres realizados da pessoa
	 * @return unsigned int numero de alugueres
	 */
	unsigned int getNumAlugueresRealizados() const;
	/**
	 * @brief Retorna um vector com apontadores para os alugueres activos da pessoa
	 * @return const vector<Aluguer*> apontadores para os alugueres
	 */
	const vector<Aluguer*>& getAlugueresActivos() const;
	/**
	 * @brief Retorna um vector com os IDs dos alugueres activos da pessoa
	 * @return const vector<int> IDs dos alugueres
	 */
	const vector<int>& getIDalugueresActivos() const;
	/**
	 * @brief Verifica se a pessoa tem um certo aluguer activo
	 * @param Aluguer que deve ser procurado
	 * @return bool verdadeiro se a pessoa tiver esse aluguer activo, falso se nao tiver
	 */
	bool hasAluguer(Aluguer* al);

	/**
	 * @brief Adiciona um aluguer a pessoa
	 * @param Aluguer* apontador para o aluguer que deve ser adicionado
	 */
	virtual void addAluguer(Aluguer* novo_aluguer);
	/**
	 * @brief Termina um aluguer activo de uma pessoa
	 * @param Aluguer* apontador para o aluguer que deve ser terminado
	 */
	void finishAluguer(Aluguer* al);
	/**
	 * @brief Cancela um aluguer activo de uma pessoa
	 * @param Aluguer* apontador para o aluguer que deve ser cancelado
	 */
	virtual void cancelAluguer(Aluguer* al);
	/**
	 * @brief Mostra os alugueres activo de uma pessoa
	 */
	void showAlugueresActivos() const;
	/**
	 * @brief Verifica se a pessoa tem algum aluguer activo
	 * @return bool verdadeiro se a pessoa tiver algum aluguer activo, falso se nao tiver
	 */
	bool hasAlugueresActivos() const;

	/**
	 * @brief Mostra as informacoes de uma pessoa
	 */
	virtual void showInfo() const;
	/**
	 * @brief Retorna a subclasse da Pessoa
	 *
	 * Retorna um numero que identifica a subclasse da pessoa
	 * 1- Funcionario
	 * 2- Cliente
	 *
	 * @return int numero que identifica a categoria da pessoa
	 */
	virtual int subclasse() const = 0;

	/**
	 * @brief Altera o nome da pessoa
	 * @param const string nome que deve ser utilizado
	 */
	void setNome(const string& nome);
	/**
	 * @brief Altera o BI da pessoa
	 * @param const string BI que deve ser utilizado
	 */
	void setBI(const string& BI);
	/**
	 * @brief Altera a data de nascimento da pessoa
	 * @param Data* data de nascimento que deve ser utilizada
	 */
	void setData(Data* data_nascimento);
	/**
	 * @brief Altera o contato da pessoa
	 * @param Contato* contato que deve ser utilizado
	 */
	void setContato(Contato* contato);
	/**
	 * @brief Altera o NIF da pessoa
	 * @param const string NIF que deve ser utilizado
	 */
	virtual void setNIF(const string& NIF) {}

	/**
	 * @brief Grava uma Pessoa num ficheiro
	 * @param fstream ficheiro para o qual deve guardar os seus atributos
	 */
	void savePessoa(fstream& outFile) const;
	/**
	 * @brief Carrega uma Pessoa de um ficheiro
	 * @param fstream ficheiro para o qual deve guardar os seus atributos
	 */
	virtual void loadPessoa(fstream& inFile);
};

class menorIdade {
public:
	string nome;
	menorIdade(const string& nome_) {nome = nome_;}
	const string& getNome() const {return nome;}
};

#endif /* PESSOA_H_ */
