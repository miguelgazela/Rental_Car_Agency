/*
 * Agencia.cpp
 */

#include "Agencia.h"

unsigned int Agencia::posNextFuncionario = 0;
unsigned int Agencia::alugueresFeitos = 0;

Agencia::Agencia() : viaturas(Viatura()) // construtor da classe Agencia
{
	// define os caminhos dos ficheiros utilizados
	filenameFuncionarios = "funcionarios.txt";
	filenameClientes = "clientes.txt";
	filenameViaturas = "viaturas.txt";
	filenameAlugueres = "alugueres.txt";
	filenameCatalogo = "catalogo.txt";
	filenameOficinas = "oficinas.txt";

	loadAgencia(); // carrega os dados dos ficheiros
}

Agencia::~Agencia() // destrutor da classe Agencia
{
	// desalocar os blocos de memoria utilizados
	for (unsigned int i = 0; i < viaturas_existentes.size(); i++)
		delete viaturas_existentes.at(i);
	for (unsigned int i = 0; i < clientes_registados.size(); i++)
		delete clientes_registados.at(i);
	for (unsigned int i = 0; i < funcionarios.size(); i++)
		delete funcionarios.at(i);
	for (unsigned int i = 0; i < alugueres_activos.size(); i++)
		delete alugueres_activos.at(i);
}

void Agencia::addCliente(Cliente* novoCliente) // adiciona novo cliente à agencia
{
	for (unsigned int i = 0; i < clientes_registados.size(); i++) // percorre todos os clientes
	{
		if ( novoCliente->getBI() == clientes_registados.at(i)->getBI() ) // se existe cliente com BI igual ao novo Cliente
			throw jaExiste(clientes_registados.at(i)->getID(), 1);
		if ( *(novoCliente->getNIF()) == *(clientes_registados.at(i)->getNIF()) ) // ve se existe Cliente com NIF igual ao novo Cliente
			throw jaExiste(clientes_registados.at(i)->getID(), 2);
	}
	clientes_registados.push_back(novoCliente);
	save1object(novoCliente, filenameClientes); // grava a informacao sobre o novo Cliente
}

void Agencia::addFuncionario(Funcionario* novoFuncionario) // adiciona novo Funcionario a agencia
{
	for (unsigned int i = 0; i < funcionarios.size(); i++) // percorre todos os funcionarios
	{
		if ( novoFuncionario->getBI() == funcionarios.at(i)->getBI() ) // se existe funcionario com BI igual ao novo Funcionario
			throw jaExiste(funcionarios.at(i)->getID(), 1);
	}
	funcionarios.push_back(novoFuncionario);
	save1object(novoFuncionario, filenameFuncionarios); // grava a informacao sobre o novo Funcionario
}

void Agencia::addViatura(Viatura* novaViatura) // adiciona nova Viatura a agencia
{
	for (unsigned int i = 0; i < viaturas_existentes.size(); i++) // percorre todas as viaturas
	{
		if ( novaViatura->getMatricula() == viaturas_existentes.at(i)->getMatricula() ) // se existe Viatura com matricula igual a da nova Viatura
			throw jaExiste(viaturas_existentes.at(i)->getID(), 0);
	}
	viaturas_existentes.push_back(novaViatura);
	save1object(novaViatura, filenameViaturas); // grava a informacao sobre a nova Viatura
}

void Agencia::addAluguer(Aluguer* novoAluguer) // adiciona novo Aluguer a agencia
{
	alugueres_activos.push_back(novoAluguer);
	if ( posNextFuncionario >= funcionarios.size() ) // se a posicao do proximo funcionario a receber aluguer for superior a ultima posicao
		posNextFuncionario = 0; // faz reset a posicao
	funcionarios.at(posNextFuncionario)->addAluguer(novoAluguer); // adiciona o aluguer ao funcionario
	updateNextFuncionario(funcionarios.size()); // atualiza a posicao do proximo
}

void Agencia::changeCF(Cliente* c, string& str, unsigned int op) // altera a informacao de um Cliente
{
	changeCFs(clientes_registados, c, str, op); // chama funcao template para alterar o Cliente
	saveAgencia(1); // guarda os clientes
}

void Agencia::changeCF(Funcionario* f, string& str, unsigned int op) // altera a informacao de um Funcionario
{
	changeCFs(funcionarios, f, str, op); // chama funcao template para alterar o Funcionario
	saveAgencia(2); // guarda os funcionarios
}

template <class T>
void Agencia::changeCFs(vector<T*>& originais, T* cf, string& str,  unsigned int& op) // funcao template para alterar clientes e funcionarios
{
	switch (op)
	{
	case 1: // muda o nome
	{
		cf->setNome(str);
	}
	break;
	case 2: // muda o pais
	{
		(cf->getContato())->setPais(str);
	}
	break;
	case 3:	// muda a morada
	{
		(cf->getContato())->setMorada(str);
	}
	break;
	case 4: // muda a cidade
	{
		(cf->getContato())->setCidade(str);
	}
	break;
	case 5: // muda o codigo-postal
	{
		(cf->getContato())->setPostal(str);
	}
	break;
	case 6: // muda o numero telefonico
	{
		(cf->getContato())->setPhoneNumber(str);
	}
	break;
	case 7: // muda o e-mail
	{
		(cf->getContato())->setEmail(str);
	}
	break;
	case 8: // muda o BI
	{
		for (unsigned int i = 0; i < originais.size(); i++) // percorrer todos os objectos na agencia
		{
			long BI = convertString(str);
			if ( BI == originais.at(i)->getBI() && originais.at(i)->getID() != cf->getID() ) // se BI ja estiver a ser utilizado por outra pessoa
				throw jaExiste(originais.at(i)->getID(), 1); // lanca excecao com ID da pessoa
		}
		cf->setBI(str);
	}
	break;
	case 9: // muda o NIF
	{
		for (unsigned int i = 0; i < originais.size(); i++) // percorrer todos os objectos na agencia
		{
			long NIF = convertString(str);
			if ( NIF == *originais.at(i)->getNIF() && originais.at(i)->getID() != cf->getID() ) // se NIF ja estiver a ser utilizado por outra pessoa
				throw jaExiste(originais.at(i)->getID(), 2); // lanca excecao com ID da pessoa
		}
		cf->setNIF(str);
	}
	break;
	}
}

void Agencia::changeViatura(Viatura* v, string& str, unsigned int op) // funcao para alterar dados da viatura
{
	switch (op)
	{
	case 1: // muda a marca
	{
		v->setMarca(str);
	}
	break;
	case 2:	// muda o modelo
	{
		v->setModelo(str);
	}
	break;
	case 3: // muda a matricula a menos que a matricula ja exista na agencia
	{
		allUpperCase(str);
		for (unsigned int i = 0; i < viaturas_existentes.size(); i++)
		{
			if ( str == viaturas_existentes.at(i)->getMatricula() )
				throw jaExiste(viaturas_existentes.at(i)->getID(), 0);
		}
		v->setMatricula(str);
	}
	break;
	case 4: // muda a transmissao
	{
		v->setTransmissao(str);
	}
	break;
	case 5: // muda o combustivel
	{
		v->setCombustivel(str);
	}
	break;
	case 6: // muda o preco diario
	{
		v->setPrecoPorDia(str);
	}
	break;
	case 7: // muda os lugares
	{
		v->setLugares(str);
	}
	break;
	case 8: // muda o cv
	{
		v->setCV(str);
	}
	break;
	case 9: // muda a cilindrada
	{
		v->setCilindrada(str);
	}
	break;
	case 10: // muda o ar condicionado
	{
		v->setAr_condicionado(str);
	}
	break;
	default:
		break;
	}
	saveAgencia(3); // guarda as viaturas
	saveAgencia(6);
}

