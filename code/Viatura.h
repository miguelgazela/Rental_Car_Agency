/*
 * Viatura.h
 *
 */

#ifndef VIATURA_H_
#define VIATURA_H_
#include <string>
#include "Data.h"

using namespace std;

/**
 * @brief Classe que representa os objectos do tipo Viatura
 */

class Viatura {
	static unsigned int num_viaturas;
	unsigned int ID;
	string* marca;
	string* modelo;
	string* matricula;
	string* transmissao;
	string* combustivel;
	Data* registo;
	unsigned int nXalugado, precoPorDia, lugares, cv, cilindrada;
	bool disponivel, ar_condicionado;
public:
	/**
	 * Construtor que cria um objecto Viatura com atributos nulos
	 */
	Viatura();
	/**
	 * @brief Construtor de objecto viatura
	 *
	 * Construtor de Viatura que recebe 11 parametros
	 *
	 * @param const string marca da viatura
	 * @param const string modelo da viatura
	 * @param const string matricula da viatura
	 * @param const string transmissao da viatura
	 * @param const string combustivel da viatura
	 * @param Data data de registo da viatura
	 * @param unsigned int preco diario da viatura
	 * @param unsigned int lugares da viatura
	 * @param unsigned int cavalos da viatura
	 * @param unsigned int cilindrada da viatura
	 * @param bool ar condicionado da viatura
	 */
	Viatura(const string& marca_, const string& modelo_, const string& matricula_, const string& transmissao_, const string& combustivel_, Data* registo_, unsigned int precoPorDia_, unsigned int lugares_, unsigned int cv_, unsigned int cilindrada_, bool ar_condicionado_);
	/**
	 * Destrutor de objecto Viatura
	 */
	~Viatura();

	/**
	 * @brief Retorna o ID da viatura
	 * @return int ID
	 */
	const unsigned int& getID() const;

	/**
	 * @brief Retorna a marca da viatura
	 * @return string marca
	 */
	const string& getMarca() const;

	/**
	 * @brief Retorna o modelo da viatura
	 * @return string modelo
	 */
	const string& getModelo() const;

	/**
	 * @brief Retorna a matricula da viatura
	 * @return string matricula
	 */
	const string& getMatricula() const;

	/**
	 * @brief Retorna a transmissao da viatura
	 * @return string transmissao
	 */
	const string& getTransmissao() const;

	/**
	 * @brief Retorna o combustivel da viatura
	 * @return string combustivel
	 */
	const string& getCombustivel() const;

	/**
	 * @brief Retorna a data de registo da viatura
	 * @return Data registo
	 */
	const Data* getRegisto() const;

	/**
	 * @brief Retorna o numero de vezes que a viatura foi alugada
	 * @return int numero de vezes
	 */
	const unsigned int& getnXalugado() const;

	/**
	 * @brief Retorna preco diario de aluguer da viatura
	 * @return int preco diario
	 */
	const unsigned int& getPrecoPorDia() const;

	/**
	 * @brief Retorna o numero de lugares da viatura
	 * @return int numero de lugares
	 */
	const unsigned int& getLugares() const;

	/**
	 * @brief Retorna o numero de cavalos da viatura
	 * @return int numero de cavalos
	 */
	const unsigned int& getCV() const;

	/**
	 * @brief Retorna a cilindrada da viatura
	 * @return int cilindrada
	 */
	const unsigned int& getCilindrada() const;

	/**
	 * @brief Verifica se a viatura esta disponivel para aluguer
	 * @return bool verdadeiro se a viatura estiver disponivel, falso se nao estiver
	 */
	bool getDisponivel() const;

	/**
	 * @brief Verifica se a viatura tem ar condicionado
	 * @return bool verdadeiro se a viatura tiver ar condicionado, falso se nao tiver
	 */
	bool getAr_condicionado() const;

	/**
	 * @brief Altera o numero de viaturas
	 * @param unsigned int numero de viaturas que deve ser utilizado
	 */
	static void setNumViaturas(unsigned int numViaturas);

