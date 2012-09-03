/*
 * Contato.h
 *
 *  Created on: 1 de Out de 2011
 *      Author: migueloliveira
 */

#ifndef CONTATO_H_
#define CONTATO_H_
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

/**
 * @brief Classe que representa os objectos do tipo Contato
 */

class Contato {
	string* pais;
	string* morada;
	string* cidade;
	string* codigo_postal;
	long* phoneNumber;
	string* email;
public:
	/**
	 * Construtor que cria um objecto Contato com atributos nulos
	 */
	Contato();
	/**
	 * @brief Construtor de objecto Contato
	 *
	 * Construtor de Contato que recebe 6 parametros
	 *
	 * @param const string pais do contato
	 * @param const string morada do contato
	 * @param const string cidade do contato
	 * @param const string codigo postal do contato
	 * @param const long numero de telefone do contato
	 * @param const string email do contato
	 */
	Contato(const string& pais, const string& morada, const string& cidade, const string& codigo_postal, const long& phoneNumber, const string& email);
	/**
	 * Destrutor de objecto Contato
	 */
	~Contato();

	/**
	 * @brief Retorna o pais do contato
	 * @return const string pais
	 */
	const string& getPais() const;
	/**
	 * @brief Retorna a morada do contato
	 * @return const string morada
	 */
	const string& getMorada() const;
	/**
	 * @brief Retorna a cidade do contato
	 * @return const string cidade
	 */
	const string& getCidade() const;
	/**
	 * @brief Retorna o codigo postal do contato
	 * @return const string codigo postal
	 */
	const string& getPostal() const;
	/**
	 * @brief Retorna o email do contato
	 * @return const string email
	 */
	const string& getEmail() const;
	/**
	 * @brief Retorna o numero do telefone do contato
	 * @return const long numero de telefone
	 */
	const long& getPhoneNumber() const;

	/**
	 * @brief Altera o pais do contato
	 * @param const string NIF que deve ser utilizado
	 */
	void setPais(const string& pais);
	/**
	 * @brief Altera a morada do contato
	 * @param const string morada que deve ser utilizada
	 */
	void setMorada(const string& morada);
	/**
	 * @brief Altera a cidade do contato
	 * @param const string cidade que deve ser utilizada
	 */
	void setCidade(const string& cidade);
	/**
	 * @brief Altera o codigo postal do contato
	 * @param const string codigo postal que deve ser utilizado
	 */
	void setPostal(const string& codigo_postal);
	/**
	 * @brief Altera o numero de telefone do contato
	 * @param const string numero de telefone que deve ser utilizado
	 */
	void setPhoneNumber(const string& phoneNumber);
	/**
	 * @brief Altera o email do contato
	 * @param const string email que deve ser utilizado
	 */
	void setEmail(const string& email);

	/**
	 * @brief Grava um Contato num ficheiro
	 * @param fstream ficheiro para o qual deve guardar os seus atributos
	 */
	void saveContato(fstream &outFile) const;
	/**
	 * @brief Carrega um Contato de um ficheiro
	 * @param fstream ficheiro para o qual deve guardar os seus atributos
	 */
	void loadContato(fstream &inFile);
};

ostream& operator <<(ostream& os, const Contato& c);

#endif /* CONTATO_H_ */