void Agencia::changeAluguer(Aluguer* al, Data* d)
{
	int dif_dias;
	float custo = al->getCustoTotal(); // vai buscar custo total atual do aluguer
	int pontos = al->getPontos(); // vai buscar pontos atuais do aluguer

	if ( *d < *al->getDataFim() ) // se a nova data for menor que a antiga data
	{
		dif_dias = (*al->getDataFim() - *d); // data antiga - nova data
		custo = custo - (dif_dias * (al->getViaturaAlugada()->getPrecoPorDia())); // retira o custo dos dias retirados
		pontos = pontos - (dif_dias * (al->getViaturaAlugada()->getPrecoPorDia()) * 2); // retira os pontos;
	}
	else
	{
		dif_dias = (*d - *al->getDataFim()); // data nova - data antiga
		custo = custo + (dif_dias * (al->getViaturaAlugada()->getPrecoPorDia())); // adiciona o custo dos dias a mais
		pontos = pontos + (dif_dias * (al->getViaturaAlugada()->getPrecoPorDia()) * 2); // adiciona os pontos
	}

	al->setDataFim(d); // altera a data
	al->setCustoTotal(custo); // altera o custo
	al->setPontos(pontos); // altera os pontos
	saveAgencia(4); // guarda os alugueres
}

void Agencia::removeCliente(Cliente* c) // remove cliente da Agencia
{
	int pos = BinarySearch(clientes_registados, *c); // utiliza pesquisa binaria para descobrir a posicao do cliente
	clientes_registados.erase(clientes_registados.begin()+pos); // apaga o cliente
	saveAgencia(1); // guarda os clientes
}

void Agencia::removeFuncionario(Funcionario* f) // remove funcionario da Agencia
{
	int pos = BinarySearch(funcionarios, *f); // descobre posicao do funcionario no vector
	funcionarios.erase(funcionarios.begin()+pos); // apaga funcionario
	saveAgencia(2); // guarda os funcionarios
}

void Agencia::removeViatura(Viatura* v) // remove viatura da Agencia
{
	int pos;
	for (size_t i = 0; i < viaturas_existentes.size(); i++)
		if (viaturas_existentes.at(i)->getID() == v->getID())
			pos = i;
	viaturas_existentes.erase(viaturas_existentes.begin()+pos); // apaga viatura
	saveAgencia(3); // guarda as viaturas
}

void Agencia::cancelAluguer(Aluguer* al) // cancela um aluguer
{
	CancelFinishAluguer(al, 2);
}

void Agencia::finishAluguer(Aluguer* al) // termina aluguer
{
	changeAluguer(al, &returnDataActual()); // no caso de o aluguer ser finalizado antes da data final original
	CancelFinishAluguer(al, 1);
	alugueresFeitos++;
}

void Agencia::CancelFinishAluguer(Aluguer* al, unsigned int op)
{
	al->getViaturaAlugada()->setDisponivel(true); // mete viatura utilizada no aluguer como disponivel

	// termina/cancela aluguer no cliente que o fez e no funcionario responsavel por ele
	for (vector<Cliente*>::const_iterator it = clientes_registados.begin(); it != clientes_registados.end(); it++)
		if ( (*it)->hasAluguer(al) )
			if ( op == 1 )
			{
				(*it)->setUltimoAluguer(new Data(returnDataActual().getDia(),returnDataActual().getMes(),returnDataActual().getAno())); //altera a data do ultimo aluguer do cliente
				(*it)->finishAluguer(al); // termina aluguer no cliente certo
			}
			else
				(*it)->cancelAluguer(al); // cancela aluguer no cliente certo

	for (vector<Funcionario*>::const_iterator it = funcionarios.begin(); it != funcionarios.end(); it++)
		if ( (*it)->hasAluguer(al) )
			if ( op == 1)
				(*it)->finishAluguer(al); // termina aluguer no funcionario responsavel
			else
				(*it)->cancelAluguer(al); // cancela aluguer no cliente certo

	int pos = BinarySearch(alugueres_activos, *al); // posicao do aluguer no vector
	alugueres_activos.erase(alugueres_activos.begin()+pos);
	saveAgencia(5); // guarda os dados da agencia
}

bool Agencia::hasFinishingToday() const // devolve se Agencia tem alugueres a terminar na data atual
{
	for (vector<Aluguer*>::const_iterator it = alugueres_activos.begin(); it != alugueres_activos.end(); it++)
		if ((*it)->getDiasParaAcabar() == 0) // se faltam 0 dias para acabar
			return true;
	return false;
}

void Agencia::getFinishingToday(vector<Aluguer*>& resultados) const // coloca no vetor recebido os alugueres que terminam na data atual
{
	for (vector<Aluguer*>::const_iterator it = alugueres_activos.begin(); it != alugueres_activos.end(); it++)
			if ((*it)->getDiasParaAcabar() == 0) // se faltam 0 dias para acabar
				resultados.push_back((*it)); // adiciona ao vetor
}

unsigned int Agencia::getNumClientes() const
{
	return (clientes_registados.size()); // devolve numero de clientes registados na agencia
}

unsigned int Agencia::getNumFuncionarios() const
{
	return (funcionarios.size()); // devolve numero de funcionarios a trabalhar na agencia
}

unsigned int Agencia::getNumViaturas() const
{
	return (viaturas_existentes.size()); // devolve numero de viaturas presentes na agencia
}

unsigned int Agencia::getNumViaturasDisponiveis () const
{
	int viaturasDisponiveis = 0;

	for (vector<Viatura*>::const_iterator it = viaturas_existentes.begin(); it != viaturas_existentes.end(); it++)
		if ((*it)->getDisponivel()) // por cada viatura disponivel
			viaturasDisponiveis++; // incrementa contador

	return viaturasDisponiveis; // devolve contador
}

unsigned int Agencia::getNumAlugueresFeitos() const
{
	return alugueresFeitos; // devolve numero de alugueres ja realizados
}

unsigned int Agencia::getNumAlugueresActivos() const
{
	return alugueres_activos.size(); // devolve numero de alugueres ativos
}

void Agencia::updateNextFuncionario(const unsigned int& numFuncionarios)
{
	if ( posNextFuncionario == (numFuncionarios-1) ) // se esta no ultimo funcionario do vetor
		posNextFuncionario = 0; // faz reset a posicao
	else
		posNextFuncionario++; // ou passa para o proximo funcionario
}

void Agencia::pesquisarCFs(vector<Funcionario*>& resultados, pesquisaCF& p) // pesquisa funcionario
{
	pesquisarCF(resultados, p, funcionarios);
}

void Agencia::pesquisarCFs(vector<Cliente*>& resultados, pesquisaCF& p) // pesquisa cliente
{
	pesquisarCF(resultados, p, clientes_registados);
}

template <class T>
void Agencia::pesquisarCF(vector<T*>& resultados, pesquisaCF& p, vector<T*>& originais) // pesquisa funcionarios ou clientes
{
	for (typename vector<T*>::const_iterator it = originais.begin(); it != originais.end(); it++) // corre os f/c todos
	{
		int criterios = numCriteriosCF(p); // define num de criterios alterados na pesquisa

		if (p.nome != "null") // se criterio nome foi alterado
			if( foundIt((*it)->getNome(), p.nome) ) // se o nome do f/c tem a substr a pesquisar
				criterios--; // diminui numero de criterios

		if (p.BI != 0) // se criterio nome foi alterado
			if( (*it)->getBI() == p.BI ) // se o BI é igual
				criterios--;

		if (p.pais != "null") // se criterio pais foi alterado
			if (foundIt( ((*it)->getContato())->getPais(), p.pais))
				criterios--;

		if (p.morada != "null") // se criterio morada foi alterado
			if (foundIt( ((*it)->getContato())->getMorada(), p.morada))
				criterios--;

		if (p.cidade != "null") // se criterio cidade foi alterado
			if (foundIt( ((*it)->getContato())->getCidade(), p.cidade))
				criterios--;

		if (p.codigopostal != "null") // se criterio codigopostal foi alterado
			if (foundIt( ((*it)->getContato())->getPostal(), p.codigopostal))
				criterios--;

		if (p.phone != 0) // se criterio phone foi alterado
			if ( (*it)->getContato()->getPhoneNumber() == p.phone)
				criterios--;

		if (p.email != "null") // se criterio email foi alterado
			if (foundIt( ((*it)->getContato())->getEmail(), p.email))
				criterios--;

		if (p.NIF != 0) // se criterio NIF foi alterado
			if ( *((*it)->getNIF()) == p.NIF)
				criterios--;

		if ( p.idade_inf != 0 ) // foi utilizado o criterio idade (idade_inf e alterado em qualquer opcao da idade)
			if ( (*it)->getIdade() >= p.idade_inf && (*it)->getIdade() <= p.idade_sup )
				criterios--;

		if ( p.vencimento_inf != 0 ) // foi utilizado o criterio vencimento (vencimento_inf e alterado em qualquer opcao do vencimento)
			if ( (*it)->getVencimento() >= (unsigned int)p.vencimento_inf && (*it)->getVencimento() <= (unsigned int)p.vencimento_sup )
				criterios--;

		if (criterios == 0) // significa que o f/c verifica todos os criterios alterados
			resultados.push_back(*it); // insere-o nos resultados da pesquisa
	}
}