	/**
	 * @brief Decrementa o numero de viaturas
	 */
	static void anularViatura();

	/**
	 * @brief Altera o ID da viatura
	 * @param const unsigned int ID que deve ser utilizado
	 */
	void setID(const unsigned int& ID_);

	/**
	 * @brief Altera a marca da viatura
	 * @param const string marca que deve ser utilizada
	 */
	void setMarca(const string& marca_);

	/**
	 * @brief Altera o modelo da viatura
	 * @param const string modelo que deve ser utilizado
	 */
	void setModelo(const string& modelo_);

	/**
	 * @brief Altera a matricula da viatura
	 * @param const string matricula que deve ser utilizada
	 */
	void setMatricula(const string& matricula_);

	/**
	 * @brief Altera a transmissao da viatura
	 * @param const string transmissao que deve ser utilizada
	 */
	void setTransmissao(const string& transmissao_);

	/**
	 * @brief Altera o combustivel da viatura
	 * @param const string combustivel que deve ser utilizada
	 */
	void setCombustivel(const string& combustivel_);

	/**
	 * @brief Altera a data de registo da viatura
	 * @param Data data de registo que deve ser utilizada
	 */
	void setRegisto(Data* registo_);

	/**
	 * @brief Incrementa o numero de vezes que uma viatura foi alugada
	 */
	void incnXalugado();

	/**
	 * @brief Altera o preco diario de aluger da viatura
	 * @param const string preco diario que deve ser utilizado
	 */
	void setPrecoPorDia(const string& precoPorDia_);

	/**
	 * @brief Altera o numero de lugares da viatura
	 * @param const string numero de lugares que deve ser utilizado
	 */
	void setLugares(const string& lugares_);

	/**
	 * @brief Altera o numero de cavalos da viatura
	 * @param const string numero de cavalos que deve ser utilizado
	 */
	void setCV(const string& cv_);

	/**
	 * @brief Altera a cilindrada da viatura
	 * @param const string cilindrada que deve ser utilizada
	 */
	void setCilindrada(const string& cilindrada_);

	/**
	 * @brief Altera o estado de desponibilidade da viatura
	 * @param bool estado que deve ser utilizado
	 */
	void setDisponivel(bool disponivel_);

	/**
	 * @brief Altera o estado do ar condicionado da viatura
	 * @param const string estado que deve ser utilizado
	 */
	void setAr_condicionado(const string& ar_condicionado_);

	/**
	 * @brief Mostra a informacao da viatura
	 */
	void showInfo() const;

	/**
	 * @brief Grava uma Viatura num ficheiro
	 * @param fstream ficheiro para o qual deve guardar os seus atributos
	 */
	virtual void saveInfo(fstream& outFile) const;

	/**
	 * @brief Carrega uma Viatura de um ficheiro
	 * @param fstream ficheiro para o qual deve guardar os seus atributos
	 */
	void loadInfo(fstream& inFile);

	/**
	 * @brief Verifica se uma Viatura foi adicionada mais recentemente que outra
	 *
	 * Overload do operador '<' para verificar se uma viatura tem o ID menor que o de outra
	 *
	 * @return bool verdadeiro se for nao for mais recente, falso se for
	 */
	bool operator < (const Viatura& v2) const {

		if ( registo->getAno() == v2.getRegisto()->getAno() )
			if ( lugares == v2.getLugares() )
				return (*combustivel) < v2.getCombustivel();
			else
				return lugares < v2.getLugares();
		else
			return (registo->getAno() < v2.getRegisto()->getAno());

		/*if ( (registo->getAno()) < (v2.getRegisto()->getAno()) )
			return true;
		else if (lugares < v2.getLugares())
			return true;
		else if (*combustivel < v2.getCombustivel())
			return true;
		else
			return false;*/
	}

	bool operator == (const Viatura& v2) const {
		return (ID == v2.getID());
	}
};

#endif /* VIATURA_H_ */





