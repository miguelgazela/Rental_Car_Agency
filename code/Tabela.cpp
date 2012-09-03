#include "Tabela.h"
#include <iostream>

using namespace std;

bool Tabela::contem(const Cliente* cl) const //verifica se a tabela contem o cliente cl
{
	for( HashInativos::iterator it = clientes_inativos.begin();	it != clientes_inativos.end(); it++)
		if ((*it)->getID() == cl->getID())
			return true;

	return false;
}


void Tabela::inserirCliente(Cliente* c1) //insere o cliente c1 na tabela
{
	clientes_inativos.insert(c1);
}

void Tabela::removerCliente(Cliente* c1) //remove o cliente c1 da tabela
{
	clientes_inativos.erase(c1);
}

int Tabela::getNumInativos() const //retorna o numero de clientes na tabela
{
	return clientes_inativos.size();
}

vector<Cliente*> Tabela::getClientesInativos() //retorna os clientes na tabela
{
	vector<Cliente*> cinativos;
	HashInativos::iterator it = clientes_inativos.begin();
	for(HashInativos::iterator it = clientes_inativos.begin();it!=clientes_inativos.end();it++)
		cinativos.push_back(*it);

	return cinativos;
}