void Agencia::pesquisarViatura(vector<Viatura*>& resultados, pesquisaViatura& p) // pesquisa de viaturas
{
	for (vector<Viatura*>::const_iterator it = viaturas_existentes.begin(); it != viaturas_existentes.end(); it++)
	{
		int criterios = numCriteriosViatura(p); // define num de criterios alterados na pesquisa

		if (p.marca != "null") // se criterio marca foi alterado
			if (foundIt((*it)->getMarca(), p.marca))
					criterios--;

		if (p.modelo != "null") // se criterio modelo foi alterado
			if (foundIt((*it)->getModelo(), p.modelo))
				criterios--;

		if (p.matricula != "null") // se criterio matricula foi alterado
			if (foundIt((*it)->getMatricula(), p.matricula))
				criterios--;

		if (p.transmissao != "null") // se criterio transmissao foi alterado
			if (foundIt((*it)->getTransmissao(), p.transmissao))
				criterios--;

		if (p.combustivel != "null") // se criterio combustivel foi alterado
			if (foundIt((*it)->getCombustivel(), p.combustivel))
				criterios--;

		if (p.ano != 0 ) // se criterio ano foi alterado
			if (p.anoOp == 1) // opcao 1 - superior a
			{
				if ((*it)->getRegisto()->getAno() >= p.ano)
					criterios--;
			}
			else // opcao 2 - inferior a
				if ((*it)->getRegisto()->getAno() <= p.ano)
					criterios--;

		if (p.nXalugado != -1 ) // se criterio nXalugado foi alterado
			if (p.nXalugadoOp == 1) // opcao 1 - superior a
			{
				if ((int)(*it)->getnXalugado() >= p.nXalugado )
					criterios--;
			}
			else // opcao 2 - inferior a
				if ((int)(*it)->getnXalugado() <= p.nXalugado)
					criterios--;

		if ( p.precoPorDia_inf != -1 ) // foi utilizado o criterio preco por dia (precoPorDia_inf e alterado em qualquer opcao do preco)
			if ( (int)(*it)->getPrecoPorDia() >= p.precoPorDia_inf && (int)(*it)->getPrecoPorDia() <= p.precoPorDia_sup )
				criterios--;

		if (p.cv != 0 ) // se criterio cv foi alterado
			if (p.cvOp == 1) // opcap 1 - superior a
			{
				if ((int)(*it)->getCV() >= p.cv )
					criterios--;
			}
			else // opcao 2 - inferior a
				if ((int)(*it)->getCV() <= p.cv)
					criterios--;

		if (p.cilindrada != -1 ) // se criterio cilindrada foi alterado
			if (p.cilindradaOp == 1)
			{
				if ((int)(*it)->getCilindrada() >= p.cilindrada )
					criterios--;
			}
			else
				if ((int)(*it)->getCilindrada() <= p.cilindrada)
					criterios--;

		if(criterios == 0)
			resultados.push_back(*it);
	}
}

void Agencia::pesquisarAluguer(vector<Aluguer*>& resultados, pesquisaAluguer& p) // pesquisa de aluguer
{
	for (vector<Aluguer*>::const_iterator it = alugueres_activos.begin(); it != alugueres_activos.end(); it++)
	{
		int criterios = numCriteriosAluguer(p); // vai buscar o numero de criterios que foi alterado

		if (p.nomeCliente != "null") // se o nome do cliente foi alterado
			for(vector<Cliente*>::const_iterator it2 = clientes_registados.begin(); it2 != clientes_registados.end(); it2 ++)
			{
				if ((*it2)->hasAluguer(((*it)))) // verifica qual o cliente que tem esse aluguer activo
					if (foundIt((*it2)->getNome(),p.nomeCliente)) // se o nome dele tem a string procurada
						criterios--;
			}

		if (p.nomeFuncionario != "null")
			for(vector<Funcionario*>::const_iterator it2 = funcionarios.begin(); it2 != funcionarios.end(); it2 ++)
			{
				if ((*it2)->hasAluguer(((*it))))
					if (foundIt((*it2)->getNome(),p.nomeFuncionario))
						criterios--;
			}

		if (p.marcaViatura != "null")
			if (foundIt((*it)->getViaturaAlugada()->getMarca(), p.marcaViatura))
				criterios--;

		if (p.valor != 0)
			if (p.valorOp == 1)
			{
				if ((int)(*it)->getCustoTotal() >= p.valor)
					criterios--;
			}
			else
				if ((int)(*it)->getCustoTotal() <= p.valor)
					criterios--;

		if (p.dias != 0)
			if (p.diasOp == 1)
			{
				if ((*it)->getDiasParaAcabar() >= p.dias)
					criterios--;
			}
			else
				if ((*it)->getDiasParaAcabar() <= p.dias)
					criterios--;

		if(criterios == 0)
			resultados.push_back(*it);
	}
}

const vector<Cliente*>& Agencia::getClientes() const
{
	return clientes_registados; // retorna vector de clientes
}

const vector<Funcionario*>& Agencia::getFuncionarios() const
{
	return funcionarios; // retorna vector de funcionarios
}

const vector<Viatura*>& Agencia::getViaturas() const
{
	return viaturas_existentes; // retorna vector de viaturas
}

const vector<Aluguer*>& Agencia::getAlugueres() const
{
	return alugueres_activos; // retorna vector de alugueres
}

void Agencia::showClientes(const vector<Cliente*>& clientes) const
{
	int numeroClientes = 52; // numero maximo de Clientes que pode representar na resolucao dos ecras da FEUP
	int x = 0; // posicao do primeiro Cliente a ser apresentado
	int y = numeroClientes; //
	bool onePage = false;
	const char ENTER = 13;
	char ch = ENTER;

	if ((int)clientes.size() <= numeroClientes)
		onePage = true;

	do {
		clearScreen();
		showFrames();
		gotoxy(77,2); cout << "*** CLIENTES ***";
		int yCoor = 7;
		gotoxy(2,yCoor); cout << left << setw(5) << "ID" << setw(40) << "NOME" << setw(9) << "IDADE" << setw(25) << "CIDADE" << setw(16) << "ALUG. ATIVOS" << setw(21) << "NUM. ALUG. ATIVOS" << setw(21) << "NUM. ALUG. REALIZ." << setw(23) << "ALUG. EM ATRASADO";
		yCoor++;
		for (int xCoor = 2; xCoor < 175;xCoor++)
		{
			gotoxy(xCoor,yCoor); cout << '-';
		}
		for (; x != y; x++)
		{
			if ( x < (int)clientes.size() && clientes.at(x)->getAtivo())
			{
				if ( (x % 2) == 0 ) // se x e par
					setcolor(8); // cor cinzento escuro

				gotoxy(2,++yCoor);
				cout << left << setw(5) << clientes.at(x)->getID() << setw(40) << clientes.at(x)->getNome() << setw(9) << clientes.at(x)->getIdade() << setw(25) << clientes.at(x)->getContato()->getCidade() << setw(16);
				if (clientes.at(x)->hasAlugueresActivos())
					cout << "SIM";
				else
					cout << "NAO";
				cout << setw(21) << clientes.at(x)->getAlugueresActivos().size() << setw(21) << clientes.at(x)->getNumAlugueresRealizados() << setw(23);
				if (clientes.at(x)->hasAluguerAtrasados())
					cout << "SIM";
				else
					cout << "NAO";

				if ( (x % 2) == 0 ) // se x e par
					setcolor(15); // branco
			}
		}

		if (!onePage)
		{
			gotoxy(10,62);
			cout << "Prima a tecla 'B' para ver os clientes anteriores, ou a tecla 'N' para ver os proximos clientes. Prima ENTER para continuar.";
			multiplePagesView(ch, x, y, numeroClientes, clientes);
		}

	} while (ch != ENTER && !onePage);
}

