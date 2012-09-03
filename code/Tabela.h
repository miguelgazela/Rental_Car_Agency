/*
 * Tabela.h
 *
 */

#ifndef TABELA_H_
#define TABELA_H_

#include <unordered_set>
#include <string>
#include "Cliente.h"

using namespace stdext;
using namespace std;

/**
 * @brief Classe que representa as tabelas de dispersao de clientes inativos
 */

struct hInativo
{
	int operator() (const Cliente* cl) const
	{
		return cl->getID();
	}
};

struct eqInativo
{
  bool operator()(const Cliente* cl1, const Cliente* cl2) const
  {
	  return (cl1->getID() == cl2->getID());
  }
};

typedef unordered_set<Cliente*, hInativo, eqInativo> HashInativos;

class Tabela
{
	HashInativos clientes_inativos;
public:
	/**
	 * @brief Construtor de objecto Tabela
	 *
	 * Construtor por defeito do objecto Tabela
	 *
	 */
	Tabela() {}

	/**
	 * @brief Verifica se o cliente cl e invalido
	 *
	 * Verifica se a tabela de clientes inativos contem o cliente cl
	 *
	 * @return bool verdadeiro se for invalido, falso se nao
	 */
	bool contem(const Cliente* cl) const;

	/**
	 * @brief Adiciona um cliente a tabela
	 * @param Cliente* apontador para o cliente que deve ser adicionado
	 */
	void inserirCliente(Cliente* c1);

	/**
	 * @brief Remove um cliente da tabela
	 * @param Cliente* apontador para o cliente que deve ser removido
	 */
	void removerCliente(Cliente* c1);

	/**
	 * @brief Retorna o numero de clientes inativos
	 * @return int numero de clientes na tabela
	 */
	int getNumInativos() const; 

	/**
	 * @brief Retorna um vector de apontadores de clientes inativos
	 * @return vector<Cliente*> vector com apontadores para os clientes na tabela
	 */
	vector<Cliente*> getClientesInativos();
};

#endif 