void Agencia::showFuncionarios(const vector<Funcionario*>& funcionarios) const
{
	int numeroFuncionarios = 52;
	int x = 0;
	int y = numeroFuncionarios;
	bool onePage = false;
	const char ENTER = 13;
	char ch = ENTER;

	if ((int)funcionarios.size() <= numeroFuncionarios)
			onePage = true;

	do {
		clearScreen();
		showFrames();
		gotoxy(77,2); cout << "*** FUNCIONARIOS ***";
		int yCoor = 7;
		gotoxy(2,yCoor); cout << left << setw(5) << "ID" << setw(40) << "NOME" << setw(9) << "IDADE" << setw(14) << "VENCIMENTO" << setw(25) << "CIDADE" << setw(22) << "RESPONSAVEL POR x ALUG." << endl;
		yCoor++;
		for (int xCoor = 2; xCoor < 175;xCoor++)
		{
			gotoxy(xCoor,yCoor); cout << '-';
		}
		for (; x != y; x++)
			if ( x < (int)funcionarios.size())
			{
				if ( (x % 2) == 0 ) // se x e par
					setcolor(8);

				gotoxy(2,++yCoor);
				cout << uppercase << left << setw(5) << funcionarios.at(x)->getID() << setw(40) << funcionarios.at(x)->getNome() << setw(9) << funcionarios.at(x)->getIdade() << setw(14) << funcionarios.at(x)->getVencimento();
				cout << setw(25) << funcionarios.at(x)->getContato()->getCidade() << setw(22) << right << funcionarios.at(x)->getAlugueresActivos().size();

				if ( (x % 2) == 0 ) // se x e par
					setcolor(15);
			}

		if (!onePage)
		{
			gotoxy(10,62);
			cout << "Prima a tecla 'B' para ver os funcionarios anteriores, ou a tecla 'N' para ver os proximos funcionarios. Prima ENTER para continuar.";
			multiplePagesView(ch, x, y, numeroFuncionarios, funcionarios);
		}

	} while (ch != ENTER && !onePage);
}

void Agencia::showViaturas(const vector<Viatura*>& viaturas) const
{
	int numeroViaturas = 52;
	int x = 0;
	int y = numeroViaturas;
	bool onePage = false;
	const char ENTER = 13;
	char ch = ENTER;

	if ((int)viaturas.size() <= numeroViaturas)
		onePage = true;

	do {
		clearScreen();
		showFrames();
		gotoxy(80,2); cout << "*** VIATURAS ***";
		int yCoor = 7;
		gotoxy(2,yCoor); cout << left << setw(5) << "ID" << setw(25) << "MARCA" << setw(25) << "MODELO" << setw(12) << "MATRICULA" << setw(15) << "COMBUSTIVEL" << setw(20) << "TRANSMISSAO" << setw(13) << "POTENCIA(cv)" << setw(6) << "ANO" << setw(9) << "PRECO"  << setw(16) << "NUM x ALUGADO" << setw(12) << "DISPONIVEL" << endl;
		yCoor++;
		for (int xCoor = 2; xCoor < 175;xCoor++)
		{
			gotoxy(xCoor,yCoor); cout << '-';
		}
		for (; x != y; x++)
		{
			if (x < (int)viaturas.size())
			{
				if ( (x % 2) == 0 ) // se x e par
					setcolor(8); // cor cinzento escuro

				gotoxy(2,++yCoor); cout << uppercase << left << setw(5) << viaturas.at(x)->getID() << setw(25) << viaturas.at(x)->getMarca() << setw(25) << viaturas.at(x)->getModelo() << setw(12) << viaturas.at(x)->getMatricula() << setw(15) << viaturas.at(x)->getCombustivel() << setw(20) << viaturas.at(x)->getTransmissao() << setw(13) << viaturas.at(x)->getCV() << setw(6) << viaturas.at(x)->getRegisto()->getAno() << setw(9) << viaturas.at(x)->getPrecoPorDia() << setw(16) << viaturas.at(x)->getnXalugado() << setw(12);
				if (viaturas.at(x)->getDisponivel())
					cout << "SIM" << endl;
				else
					cout << "NAO" << endl;

				if ( (x % 2) == 0 ) // se x e par
					setcolor(15);
			}
		}

		if (!onePage)
		{
			gotoxy(10,62);
			cout << "Prima a tecla 'B' para ver as viaturas anteriores, ou a tecla 'N' para ver as proximas viaturas. Prima ENTER para continuar.";
			multiplePagesView(ch, x, y, numeroViaturas, viaturas);
		}

	} while (ch != ENTER && !onePage); // depois usar o getch
}

void Agencia::showViaturasDisponiveis () const // passar para um vector os que tao disponiveis e depois mandar para o showViaturas
{
	vector<Viatura*> disponiveis;

	for (vector<Viatura*>::const_iterator it = viaturas_existentes.begin(); it != viaturas_existentes.end(); it++)
		if ((*it)->getDisponivel())
			disponiveis.push_back(*it);
	showViaturas(disponiveis);

}

void Agencia::showAlugueres(const vector<Aluguer*>& alugueres) const
{
	int numeroAlugueres = 52;
	int x = 0;
	int y = numeroAlugueres;

	bool onePage = false;
	const char ENTER = 13;
	char ch = ENTER;

	if ((int)alugueres.size() <= numeroAlugueres)
			onePage = true;

	do {
		clearScreen();
		showFrames();
		gotoxy(80,2); cout << "*** ALUGUERES ***";
		int yCoor = 7;
		gotoxy(2,yCoor); cout << left << setw(5) << "ID" << setw(22) << "MARCA DA VIATURA" << setw(12) << "MATRICULA" << setw(12) << "INICIO" << setw(12) << "FIM" << setw(20) << "CUSTO TOTAL" << setw(12) << "PONTOS" << setw(15) << "COM DESCONTO" << endl;
		yCoor++;
		for (int xCoor = 2; xCoor < 175;xCoor++)
		{
			gotoxy(xCoor,yCoor); cout << '-';
		}
		for (; x != y; x++)
		{
			if (x < (int)alugueres.size())
			{
				if ( (x % 2) == 0 ) // se x e par
					setcolor(8); // cor cinzento escuro

				if (alugueres.at(x)->getDiasParaAcabar() < 0)
					setcolor(4);
				gotoxy(2,++yCoor); cout << left << fixed << setprecision(2) << setw(5) << alugueres.at(x)->getID() << setw(22) << alugueres.at(x)->getViaturaAlugada()->getMarca() << setw(12) << alugueres.at(x)->getViaturaAlugada()->getMatricula() << (*alugueres.at(x)->getDataInicio()) << (*alugueres.at(x)->getDataFim()) << setw(20) << alugueres.at(x)->getCustoTotal() << setw(12) << alugueres.at(x)->getPontos() << setw(15);
				if (alugueres.at(x)->getDesconto())
					cout << "SIM" << endl;
				else
					cout << "NAO" << endl;
				setcolor(15);
			}
		}

		if (!onePage)
		{
			gotoxy(10,62);
			cout << "Prima a tecla 'B' para ver os alugueres anteriores, ou a tecla 'N' para ver os proximos alugueres. Prima ENTER para continuar.";
			multiplePagesView(ch, x, y, numeroAlugueres, alugueres);
		}

	} while (ch != ENTER && !onePage);
}

template <class T>
void Agencia::multiplePagesView(char& ch, int& x, int& y, int& numeroObjectos, const vector<T*>& objectos) const
{
	const char ENTER = 13, TECLAB = 'b', TECLAN = 'n';
	do
	{ ch = _getch(); } while (ch != ENTER && ch != TECLAB && ch != TECLAN);


	if (ch == TECLAB && x == numeroObjectos)
	{
		x = 0;
		y = numeroObjectos;
	}
	else if (ch == TECLAB && x != 0)
	{
		x -= 2*numeroObjectos;
		y -= numeroObjectos;
	}
	else if (ch == TECLAN && y < (int)objectos.size())
		y += numeroObjectos;
	else if (ch == TECLAN && x >= (int)objectos.size())
		x -= numeroObjectos;
}

Cliente* Agencia::getClienteByID(unsigned int& IDcliente) // devolve cliente com ID recebido
{
	Cliente c1;	c1.setID(IDcliente);
	int pos = BinarySearch(clientes_registados, c1); // posicao do cliente com ID recebido
	if (pos != -1) // se achou o cliente
		return clientes_registados.at(pos); // devolve cliente
	else // se posicao e invalida
		throw NaoExiste(IDcliente); // lanca excecao
}

Viatura* Agencia::getViaturaByID(unsigned int& IDviatura) // devolve viatura com ID recebido
{
	Viatura v1;	v1.setID(IDviatura);
	int pos = -1;
	for (size_t i = 0; i < viaturas_existentes.size(); i++)
		if (viaturas_existentes.at(i)->getID() == v1.getID())
			pos = i; // posicao da viatura com ID recebido
	if ( pos != -1) // se achou a viatura
			return viaturas_existentes.at(pos); // devolve a viatura
	else // se posicao e invalida
		throw NaoExiste(IDviatura); // lanca excecao
}

Funcionario* Agencia::getFuncionarioByID(unsigned int& IDfuncionario) // devolve funcionario com ID recebido
{
	Funcionario f1;	f1.setID(IDfuncionario);
	int pos = BinarySearch(funcionarios, f1); // posicao do funcionario com ID recebido
	if (pos != -1) // se achou o funcionario
		return funcionarios.at(pos); // devolve o funcionario
	else
		throw NaoExiste(IDfuncionario); // lanca excecao
}

Aluguer* Agencia::getAluguerByID(unsigned int& IDaluguer) // devolve aluguer com ID recebido
{
	Aluguer a1;	a1.setID(IDaluguer);
	int pos = BinarySearch(alugueres_activos, a1); // posicao do aluguer com ID recebido
	if (pos != -1) // se achou o aluguer
		return alugueres_activos.at(pos); // devolve o aluguer
	else
		throw NaoExiste(IDaluguer); //lanca excecao
}

void Agencia::saveAgencia(const unsigned int& op) const // grava os dados da agencia
{
	fstream file;
	switch (op)
	{
	case 1: // guardar clientes
	{
		file.open (filenameClientes.c_str(), fstream::out); // abre o ficheiro com operacoes de output
		if ( file.is_open() )
			save(clientes_registados,file);
	}
	break;
	case 2: // guardar funcionarios
	{
		file.open (filenameFuncionarios.c_str(), fstream::out);
		if ( file.is_open() )
		{
			file << posNextFuncionario;
			file << '\n';
			save(funcionarios,file);
		}
	}
	break;
	case 3: // guarda viaturas
	{
		file.open (filenameViaturas.c_str(), fstream::out);
		if ( file.is_open() )
			save(viaturas_existentes,file);
	}
	break;
	case 4:	// guardar alugueres
	{
		file.open (filenameAlugueres.c_str(), fstream::out);
		if ( file.is_open() )
			save(alugueres_activos,file);
	}
	break;
	case 5: // grava todos os dados
	{
		saveAgencia(1);
		saveAgencia(2);
		saveAgencia(3);
		saveAgencia(4);
		saveAgencia(6);
		saveAgencia(7);
	}
	break;
	case 6: // guardar catalogo
	{
		file.open(filenameCatalogo.c_str(), fstream::out);
		if ( file.is_open() )
			saveCatalogo(file);
	}
	break;
	case 7: // guardar oficinas
	{
		file.open(filenameOficinas.c_str(), fstream::out);
		if ( file.is_open() )
			saveOficinas(file);
	}
	}
	file.close();
}

void Agencia::saveCatalogo(fstream& outFile) const
{
	BSTItrIn<Viatura> it(viaturas);

	for (int i = 0; !it.isAtEnd(); it.advance(), i++)
	{
		if (i != 0)
			outFile << '\n';
		it.retrieve().saveInfo(outFile);
	}
}

template <class T>
void Agencia::save(const vector<T*>& objects, fstream& outFile) const // grava um vector completo de objectos
{
	for (unsigned int i = 0; i < objects.size(); i++)
	{
		if ( i != 0 ) // todos os objectos, excepto o 1 devem inserir nova linha
			outFile << '\n';
		objects.at(i)->saveInfo(outFile); // guarda info sobre o objecto
	}
}

template <class T>
void Agencia::save1object(const T* object, const string& filename) // grava num ficheiro um objecto
{
	fstream file;
	file.open (filename.c_str(), fstream::out | fstream::app); // abre o ficheiro com operacoes de output e append
	if (file.is_open())
	{
		if (object->getID() != 1) // se nao for o 1 elemento a ser gravado
			file << '\n'; // insere nova linha
		object->saveInfo(file);
	}
	file.close();
}

void Agencia::loadAgencia() // carrega os dados da agencia
{
	fstream fileClientes, fileFuncionarios, fileViaturas, fileAlugueres, fileCatalogo, fileOficinas;

	// load clientes
	if (!blankFile(1)) // se o ficheiro nao esta vazio, deve ler
	{
		fileClientes.open ( filenameClientes.c_str(), fstream::in ); // abre o ficheiro com operacoes de input
		if ( fileClientes.is_open() )
			while( !fileClientes.eof() ) // se ainda nao chegou a end-of-file
				load(clientes_registados, fileClientes); // carrega a info do cliente
		fileClientes.close();
		if (!clientes_registados.empty()) // se foram carregados clientes
			Cliente::setNumClientes(clientes_registados.at(clientes_registados.size()-1)->getID()); // actualiza o num de clientes
	}

	printf("entra loadAgencia\n");
	// load funcionarios
	if (!blankFile(2)) // se o ficheiro nao esta vazio, deve ler
	{
		fileFuncionarios.open ( filenameFuncionarios.c_str(), fstream::in ); // abre o ficheiro com operacoes de input
		if ( fileFuncionarios.is_open() )
		{
			fileFuncionarios >> posNextFuncionario;
			fileFuncionarios.ignore(1,'\n');
			while( !fileFuncionarios.eof() )
			{
				load(funcionarios, fileFuncionarios); // carrega a info do funcionario
			}
		}
		fileFuncionarios.close();
		if (!funcionarios.empty()) // se foram carregados funcionarios
			Funcionario::setNumFuncionarios(funcionarios.at(funcionarios.size()-1)->getID()); // actualiza o num de funcionarios
	}

	// load oficinas
	if (!blankFile(6))
	{
		fileOficinas.open(filenameOficinas.c_str(), fstream::in);
		if (fileOficinas.is_open())
		{
			int numOficinas, numRepair;

			fileOficinas >> numOficinas;
			fileOficinas.ignore(1,'\n');

			fileOficinas >> numRepair;
			fileOficinas.ignore(1,'\n');

			Reparacao::setNumReparacoes(numRepair);
			Oficina::setNumOficinas(numOficinas);

			while ( !fileOficinas.eof())
			{
				Oficina of;
				of.loadInfo(fileOficinas);
				fileOficinas.ignore(1,'\n');
				oficinas.push(of);
			}
		}
	}

	int num_viaturas = 0;

	// load catalogo
	if (!blankFile(5)) // se o ficheiro nao esta vazio, deve ler
	{
		fileCatalogo.open(filenameCatalogo.c_str(), fstream::in);
		if ( fileCatalogo.is_open() )
		{
			while ( !fileCatalogo.eof() )
			{
				Viatura* v = new Viatura();
				v->loadInfo(fileCatalogo);
				if (v->getID() != 0)
				{
					if ( (int)v->getID() > num_viaturas )
						num_viaturas = v->getID();
					viaturas.insert(*v);
				}
				fileViaturas.ignore(1,'\n');
			}
		}
		fileCatalogo.close();
	}

	// load Viaturas
	if (!blankFile(3)) // se o ficheiro nao esta vazio, deve ler
	{
		fileViaturas.open ( filenameViaturas.c_str(), fstream::in );
		if ( fileViaturas.is_open() )
			while( !fileViaturas.eof() )
			{
				Viatura* v = new Viatura();
				v->loadInfo(fileViaturas);
				if (v->getID() > num_viaturas)
					num_viaturas = v->getID();
				viaturas_existentes.push_back(v);
				fileViaturas.ignore(1,'\n');
			}
		fileViaturas.close();
	}

	Viatura::setNumViaturas(num_viaturas); // atualiza o numero de viaturas

	// load Alugueres
	if (!blankFile(4)) // se o ficheiro nao esta vazio, deve ler
	{
		fileAlugueres.open ( filenameAlugueres.c_str(), fstream::in ); // abre o ficheiro com operacoes de input
		if ( fileAlugueres.is_open() )
			while( !fileAlugueres.eof() )
				load(alugueres_activos, fileAlugueres); // carrega info do aluguer
		fileAlugueres.close();
		if (!alugueres_activos.empty())
			Aluguer::setNumAlugueres(alugueres_activos.at(alugueres_activos.size()-1)->getID());
	}

	matchAlugueres();
	matchClientes();
	matchFuncionarios();
	
}

template <class T>
void Agencia::load(vector<T*>& objects, fstream& inFile)
{
	T* object = new T(); // cria um novo apontador para um objecto
	object->loadInfo(inFile); // lê as informações para esse objecto
	objects.push_back(object); // acrescenta o novo objecto ao vector
	inFile.ignore(1,'\n'); // ignora a linha em branco no ficheiro
}

bool Agencia::blankFile(unsigned int op)
{
	fstream file;
	string teste;

	if ( op == 1) // verifica o ficheiro dos clientes
		file.open(filenameClientes.c_str(), fstream::in);
	else if ( op == 2) // verifica o ficheiro dos funcionarios
		file.open(filenameFuncionarios.c_str(), fstream::in);
	else if ( op == 3) // verifica o ficheiro das viaturas
		file.open(filenameViaturas.c_str(), fstream::in);
	else if (op == 4) // verifica o ficheiro dos alugueres
		file.open(filenameAlugueres.c_str(), fstream::in);
	else if (op == 5)
		file.open(filenameCatalogo.c_str(), fstream::in);
	else if (op == 6)
		file.open(filenameOficinas.c_str(), fstream::in);

	if (file.is_open())
		getline(file,teste); // vai buscar a primeira linha do ficheiro
	file.close();

	if ( teste.size() != 0) // se tamanho nao for 0
		return false; // o ficheiro nao esta vazio

	return true;
}

void Agencia::exitAgencia() // apaga ficheiros que nao contenham informacao
{
	saveAgencia(5); // grava os dados
	// apaga ficheiros que fiquem vazios
	if (viaturas_existentes.empty())
		remove(filenameViaturas.c_str());
	if(funcionarios.empty())
		remove(filenameFuncionarios.c_str());
	if(clientes_registados.empty())
		remove(filenameClientes.c_str());
	if(alugueres_activos.empty())
		remove(filenameAlugueres.c_str());
	if(viaturas.isEmpty())
		remove(filenameCatalogo.c_str());
	if (oficinas.empty())
		remove(filenameOficinas.c_str());
}

/*
 * funcao que vai buscar os ID's dos alugueres que o cliente tem activos
 * e passa os alugueres para o seu vector de alugueres.
 */
void Agencia::matchClientes()
{
	// percorrer os clientes todos
	for (vector<Cliente*>::iterator it = clientes_registados.begin(); it != clientes_registados.end(); it++)
	{
		// vai buscar o vector que contem os ID's dos alugueres
		vector<int> IDalugueresCliente = (*it)->getIDalugueresActivos();

		// percorre os ID's todos
		for (unsigned int i = 0; i < IDalugueresCliente.size(); i++)
		{
			Aluguer tmp; // cria um novo objecto de tipo aluguer
			tmp.setID(IDalugueresCliente.at(i)); // define o ID desse aluguer com o da posicao actual
			int posAluguer = BinarySearch(alugueres_activos, tmp); // vai pesquisar a posicao do aluguer no vector da agencia
			(*it)->addAluguer(alugueres_activos.at(posAluguer)); // adiciona o aluguer ao vector do cliente
		}
	}
}

/*
 * @ funcao que vai atribuir as viaturas aos alugueres que ate agora so contem
 * uma viatura vazia com o ID da viatura original
 */
void Agencia::matchAlugueres()
{
	for (vector<Aluguer*>::iterator it = alugueres_activos.begin(); it != alugueres_activos.end(); it++)
	{
		Viatura* v = (*it)->getViaturaAlugada();

		int pos;
		for (size_t i = 0; i < viaturas_existentes.size(); i++)
			if (viaturas_existentes.at(i)->getID() == v->getID())
				pos = i;

		(*it)->setViaturaAlugada(viaturas_existentes.at(pos));
		delete v;
		//actualiza os pontos e o custo total
		(*it)->setCustoTotal(0);
		(*it)->setPontos(0);
	}
}

void Agencia::matchFuncionarios()
{
	// percorrer os funcionarios todos
	for (vector<Funcionario*>::iterator it = funcionarios.begin(); it != funcionarios.end(); it++)
	{
		// vai buscar o vector que contem os ID's dos alugueres
		vector<int> IDalugueresFuncionario = (*it)->getIDalugueresActivos();

		// percorre os ID's todos
		for (unsigned int i = 0; i < IDalugueresFuncionario.size(); i++)
		{
			Aluguer tmp; // cria um novo objecto de tipo aluguer
			tmp.setID(IDalugueresFuncionario.at(i)); // define o ID desse aluguer com o da posicao actual
			int posAluguer = BinarySearch(alugueres_activos, tmp); // vai pesquisar a posicao do aluguer no vector da agencia
			(*it)->addAluguer(alugueres_activos.at(posAluguer)); // adiciona o aluguer ao vector do cliente
		}
	}
}

// novas funcoes para o catalogo de viaturas

bool Agencia::catalogoEmpty() const
{
	return viaturas.isEmpty();
}

void Agencia::addViaturaCatalogo(Viatura* novaV)
{
	viaturas.insert(*novaV);
	save1object(novaV, filenameCatalogo); // grava a informacao sobre a nova Viatura
}

void Agencia::showCatalogo()
{
	BSTItrIn<Viatura> it(viaturas); //iterador em ordem

	cout << left << setw(5) << "ID" << setw(25) << "MARCA" << setw(25) << "MODELO" << setw(12) << "MATRICULA" << setw(15) << "COMBUSTIVEL" << setw(20) << "TRANSMISSAO" << setw(13) << "POTENCIA(cv)" << setw(6) << "ANO" << setw(9) << "PRECO"  << setw(16) << "NUM x ALUGADO" << setw(12) << "DISPONIVEL" << endl << endl;

	for (; !it.isAtEnd(); it.advance())
	{
		cout << uppercase << left << setw(5) << it.retrieve().getID() << setw(25) << it.retrieve().getMarca() << setw(25) << it.retrieve().getModelo() << setw(12) << it.retrieve().getMatricula() << setw(15) << it.retrieve().getCombustivel() << setw(20) << it.retrieve().getTransmissao() << setw(13) << it.retrieve().getCV() << setw(6) << it.retrieve().getRegisto()->getAno() << setw(9) << it.retrieve().getPrecoPorDia() << setw(16) << it.retrieve().getnXalugado() << setw(12);
		if (it.retrieve().getDisponivel())
			cout << "SIM" << endl;
		else
			cout << "NAO" << endl;
	}
}

BST<Viatura>& Agencia::getCatalogo()
{
	return viaturas;
}

void Agencia::pesquisarCatalogo(vector<Viatura*>& resultados, pesquisaViatura& p) // pesquisa de viaturas
{
	BSTItrIn<Viatura> it (viaturas);

	for (; !it.isAtEnd(); it.advance())
	{
		int criterios = numCriteriosViatura(p); // define num de criterios alterados na pesquisa

		if (p.marca != "null") // se criterio marca foi alterado
			if (foundIt(it.retrieve().getMarca(), p.marca))
				criterios--;

		if (p.modelo != "null") // se criterio modelo foi alterado
			if (foundIt(it.retrieve().getModelo(), p.modelo))
				criterios--;

		if (p.matricula != "null") // se criterio matricula foi alterado
			if (foundIt(it.retrieve().getMatricula(), p.matricula))
				criterios--;

		if (p.transmissao != "null") // se criterio transmissao foi alterado
			if (foundIt(it.retrieve().getTransmissao(), p.transmissao))
				criterios--;

		if (p.combustivel != "null") // se criterio combustivel foi alterado
			if (foundIt(it.retrieve().getCombustivel(), p.combustivel))
				criterios--;

		if (p.ano != 0 ) // se criterio ano foi alterado
			if (p.anoOp == 1) // opcao 1 - superior a
			{
				if (it.retrieve().getRegisto()->getAno() >= p.ano)
					criterios--;
			}
			else // opcao 2 - inferior a
				if (it.retrieve().getRegisto()->getAno() <= p.ano)
					criterios--;

		if (p.nXalugado != -1 ) // se criterio nXalugado foi alterado
			if (p.nXalugadoOp == 1) // opcao 1 - superior a
			{
				if ((int)it.retrieve().getnXalugado() >= p.nXalugado )
					criterios--;
			}
			else // opcao 2 - inferior a
				if ((int)it.retrieve().getnXalugado() <= p.nXalugado)
					criterios--;

		if ( p.precoPorDia_inf != -1 ) // foi utilizado o criterio preco por dia (precoPorDia_inf e alterado em qualquer opcao do preco)
			if ( (int)it.retrieve().getPrecoPorDia() >= p.precoPorDia_inf && (int)it.retrieve().getPrecoPorDia() <= p.precoPorDia_sup )
				criterios--;

		if (p.cv != 0 ) // se criterio cv foi alterado
			if (p.cvOp == 1) // opcap 1 - superior a
			{
				if ((int)it.retrieve().getCV() >= p.cv )
					criterios--;
			}
			else // opcao 2 - inferior a
				if ((int)it.retrieve().getCV() <= p.cv)
					criterios--;

		if (p.cilindrada != -1 ) // se criterio cilindrada foi alterado
			if (p.cilindradaOp == 1)
			{
				if ((int)it.retrieve().getCilindrada() >= p.cilindrada )
					criterios--;
			}
			else
				if ((int)it.retrieve().getCilindrada() <= p.cilindrada)
					criterios--;

		if(criterios == 0)
			resultados.push_back(&it.retrieve());
	}
}


// novas funcoes para as oficinas

bool Agencia::hasOficinas () const
{
	return (!oficinas.empty());
}

void Agencia::adicionaReparacao(const Reparacao& r)
{
	try
	{
		// vai buscar a Oficina disponivel mais cedo, que tenha disponibilidade suficiente
		Oficina of = disponivelMaisCedo(r.getTempoReparacao());
		try
		{
			of.addReparacao(r);
		}
		catch (Oficina::UltrapassadaOcupacaoMaxima& upm)
		{
			cout << "Erro no algoritmo de funcao \"disponivel mais cedo\". ";
		}
		
		// volta a adicionar a oficina a fila
		oficinas.push(of);
		cout << "\nReparacao adicionada com sucesso a oficina " << of.getNome() << ". ";
	}
	catch(NaoExisteOficinaDisponivel& neof)
	{
		throw NaoExisteOficinaDisponivel ();
	}
	saveAgencia(7); // guarda info das oficinas
}

Oficina Agencia::disponivelMaisCedo (int tempoReparacao)
{
	vector<Oficina> temp;

	while (!oficinas.empty())
	{
		Oficina of = oficinas.top();
		oficinas.pop();

		// verifica se oficina tem disponibilidade suficiente
		if ( of.getDisponibilidade() >= tempoReparacao )
		{
		 	// se encontrou uma oficina viavel, volta a meter as outras na fila
			for (size_t i = 0; i < temp.size(); i++)
				oficinas.push(temp[i]);
			return of;
		}
		else
			temp.push_back(of);
	}
	
	// se nao encontrou nenhuma, volta a meter as oficinas e lanca excepcao;
	for (size_t i = 0; i < temp.size(); i++)
		oficinas.push(temp[i]);
	throw NaoExisteOficinaDisponivel();
}

void Agencia::addOficina(Oficina& of)
{
	oficinas.push(of);
	save1object(&of, filenameOficinas);
}

void Agencia::removeOficina(int ID)
{
	vector<Oficina> temp;
	
	// guarda o numero de oficinas com que iniciou o algoritmo
	int numOficinas_i = oficinas.size(), numOficinas_f = 0;

	while (!oficinas.empty())
	{
		Oficina of = oficinas.top();
		oficinas.pop();

		if (of.getID() != ID)
			temp.push_back(of); // guarda em temp as que nao correspodem
	}

	for (size_t i = 0; i < temp.size(); i++)
	{
		numOficinas_f++; // calcula o numero de oficinas com que ficou no final
		oficinas.push(temp[i]);
	}

	if ( numOficinas_i == numOficinas_f ) // significa que nao encontrou a oficina
		throw OficinaNaoExistente(ID);
	saveAgencia(7); // guarda info das oficinas
}

void Agencia::showOficinas()
{
	vector<Oficina> temp;

	while (!oficinas.empty())
	{
		Oficina of = oficinas.top();
		oficinas.pop();

		cout << of << endl << "--------------\n" << endl;

		temp.push_back(of);
	}

	for (size_t i = 0; i < temp.size(); i++)
		oficinas.push(temp[i]);
}

void Agencia::saveOficinas(fstream& outFile) const
{

	if (!oficinas.empty())
	{
		HEAP_OFICINAS buffer = oficinas;
		int i = 0;

		outFile << Oficina::getNumOficinas() << '\n';
		outFile << Reparacao::getNumReparacoes() << '\n';

		while (!buffer.empty())
		{
			Oficina of = buffer.top();
			buffer.pop();

			if (i != 0)
				outFile << '\n';
			else
				i++;
			of.saveInfo(outFile);
		}
	}
}

Oficina Agencia::getOficinaById(int ID)
{
	if (oficinas.empty())
		throw OficinaNaoExistente(ID);
	else
	{
		vector<Oficina> temp;

		while (!oficinas.empty())
		{
			Oficina of = oficinas.top();
			oficinas.pop();

			if (of.getID() == ID)
			{
				// volta a meter as oficinas de temp para a fila
				for (size_t i = 0; i < temp.size(); i++)
					oficinas.push(temp[i]);
				return of;
			}
			else
				temp.push_back(of);
		}

		// se nao encontrou, mete as oficinas na fila
		for (size_t i = 0; i < temp.size(); i++)
			oficinas.push(temp[i]);

		throw OficinaNaoExistente(ID); // nao existe oficina com este ID
	}
}

Reparacao Agencia::getReparacaoById(int ID)
{
	vector<Oficina> temp;
	Reparacao r;
	Viatura* v;
	unsigned int IDviatura;

	while (!oficinas.empty())
	{
		Oficina of = oficinas.top();
		oficinas.pop();

		try
		{
			r = of.getReparacaoById(ID);

			// mete as oficinas de temp para a fila
			for (size_t i = 0; i < temp.size(); i++)
				oficinas.push(temp[i]);

			//actualiza ocupacao
			of.updateOcupacaoAtual(r.getTempoReparacao());

			// mete viatura como disponivel
			IDviatura = r.getIDviatura();
			v = getViaturaByID(IDviatura);
			v->setDisponivel(true);

			// mete a oficina na fila
			oficinas.push(of);

			return r;
		}
		catch (Oficina::ReparacaoNaoExistente& rne)
		{
			temp.push_back(of);
		}
	}

	// mete as oficinas de temp para a fila
	for (size_t i = 0; i < temp.size(); i++)
		oficinas.push(temp[i]);

	throw Oficina::ReparacaoNaoExistente();
}

void Agencia::pesquisarOficina(vector<Oficina>& resultados, pesquisaOficina& p)
{
	vector<Oficina> temp;

	while (!oficinas.empty())
	{
		Oficina of = oficinas.top();
		oficinas.pop();

		int numCriterios = numCriteriosOficina(p);

		if (p.nome != "null")
			if (foundIt(of.getNome(), p.nome))
				numCriterios--;

		if (p.cidade != "null")
			if (foundIt(of.getLocalizacao(), p.cidade))
				numCriterios--;

		if (p.distancia_inf != -1) // criterio distancia_inf e alterado em qualquer pesquisa por distancia
			if (of.getDistancia() >= p.distancia_inf && of.getDistancia() <= p.distancia_sup)
				numCriterios--;

		if (p.numFuncionarios_inf != -1)
			if ( ((of.getOcupacao()+of.getDisponibilidade())/8) >= p.numFuncionarios_inf &&
					((of.getOcupacao()+of.getDisponibilidade())/8) <= p.numFuncionarios_sup )
				numCriterios--;

		if (numCriterios == 0) // oficina corresponde aos criterios da pesquisa
			resultados.push_back(of);
		else // vai guardando as que nao correspondem
			temp.push_back(of);
	}

	// tem de voltar a meter as que nao corresponderam para a fila
	for (size_t i = 0; i < temp.size(); i++)
		oficinas.push(temp[i]);
}

void Agencia::autoFinishRepairs()
{
	vector<Oficina> temp;
	vector<int> viaturasID;
	Data atual = returnDataActual();

	while (!oficinas.empty())
	{
		Oficina of = oficinas.top();
		oficinas.pop();

		of.autoFinishRepairs(atual,viaturasID);

		temp.push_back(of);
	}

	// voltar a colocar as oficinas
	for (size_t i = 0; i < temp.size(); i++)
		oficinas.push(temp[i]);

	// mete as viaturas que estavam a ser reparadas como disponiveis
	for (size_t j = 0; j < viaturasID.size(); j++)
	{
		unsigned int ID = viaturasID[j];
		Viatura* v = getViaturaByID(ID);
		v->setDisponivel(true);
	}
	saveAgencia(7); // guarda info das oficinas
}

//Clientes inativos

void Agencia::reactivarCliente(Cliente* novoCliente)
{
	clientes_inativos.removerCliente(novoCliente);
}

void Agencia::desativarCliente(Cliente* novoCliente)
{
	clientes_inativos.inserirCliente(novoCliente);
}

void Agencia::removeClienteInativo(Cliente* novoCliente)
{
	reactivarCliente(novoCliente);
	removeCliente(novoCliente);
	saveAgencia(1);
}
Tabela Agencia::getTabelaInativos() const
{
	return clientes_inativos;
}

void Agencia::checkClientesInativos()
{
	for (vector<Cliente*>::const_iterator it = clientes_registados.begin(); it != clientes_registados.end(); it++)
		if ( (returnDataActual() - (*(*it)->getUltimoAluguer()) ) > 730)
		{
			desativarCliente(*it);
			(*it)->setAtivo(false);
		}
}

bool Agencia::hasClientesInativos() const
{
	return (clientes_inativos.getNumInativos() > 0);
}

void Agencia::showClientesInativos(const vector<Cliente*>& clientes) const
{
	int numeroClientes = 52; // numero maximo de Clientes que pode representar na resolucao dos ecras da FEUP
	int x = 0; // posicao do primeiro Cliente a ser apresentado
	int y = numeroClientes; //
	bool onePage = false;
	const char ENTER = 13;
	char ch = ENTER;

	if ((int)clientes.size() <= numeroClientes)
		onePage = true;

	do {
		clearScreen();
		showFrames();
		gotoxy(73,2); cout << "*** CLIENTES INATIVOS ***";
		int yCoor = 7;
		gotoxy(2,yCoor); cout << left << setw(5) << "ID" << setw(40) << "NOME" << setw(9) << "IDADE" << setw(25) << "CIDADE" << setw(16) << "ALUG. ATIVOS" << setw(21) << "NUM. ALUG. ATIVOS" << setw(21) << "NUM. ALUG. REALIZ." << setw(23) << "ALUG. EM ATRASADO";
		yCoor++;
		for (int xCoor = 2; xCoor < 175;xCoor++)
		{
			gotoxy(xCoor,yCoor); cout << '-';
		}
		for (; x != y; x++)
		{
			if ( (x < (int)clientes.size()) && !clientes.at(x)->getAtivo())
			{

				if ( (x % 2) == 0 ) // se x e par
					setcolor(8); // cor cinzento escuro

				gotoxy(2,++yCoor);
				cout << left << setw(5) << clientes.at(x)->getID() << setw(40) << clientes.at(x)->getNome() << setw(9) << clientes.at(x)->getIdade() << setw(25) << clientes.at(x)->getContato()->getCidade() << setw(16);
				if (clientes.at(x)->hasAlugueresActivos())
					cout << "SIM";
				else
					cout << "NAO";
				cout << setw(21) << clientes.at(x)->getAlugueresActivos().size() << setw(21) << clientes.at(x)->getNumAlugueresRealizados() << setw(23);
				if (clientes.at(x)->hasAluguerAtrasados())
					cout << "SIM";
				else
					cout << "NAO";
				setcolor(15);
			}
		}

		if (!onePage)
		{
			gotoxy(10,62);
			cout << "Prima a tecla 'B' para ver os clientes anteriores, ou a tecla 'N' para ver os proximos clientes. Prima ENTER para continuar.";
			multiplePagesView(ch, x, y, numeroClientes, clientes);
		}

	} while (ch != ENTER && !onePage);
}



long convertString(string& str)
{
	stringstream ss(str);
	long num = 0;
	ss >> num;
	return num;
}

bool foundIt (const string original, string pesquisa) // checks if a string name has a certain string of characters
{
	string nova(original);
	allUpperCase (nova); // converts the letters in name to uppercase
	allUpperCase (pesquisa); // does the same to the string pesquisa

	if (nova.find(pesquisa) != string::npos) // if it finds, the position will be different from npos (normally -1)
		return true; // so it returns true
	return false; // otherwise, returns false
}

void allUpperCase (string& str) // converts all the letters in a string to uppercase
{
	for (int i = 0; i < (int)str.size(); i++)
		str[i] = toupper (str[i]); // uses toupper to convert, if letter is already uppercase stays the same
}
