/*
 * mainHelper.cpp
 */

#include "mainHelper.h"

/* ********************************************************
 *
 * AREA DE FUNCIONARIOS
 *
 * ********************************************************
 */

bool addNovoFuncionario(Agencia& a) // adiciona novo funcionario
{
	string nome;
	Data* nascimento;
	Contato* contacto; string pais, morada, cidade, postal, email; long phone;
	Funcionario* novoFunc;
	long BI;
	unsigned int vencimento;
	bool proceed = true;

	cout << endl;
	lerString(nome, 1, proceed); // le nome

	if (proceed) // se proceed ainda e verdadeiro, entao o programa continua
	{
		int dia = 0, mes = 0, ano = 0;
		bool dataValida = true;

		do
		{
			cout << endl;
			cout << "Data de nascimento\n";
			lerData(dia,mes,ano,proceed);

			if (proceed)
			{
				try // tenta criar uma data com os dados lidos
				{
					nascimento = new Data(dia,mes,ano);
					dataValida = true;
				}
				catch (DataInvalida &e) // a data inserida nao era valida
				{
					cout << "Data Invalida. Tente outra vez. ";
					pressEnter();
					cout << endl;
					dataValida = false;
				}
			}
		} while ( !dataValida && proceed);
	}

	cout << endl;
	if (proceed)
		lerString(pais, 2, proceed); // le o pais do funcionario

	if (proceed) // le a morada
		do
		{
			cout << endl;
			cout << "(*)Morada: ";
			getline(cin,morada);

			if ( !testProceed(morada,proceed) )
				break;

			if (isNumber(morada))
			{
				cout << "Morada invalida. Tente outra vez ";
				pressEnter();
			}
		} while (isNumber(morada) );

	cout << endl;
	if (proceed)
		lerString(cidade,3, proceed); // le a cidade


	if (proceed) // le codigo postal
	{
		cout << endl;
		cout << "(*)Codigo-Postal: ";
		getline(cin,postal);

		testProceed(postal,proceed);
	}

	cout << endl;
	if (proceed) // le o numero de telefone
		lerNumero(phone, proceed, 1);

	if(proceed) // le o email
		do
		{
			cout << endl;
			cout << "(*)e-mail: ";
			getline(cin, email);

			if ( !testProceed(email, proceed))
				break;

			if (!validMail(email))
			{
				cout << "Email invalido. Tente outra vez. ";
				pressEnter();
				cout << endl;
			}
		} while(!validMail(email)); // enquanto email nao for valido

	if (proceed) // cria Contato
	{
		contacto = new Contato(pais, morada, cidade, postal, phone, email);
        cout << endl;
		lerNumero(BI, proceed, 2);
	}

    cout << endl;
	if (proceed)
		lerNumero(vencimento, proceed, 3); // le vencimento

	if (proceed)
	{
		try
		{
			novoFunc = new Funcionario(nome, BI , nascimento , contacto , vencimento); // tenta criar um novo funcionario
		}
		catch(menorIdade& mI) // o funcionario era menor de idade
		{
			cout << endl << mI.getNome() << " nao pode ser adicionado por ser menor de idade. ";
			pressEnter();
			proceed = false;
		}
	}
	if (proceed)
	{
		try
		{
			a.addFuncionario(novoFunc);
			cout << endl << "Funcionario " << novoFunc->getNome() << " adicionado com sucesso com o ID: " << novoFunc->getID() << ". ";
			return true;
		}
		catch(jaExiste& j) // o BI dado ja esta a ser utilizado por outro funcionario
		{
			delete novoFunc; // nao foi acrescentado a agencia, logo nao ia ser apagado
			Funcionario::anularFuncionario(); // decrementa o numero dos funcionarios
            cout << endl;
			cout << endl << "O BI escolhido ja esta a ser utilizado pelo funcionario com o ID: " << j.getID() << '.' << endl;
			cout << "Tente outra vez ou remova o funcionario em questao. ";
			pressEnter();
		}
	}
	return false;
}

Funcionario* searchFuncionario(Agencia& a, bool& proceed, bool& didSearch) // pesquisa um funcionario
{
	Funcionario* nulo = NULL;
	vector<Funcionario*> resultados; // vector que tera os resultados da pesquisa
	searchIt(a, resultados, proceed, 1, didSearch); // funcao template de pesquisa de funcionarios/clientes
	if (!resultados.empty()) // se obteve resultados
	{
		unsigned int ID;
		if (resultados.size() == 1) // se so teve 1 resultado
		{
			ID = resultados.at(0)->getID();
			return a.getFuncionarioByID(ID); // devolve logo esse funcionario
		}

		a.showFuncionarios(resultados); // mostra os resultados
		if ( resultados.size() <= 52) // se os resultados ficarem numa pagina apenas
		{
			gotoxy(10,62); pressEnter(); // deve pedir para continuar
		}
		bool foundIt;
		do
		{
			clearScreen();
			foundIt = false;
			lerNumero(ID,proceed, 5);
			if (proceed)
			{
				clearScreen();
				for (unsigned int i = 0; i < resultados.size(); i++)
					if ( ID == resultados.at(i)->getID() ) // se o funcionario com o ID escolhido faz parte dos resultados
						foundIt = true;
				if(!foundIt)
				{
					cout << "O funcionario com ID " << ID << " nao faz parte dos encontrados pela pesquisa. Tente outra vez. ";
					pressEnter();
				}
			}
		} while (!foundIt && proceed);

		if (proceed)
			return a.getFuncionarioByID(ID);
	}
	return nulo;
}

void ModifyRemoveFuncionario(Agencia& a, bool& proceed, unsigned int mr) // mr = 1 se for para modificar e 2 para remover
{
	int estado = 0, input;
	do {
		clearScreen(); // limpa ecra
		do {
			int x = 69, y = 28;

			gotoxy(77,2);
			if (mr == 1)
				cout << "*** MODIFICAR";
			else
				cout << "*** REMOVER";
			cout << " FUNCIONARIO ***";

			y = (y+4*estado);

			displayMenuPlusArrows(x,44,y,6,input,estado,4);

		} while ( input != ENTER && input != ESC ); // repete enquanto opcao nao for valida

		switch(estado)
		{
		case 0: // mostrar todos os funcionarios
		{
			if (a.getNumFuncionarios() != 0) // se houver funcionario para mostrar
			{
				unsigned int ID;
				bool validID;
				Funcionario* f;
				a.showFuncionarios(a.getFuncionarios()); // mostra funcionarios
				if ( a.getNumFuncionarios() <= 52 ) // se funcionarios ficarem apenas numa pagina
				{
					gotoxy(10,62); pressEnter(); // pede para continuar
				}
				clearScreen(); // limpa ecra
				do
				{

					validID = true;
					lerNumero(ID,proceed, 5);
					if (proceed)
					{
						try
						{
							f = a.getFuncionarioByID(ID); // tenta ir buscar o funcionario
						}
						catch (NaoExiste& ne) // se nao existe funcionario com esse ID
						{
							cout << "O funcionario com ID " << ne.getID() << " nao existe. Tente outra vez. ";
							pressEnter();
							cout << endl;
							validID = false;
						}
					}
				} while (!validID);
				if(proceed)
					if (mr == 1)
						modify(a, f, proceed); // modifica o funcionario
					else
					{
						if (f->hasAlugueresActivos())
						{
							cout << "O funcionario com ID " << f->getID() << " nao pode ser removido pois tem alugueres activos. Tente outra vez. ";
							pressEnter();
							cout << endl;
						}
						else
							a.removeFuncionario(f); // remove o funcionario
					}
			}
			else
			{
				gotoxy(58,45); cout << "Nao ha funcionarios registados na agencia. ";
				pressEnter();
			}
			break;
		}
		case 1: // pesquisar um funcionario
		{
			if (a.getNumFuncionarios() != 0)
			{
				bool didSearch = false;
				Funcionario* f = searchFuncionario(a, proceed, didSearch);
				if (f != NULL)
					if (mr == 1)
						modify(a, f, proceed);
					else
					{
						if (f->hasAlugueresActivos())
						{
							cout << "O funcionario com ID " << f->getID() << " nao pode ser removido pois tem alugueres activos. Tente outra vez. ";
							pressEnter();
							cout << endl;
						}
						else
							a.removeFuncionario(f); // remove o funcionario
					}
				else if (didSearch && proceed)
				{
					cout << "Nao foram encontrados resultados. ";
					pressEnter();
				}
			}
			else
			{
				gotoxy(58,45); cout << "Nao ha funcionarios registados na agencia. ";
				pressEnter();
			}
		}
		break;
		case 2: // introduzir ID do funcionario
		{
			if (a.getNumFuncionarios() != 0)
			{
				unsigned int ID;
				bool validID;
				Funcionario* f;
				do
				{
					clearScreen();
					validID = true;
					lerNumero(ID,proceed, 5);
					if (proceed)
					{
						try
						{
							f = a.getFuncionarioByID(ID);
						}
						catch (NaoExiste& ne)
						{
							cout << "O funcionario com ID " << ne.getID() << " nao existe. Tente outra vez. ";
							pressEnter();
							validID = false;
						}
					}
				} while (!validID);

				if (proceed)
					if (mr == 1)
						modify(a,f,proceed);
					else
					{
						if (f->hasAlugueresActivos())
						{
							cout << "O funcionario com ID " << f->getID() << " nao pode ser removido pois tem alugueres activos. Tente outra vez. ";
							pressEnter();
							cout << endl;
						}
						else
							a.removeFuncionario(f); // remove o funcionario
					}
			}
			else
			{
				gotoxy(58,56); cout << "Nao ha funcionarios registados na agencia. ";
				pressEnter();
			}
		}
		break;
		}
	} while (estado != 3);
}

/* ********************************************************
 *
 * AREA DE CLIENTES
 *
 * ********************************************************
 */

bool addNovoCliente(Agencia& a)
{
	string nome;
	Data* nascimento;
	Contato* contacto; string pais, morada, cidade, postal, email; long phone;
	Cliente* novoClie;
	long BI, NIF;
	bool proceed = true;

	cout << endl;
	lerString(nome, 1, proceed);

	if (proceed) // se proceed ainda e verdadeiro, entao o programa continua
	{
		int dia = 0, mes = 0, ano = 0;
		bool dataValida = true;

		do
		{
			cout << endl;
			cout << "Data de nascimento\n";
			lerData(dia,mes,ano,proceed);

			if (proceed)
			{
				try
				{
					nascimento = new Data(dia,mes,ano);
					dataValida = true;
				}
				catch (DataInvalida &e) // quando nao da certo nao funciona, porque?
				{
					cout << "Data Invalida. Tente outra vez. ";
					pressEnter();
					cout << endl;
					dataValida = false;
				}
			}
		} while ( !dataValida && proceed);
	}

	cout << endl;
	if (proceed)
		lerString(pais, 2, proceed);

	if (proceed)
		do
		{
			cout << endl;
			cout << "(*)Morada: ";
			getline(cin,morada);

			if ( !testProceed(morada,proceed) )
				break;

			if (isNumber(morada))
			{
				cout << "Morada invalida. Tente outra vez ";
				pressEnter();
			}
		} while (isNumber(morada) );

	cout << endl;
	if (proceed)
		lerString(cidade,3, proceed);

	cout << endl;
	if (proceed)
	{
		cout << "(*)Codigo-Postal: ";
		getline(cin,postal);

		testProceed(postal,proceed);
	}

	cout << endl;
	if (proceed)
		lerNumero(phone, proceed, 1);

	if(proceed)
		do
		{
			cout << endl;
			cout << "(*)e-mail: ";
			getline(cin, email);

			if ( !testProceed(email, proceed))
				break;

			if (!validMail(email))
			{
				cout << "Email invalido. Tente outra vez. ";
				pressEnter();
				cout << endl;
			}

		} while(!validMail(email));


	if (proceed)
	{
		contacto = new Contato(pais, morada, cidade, postal, phone, email);
		lerNumero(BI, proceed, 2);
	}

	if (proceed)
		lerNumero(NIF, proceed, 4);

	if (proceed)
	{
		try
		{
			novoClie = new Cliente(nome, BI , nascimento , contacto , NIF);
		}
		catch(menorIdade& mI)
		{
			cout << mI.getNome() << " nao pode ser adicionado por ser menor de idade. ";
			pressEnter();
			proceed = false;
		}
	}
	if (proceed)
	{
		try
		{
			a.addCliente(novoClie);
			cout << "Cliente " << novoClie->getNome() << " adicionado com sucesso com o ID: " << novoClie->getID() << ". ";
			return true;
		}
		catch(jaExiste& j)
		{
			delete novoClie; // nao foi acrescentado a agencia, logo nao ia ser apagado
			Cliente::anularCliente(); // decrementa o numero dos clientes

			if ( j.getRazao() == 1)
				cout << "O BI escolhido ja esta a ser utilizado pelo cliente com o ID: " << j.getID() << '.' << endl;
			else
				cout << "O NIF escolhido ja esta a ser utilizado pelo cliente com o ID: " << j.getID() << '.' << endl;
			cout << "Tente outra vez ou remova o cliente em questao. ";
			pressEnter();
		}
	}
	return false;
}

Cliente* searchCliente(Agencia& a, bool& proceed, bool& didSearch, bool atividade)
{
	Cliente* nulo = NULL;
	vector<Cliente*> resultados;
	searchIt(a, resultados, proceed, 2, didSearch);

	if (!didSearch)
		proceed = false;

	if (!resultados.empty())
	{
		vector<Cliente*>::iterator it = resultados.begin();
		while(it != resultados.end())
		{
			if (atividade != (*it)->getAtivo())
			{
				it = resultados.erase(it);
			}
			else
				it++;
		}

		if(resultados.empty())
			return nulo;

		unsigned int ID;
		if (resultados.size() == 1)
		{
			ID = resultados.at(0)->getID();
			return a.getClienteByID(ID);
		}

		if(atividade)
			a.showClientes(resultados);
		else
			a.showClientesInativos(resultados);

		if ( resultados.size() <= 52)
		{
			gotoxy(10,62); pressEnter();
		}
		bool foundIt;

		do
		{
			clearScreen();
			foundIt = false;
			lerNumero(ID,proceed, 5);
			if (proceed)
			{
				clearScreen();
				for (unsigned int i = 0; i < resultados.size(); i++)
					if ( ID == resultados.at(i)->getID() ) // se o cliente com o ID escolhido faz parte dos resultados
						foundIt = true;
				if (!foundIt)
				{
					cout << "O cliente com ID " << ID << " nao faz parte dos encontrados pela pesquisa. Tente outra vez. ";
					pressEnter();
				}
			}
		} while (!foundIt && proceed);

		if (proceed)
			return a.getClienteByID(ID);
	}
	return nulo;
}

void ModifyRemoveCliente(Agencia& a, bool& proceed, unsigned int mr)
{
	int estado = 0, input;
	do {
		clearScreen();
		do {
			int x = 69, y = 28;

			gotoxy(77,2);
			if (mr == 1)
				cout << "*** MODIFICAR";
			else
				cout << "*** REMOVER";
			cout << " CLIENTE ***";

			y = (y+4*estado);

			displayMenuPlusArrows(x,44,y,7,input,estado,4);

		} while ( input != ENTER && input != ESC );

		switch(estado)
		{
		case 0: // mostrar todos os clientes
		{
			if (a.getNumClientes() != 0)
			{
				unsigned int ID;
				bool validID;
				Cliente* c;
				a.showClientes(a.getClientes());
				if ( a.getNumClientes() <= 52 )
				{
					gotoxy(10,62); pressEnter();
				}
				clearScreen();
				do
				{
					validID = true;
					lerNumero(ID,proceed, 5);
					if (proceed)
					{
						try
						{
							c = a.getClienteByID(ID);
						}
						catch (NaoExiste& f)
						{
							cout << "O cliente com ID " << f.getID() << " nao existe. Tente outra vez. ";
							pressEnter();
							cout << endl;
							validID = false;
						}
						if(validID && !c->getAtivo())
						{
							cout << "O cliente com ID " << c->getID() <<" esta inativo. Utilize a area de clientes inativos. ";
							pressEnter();
							cout << endl;
							validID = false;
						}
					}
				} while (!validID);
				if(proceed)
					if (mr == 1)
						modify(a, c, proceed);
					else
					{
						if (c->hasAluguerAtrasados())
						{
							cout << "O cliente com ID " << c->getID() <<" nao pode ser removido pois ainda tem alugueres em atraso. Tente outra vez. ";
							pressEnter();
						}
						else
							a.removeCliente(c);
					}
			}
			else
			{
				gotoxy(58,45); cout << "Nao ha clientes registados na agencia. ";
				pressEnter();
			}
			break;
		}
		case 1: // pesquisar um cliente
		{
			if (a.getNumClientes() != 0)
			{
				bool didSearch = false;
				Cliente* c = searchCliente(a, proceed, didSearch, true);
				if (c != NULL)
					if (mr == 1)
						modify(a, c, proceed);
					else
					{
						if (c->hasAluguerAtrasados())
						{
							cout << "O cliente com ID " << c->getID() <<" nao pode ser removido pois ainda tem alugueres em atraso. Tente outra vez. ";
							pressEnter();
						}
						else
							a.removeCliente(c);
					}
				else if (didSearch && proceed)
				{
					cout << "Nao foram encontrados resultados. ";
					pressEnter();
				}
			}
			else
			{
				gotoxy(58,45); cout << "Nao ha clientes registados na agencia. ";
				pressEnter();
			}
		}
		break;
		case 2: // introduzir ID do cliente
		{
			if (a.getNumClientes() != 0)
			{
				unsigned int ID;
				bool validID;
				Cliente* c;
				do
				{
					clearScreen();
					validID = true;
					lerNumero(ID,proceed, 5);
					if (proceed)
					{
						try
						{
							c = a.getClienteByID(ID);
						}
						catch (NaoExiste& f)
						{
							cout << "O cliente com ID " << f.getID() << " nao existe. Tente outra vez. ";
							pressEnter();
							validID = false;
						}
						if(validID && !c->getAtivo())
						{
							cout << "O cliente com ID " << c->getID() <<" esta inativo. Utilize a area de clientes inativos. ";
							pressEnter();
							cout << endl;
							validID = false;
						}
					}
				} while (!validID);

				if (proceed)
					if (mr == 1)
						modify(a,c,proceed);
					else
					{
						if (c->hasAluguerAtrasados())
						{
							cout << "O cliente com ID " << c->getID() <<" nao pode ser removido pois ainda tem alugueres em atraso. Tente outra vez. ";
							pressEnter();
						}
						else
							a.removeCliente(c);
					}
			}
			else
			{
				gotoxy(58,45); cout << "Nao ha clientes registados na agencia. ";
				pressEnter();
			}

		}
		break;
		}
	} while (estado != 3);
}

void reativarCliente(Agencia& a, bool& proceed)
{
	int estado = 0, input;

	do {
		clearScreen();
		do {
			int x = 69, y = 28; // coordenadas para as setas iniciais

			gotoxy(73,2);
			cout << "*** REATIVAR CLIENTE INATIVO ***";

			y = (y+4*estado); // calculo de coordenada y de acordo com o estado atual

			displayMenuPlusArrows(x,44,y,7,input,estado,4); // mostrar menus e setas na posicao certa

		} while ( input != ENTER && input != ESC );

		switch(estado)
		{
		case 0: // mostrar todos os clientes inativos
			{
				if (a.hasClientesInativos())
				{
					unsigned int ID;
					bool validID;
					Cliente* c;
					a.showClientesInativos(a.getTabelaInativos().getClientesInativos());
					if ( a.getTabelaInativos().getNumInativos() <= 52 )
					{
						gotoxy(10,62); pressEnter();
					}
					clearScreen();
					do
					{
						validID = true;
						lerNumero(ID,proceed, 5);
						if (proceed)
						{
							try
							{
								c = a.getClienteByID(ID);
							}
							catch (NaoExiste& f)
							{
								cout << "O cliente com ID " << f.getID() << " nao existe. Tente outra vez. ";
								pressEnter();
								cout << endl;
								validID = false;
							}
							if(validID && c->getAtivo())
							{
								cout << "O cliente com ID " << c->getID() << " nao esta inativo. Tente outra vez. ";
								pressEnter();
								cout << endl;
								validID = false;
							}
						}
					} while (!validID);
					if(proceed)
					{
						a.reactivarCliente(c);
						c->setAtivo(true);
						c->setUltimoAluguer(new Data(returnDataActual().getDia(),returnDataActual().getMes(),returnDataActual().getAno()));
						a.saveAgencia(1);
					}

				}
				else
				{
					gotoxy(58,45); cout << "Nao ha clientes inativos na agencia. ";
					pressEnter();
				}
				break;
			}
		case 1: // pesquisar um cliente inativo
			{
				if (a.hasClientesInativos())
				{
					bool didSearch = false;
					Cliente* c = searchCliente(a, proceed, didSearch, false);
					if (c != NULL)
					{
						a.reactivarCliente(c);
						c->setAtivo(true);
						c->setUltimoAluguer(new Data(returnDataActual().getDia(),returnDataActual().getMes(),returnDataActual().getAno()));
						a.saveAgencia(1);
					}
					else if (didSearch && proceed)
					{
						cout << "Nao foram encontrados resultados. ";
						pressEnter();
					}
				}
				else
				{
					gotoxy(58,45); cout << "Nao ha clientes inativos na agencia. ";
					pressEnter();
				}
			}
			break;
		case 2: // introduzir ID do cliente
			{
				if (a.hasClientesInativos())
				{
					unsigned int ID;
					bool validID;
					Cliente* c;
					do
					{
						clearScreen();
						validID = true;
						lerNumero(ID,proceed, 5);
						if (proceed)
						{
							try
							{
								c = a.getClienteByID(ID);
							}
							catch (NaoExiste& f)
							{
								cout << "O cliente com ID " << f.getID() << " nao existe. Tente outra vez. ";
								pressEnter();
								validID = false;
							}
							if(validID && c->getAtivo())
							{
								cout << "O cliente com ID " << c->getID() << " nao esta inativo. Tente outra vez. ";
								pressEnter();
								cout << endl;
								validID = false;
							}
						}
					} while (!validID);

					if (proceed)
					{
						a.reactivarCliente(c);
						c->setAtivo(true);
						c->setUltimoAluguer(new Data(returnDataActual().getDia(),returnDataActual().getMes(),returnDataActual().getAno()));
						a.saveAgencia(1);
					}
				}
				else
				{
					gotoxy(58,45); cout << "Nao ha clientes inativos na agencia. ";
					pressEnter();
				}

			}
			break;
		}
	} while (estado != 3);
}

void ModifyRemoveClienteInativo(Agencia& a, bool& proceed, unsigned int mr)
{
	int estado = 0, input;

	do {
		clearScreen();
		do {
			int x = 69, y = 28; // coordenadas para as setas iniciais

			gotoxy(73,2);
			if (mr == 1)
				cout << "*** MODIFICAR";
			else
				cout << "*** REMOVER";
			cout << " CLIENTE INATIVO ***";

			y = (y+4*estado); // calculo de coordenada y de acordo com o estado atual

			displayMenuPlusArrows(x,44,y,7,input,estado,4); // mostrar menus e setas na posicao certa


		} while ( input != ENTER && input != ESC );

		switch(estado)
		{
		case 0: // mostrar todos os clientes inativos
			{
				if (a.hasClientesInativos())
				{
					unsigned int ID;
					bool validID;
					Cliente* c;

					a.showClientesInativos(a.getTabelaInativos().getClientesInativos());
					if ( a.getTabelaInativos().getNumInativos() <= 52 )
					{
						gotoxy(10,62); pressEnter();
					}
					clearScreen();
					do
					{
						validID = true;
						lerNumero(ID,proceed, 5);
						if (proceed)
						{
							try
							{
								c = a.getClienteByID(ID);
							}
							catch (NaoExiste& f)
							{
								cout << "O cliente com ID " << f.getID() << " nao existe. Tente outra vez. ";
								pressEnter();
								cout << endl;
								validID = false;
							}
							if(validID && c->getAtivo())
							{
								cout << "O cliente com ID " << c->getID() << " nao esta inativo. Tente outra vez. ";
								pressEnter();
								cout << endl;
								validID = false;
							}
						}
					} while (!validID);
					if(proceed)
						if (mr == 1)
							modify(a, c, proceed);
						else
							a.removeClienteInativo(c);

				}
				else
				{
					gotoxy(58,45); cout << "Nao ha clientes inativos na agencia. ";
					pressEnter();
				}
				break;
			}
		case 1: // pesquisar um cliente inativo
			{
				if (a.hasClientesInativos())
				{
					bool didSearch = false;
					Cliente* c = searchCliente(a, proceed, didSearch, false);
					if (c != NULL)
						if (mr == 1)
							modify(a, c, proceed);
						else
							a.removeClienteInativo(c);
					else if (didSearch && proceed)
					{
						cout << "Nao foram encontrados resultados. ";
						pressEnter();
					}
				}
				else
				{
					gotoxy(58,45); cout << "Nao ha clientes inativos na agencia. ";
					pressEnter();
				}
			}
			break;
		case 2: // introduzir ID do cliente
			{
				if (a.hasClientesInativos())
				{
					unsigned int ID;
					bool validID;
					Cliente* c;
					do
					{
						clearScreen();
						validID = true;
						lerNumero(ID,proceed, 5);
						if (proceed)
						{
							try
							{
								c = a.getClienteByID(ID);
							}
							catch (NaoExiste& f)
							{
								cout << "O cliente com ID " << f.getID() << " nao existe. Tente outra vez. ";
								pressEnter();
								validID = false;
							}
							if(validID && c->getAtivo())
							{
								cout << "O cliente com ID " << c->getID() << " nao esta inativo. Tente outra vez. ";
								pressEnter();
								cout << endl;
								validID = false;
							}
						}
					} while (!validID);

					if (proceed)
						if (mr == 1)
							modify(a,c,proceed);
						else
							a.removeClienteInativo(c);
				}
				else
				{
					gotoxy(58,45); cout << "Nao ha clientes inativos na agencia. ";
					pressEnter();
				}

			}
			break;
		}
	} while (estado != 3);
}



/* ********************************************************
 *
 * AREA DE VIATURAS
 *
 * ********************************************************
 */

bool addNovaViatura(Agencia& a, int opt)
{
	string marca, modelo, matricula, transmissao, categoria, combustivel;
	Data* registo;
	unsigned int precoPorDia, lugares, cv, cilindrada;
	string ar_str;
	bool ar_condicionado;
	bool proceed = true;
	string option = "null";
	int op = -1;

	cout << endl;
	lerString(marca, 4, proceed);

	if (proceed)
	{
		cout << endl;
		cout << "(*)Modelo: ";
		getline(cin,modelo);
		testProceed(modelo,proceed);
	}
	if(proceed)
		do
		{
			cout << endl;
			cout << "A matricula deve ser inserida no formato XX-XX-XX\n";
			cout << "(*)Matricula: ";
			getline(cin, matricula);

			if ( !testProceed(matricula, proceed))
				break;

			if (!validMatricula(matricula))
			{
				cout << "Matricula invalida. Tente outra vez. ";
				pressEnter();
				cout << endl;
			}

		} while(!validMatricula(matricula));

	cout << endl;
	if (proceed)
		lerString(transmissao,5, proceed);

	cout << endl;
	if (proceed)
		lerString(combustivel,6, proceed);

	cout << endl;
	if (proceed)
	{
		int dia = 0, mes = 0, ano = 0;
		bool dataValida = true;

		do
		{
			cout << "Data de registo\n";
			lerData(dia,mes,ano,proceed);

			if (proceed)
			{
				try
				{
					registo = new Data(dia,mes,ano);
					dataValida = true;
				}
				catch (DataInvalida &e)
				{
					cout << "Data Invalida. Tente outra vez. ";
					pressEnter();
					cout << endl;
					dataValida = false;
				}
			}
		} while ( !dataValida && proceed);
	}

	cout << endl;
	if (proceed)
		lerNumero(precoPorDia, proceed, 6);

	cout << endl;
	if (proceed)
		lerNumero(lugares, proceed, 7);

	cout << endl;
	if (proceed)
		lerNumero(cv, proceed, 8);

	cout << endl;
	if (proceed)
		lerNumero(cilindrada, proceed, 9);

	cout << endl;
	if (proceed)
	{
		cout << "Ar condicionado\n";
		cout << "1 - Sim\n";
		cout << "2 - Nao\n";
		do
		{
			cout << endl;
			cout << "(*)Opcao: ";
			getline (cin, ar_str);

			if (!testProceed(ar_str, proceed))
				break;

		} while (!validateOption (ar_str,atoi(ar_str.c_str()),2, 0, 0));

		int ar_ = atoi(ar_str.c_str());
		if(ar_ == 1)
			ar_condicionado = true;
		else if(ar_ == 2)
			ar_condicionado = false;
	}


	if (proceed)
	{
		allUpperCase(matricula);
		Viatura* v = NULL;

		try
		{
			v = new Viatura(marca,modelo,matricula,transmissao,combustivel,registo,precoPorDia,lugares,cv,cilindrada,ar_condicionado);

			if (opt == 1)
			{
				a.addViatura(v);
				cout << "\nViatura " << v->getMarca() << " " << v->getModelo() << " adicionada com sucesso com o ID: " << v->getID() << ". ";
			}
			else if (opt == 2)
			{
				a.addViaturaCatalogo(v);
				cout << "\nViatura " << v->getMarca() << " " << v->getModelo() << " adicionada com sucesso ao catalogo. ";
			}
			return true;
		}
		catch(jaExiste& j)
		{
			delete v;

			Viatura::anularViatura();
			cout << "A matricula escolhida ja esta a ser utilizada pela viatura com o ID: " << j.getID() << '.' << endl;
			cout << "Tente outra vez ou remova a viatura em questao.";
			pressEnter();
		}
		catch(DataInvalida& i)
		{
			Viatura::anularViatura();
			cout << "A viatura nao foi registada pois tem uma data de registo invalida. Tente outra vez. ";
			pressEnter();
		}
	}
	return false;
}

Viatura* searchViatura(Agencia& a, bool& proceed, int opt, bool& didSearch) // opt = 1 pesquisa em vector / opt = 2 pesquisa em BST
{
	Viatura* nula = NULL;
	vector<Viatura*> resultados;
	string option = "null";
	int op = -1;
	pesquisaViatura novaPesquisa;
	nulificarViatura(novaPesquisa);

	do
	{
		clearScreen();
		string str = "null";
		cout << "--------------------------------------------------------------------\n";
		cout << "Escolha o que deseja pesquisa\n";
		cout << "Nota: Quantos mais criterios utilizar, mais precisa sera a pesquisa.\n";
		cout << "--------------------------------------------------------------------\n";
		cout << "\n1 - Marca\n";
		cout << "\n2 - Modelo\n";
		cout << "\n3 - Matricula\n";
		cout << "\n4 - Transmissao\n";
		cout << "\n5 - Combustivel\n";
		cout << "\n6 - Ano\n";
		cout << "\n7 - Numero de vezes alugado\n";
		cout << "\n8 - Preco diario\n";
		cout << "\n9 - Potencia(cv)\n";
		cout << "\n10 - Cilindrada\n\n";
		cout << "--------------------------------------------------------------------\n";
		cout<<  "0 - Apresentar resultados ou voltar ao menu anterior\n";
		do
		{
			cout << endl;
			readOption(option, op);
		} while (!validateOption(option, op, 10, 0, 0));

		clearScreen();
		switch (op)
		{
		case 0 : //calcula os resultados
        {
			if(numCriteriosViatura(novaPesquisa) != 0)
			{
				if (opt == 1)
					a.pesquisarViatura(resultados, novaPesquisa);
				else
					a.pesquisarCatalogo(resultados, novaPesquisa);
			}
			else
				proceed = false;
        }
		break;
		case 1: // altera a marca a pesquisar
		{
			lerString(str, 4, proceed);
			if (proceed)
			{
				novaPesquisa.marca = str;
				cout << "Criterio actualizado com sucesso. ";
				pressEnter();
				didSearch = true;
			}
		}
		break;
		case 2: // altera o modelo a pesquisar
		{
			cout << "(*)Modelo: ";
			getline(cin,str);
			testProceed(str,proceed);
			if (proceed)
			{
				novaPesquisa.modelo = str;
				cout << "Criterio actualizado com sucesso. ";
				pressEnter();
				didSearch = true;
			}
		}
		break;
		case 3: // altera a matricula a pesquisar (deixa pesquisar sem colocar uma matricula inteira)
		{
			cout << "(*)Matricula: ";
			getline(cin,str);
			testProceed(str,proceed);
			if (proceed)
			{
				novaPesquisa.matricula = str;
				cout << "Criterio actualizado com sucesso. ";
				pressEnter();
				didSearch = true;
			}
		}
		break;
		case 4: // altera a transmissao a pesquisar
		{
			lerString(str, 5, proceed);
			if (proceed)
			{
				novaPesquisa.transmissao = str;
				cout << "Criterio actualizado com sucesso. ";
				pressEnter();
				didSearch = true;
			}
		}
		break;
		case 5: // altera o combustivel
		{
			lerString(str, 6, proceed);
			if (proceed)
			{
				novaPesquisa.combustivel = str;
				cout << "Criterio actualizado com sucesso. ";
				pressEnter();
				didSearch = true;
			}
		}
		break;
		case 6: // altera o ano
		{
			string option = "null";
			int op = -1;
			int num;
			cout << "----------------------------\n";
			cout << "             ANO\n";
			cout << "----------------------------\n";
			cout << "\n1 - Posterior a ...\n";
			cout << "\n2 - Anterior a ...\n\n";
			cout << "----------------------------\n";
			cout<<  "0 - VOLTAR AO MENU ANTERIOR\n";
			do
			{
				cout << endl;
				readOption(option, op);

			} while ( !validateOption(option, op, 2, 0, 0) );

			clearScreen();
			switch(op)
			{
			case 0:
				break;
			case 1:
			{
				lerNumero(num,proceed,13);
				if (proceed)
				{
					novaPesquisa.ano = num+1;
					novaPesquisa.anoOp = 1;
					cout << "Criterio actualizado com sucesso. ";
					pressEnter();
					didSearch = true;
				}
				break;
			}
			case 2:
			{
				lerNumero(num,proceed,13);
				if (proceed)
				{
					novaPesquisa.ano = num-1;
					novaPesquisa.anoOp = 2;
					cout << "Criterio actualizado com sucesso. ";
					pressEnter();
					didSearch = true;
				}
				break;
			}
			}
		}
		break;
		case 7: // altera o numero de vezes que foi alugado
		{
			string option = "null";
			int op = -1;
			int num;
			cout << "----------------------------\n";
			cout << "    NUMERO VEZES ALUGADO\n";
			cout << "----------------------------\n";
			cout << "\n1 - Mais de ... vezes\n";
			cout << "\n2 - Menos de ... vezes\n\n";
			cout << "----------------------------\n";
			cout<<  "0 - VOLTAR AO MENU ANTERIOR\n";
			do
			{
				cout << endl;
				readOption(option, op);

			} while ( !validateOption(option, op, 2, 0, 0) );

			clearScreen();
			switch (op)
			{
			case 1: // Mais de x vezes
			{
				lerNumero(num,proceed,14);
				if (proceed)
				{
					novaPesquisa.nXalugado = num+1;
					novaPesquisa.nXalugadoOp = 1; // queremos maior que num
					cout << "Criterio actualizado com sucesso. ";
					pressEnter();
					didSearch = true;
				}
			}
			break;
			case 2:
			{
				lerNumero(num,proceed,14);
				if (proceed)
				{
					novaPesquisa.nXalugado = num-1;
					novaPesquisa.nXalugadoOp = 2; // queremos menor que num
					cout << "Criterio actualizado com sucesso. ";
					pressEnter();
					didSearch = true;
				}
			}
			break;
			}
		}
		break;
		case 8: // alterar o preco diario
		{
			string option = "null";
			int op = -1;
			int num;
			cout << "-----------------------------\n";
			cout << "     PRECO DIARIO - EUROS\n";
			cout << "-----------------------------\n";
			cout << "\n1 - Mais de ... euros\n";
			cout << "\n2 - Menos de ... euros\n";
			cout << "\n3 - Entre ... e ... euros\n\n";
			cout << "-----------------------------\n";
			cout<<  "0 - VOLTAR AO MENU ANTERIOR\n";
			do
			{
				cout << endl;
				readOption(option, op);

			} while ( !validateOption(option, op, 3, 0, 0) );

			clearScreen();
			switch (op)
			{
			case 1: // Mais de x euros
			{
				lerNumero(num,proceed,6);
				if (proceed)
				{
					novaPesquisa.precoPorDia_inf = num+1;
					cout << "Criterio actualizado com sucesso. ";
					pressEnter();
					didSearch = true;
				}
			}
			break;
			case 2:
			{
				lerNumero(num,proceed,6);
				if (proceed)
				{
					novaPesquisa.precoPorDia_inf = 0;
					novaPesquisa.precoPorDia_sup = num-1;
					cout << "Criterio actualizado com sucesso. ";
					pressEnter();
					didSearch = true;
				}
			}
			break;
			case 3:
			{
				int x,y,tmp;
				lerNumero(x,proceed,11);
				if (proceed)
				{
					lerNumero(y,proceed,12);
					if(proceed)
					{
						if (x > y)
						{
							tmp = x;
							x = y;
							y = tmp;
						}
						novaPesquisa.precoPorDia_inf = x;
						novaPesquisa.precoPorDia_sup = y;
						cout << "Criterio actualizado com sucesso. ";
						pressEnter();
						didSearch = true;
					}
				}
			}
			break;
			}
		}
		break;
		case 9: // alterar a potencia(cv)
		{
			string option = "null";
			int op = -1;
			int num;
			cout << "----------------------------\n";
			cout << "       POTENCIA (cv)\n";
			cout << "----------------------------\n";
			cout << "\n1 - Mais de ... CV\n";
			cout << "\n2 - Menos de ... CV\n\n";
			cout << "----------------------------\n";
			cout<<  "0 - VOLTAR AO MENU ANTERIOR\n";
			do
			{
				cout << endl;
				readOption(option, op);

			} while ( !validateOption(option, op, 2, 0, 0) );

			clearScreen();
			switch (op)
			{
			case 1: // Mais de x vezes
			{
				lerNumero(num,proceed,8);
				if (proceed)
				{
					novaPesquisa.cv = num+1;
					novaPesquisa.cvOp = 1; // queremos maior que num
					cout << "Criterio actualizado com sucesso. ";
					pressEnter();
					didSearch = true;
				}
			}
			break;
			case 2:
			{
				lerNumero(num,proceed,8);
				if (proceed)
				{
					novaPesquisa.cv = num-1;
					novaPesquisa.cvOp = 2; // queremos menor que num
					cout << "Criterio actualizado com sucesso. ";
					pressEnter();
					didSearch = true;
				}
			}
			break;
			}
		}
		break;
		case 10: // alterar a cilindrada
		{
			string option = "null";
			int op = -1;
			int num;
			cout << "----------------------------\n";
			cout << "       CILINDRADA (cc)\n";
			cout << "----------------------------\n";
			cout << "\n1 - Mais de ... cc\n";
			cout << "\n2 - Menos de ...cc\n\n";
			cout << "----------------------------\n";
			cout<<  "0 - VOLTAR AO MENU ANTERIOR\n";
			do
			{
				cout << endl;
				readOption(option, op);

			} while ( !validateOption(option, op, 2, 0, 0) );

			clearScreen();
			switch (op)
			{
			case 1: // Mais de x vezes
			{
				lerNumero(num,proceed,14);
				if (proceed)
				{
					novaPesquisa.cilindrada = num+1;
					novaPesquisa.cilindradaOp = 1; // queremos maior que num
					cout << "Criterio actualizado com sucesso. ";
					pressEnter();
					didSearch = true;
				}
			}
			break;
			case 2:
			{
				lerNumero(num,proceed,14);
				if (proceed)
				{
					novaPesquisa.cilindrada = num-1;
					novaPesquisa.cilindradaOp = 2; // queremos menor que num
					cout << "Criterio actualizado com sucesso. ";
					pressEnter();
					didSearch = true;
				}
			}
			break;
			}
		}
		break;
        }
	} while (op != 0);

	if (!resultados.empty())
	{
		unsigned int ID;
		if (resultados.size() == 1)
			return resultados.at(0);

		a.showViaturas(resultados);
		if ( resultados.size() <= 52)
		{
			gotoxy(10,62); pressEnter();
		}
		bool foundIt;

		do {
			clearScreen();
			foundIt = false;
			lerNumero(ID,proceed, 5);
			if (proceed)
			{
				for (size_t i = 0; i < resultados.size(); i++)
					if ( ID == resultados.at(i)->getID() ) // se a viatura com o ID escolhido faz parte dos resultados
						foundIt = true;
				if (!foundIt)
				{
					cout << "A viatura com ID " << ID << " nao faz parte dos resultados da pesquisa. Tente outra vez. ";
					pressEnter();
				}
			}
		} while (!foundIt && proceed);

		if (proceed)
			if (opt == 1)
				return a.getViaturaByID(ID);
			else
				for (size_t i = 0; i < resultados.size(); i++)
					if ( ID == resultados.at(i)->getID() )
						return resultados.at(i);
	}
    
	return nula;
}

void ModifyRemoveViatura(Agencia& a, bool& proceed, unsigned int mr)
{
	int estado = 0, input;
	do {
		clearScreen();
		do {
			int x = 69, y = 28;

			gotoxy(77,2);
			if (mr == 1 || mr == 3)
				cout << "*** MODIFICAR";
			else if (mr == 2 || mr == 4)
				cout << "*** REMOVER";
			else
				cout << "*** COMPRAR";
			cout << " VIATURA ***";

			y = (y+4*estado);

			displayMenuPlusArrows(x,44,y,8,input,estado,4);
		} while ( input != ENTER && input != ESC );

		switch(estado)
		{
		case 0: // mostrar todas as viaturas
		{
			if (a.getNumViaturas() != 0 || !a.catalogoEmpty())
			{
				unsigned int ID;
				bool validID;
				Viatura* v;
				if (mr == 1 || mr == 2)
				{
					a.showViaturas(a.getViaturas());
					if ( a.getNumViaturas() <= 52 )
					{
						gotoxy(10,62); pressEnter();
					}
					clearScreen();
				}
				else if (mr == 3 || mr == 4 || mr == 5)
				{
					clearScreen();
					a.showCatalogo();
					cout << endl;
				}

				do
				{
					validID = true;
					lerNumero(ID,proceed, 5);
					if (proceed)
					{
						if ( mr == 1 || mr == 2 )
						{
							try
							{
								v = a.getViaturaByID(ID);
							}
							catch (NaoExiste& f)
							{
								cout << "A viatura com ID " << f.getID() << " nao existe. Tente outra vez. ";
								pressEnter();
								cout << endl;
								validID = false;
							}
						}
						else
						{
							v = new Viatura();
							(*v).setID(ID);
							BSTItrIn<Viatura> it(a.getCatalogo());

							for (; !it.isAtEnd(); it.advance())
								if (it.retrieve().getID() == ID)
								{
									(*v) = it.retrieve();
									v->setMarca(it.retrieve().getMarca());
									v->setModelo(it.retrieve().getModelo());
									v->setMatricula(it.retrieve().getMatricula());
									v->setTransmissao(it.retrieve().getTransmissao());
									v->setCombustivel(it.retrieve().getCombustivel());
									v->setRegisto(new Data(*it.retrieve().getRegisto()));
								}

							if (v->getRegisto() == NULL) // nao encontrou a viatura no catalogo
							{
								cout << "A viatura com ID " << ID << " nao existe. Tente outra vez. ";
								pressEnter();
								cout << endl;
								validID = false;
							}
						}
					}
				} while (!validID);

				if(proceed)
					if (mr == 1) // modifica viatura da agencia
						modifyViatura(a, v, proceed);
					else if (mr == 2) // remove viatura da agencia
					{
						if (v->getDisponivel() == false) 
						{
							cout << "A viatura com ID " << ID << " nao pode ser eliminada pois nao esta disponivel. Tente outra vez. ";
							cout << endl;
							pressEnter();
						}
						else
							a.removeViatura(v);
					}
					else if (mr == 3) // modifica viatura do catalogo
						modifyViatura(a, v, proceed);
					else if (mr == 4) // remove viatura do catalogo
						a.getCatalogo().remove(*v);
					else // compra viatura
					{
						try
						{
							a.addViatura(v);
							a.getCatalogo().remove(*v);
							a.saveAgencia(6);
						}
						catch(jaExiste& j)
						{
							delete v;

							Viatura::anularViatura();

							cout << "A matricula escolhida ja esta a ser utilizada pela viatura com o ID: " << j.getID() << '.' << endl;
							cout << "Tente outra vez ou remova a viatura em questao.";

							pressEnter();
						}
					}
			}
			else
			{
				if (mr == 1 || mr == 2)
				{
					gotoxy(58,45); cout << "Nao ha viaturas registadas na agencia. ";
				}
				else
				{
					gotoxy(58,45); cout << "Nao ha viaturas disponiveis no catalogo. ";
				}
				pressEnter();
			}
			break;
		}
		case 1: // pesquisar viatura
		{
			if (a.getNumViaturas() != 0 || !a.catalogoEmpty())
			{
				bool didSearch = false;
				Viatura* v;
				Viatura* v1 = new Viatura();

				if (mr == 1 || mr == 2)
					v = searchViatura(a, proceed,1,didSearch);
				else
				{
					v = searchViatura(a,proceed,2,didSearch);
					if (proceed && didSearch)
					{
						(*v1) = (*v);
						v1->setMarca(v->getMarca());
						v1->setModelo(v->getModelo());
						v1->setMatricula(v->getMatricula());
						v1->setTransmissao(v->getTransmissao());
						v1->setCombustivel(v->getCombustivel());
						v1->setRegisto(new Data(*(v->getRegisto())));
					}
				}

				if (v != NULL)
					if (mr == 1)
						modifyViatura(a, v, proceed);
					else if (mr == 2)
					{
						if (v->getDisponivel() == false) 
						{
							cout << "A viatura com ID " << v->getID() << " nao pode ser eliminada pois nao esta disponivel. Tente outra vez. ";
							cout << endl;
							pressEnter();
						}
						else
						{
							v->showInfo();
							cout << "\n";
							pressEnter();
							a.removeViatura(v);
						}
					}
					else if (mr == 3)
						modifyViatura(a,v,proceed);
					else if (mr == 4)
					{
						v->showInfo();
						cout << "\n";
						pressEnter();
						a.getCatalogo().remove(*v);
						a.saveAgencia(6);
					}
					else // compra viatura
					{
						try
						{
							a.addViatura(v1);
							a.getCatalogo().remove(*v);
							a.saveAgencia(6);
						}
						catch(jaExiste& j)
						{
							delete v;

							Viatura::anularViatura();

							cout << "A matricula escolhida ja esta a ser utilizada pela viatura com o ID: " << j.getID() << '.' << endl;
							cout << "Tente outra vez ou remova a viatura em questao.";

							pressEnter();
						}
					}
				else if (didSearch && proceed)
				{
					cout << "Nao foram encontrados resultados. ";
					pressEnter();
				}

			}
			else
			{
				if (mr == 1 || mr == 2)
				{
					gotoxy(58,45); cout << "Nao ha viaturas registadas na agencia. ";
				}
				else
				{
					gotoxy(58,45); cout << "Nao ha viaturas disponiveis no catalogo. ";
				}
				pressEnter();
			}
			break;
		}
		case 2: // introduzir ID da viatura
		{
			if ( a.getNumViaturas() != 0 || !a.catalogoEmpty() )
			{
				unsigned int ID;
				bool validID;
				Viatura* v;
				do
				{
					clearScreen();
					validID = true;
					lerNumero(ID,proceed, 5);
					if (proceed)
					{
						if ( mr == 1 || mr == 2 )
						{
							try
							{
								v = a.getViaturaByID(ID);
								if (v->getDisponivel() == false && mr == 2) 
								{
									cout << "A viatura com ID " << ID << " nao pode ser eliminada pois nao esta disponivel. Tente outra vez. ";
									cout << endl;
									pressEnter();
									validID = false;
								}
							}
							catch (NaoExiste& f)
							{
								cout << "A viatura com ID " << f.getID() << " nao existe. Tente outra vez. ";
								pressEnter();
								cout << endl;
								validID = false;
							}
						}
						else
						{
							v = new Viatura();
							(*v).setID(ID);
							BSTItrIn<Viatura> it(a.getCatalogo());

							for (; !it.isAtEnd(); it.advance())
								if (it.retrieve().getID() == ID)
								{
									(*v) = it.retrieve();
									v->setMarca(it.retrieve().getMarca());
									v->setModelo(it.retrieve().getModelo());
									v->setMatricula(it.retrieve().getMatricula());
									v->setTransmissao(it.retrieve().getTransmissao());
									v->setCombustivel(it.retrieve().getCombustivel());
									v->setRegisto(new Data(*it.retrieve().getRegisto()));
								}

							if (v->getRegisto() == NULL) // nao encontrou a viatura no catalogo
							{
								cout << "A viatura com ID " << ID << " nao existe. Tente outra vez. ";
								pressEnter();
								cout << endl;
								validID = false;
							}
						}
					}
				} while (!validID);

				if (proceed)
					if (mr == 1)
						modifyViatura(a, v, proceed);
					else if (mr == 2)
					{
						v->showInfo();
						cout << "\n";
						pressEnter();
						a.removeViatura(v);
					}
					else if (mr == 3)
						modifyViatura(a,v,proceed);
					else if (mr == 4)
					{
						v->showInfo();
						cout << "\n";
						pressEnter();
						a.getCatalogo().remove(*v);
						a.saveAgencia(6);
					}
					else // compra viatura
					{
						a.getCatalogo().remove(*v);
						try
						{
							a.addViatura(v);
							a.getCatalogo().remove(*v);
							a.saveAgencia(6);
						}
						catch(jaExiste& j)
						{
							delete v;

							Viatura::anularViatura();

							cout << "A matricula escolhida ja esta a ser utilizada pela viatura com o ID: " << j.getID() << '.' << endl;
							cout << "Tente outra vez ou remova a viatura em questao.";

							pressEnter();
						}
					}
			}
			else
			{
				if (mr == 1 || mr == 2)
				{
					gotoxy(58,45); cout << "Nao ha viaturas registadas na agencia. ";
				}
				else
				{
					gotoxy(58,45); cout << "Nao ha viaturas disponiveis no catalogo. ";
				}
				pressEnter();
			}
			break;
		}
		}
	} while (estado != 3);

}

void modifyViatura(Agencia& a, Viatura* viat, bool& proceed)
{
	string option = "null";
	int op = -1;
	do
	{
		clearScreen();
		string str = "null";
		long num = 0;
		if (proceed) // se ja percorreu o loop e proceed ainda e verdadeiro, mostra os dados actuais
		{
			cout << "Dados atuais:\n";
			viat->showInfo();
			cout << "\n";
			pressEnter();
			cout << "\n\n";
		}

		cout << "-------------------------------\n";
		cout << "Escolha o que deseja modificar\n";
		cout << "-------------------------------\n";
		cout << "\n1 - Marca\n";
		cout << "\n2 - Modelo\n";
		cout << "\n3 - Matricula\n";
		cout << "\n4 - Transmissao\n";
		cout << "\n5 - Combustivel\n";
		cout << "\n6 - Data de registo\n";
		cout << "\n7 - Preco diario\n";
		cout << "\n8 - Lugares\n";
		cout << "\n9 - Cavalos\n";
		cout << "\n10 - Cilindrada\n";
		cout << "\n11 - Ar condicionado\n\n";
		cout << "--------------------------------\n";
		cout<<  "0 - Gravar e voltar ao menu anterior\n";

		do
		{
			cout << endl;
			readOption(option, op);
		} while (!validateOption(option, op, 11, 0, 0));

		clearScreen();
		switch (op)
		{
		case 0: // gravar e voltar atras
			break;
		case 1: // mudar marca
		{
			lerString(str, 4, proceed);
			if (proceed)
			{
				a.changeViatura(viat, str, 1);
				cout << "A marca foi alterada com sucesso para " << str << '.' << endl;
				pressEnter();
			}
		}
		break;
		case 2: //mudar modelo
		{
			cout << "(*)Modelo: ";
			getline(cin,str);
			testProceed(str,proceed);
			if (proceed)
			{
				a.changeViatura(viat, str, 2);
				cout << "Modelo alterado com sucesso para " << str << '.' << endl;
				pressEnter();
			}
		}
		break;
		case 3: //mudar matricula
		{
			do
			{
				cout << "(*)Matricula: ";
				getline(cin, str);

				if ( !testProceed(str, proceed))
					break;

				if (!validMatricula(str))
				{
					cout << "Matricula invalida. Tente outra vez. ";
					pressEnter();
				}

			} while(!validMatricula(str));
			if (proceed)
			{
				try
				{
					a.changeViatura(viat, str, 3);
					cout << "Matricula alterada com sucesso para " << str << '.' << endl;
				}
				catch(jaExiste&j)
				{
					cout << "A matricula escolhida ja esta a ser utilizada pela viatura com o ID: " << j.getID() << '.' << endl;
					cout << "Tente outra vez ou remova a viatura em questao. " << endl;
				}
				pressEnter();
			}
		}
		break;
		case 4: //mudar transmissao
		{
			lerString(str, 5, proceed);
			if (proceed)
			{
				a.changeViatura(viat, str, 4);
				cout << "Transmissao alterada com sucesso para " << str << '.' << endl;
				pressEnter();
			}
		}
		break;
		case 5: //mudar combustivel
		{
			lerString(str, 5, proceed);
			if (proceed)
			{
				a.changeViatura(viat, str, 5);
				cout << "Combustivel alterado com sucesso para " << str << '.' << endl;
				pressEnter();
			}
		}
		break;
		case 6: //mudar data de registo
		{
			int dia = 0, mes = 0, ano = 0;
			bool dataValida = true;
			Data* registo;

			do
			{
				cout << "Data de registo\n";
				lerData(dia,mes,ano,proceed);

				if (proceed)
				{
					try
					{
						registo = new Data(dia,mes,ano);
						dataValida = true;
					}
					catch (DataInvalida &e)
					{
						cout << "Data Invalida. Tente outra vez. ";
						pressEnter();
						dataValida = false;
					}
				}
			} while ( !dataValida && proceed);
			if (proceed)
			{
				viat->setRegisto(registo);
				cout << "A data de registo foi alterada com sucesso para " << *registo << ". ";
				pressEnter();
			}
		}
		break;
		case 7: //mudar preco diario
		{
			lerNumero(num,proceed,6);
			if(proceed)
			{
				str = convertNum(num);
				a.changeViatura(viat, str, 6);
				cout << "Preco diario alterado com sucesso para " << str << "euros." << endl;
				pressEnter();
			}
		}
		break;
		case 8: //mudar lugares
		{
			lerNumero(num,proceed,7);
			if(proceed)
			{
				str = convertNum(num);
				a.changeViatura(viat, str,7);
				cout << "Lugares alterados com sucesso para " << str << '.' << endl;
				pressEnter();
			}
		}
		break;
		case 9: //mudar cv
		{
			lerNumero(num,proceed,8);
			if(proceed)
			{
				str = convertNum(num);
				a.changeViatura(viat, str, 8);
				cout << "Cavalos alterados com sucesso para " << str << '.' << endl;
				pressEnter();
			}
		}
		break;
		case 10: //mudar cilindrada
		{
			lerNumero(num,proceed,9);
			if(proceed)
			{
				str = convertNum(num);
				a.changeViatura(viat, str, 9);
				cout << "Cilindrada alterada com sucesso para " << str << '.' << endl;
				pressEnter();
			}
		}
		break;
		case 11: //mudar ar condicionado
		{
			do
			{
				cout << "(*)Ar condicionado: \n";
				cout << "\n1 - Sim\n";
				cout << "\n2 - Nao\n\n";
				cout << "Opcao: ";
				getline (cin, str);

				if (!testProceed(str, proceed))
					break;

			} while (!validateOption (str,atoi(str.c_str()),2, 0, 0));

			if(proceed)
			{
				a.changeViatura(viat, str, 11);
				cout << "Ar condicionado alterado com sucesso. " << endl;
				pressEnter();
			}


		}
		break;
		}

	} while ( op != 0 );
}

/* ********************************************************
 *
 * AREA DE ALUGUERES
 *
 * ********************************************************
 */

bool addNovoAluguer(Agencia& a)
{
	Data d1 = returnDataActual();
	Data* inicio = new Data(d1.getDia(),d1.getMes(),d1.getAno());
	string option = "null";
	int op = -1;
	bool proceed = true;
	int x = 70;
	int estado = 0, input;

	do
	{
		clearScreen();
		showFrames();
		gotoxy(77,2); cout << "*** NOVO ALUGUER ***";
		gotoxy(x,27); cout << " --------------------------------------";
		gotoxy(x,28); cout << "|  1 - Novo cliente                    |";
		gotoxy(x,29); cout << " --------------------------------------";
		gotoxy(x,31); cout << " --------------------------------------";
		gotoxy(x,32); cout << "|  2 - Cliente ja registado            |";
		gotoxy(x,33); cout << " --------------------------------------";
		gotoxy(x,35); cout << " --------------------------------------";
		gotoxy(x,36); cout << "|  0 - VOLTAR AO MENU ANTERIOR         |";
		gotoxy(x,37); cout << " --------------------------------------";

		clrln(41);
		gotoxy(70,41); readOption(option, op);

	} while (!validateOption(option, op, 2, 58, 41) );

	Cliente* c;

	clearScreen();
	switch (op)
	{
	case 1: // realizar aluguer para um novo cliente
	{
		if (addNovoCliente(a))
		{
			pressEnter();
			unsigned int IDultimoCliente = Cliente::getNumClientes();
			c = a.getClienteByID(IDultimoCliente);
		}
		else
			proceed = false;

	}
		break;
	case 2:
	{
		clearScreen();
		do {
			int x = 69, y = 28;

			gotoxy(77,2); cout << "*** ESCOLHA DO CLIENTE ***";

			y = (y+4*estado);

			displayMenuPlusArrows(x,44,y,7,input,estado,4);

		} while ( input != ENTER && input != ESC );

		clearScreen();

		switch(estado)
		{
		case 0: // mostrar todos os clientes
		{
			unsigned int ID;
			bool validID;
			gotoxy(77,2); cout << "*** ESCOLHA DO CLIENTE ***";
			a.showClientes(a.getClientes());
			if ( a.getNumClientes() <= 52 )
			{
				gotoxy(10,62); pressEnter();
			}
			clearScreen();
			do
			{
				validID = true;
				lerNumero(ID,proceed, 5);
				if (proceed)
				{
					try
					{
						c = a.getClienteByID(ID);
						if (c->hasAluguerAtrasados())
						{
							proceed = false;
							cout << "Esse cliente nao pode efectuar alugueres pois tem alugueres em atraso. ";
							pressEnter();
						}
					}
					catch (NaoExiste& f)
					{
						cout << "O cliente com ID " << f.getID() << " nao existe. Tente outra vez. ";
						pressEnter();
						cout << endl;
						validID = false;
					}
					if(!c->getAtivo() && validID)
					{
						cout << "O cliente com ID " << c->getID() <<" esta inativo. Utilize a area de clientes inativos. ";
						pressEnter();
						cout << endl;
						validID = false;
					}
				}
			} while (!validID);
		}
		break;
		case 1: // pesquisar um cliente
		{
			bool didSearch = false;
			c = searchCliente(a, proceed,didSearch,true);
			if (c == NULL)
			{
				if (didSearch && proceed)
				{
					cout << "Nao foram encontrados resultados. ";
					pressEnter();
				}
			}
			else if (c->hasAluguerAtrasados())
			{
				proceed = false;
				cout << "Esse cliente nao pode efectuar alugueres pois tem alugueres em atraso. ";
				pressEnter();
			}
		}
		break;
		case 2: // introduzir ID do cliente
		{
			unsigned int ID;
			bool validID;
			do
			{
				clearScreen();
				validID = true;
				lerNumero(ID,proceed, 5);
				if (proceed)
				{
					try
					{
						c = a.getClienteByID(ID);
						if (c->hasAluguerAtrasados())
						{
							proceed = false;
							cout << "Esse cliente nao pode efectuar alugueres pois tem alugueres em atraso. ";
							pressEnter();
						}
					}
					catch (NaoExiste& f)
					{
						cout << "O cliente com ID " << f.getID() << " nao existe. Tente outra vez. ";
						pressEnter();
						validID = false;
					}

					if (validID && !c->getAtivo())
					{
						cout << "O cliente com ID " << c->getID() <<" esta inativo. Utilize a area de clientes inativos. ";
						pressEnter();
						validID = false;
					}
				}
			} while (!validID);
		}
		break;
		}
	}
		break;
	}

	if (proceed && estado != 3)
	{
		clearScreen();
		estado = 0;

		do {
			int x = 69, y = 28;

			gotoxy(77,2); cout << "*** ESCOLHA DA VIATURA ***";

			y = (y+4*estado);
			displayMenuPlusArrows(x,44,y,8,input,estado,4);

		} while ( input != ENTER && input != ESC );

		Viatura* v;
		clearScreen();

		switch(estado)
		{
		case 0: // mostrar todos as viaturas disponiveis
		{
			unsigned int ID;
			bool validID;
			a.showViaturasDisponiveis();
			if ( a.getNumViaturasDisponiveis() <= 52 )
			{
				gotoxy(10,62); pressEnter();
			}
			clearScreen();
			do
			{
				validID = true;
				lerNumero(ID,proceed, 5);
				if (proceed)
				{
					try
					{
						v = a.getViaturaByID(ID);
						if (v->getDisponivel() == false) 
						{
							cout << "A viatura com ID " << ID << " nao esta disponivel. Tente outra vez. ";
							pressEnter();
							cout << endl;
							validID = false;
						}
					}
					catch (NaoExiste& f)
					{
						cout << "A viatura com ID " << f.getID() << " nao existe. Tente outra vez. ";
						pressEnter();
						cout << endl;
						validID = false;
					}
				}
			} while (!validID);
		}
		break;
		case 1: // pesquisar uma viatura
		{
			bool didSearch = false;
			v = searchViatura(a, proceed,1,didSearch);

			if (proceed)
				if (v != NULL)
				{
					if (v->getDisponivel())
					{
						v->showInfo();
						pressEnter();
						cout << endl;
					}
					else
					{
						cout << "A viatura com ID " << v->getID() << " nao esta disponivel. Tente outra vez. ";
						pressEnter();
						cout << endl;
						proceed = false;
					}
				}
				else if (didSearch && proceed)
				{
					cout << "Nao foram encontrados resultados. ";
					pressEnter();
				}
		}
		break;
		case 2: // introduzir ID da viatura
		{
			unsigned int ID;
			bool validID;
			do
			{
				clearScreen();
				validID = true;
				lerNumero(ID,proceed, 5);
				if (proceed)
				{
					try
					{
						v = a.getViaturaByID(ID);
						if (v->getDisponivel() == false) 
						{
							cout << "A viatura com ID " << ID << " nao esta disponivel. Tente outra vez. ";
							pressEnter();
							cout << endl;
							validID = false;
						}
					}
					catch (NaoExiste& f)
					{
						cout << "A viatura com ID " << f.getID() << " nao existe. Tente outra vez. ";
						pressEnter();
						cout << endl;
						validID = false;
					}
				}
			} while (!validID);
		}
		break;
		}

		if (proceed && estado != 3) // vai escolher a data de fim
		{
			Data* fim;
			cout << "\nData do fim do aluguer\n";
			bool validData = true;
			int dia, mes, ano;

			do
			{
				lerData(dia,mes,ano,proceed);
				if (proceed)
				{
					try
					{
						fim = new Data(dia,mes,ano);
						validData = true;
					}
					catch (DataInvalida &e)
					{
						cout << "Data Invalida. Tente outra vez. ";
						pressEnter();
						cout << endl;
						validData = false;
					}
				}

			} while (!validData && proceed);

			if (proceed)
			{
				Aluguer* al;

				string option = "null";
				int op = -1;

				if (c->descontoCandidate()) // se cliente ja pode usufruir de desconto
				{
					cout << "Deseja efectuar o aluguer com o desconto de 5%?\n";
					cout << "1 - Sim\n";
					cout << "2 - Nao\n";
					do
					{
						cout << endl;
						readOption(option, op);

					} while ( !validateOption(option, op, 2, 0, 0)  );
				}

				if (op != 0)
				{
					bool validAluguer = true;
					try
					{
						if (op == 1)
							al = new Aluguer(v,inicio,fim,true);
						else
							al = new Aluguer(v,inicio,fim,false);
						cout.precision(2);
						cout << "Aluguer com ID " << al->getID() << ", uma duracao de " << (int)(*fim-*inicio) << " dias e um custo total de ";
						cout << showpoint << fixed << al->getCustoTotal() << " euros realizado com sucesso. ";
					}
					catch(invalidAluguer& ial)
					{
						cout << "O aluguer nao pode ser realizado, a data de inicio de aluguer e invalida. Tente outra vez. ";
						pressEnter();
						validAluguer = false;
					}
					if (validAluguer)
					{
						a.addAluguer(al); // adiciona aluguer a agencia
						v->setDisponivel(false); // muda a disponibilidade da viatura
						c->addAluguer(al); // adiciona aluguer ao cliente
						a.saveAgencia(5);
						return true;
					}
				}
			}
		}
	}
	return false;
}

Aluguer* searchAluguer(Agencia& a, bool& proceed, bool& didSearch)
{
	Aluguer* nulo = NULL;
	vector<Aluguer*> resultados;
	string option = "null";
	int op = -1;
	pesquisaAluguer novaPesquisa;
	nulificarAluguer(novaPesquisa);

	do {
		clearScreen();
		string str = "null";
		cout << "--------------------------------------------------------------------\n";
		cout << "Escolha o que deseja pesquisa\n";
		cout << "Nota: Quantos mais criterios utilizar, mais precisa sera a pesquisa.\n";
		cout << "--------------------------------------------------------------------\n";
		cout << "\n1 - Nome do cliente\n";
		cout << "\n2 - Nome do funcionario responsavel\n";
		cout << "\n3 - Marca da viatura\n";
		cout << "\n4 - Valor aluguer\n";
		cout << "\n5 - Dias para acabar o aluguer\n\n";
		cout << "--------------------------------------------------------------------\n";
		cout<<  "0 - Apresentar resultados ou voltar ao menu anterior\n";
		do
		{
			cout << endl;
			readOption(option, op);
		} while (!validateOption(option, op, 5, 0, 0));

		clearScreen();
		switch (op)
		{
		case 0: // calcula os resultados
			if (numCriteriosAluguer(novaPesquisa) != 0)
				a.pesquisarAluguer(resultados, novaPesquisa);
			break;
		case 1: // altera o nome do cliente
		{
			lerString(str, 1, proceed);
			if (proceed)
			{
				novaPesquisa.nomeCliente = str;
				cout << "Criterio actualizado com sucesso. ";
				pressEnter();
				didSearch = true;
			}
		}
		break;
		case 2: // alterar o nome do funcionario
		{
			lerString(str, 1, proceed);
			if (proceed)
			{
				novaPesquisa.nomeFuncionario = str;
				cout << "Criterio actualizado com sucesso. ";
				pressEnter();
				didSearch = true;
			}
		}
		break;
		case 3: // altera a marca da viatura
		{
			lerString(str, 4, proceed);
			if (proceed)
			{
				novaPesquisa.marcaViatura = str;
				cout << "Criterio actualizado com sucesso. ";
				pressEnter();
				didSearch = true;
			}
		}
		break;
		case 4: // altera o valor do aluguer
		{
			string option = "null";
			int op = -1;
			int num;
			cout << "------------------------------\n";
			cout << "       VALOR ALUGUER\n";
			cout << "------------------------------\n";
			cout << "\n1 - Mais caro que ... euros\n";
			cout << "\n2 - Mais barato que ... euros\n\n";
			cout << "------------------------------\n";
			cout<<  "0 - VOLTAR AO MENU ANTERIOR\n";
			do
			{
				cout << endl;
				readOption(option, op);

			} while ( !validateOption(option, op, 2, 0, 0) );

			clearScreen();
			switch(op)
			{
			case 0:
				break;
			case 1:
			{
				lerNumero(num,proceed,15);
				if (proceed)
				{
					novaPesquisa.valor = num+1;
					novaPesquisa.valorOp = 1;
					cout << "Criterio actualizado com sucesso. ";
					pressEnter();
					didSearch = true;
				}
				break;
			}
			case 2:
			{
				lerNumero(num,proceed,15);
				if (proceed)
				{
					novaPesquisa.valor = num-1;
					novaPesquisa.valorOp = 2;
					cout << "Criterio actualizado com sucesso. ";
					pressEnter();
					didSearch = true;
				}
				break;
			}
			}
		}
		break;
		case 5: // altera os dias para acabar
		{
			string option = "null";
			int op = -1;
			int num;
			cout << "------------------------------\n";
			cout << "       DIAS RESTANTES\n";
			cout << "------------------------------\n";
			cout << "\n1 - Mais de ... dias\n";
			cout << "\n2 - Menos de ... dias\n\n";
			cout << "------------------------------\n";
			cout<<  "0 - VOLTAR AO MENU ANTERIOR\n";
			do
			{
				cout << endl;
				readOption(option, op);

			} while ( !validateOption(option, op, 2, 0, 0) );
			clearScreen();
			switch(op)
			{
			case 0:
				break;
			case 1:
			{
				lerNumero(num,proceed,16);
				if (proceed)
				{
					novaPesquisa.dias = num+1;
					novaPesquisa.diasOp = 1;
					cout << "Criterio actualizado com sucesso. ";
					pressEnter();
					didSearch = true;
				}
			}
			break;
			case 2:
			{
				lerNumero(num,proceed,16);
				if (proceed)
				{
					novaPesquisa.dias = num-1;
					novaPesquisa.diasOp = 2;
					cout << "Criterio actualizado com sucesso. ";
					pressEnter();
					didSearch = true;
				}
			}
			break;
			}
		}
		break;
		}
	} while (op != 0);

	if (!resultados.empty())
	{
		unsigned int ID;
		if (resultados.size() == 1)
		{
			ID = resultados.at(0)->getID();
			return a.getAluguerByID(ID);
		}

		a.showAlugueres(resultados);
		if ( resultados.size() <= 52)
		{
			gotoxy(10,62); pressEnter();
		}
		bool foundIt;

		do
		{
			clearScreen();
			foundIt = false;
			lerNumero(ID,proceed, 5);
			if (proceed)
			{
				for (unsigned int i = 0; i < resultados.size(); i++)
					if ( ID == resultados.at(i)->getID() ) // se o aluguer com o ID escolhido faz parte dos resultados
						foundIt = true;
				if (!foundIt)
					cout << "O aluguer com ID " << ID << " nao faz parte dos encontrados pela pesquisa. Tente outra vez. ";
			}
		} while (!foundIt && proceed);

		if (proceed)
			return a.getAluguerByID(ID);
	}
	return nulo;
}

void ModifyCancelFinishAluguer(Agencia& a, bool& proceed, unsigned int mr)
{
	int estado = 0, input;
	Aluguer* al;

	do {
		clearScreen();
		do {
			int x = 69, y = 28;

			gotoxy(77,2);
			if (mr == 1)
				cout << "*** MODIFICAR";
			else if (mr == 2)
				cout << "*** CANCELAR";
			else
				cout << "*** FINALIZAR";
			cout << " ALUGUER ***";

			y = (y+4*estado);
			displayMenuPlusArrows(x,44,y,5,input,estado,4);

		} while ( input != ENTER && input != ESC );

		switch(estado)
		{
		case 0: // mostrar todos os alugueres
		{
			unsigned int ID;
			bool validID;
			if (a.getNumAlugueresActivos() != 0)
			{
				a.showAlugueres(a.getAlugueres());
				if ( a.getNumAlugueresActivos() <= 52 )
				{
					gotoxy(10,62); pressEnter();
				}
				clearScreen();
				do
				{
					validID = true;
					lerNumero(ID,proceed, 5);
					if (proceed)
					{
						try
						{
							al = a.getAluguerByID(ID);
						}
						catch (NaoExiste& f)
						{
							cout << "O aluguer com ID " << f.getID() << " nao existe. Tente outra vez. ";
							pressEnter();
							cout << endl;
							validID = false;
						}
					}
				} while (!validID);

				if(proceed)
				{
					if (mr == 1)
						modifyAluguer(a, al, proceed);
					else if (mr == 2)
						a.cancelAluguer(al);
					else if ( mr == 3)
						a.finishAluguer(al);
					return;
				}
			}
			else
			{
				gotoxy(58,45); cout << "Nao ha alugueres activos na agencia. ";
				pressEnter();
			}
			break;
		}
		case 1: // pesquisar aluguer
		{
			if (a.getNumAlugueresActivos() != 0)
			{
				bool didSearch = false;
				al = searchAluguer(a, proceed,didSearch);
				if (al != NULL)
					if (mr == 1)
					{
						modifyAluguer(a, al, proceed);
						return;
					}
					else if (mr == 2)
					{
						a.cancelAluguer(al);
						return;
					}
					else
					{
						a.finishAluguer(al);
						return;
					}
				else if (proceed && didSearch)
				{
					cout << "Nao foram encontrados resultados. ";
					pressEnter();
				}
			}
			else
			{
				gotoxy(58,45); cout << "Nao ha alugueres activos na agencia. ";
				pressEnter();
			}


			break;
		}
		case 2: // introduzir ID do aluguer
		{
			if (a.getNumAlugueresActivos() != 0)
			{
				unsigned int ID;
				bool validID;
				do
				{
					clearScreen();
					validID = true;
					lerNumero(ID,proceed, 5);
					if (proceed)
					{
						try
						{
							al = a.getAluguerByID(ID);
						}
						catch (NaoExiste& f)
						{
							cout << "O aluguer com ID " << f.getID() << " nao existe. Tente outra vez. ";
							pressEnter();
							validID = false;
						}
					}
				} while (!validID);

				if (proceed)
					if (mr == 1)
						modifyAluguer(a,al,proceed);
					else if (mr == 2)
						a.cancelAluguer(al);
					else
						a.finishAluguer(al);
			}
			else
			{
				gotoxy(58,45); cout << "Nao ha alugueres activos na agencia. ";
				pressEnter();
			}
			break;
		}
		}

	} while (estado != 3);
}

void modifyAluguer(Agencia& a, Aluguer* al, bool& proceed)
{
	string option = "null";
	int op = -1;
	do
	{
		clearScreen();
		string str = "null";
		if (proceed) // se ja percorreu o loop e proceed ainda e verdadeiro, mostra os dados actuais
		{
			cout << "Dados atuais:\n";
			al->showInfo();
			cout << "\n";
			pressEnter();
			cout << "\n\n";
		}

		cout << "-------------------------------\n";
		cout << "Escolha o que deseja modificar\n";
		cout << "-------------------------------\n";
		cout << "\n1 - Data fim aluguer\n\n";
		cout << "-------------------------------\n";
		cout<<  "0 - Gravar e voltar ao menu anterior\n";
		do
		{
			cout << endl;
			readOption(option, op);
		} while (!validateOption(option, op, 2, 0, 0));

		clearScreen();
		switch(op)
		{
		case 0:
			break;
		case 1: // alterar data de fim de aluguer
		{
			int dia,mes,ano;
			bool dataValida = true;
			Data* novaData;
			Data* antigaData = al->getDataFim();
			do
			{
				cout << "Nova data\n";
				lerData(dia,mes,ano,proceed);

				if (proceed)
				{
					try
					{
						novaData = new Data(dia,mes,ano);
						dataValida = true;
						if (*novaData == *antigaData)
						{
							cout << "A nova data Ž a mesma que a data antiga. Tente outra vez. ";
							pressEnter();
						}
					}
					catch (DataInvalida &e)
					{
						cout << "Data Invalida. Tente outra vez. ";
						pressEnter();
						dataValida = false;
					}
				}
			} while (!dataValida || (*novaData == *antigaData) && proceed);

			if (proceed)
			{
				a.changeAluguer(al,novaData);
				delete antigaData;
				cout << "Data final do aluguer alterada com sucesso para " << novaData << ". ";
				pressEnter();
			}
		}
		break;
		}

	} while (op != 0);
}

/* ********************************************************
 *
 * Area de Oficinas
 *
 * ********************************************************
 */


bool addNovaOficina(Agencia& a)
{
	string nome, localizacao;
	int distancia, numFuncionarios;
	bool proceed = true;

	cout << endl;
	lerString(nome, 1, proceed); // reads name

	cout << endl;
	if (proceed)
		lerString(localizacao,3, proceed); // reads city

	cout << endl;
	if(proceed)
		lerNumero(distancia, proceed, 17); // reads distance

	cout << endl;
	if (proceed)
		lerNumero(numFuncionarios, proceed, 18); // reads number of employees

	cout << endl;
	if (proceed)
	{
			Oficina novaOficina (nome, localizacao, distancia, numFuncionarios);
			a.addOficina(novaOficina);
			cout << "A oficina \"" << novaOficina.getNome() << "\" com uma ocupacao maxima diaria de " << novaOficina.getDisponibilidade() << " horas foi adicionada com sucesso a base de dados da Agencia. ";
			return true;
	}
	return false;
}

void sendCarToShop(Agencia& a)
{
	bool proceed = true;
	int estado = 0, input;

	do {
		clearScreen();
		showFrames();
		do {
			int x = 66, y = 28;

			y = (y+4*estado); // calculo de coordenada y de acordo com o estado atual
			setcolor(9); gotoxy(x,y); cout << "==>";
			gotoxy(x+45,y); cout << "<=="; setcolor(15);

			gotoxy(77,2); cout << "*** ESCOLHA DA VIATURA ***";
			gotoxy(70,27); cout << "                                      ";
			gotoxy(70,28); cout << "|     Mostrar viaturas disponiveis    |";
			gotoxy(70,29); cout << "                                      ";
			gotoxy(70,31); cout << "                                      ";
			gotoxy(70,32); cout << "|          Pesquisar viatura          |";
			gotoxy(70,33); cout << "                                      ";
			gotoxy(70,35); cout << "                                      ";
			gotoxy(70,36); cout << "|       Introduzir ID da viatura      |";
			gotoxy(70,37); cout << "                                      ";
			gotoxy(70,39); cout << "                                      ";
			gotoxy(70,40); cout << "|       VOLTAR AO MENU ANTERIOR       |";
			gotoxy(70,41); cout << "                                      ";
			gotoxy(0,0);

			input = getArrowKeys();
			estado = stateMachine (4,input,estado);

			gotoxy(x,y); cout << "   ";
			gotoxy(x+45,y); cout << "   ";

		} while ( input != ENTER && input != ESC );

		Viatura* v;
		clearScreen();

		switch(estado)
		{
		case 3:
			break;
		case 0: // mostrar todos as viaturas disponiveis
		{
			unsigned int ID;
			bool validID;
			a.showViaturasDisponiveis();
			if ( a.getNumViaturasDisponiveis() <= 52 )
			{
				gotoxy(10,62); pressEnter();
			}
			clearScreen();
			do
			{
				validID = true;
				lerNumero(ID,proceed, 5);
				if (proceed)
				{
					try
					{
						v = a.getViaturaByID(ID);
						if (v->getDisponivel() == false) 
						{
							cout << "A viatura com ID " << ID << " nao esta disponivel. Tente outra vez. ";
							pressEnter();
							cout << endl;
							validID = false;
						}
					}
					catch (NaoExiste& f)
					{
						cout << "A viatura com ID " << f.getID() << " nao existe. Tente outra vez. ";
						pressEnter();
						cout << endl;
						validID = false;
					}
				}
			} while (!validID);
		}
		break;
		case 1: // pesquisar uma viatura
		{
			bool didSearch = false;
			v = searchViatura(a, proceed,1,didSearch);

			if (proceed)
				if (v != NULL)
				{
					if (v->getDisponivel())
					{
						v->showInfo();
						pressEnter();
						cout << endl;
					}
					else
					{
						cout << "A viatura com ID " << v->getID() << " nao esta disponivel. Tente outra vez. ";
						pressEnter();
						cout << endl;
						proceed = false;
					}
				}
				else if (didSearch && proceed)
				{
					cout << "Nao foram encontrados resultados. ";
					pressEnter();
				}
		}
		break;
		case 2: // introduzir ID da viatura
		{
			unsigned int ID;
			bool validID;
			do
			{
				clearScreen();
				validID = true;
				lerNumero(ID,proceed, 5);
				if (proceed)
				{
					try
					{
						v = a.getViaturaByID(ID);
						if (v->getDisponivel() == false) 
						{
							cout << "A viatura com ID " << ID << " nao esta disponivel. Tente outra vez. ";
							pressEnter();
							cout << endl;
							validID = false;
						}
					}
					catch (NaoExiste& f)
					{
						cout << "A viatura com ID " << f.getID() << " nao existe. Tente outra vez. ";
						pressEnter();
						cout << endl;
						validID = false;
					}
				}
			} while (!validID);
		}
		break;
		}

		if (proceed && estado != 3)
		{
			int op = -1;
			string option = "null";

			clearScreen();
			cout << "--------------------------------------------------------------------\n";
			cout << "Escolha o tipo de reparacao\n";
			cout << "--------------------------------------------------------------------\n";
			cout << "\n1 - Revisao programada da marca (4 horas)\n";
			cout << "\n2 - Inspeccao periodica obrigatoria (1 hora)\n";
			cout << "\n3 - Mudar oleo, filtro e liquido da refrigeracao (2 horas)\n";
			cout << "\n4 - Recarregadr ar condicionado e/ou reparar fugas (1 hora)\n";
			cout << "\n5 - Substituir bateria (1 hora)\n";
			cout << "\n6 - Substituir pastilhas dos travoes e/ou discos (3 horas)\n";
			cout << "\n7 - Alinhar a direccao (1 hora)\n\n";
			cout << "--------------------------------------------------------------------\n";
			cout<<  "0 - Voltar ao menu anterior\n";
			do
			{
				cout << endl;
				readOption(option, op);
			} while (!validateOption(option, op, 7, 0, 0));

			if (proceed && op != 0)
			{
				clearScreen();

				Reparacao r(v,op);

				try
				{
					a.adicionaReparacao(r);
					pressEnter();
				}
				catch (Agencia::NaoExisteOficinaDisponivel& neof)
				{
					v->setDisponivel(true);
					cout << "\nNao foi possivel enviar a viatura para reparacao pois nao ha oficinas disponiveis. ";
					pressEnter();
				}
			}
		}
	} while (estado != 3);
}

void ModifyRemoveOficina(Agencia& a, bool& proceed, int modRem)
{
	int estado = 0, input;
	Oficina of;
	unsigned int ID;
	bool validID;

	do {
		clearScreen();
		do {
			int x = 69, y = 28;

			gotoxy(77,2);
			if (modRem == 1)
				cout << "*** MODIFICAR";
			else if (modRem == 2)
				cout << "*** REMOVER";
			cout << " OFICINA ***";

			y = (y+4*estado);

			displayMenuPlusArrows(x,44,y,11,input,estado,4);
		} while ( input != ENTER && input != ESC );

		switch (estado)
		{
		case 0: // mostrar todas as oficinas
		{
			if (a.hasOficinas())
			{
				clearScreen();
				a.showOficinas();

				do {
					validID = true;
					lerNumero(ID,proceed, 5);

					if (proceed)
					{
						try
						{
							of = a.getOficinaById(ID);
							a.saveAgencia(7);
						}
						catch(Agencia::OficinaNaoExistente& one)
						{
							cout << "\nA oficina com ID " << one.getID() << " nao existe. Tente outra vez. ";
							pressEnter();
							cout << endl << endl;
							validID = false;
						}
					}

				} while (!validID);
				
				if (proceed)
				{
					if (modRem == 1) // modificar oficina
						modifyOficina(a,proceed,of);
					else if (modRem == 2) // remover oficina
					{
						if (validID && of.temReparacoes())
						{
							a.addOficina(of);  // volta a adicionar a oficina a agencia
							cout << "\nA oficina nao pode ser removida pois ainda tem reparacoes ativas. Tente outra vez. ";
							pressEnter();
							cout << endl << endl;
							validID = false;
						}
						else
						{
							cout << "\nOficina " << of.getNome() << " removida com sucesso. ";
							pressEnter();
						}
					}
				}
			}
			else
			{
				gotoxy(58,45); cout << "Nao ha oficinas disponiveis na base de dados. ";
				pressEnter();
			}
			break;
		}
		case 1: // pesquisar oficina
		{
			if (a.hasOficinas())
			{
				Oficina of = searchOficina(a,proceed);

				if ( of.getID() != -1)
				{
					if (modRem == 1) // modificar oficina
						modifyOficina(a,proceed,of);
					else if (modRem == 2) // remover oficina
					{
						if (validID && of.temReparacoes())
						{
							a.addOficina(of); // volta a adicionar a oficina a agencia
							cout << "\nA oficina nao pode ser removida pois ainda tem reparacoes ativas. Tente outra vez. ";
							pressEnter();
							cout << endl << endl;
							validID = false;
						}
						else
						{
							cout << "\nOficina " << of.getNome() << " removida com sucesso. ";
							pressEnter();
						}
					}
				}
				else
				{
					cout << "Nao foram encontrados resultados. ";
					pressEnter();
				}

			}
			else
			{
				gotoxy(58,45); cout << "Nao ha oficinas disponiveis na base de dados. ";
				pressEnter();
			}
			break;
		}
		case 2: // introduzir ID da oficina
		{
			if (a.hasOficinas())
			{
				clearScreen();

				do {
					validID = true;
					cout << endl;
					lerNumero(ID,proceed, 5);

					if (proceed)
					{
						try
						{
							of = a.getOficinaById(ID);
							a.saveAgencia(7);
						}
						catch(Agencia::OficinaNaoExistente& one)
						{
							cout << "\nA oficina com ID " << one.getID() << " nao existe. Tente outra vez. ";
							pressEnter();
							cout << endl;
							validID = false;
						}
					}

				} while (!validID);

				if (proceed)
				{
					if (modRem == 1) // modificar oficina
						modifyOficina(a,proceed,of);
					else if (modRem == 2) // remover oficina
					{
						if (validID && of.temReparacoes())
						{
							a.addOficina(of);  // volta a adicionar a oficina a agencia
							cout << "\nA oficina nao pode ser removida pois ainda tem reparacoes ativas. Tente outra vez. ";
							pressEnter();
							cout << endl << endl;
							validID = false;
						}
						else
						{
							cout << "\nOficina " << of.getNome() << " removida com sucesso. ";
							pressEnter();
						}
					}
				}
			}
			else
			{
				gotoxy(58,45); cout << "Nao ha oficinas disponiveis na base de dados. ";
				pressEnter();
			}
		}
		break;
		}
	} while (estado != 3);
}

void modifyOficina(Agencia& a, bool& proceed, Oficina& of)
{
	string option = "null";
	int op = -1;

	do {

		clearScreen();
		string str = "null";
		int num = 0;

		if (proceed) // se percorreu o loop e proceed ainda e verdadeiro, mostra info
		{
			cout << "\nDados atuais:\n\n";
			cout << of << endl;
			pressEnter();
			cout << "\n\n";
		}

		cout << "-------------------------------\n";
		cout << "Escolha o que deseja modificar\n";
		cout << "-------------------------------\n";
		cout << "\n1 - Nome da oficina\n";
		cout << "\n2 - Localizacao\n";
		cout << "\n3 - Distancia\n";
		cout << "\n4 - Numero de funcionarios\n\n";
		cout << "--------------------------------\n";
		cout<<  "0 - Gravar e voltar ao menu anterior\n";

		do {
			cout << endl;
			readOption(option, op);
		} while (!validateOption(option, op, 4, 0, 0));

		clearScreen();

		switch(op)
		{
		case 0: // gravar e voltar atras
			break;
		case 1: // mudar nome
		{
			cout << endl;
			lerString(str, 1, proceed);
			if (proceed)
			{
				of.setNome(str);
				a.addOficina(of);
				cout << "\nO nome da oficina foi alterado com sucesso para " << str << ". " << endl;
				pressEnter();
			}
		}
			break;
		case 2: // mudar localizacao
		{
			cout << endl;
			lerString(str, 3, proceed);
			if (proceed)
			{
				of.setLocalizacao(str);
				a.addOficina(of);
				cout << "\nA localizacao da oficina foi alterada com sucesso para " << str << ". " << endl;
				pressEnter();
			}
		}
		break;
		case 3: // mudar distancia
		{
			cout << endl;
			lerNumero(num, proceed, 17);
			if (proceed)
			{
				of.setDistancia(num);
				a.addOficina(of);
				cout << "\nA distancia da oficina foi alterada com sucesso para " << num << ". " << endl;
				pressEnter();
			}
		}
		break;
		case 4: // mudar numero de funcionarios
		{
			cout << endl;
			lerNumero(num, proceed, 18);
			if (proceed)
			{
				try
				{
					of.setOcupacaoMaxima(num);
					a.addOficina(of);
					cout << "\nNumero de funcionarios alterado com sucesso para " << num << ". A oficina tem agora uma ocupacao maxima de " << num*8 << " horas. " << endl;
					pressEnter();
				}
				catch(Oficina::FaltaMaoDeObra& fmo)
				{
					cout << "\nA ocupacao atual da oficina nao permite essa reducao de funcionarios. Tente outra vez. ";
					pressEnter();
				}
			}
		}
		break;
		}

	} while (op != 0);
}

Oficina searchOficina (Agencia& a, bool& proceed)
{
	Oficina of;
	vector<Oficina> resultados;
	string option = "null";
	int op = -1;
	pesquisaOficina novaPesquisa;
	nulificarOficina(novaPesquisa);

	do {
		clearScreen();
		string str = "null";
		cout << "--------------------------------------------------------------------\n";
		cout << "Escolha o que deseja pesquisa\n";
		cout << "Nota: Quantos mais criterios utilizar, mais precisa sera a pesquisa.\n";
		cout << "--------------------------------------------------------------------\n";
		cout << "\n1 - Nome da oficina\n";
		cout << "\n2 - Localizacao\n";
		cout << "\n3 - Distancia da oficina\n";
		cout << "\n4 - Numero de funcionarios\n\n";
		cout << "--------------------------------------------------------------------\n";
		cout<<  "0 - Apresentar resultados ou voltar ao menu anterior\n";

		do
		{
			cout << endl;
			readOption(option, op);
		} while (!validateOption(option, op, 4, 0, 0));

		clearScreen();

		switch(op)
		{
		case 0: // calcula os resultados
			if (numCriteriosOficina(novaPesquisa) != 0)
			{
				a.pesquisarOficina(resultados, novaPesquisa);
				a.saveAgencia(7);
			}
			break;
		case 1: // alterar nome da oficina
		{
			cout << endl;
			lerString(str,1,proceed);
			if (proceed)
			{
				novaPesquisa.nome = str;
				cout << "Criterio actualizado com sucesso. ";
				pressEnter();
			}
		}
		break;
		case 2: // alterar localizacao
		{
			cout << endl;
			lerString(str,3,proceed);
			if (proceed)
			{
				novaPesquisa.cidade = str;
				cout << "Criterio actualizado com sucesso. ";
				pressEnter();
			}
		}
		break;
		case 3: // alterar distancia da oficina
		{
			int num;
			cout << "-----------------------------\n";
			cout << "         DISTANCIA\n";
			cout << "-----------------------------\n";
			cout << "\n1 - Mais de ... km\n";
			cout << "\n2 - Menos de ... km\n";
			cout << "\n3 - Entre ... e ... km\n\n";
			cout << "-----------------------------\n";
			cout<<  "0 - VOLTAR AO MENU ANTERIOR\n";

			do {
				cout << endl;
				readOption(option, op);

			} while ( !validateOption(option, op, 3, 0, 0) );

			clearScreen();
			switch (op)
			{
			case 1: // Mais de x km
			{
				lerNumero(num,proceed,17);
				if (proceed)
				{
					novaPesquisa.distancia_inf = num+1;
					cout << "Criterio actualizado com sucesso. ";
					pressEnter();
				}
			}
			break;
			case 2: // menos de x km
			{
				lerNumero(num,proceed,17);
				if (proceed)
				{
					novaPesquisa.distancia_inf = 0;
					novaPesquisa.distancia_sup = num-1;
					cout << "Criterio actualizado com sucesso. ";
					pressEnter();
				}
			}
			break;
			case 3: // entre x e y km
			{
				int x,y,tmp;
				lerNumero(x,proceed,11);
				if (proceed)
				{
					lerNumero(y,proceed,12);
					if(proceed)
					{
						if (x > y)
						{
							tmp = x;
							x = y;
							y = tmp;
						}
						novaPesquisa.distancia_inf = x;
						novaPesquisa.distancia_sup = y;
						cout << "Criterio actualizado com sucesso. ";
						pressEnter();
					}
				}
			}
			break;
			}
		}
		break;
		case 4: // num de funcionarios
		{
			int num;
			cout << "------------------------------------\n";
			cout << "     NUMERO FUNCIONARIOS\n";
			cout << "------------------------------------\n";
			cout << "\n1 - Mais de ... funcionarios\n";
			cout << "\n2 - Menos de ... funcionarios\n";
			cout << "\n3 - Entre ... e ... funcionarios\n\n";
			cout << "------------------------------------\n";
			cout<<  "0 - VOLTAR AO MENU ANTERIOR\n";

			do {
				cout << endl;
				readOption(option, op);

			} while ( !validateOption(option, op, 3, 0, 0) );

			clearScreen();
			switch (op)
			{
			case 1: // Mais de x funcionarios
			{
				lerNumero(num,proceed,18);
				if (proceed)
				{
					novaPesquisa.numFuncionarios_inf = num+1;
					cout << "Criterio actualizado com sucesso. ";
					pressEnter();
				}
			}
			break;
			case 2: // menos de x funcionarios
			{
				lerNumero(num,proceed,18);
				if (proceed)
				{
					novaPesquisa.numFuncionarios_inf = 0;
					novaPesquisa.numFuncionarios_sup = num-1;
					cout << "Criterio actualizado com sucesso. ";
					pressEnter();
				}
			}
			break;
			case 3: // entre x e y funcionarios
			{
				int x,y,tmp;
				lerNumero(x,proceed,11);
				if (proceed)
				{
					lerNumero(y,proceed,12);
					if(proceed)
					{
						if (x > y)
						{
							tmp = x;
							x = y;
							y = tmp;
						}
						novaPesquisa.numFuncionarios_inf = x;
						novaPesquisa.numFuncionarios_sup = y;
						cout << "Criterio actualizado com sucesso. ";
						pressEnter();
					}
				}
			}
			break;
			}
		}
		break;
		}

	} while (op != 0);

	if (!resultados.empty())
	{
		unsigned int ID;
		bool foundIt;
		if (resultados.size() == 1) // pesquisa so resultou numa oficina
			return resultados.at(0);
		else
		{
			// mostrar as oficinas que corresponderam aos criterios

			cout << endl;
			for (size_t i = 0; i < resultados.size(); i++)
				cout << resultados[i] << endl << "--------------\n" << endl;
			cout << endl;
			pressEnter();

			do {
				clearScreen();
				foundIt = false;
				lerNumero(ID, proceed, 5);
				if (proceed)
				{
					vector<Oficina>::iterator it = resultados.begin();

					while (it != resultados.end() || !foundIt)
					{
						if ( ID == it->getID())
						{
							foundIt = true;
							of = (*it);
							resultados.erase(it);
						}
						else
							it++;
					}

					if (!foundIt)
					{
						cout << "A oficina com ID " << ID << " nao faz parte dos resultados da pesquisa. Tente outra vez. ";
						pressEnter();
					}
				}
			} while (!foundIt && proceed);

			if (proceed)
			{
				// volta a adicionar as oficinas nao selecionadas a agencia
				for (size_t i = 0; i < resultados.size(); i++)
					a.addOficina(resultados[i]);

				// devolve a oficina
				return of;
			}
		}
	}
	return of; // com ID a -1 caso nao tenha feito a pesquisa ou nao tenha encontrado resultados
}

void removeReparacao(Agencia& a, bool& proceed)
{
	Reparacao r;
	string option = "null";
	int op = -1, ID;
	bool validID;

	do {
		clearScreen();
		cout << "\n--------------------------------------------------------------------\n";
		cout << "\n1 - Mostrar todas as reparacoes\n";
		cout << "\n2 - Introduzir ID da reparacao\n\n";
		cout << "--------------------------------------------------------------------\n";
		cout<<  "0 - Voltar ao menu anterior\n";

		do {
			cout << endl;
			readOption(option, op);
		} while (!validateOption(option, op, 2, 0, 0));

		switch(op)
		{
		case 1: // mostrar todas as reparacoes
		{
				clearScreen();
				cout << endl;
				a.showOficinas();
				cout << endl;
				pressEnter();
				cout << endl << endl;
				do {
					validID = true;
					lerNumero(ID,proceed, 5);

					if (proceed)
					{
						try
						{
							r = a.getReparacaoById(ID);
							a.saveAgencia(7);
						}
						catch(Oficina::ReparacaoNaoExistente& rne)
						{
							cout << "\nNao existe reparacao com esse ID. Tente outra vez. ";
							pressEnter();
							cout << endl << endl;
							validID = false;
						}
					}
				} while (!validID);

				if (proceed)
				{
					cout << "\nReparacao com ID " << r.getID() << " terminada com sucesso. ";
					pressEnter();
				}
		}
		break;
		case 2: // introduzir ID da reparacao
		{
			cout << endl;
			do {
				validID = true;
				lerNumero(ID,proceed, 5);

				if (proceed)
				{
					try
					{
						r = a.getReparacaoById(ID);
						a.saveAgencia(7);
					}
					catch(Oficina::ReparacaoNaoExistente& rne)
					{
						cout << "\nNao existe reparacao com esse ID. Tente outra vez. ";
						pressEnter();
						cout << endl << endl;
						validID = false;
					}
				}
			} while (!validID);

			if (proceed)
			{
				cout << "Reparacao com ID " << r.getID() << " terminada com sucesso. ";
				pressEnter();
			}
		}
		break;
		}

	} while (op != 0);
}


/* ********************************************************
 *
 * OUTRAS FUNCOES
 *
 * ********************************************************
 */

void displayMenuPlusArrows(int x, int x_inc, int y, int menu, int& input, int& state, int numStates)
{
	// mostra setas de selecao
	setcolor(9);
	gotoxy(x,y); cout << "==>";
	gotoxy(x+x_inc,y); cout << "<==";
	setcolor(15);

	// mostra o menu desejado
	showMenu(menu);
	gotoxy(0,0);

	// verifica o input, atualiza o estado de acordo com o input
	input = getArrowKeys();
	state = stateMachine(numStates,input,state);

	// limpa setas estado anterior
	gotoxy(x,y); cout << "   ";
	gotoxy(x+x_inc,y); cout << "   ";
}

int stateMachine (int numStates, int input, int currentState)
{
	if (input == DOWN && (currentState >= 0 && currentState < (numStates-1)))
		currentState++;
	else if (input == UP && (currentState <= (numStates-1) && currentState > 0))
		currentState--;
	else if (currentState == 0 && input == UP)
		currentState = (numStates-1);
	else if (currentState == (numStates-1) && input == DOWN)
		currentState = 0;
	else if (input == ESC)
		currentState = (numStates-1);

	return currentState;
}

int getArrowKeys()
{
	int input;
	do {
		do {
			input = _getch();
		} while (input != 0xE0 && input != ENTER && input != ESC);

		if (input != ENTER && input != ESC) // nao foi premido ENTER nem ESC
			input = _getch(); // retrieve second byte of extended code;

	} while (input != DOWN && input != UP && input != ENTER && input != ESC); // enquanto nao se clicar na seta para baixo ou para cima

	return input;
}

void pressEnter() // Microsoft C/C++ compiler specific
{
	cout << "Prima ENTER para continuar.";
	char ch;
	while (( ch = _getch()) != ENTER) // enquanto caracter for diferente de ENTER
	{ }
}

bool isNumber (const string& option) // verifica se string e constituido so por digitos
{
	for (int i = 0; i < (int)option.size(); i++) // verifica todos os caracteres da string
		if ( !isdigit(option[i]) ) //se algum caracter nao e um digito
			return false; //devolve falso
	return true; //se todos os caracteres forem digitos devolve true
}

bool hasNumber (const string& name) // verifica se string possui algum digito
{
	for (int i = 0; i < (int)name.size(); i++)
		if ( isdigit(name[i]) ) // se algum caracter for um digito devolve true;
			return true;
	return false; // se nenhum caracter for digito devolve falso;
}

bool validNoum (const string& stringTeste) // verifica se string e valida (nao tem numeros, nem e numero, nem tem espao vazio ao inicio)
{
	if (isNumber(stringTeste) || isspace(stringTeste.at(0)) || hasNumber(stringTeste) )
	{
		cout << "ERRO! Opcao invalida. Tente outra vez. ";
		pressEnter();
		cout << endl;
		return false;
	}
	return true; // e valida
}

bool validateOption (const string& option, const int& op,int escolhas, int x, int y) // valida uma opcao, imprime em coordenadas especificas os erros
{
	if ( !isNumber(option) || option.empty() || op > escolhas ) // if option isn't a number or is empty
	{
		if (x != 0 && y != 0) // se coordenadas forem diferentes de 0, entao deve imprimir na coordenada desejada
		{
			gotoxy(x,y); cout << "ERRO! Opcao invalida. Tente outra vez. ";
		}
		else // se nao imprime onde estiver
			cout << "ERRO! Opcao invalida. Tente outra vez. ";
		pressEnter();
		return false;
	}
	return true;
}

bool testProceed(const string& str, bool& proceed) // teste se deve continuar
{
    if (str.empty()) // se a string estiver vazia
    {
        proceed = false;
        return false;
    }
	proceed = true;
    return true;
}

bool validMail(const string& mail) // verifica se mail e valido
{
	size_t pos = mail.find('@'); // descobre a posicao do caracter '@' na string
	size_t pos2 = mail.find('.'); // descobre a posicao do caracter '.' na string

	if ( pos == string::npos || pos2 == string::npos ) // se nao achou pelo menos um deles
		return false; // mail nao e valido
	return true;
}

bool validMatricula(const string& matricula) // verifica se matricula e valida
{
	int numLetras = 0;

	for (unsigned int i = 0; i < matricula.size(); i++) // corre os caracteres todos da string dada
	{
		if (i == 2 || i == 5)	// verifica se os caracteres '-' estao na posicao certa
		{
			if (matricula[i] != '-')
				return false;
		}
		else
			if (!isalnum(matricula[i])) // se nenhum dos restantes caracteres for numero ou letra
				return false;	// a matricula nao e valida
		if (isalpha(matricula[i])) // conta o numero de letras na string (matriculas so tm 2 letras)
			numLetras++;
	}

	if (numLetras == 2) 	// se a string tiver 2 letras
		return true; 	// a matricula e valida
	return false;
}

void lerString(string& str, unsigned int op, bool& proceed) // pede uma string
{
	do
	{
		switch (op) // tem varias opcoes
		{
		case 1:
			cout << "(*)Nome: ";
			break;
		case 2:
			cout << "(*)Pais: ";
			break;
		case 3:
			cout << "(*)Cidade: ";
			break;
		case 4:
			cout << "(*)Marca: ";
			break;
		case 5:
			cout << "(*)Transmissao: ";
			break;
		case 6:
			cout << "(*)Combustivel: ";
			break;
		default:
			break;
		}
		getline (cin, str);

		if (!testProceed(str, proceed)) // testa a string para ver se deve continuar
			break;

	} while (!validNoum(str));
}

string convertNum(long& num) // converte numero para string
{
	stringstream ss;
	ss << num;
	return ss.str();
}

template <class T>
void lerNumero(T& num, bool& proceed, unsigned int op)
{
	string str;
	do
	{
		switch (op)
		{
		case 1:
			cout << "(*)Contato telefonico: ";
			break;
		case 2:
			cout << "(*)BI: ";
			break;
		case 3:
			cout << "(*)Vencimento: ";
			break;
		case 4:
			cout << "(*)NIF: ";
			break;
		case 5:
			cout << "(*)Insira o ID: ";
			break;
		case 6:
			cout << "(*)Preco por dia: ";
			break;
		case 7:
			cout << "(*)Lugares: ";
			break;
		case 8:
			cout << "(*)Cavalos: ";
			break;
		case 9:
			cout << "(*)Cilindrada: ";
			break;
		case 10:
			cout << "(*)Idade: ";
			break;
		case 11:
			cout << "(*)Entre: ";
			break;
		case 12:
			cout << "(*)e: ";
			break;
		case 13:
			cout << "(*)Ano: ";
			break;
		case 14:
			cout << "(*)Vezes: ";
			break;
		case 15:
			cout << "(*)Valor: ";
			break;
		case 16:
			cout << "(*)Dias: ";
			break;
		case 17:
			cout << "(*)Distancia ate a oficina (em Km): ";
			break;
		case 18:
			cout << "(*)Numero de funcionarios: ";
			break;
		}
		getline(cin, str);

		if (!testProceed(str, proceed))
			break;

		if (!isNumber(str))
		{
			cout << "Opcao invalida. Tente outra vez. ";
			pressEnter();
			cout << endl;
		}
		else
			num = atoi(str.c_str());
	} while (!isNumber(str));
}

void lerData(int& dia, int& mes, int& ano, bool& proceed)
{
	string dia_str, mes_str, ano_str;

	do {
		cout << "(*)Dia: ";
		getline(cin,dia_str);

		if ( !testProceed(dia_str,proceed) )
			break;

		if (!isNumber(dia_str))
		{
			cout << "Dia invalido. Tente outra vez. ";
			pressEnter();
			cout << endl;
		}
	} while(!isNumber(dia_str));

	if (proceed)
		do {
			cout << "(*)Mes: ";
			getline(cin,mes_str);

			if ( !testProceed(mes_str,proceed) )
				break;

			if (!isNumber(mes_str))
			{
				cout << "Mes invalido. Tente outra vez. ";
				pressEnter();
				cout << endl;
			}
		} while(!isNumber(mes_str));

	if (proceed)
		do {
			cout << "(*)Ano: ";
			getline(cin,ano_str);

			if ( !testProceed(ano_str,proceed) )
				break;

			if (!isNumber(ano_str))
			{
				cout << "Ano invalido. Tente outra vez";
				pressEnter();
				cout << endl;
			}
		} while(!isNumber(ano_str));

	if (!proceed)
		return;

	dia = atoi(dia_str.c_str());
	mes = atoi(mes_str.c_str());
	ano = atoi(ano_str.c_str());
}

void readOption(string& option, int& op)
{
	cout<< "Option: ";
	getline (cin, option); // read user option
	cin.clear();
	op = atoi(option.c_str()); // convert to integer
}

template <class T>
void showCF(const T* cf)
{
	cf->showInfo();
}

template <class T>
void modify(Agencia& a, T* cf, bool& proceed)
{
	string option = "null";
	int op = -1, escolhas;
	int classe = cf->subclasse();

	if (proceed)
	{
		do
		{
			clearScreen();
			string str = "null";
			long num = 0;
			if (proceed) // se ja percorreu o loop e proceed ainda e verdadeiro, mostra os dados actuais
			{
				cout << "Dados atuais:\n";
				showCF(cf);
				cout << "\n";
				pressEnter();
				cout << "\n\n";
			}

			if (classe == 1)
				escolhas = 9;
			else
				escolhas = 10;
			cout << "-------------------------------\n";
			cout << "Escolha o que deseja modificar\n";
			cout << "-------------------------------\n";
			cout << "\n 1 - Nome\n";
			cout << "\n 2 - BI\n";
			cout << "\n 3 - Data nascimento\n";
			cout << "\n 4 - Pais\n";
			cout << "\n 5 - Morada\n";
			cout << "\n 6 - Cidade\n";
			cout << "\n 7 - Codigo-postal\n";
			cout << "\n 8 - Contato telefonico\n";
			cout << "\n 9 - E-mail\n";
			if (classe == 2) // cd Ž um Cliente
				cout << "\n 10 - NIF\n";
			cout << "\n--------------------------------\n";
			cout<<  " 0 - Gravar e voltar ao menu anterior\n";
			do
			{
				cout << endl;
				readOption(option, op);
			} while (!validateOption(option, op, escolhas, 0, 0));

			clearScreen();
			switch (op)
			{
			case 0:
				break;
			case 1: // mudar nome
			{
				lerString(str, 1, proceed);
				if (proceed)
				{
					a.changeCF(cf, str, 1);
					cout << "O nome foi alterado com sucesso para " << str << '.' << endl;
					pressEnter();
				}
			}
			break;
			case 2: // mudar o BI
			{
				lerNumero(num, proceed, 2);
				if (proceed)
				{
					str = convertNum(num);
					try
					{
						a.changeCF(cf, str, 8);
						cout << "O BI foi alterado com sucesso para " << str << '.' << endl;
						pressEnter();
					}
					catch (jaExiste& j)
					{
						if (classe == 1)
						{
							cout << "O BI escolhido ja esta a ser utilizado pelo funcionario com o ID: " << j.getID() << '.' << endl;
							cout << "Tente outra vez ou remova o funcionario em questao. ";
						}
						else
						{
							cout << "O BI escolhido ja esta a ser utilizado pelo cliente com o ID: " << j.getID() << '.' << endl;
							cout << "Tente outra vez ou remova o cliente em questao. ";
						}
						pressEnter();
						proceed = false;
					}
				}
			}
			break;
			case 3: //mudar data nascimento
			{
				int dia = 0, mes = 0, ano = 0;
				bool dataValida = true;
				Data* nascimento;

				do
				{
					cout << "Data de nascimento\n";
					lerData(dia,mes,ano,proceed);

					if (proceed)
					{
						try
						{
							nascimento = new Data(dia,mes,ano);
							dataValida = true;
						}
						catch (DataInvalida &e)
						{
							cout << "Data Invalida. Tente outra vez. ";
							pressEnter();
							dataValida = false;
						}
					}
				} while ( !dataValida && proceed);
				if (proceed)
				{
					cf->setData(nascimento);
					cout << "A data de nascimento foi alterada com sucesso para " << *nascimento << '.' << endl;
					pressEnter();
				}
			}
			break;
			case 4: //mudar pais
			{
				lerString(str, 2, proceed);
				if (proceed)
				{
					a.changeCF(cf, str, 2);
					cout << "Pais alterado com sucesso para " << str << '.' << endl;
					pressEnter();
				}
			}
			break;
			case 5: //mudar morada
			{
				do
				{
					cout << "(*)Morada: ";
					getline(cin,str);

					if ( !testProceed(str,proceed) )
						break;

					if (isNumber(str))
						cout << "Morada invalida. Tente outra vez\n";
				} while (isNumber(str) );
				if (proceed)
				{
					a.changeCF(cf, str, 3);
					cout << "Morada alterada com sucesso para " << str << '.' << endl;
					pressEnter();
				}
			}
			break;
			case 6: //mudar cidade
			{
				lerString(str, 3, proceed);
				if(proceed)
				{
					a.changeCF(cf,str, 4);
					cout << "Cidade alterada com sucesso para " << str << '.' << endl;
					pressEnter();
				}
			}
			break;
			case 7: //mudar codigopostal
			{
				cout << "(*)Codigo-Postal: ";
				getline(cin,str);

				testProceed(str,proceed);

				if(proceed)
				{
					a.changeCF(cf, str, 5);
					cout << "Codigo-postal alterado com sucesso para " << str << '.' << endl;
					pressEnter();
				}
			}
			break;
			case 8: //mudar telefone
			{
				lerNumero(num,proceed,1);
				if(proceed)
				{
					str = convertNum(num);
					a.changeCF(cf, str, 6);
					cout << "Telefone alterado com sucesso para " << str << '.' << endl;
					pressEnter();
				}
			}
			break;
			case 9: //mudar email
			{
				do
				{
					cout << "(*)e-mail: ";
					getline(cin, str);

					if ( !testProceed(str, proceed))
						break;

					if (!validMail(str))
						cout << "Email invalido. Tente outra vez.\n";

				} while(!validMail(str));
				if (proceed)
				{
					a.changeCF(cf, str, 7);
					cout << "E-mail alterado com sucesso para " << str << '.' << endl;
					pressEnter();
				}

			}
			break;
			case 10:
			{
				lerNumero(num, proceed, 4);
				if (proceed)
				{
					str = convertNum(num);
					try
					{
						a.changeCF(cf, str, 9);
						cout << "O NIF foi alterado com sucesso para " << str << '.' << endl;
					}
					catch (jaExiste& j)
					{
						cout << "O NIF escolhido ja esta a ser utilizado pelo cliente com o ID: " << j.getID() << '.' << endl;
						cout << "Tente outra vez ou remova o cliente em questao." << endl;
						proceed = false;
					}
					pressEnter();
				}
			}
			break;
			default:
				break;
			}

		} while ( op != 0);
	}
}

template <class T>
void searchIt(Agencia& a, vector<T*>& resultados, bool& proceed, int classe, bool& didSearch)
{
	string option = "null";
	int op = -1;
	pesquisaCF novaPesquisa;
	nulificarCF(novaPesquisa);

	do
	{
		clearScreen();
		string str = "null";
		long num;
		cout << "--------------------------------------------------------------------\n";
		cout << "Escolha o que deseja pesquisar\n";
		cout << "Nota: Quantos mais criterios utilizar, mais precisa sera a pesquisa\n";
		cout << "--------------------------------------------------------------------\n";
		cout << "\n1 - Nome\n";
		cout << "\n2 - BI\n";
		cout << "\n3 - Idade\n";
		cout << "\n4 - Pais\n";
		cout << "\n5 - Morada\n";
		cout << "\n6 - Cidade\n";
		cout << "\n7 - Codigo-postal\n";
		cout << "\n8 - Contato telefonico\n";
		cout << "\n9 - E-mail\n";
		if (classe == 2) // cd Ž um Cliente
			cout << "\n10 - NIF\n\n";
		else
			cout << "\n10 - Vencimento\n\n";
		cout << "--------------------------------------------------------------------\n";
		cout<<  "0 - Apresentar resultados ou voltar ao menu anterior\n";
		do
		{
			cout << endl;
			readOption(option, op);
		} while (!validateOption(option, op, 10, 0, 0));

		clearScreen();
		switch (op)
		{
		case 0:	// calcula os resultados
		{
			if (numCriteriosCF(novaPesquisa) != 0)
				a.pesquisarCFs(resultados, novaPesquisa);
		}
		break;
		case 1: // altera o nome a pesquisar
		{
			lerString(str, 1, proceed);
			if (proceed)
			{
				novaPesquisa.nome = str;
				cout << "Criterio actualizado com sucesso. ";
				pressEnter();
				didSearch = true;
			}
		}
		break;
		case 2: // altera o BI a pesquisar
		{
			lerNumero(num,proceed,2);
			if (proceed)
			{
				novaPesquisa.BI = num;
				cout << "Criterio actualizado com sucesso. ";
				pressEnter();
				didSearch = true;
			}
		}
		break;
		case 3: // altera a idade a pesquisar
		{
			string option = "null";
			int op = -1;
			int num;
			cout << "----------------------------\n";
			cout << "          IDADE\n";
			cout << "----------------------------\n";
			cout << "\n1 - Maior do que...\n";
			cout << "\n2 - Menor do que...\n";
			cout << "\n3 - Entre ... e ...\n";
			cout << "\n4 - Igual a ...\n\n";
			cout << "----------------------------\n";
			cout<<  "0 - VOLTAR AO MENU ANTERIOR\n";
			do
			{
				cout << endl;
				readOption(option, op);

			} while ( !validateOption(option, op, 4, 0, 0) );

			clearScreen();
			switch(op)
			{
			case 0:
				break;
			case 1:
			{
				lerNumero(num,proceed,10);
				if (proceed)
				{
					novaPesquisa.idade_inf = num+1;
					didSearch = true;
				}
				break;
			}
			case 2:
			{
				lerNumero(num,proceed,10);
				if (proceed)
				{
					novaPesquisa.idade_inf = 18;
					novaPesquisa.idade_sup = num-1;
					didSearch = true;
				}
				break;
			}
			case 3:
			{
				int x,y,tmp;
				lerNumero(x,proceed,11);
				if (proceed)
				{
					lerNumero(y,proceed,12);
					if(proceed)
					{
						if (x > y)
						{
							tmp = x;
							x = y;
							y = tmp;
						}
						novaPesquisa.idade_inf = x;
						novaPesquisa.idade_sup = y;
						didSearch = true;
					}
				}
				break;
			}
			case 4:
			{
				lerNumero(num,proceed,10);
				if (proceed)
				{
					novaPesquisa.idade_inf = num;
					novaPesquisa.idade_sup = num;
					didSearch = true;
				}
				break;
			}
			}
		}
		break;
		case 4: // altera o pais a pesquisar
		{
			lerString(str, 2, proceed);
			if (proceed)
			{
				novaPesquisa.pais = str;
				cout << "Criterio actualizado com sucesso. ";
				pressEnter();
				didSearch = true;
			}
		}
		break;
		case 5: // altera a morada a pesquisar
		{
			do
			{
				cout << "(*)Morada: ";
				getline(cin,str);

				if ( !testProceed(str,proceed) )
					break;

				if (isNumber(str))
				{
					cout << "Morada invalida. Tente outra vez. ";
					pressEnter();
					cout << endl;
				}
			} while (isNumber(str) );

			if (proceed)
			{
				novaPesquisa.morada = str;
				cout << "Criterio actualizado com sucesso. ";
				pressEnter();
				didSearch = true;
			}
		}
		break;
		case 6: // altera a cidade a pesquisar
		{
			lerString(str, 3, proceed);
			if (proceed)
			{
				novaPesquisa.cidade = str;
				cout << "Criterio actualizado com sucesso. ";
				pressEnter();
				didSearch = true;
			}
		}
		break;
		case 7: // altera o codigo postal a pesquisar
		{
			cout << "(*)Codigo-Postal: ";
			getline(cin,str);

			testProceed(str,proceed);

			if(proceed)
			{
				novaPesquisa.codigopostal = str;
				cout << "Criterio actualizado com sucesso. ";
				pressEnter();
				didSearch = true;
			}
		}
		break;
		case 8: // altera o contato telefonico a pesquisar
		{
			lerNumero(num, proceed, 1);
			if (proceed)
			{
				novaPesquisa.phone = num;
				cout << "Criterio actualizado com sucesso. ";
				pressEnter();
				didSearch = true;
			}
		}
		break;
		case 9: // altera o email a pesquisar
		{
			do
			{
				cout << "(*)e-mail: ";
				getline(cin, str);

				if ( !testProceed(str, proceed))
					break;

				if (!validMail(str))
				{
					cout << "Email invalido. Tente outra vez. ";
					pressEnter();
					cout << endl;
				}

			} while(!validMail(str));
			if (proceed)
			{
				novaPesquisa.email = str;
				cout << "Criterio actualizado com sucesso. ";
				pressEnter();
				didSearch = true;
			}
		}
		break;
		case 10:
		{
			string option = "null";
			int num;
			if (classe == 2) // cd Ž um Cliente
			{
				lerNumero(num, proceed, 4);
				if(proceed)
					novaPesquisa.NIF = num;
			}
			else
			{
				string option = "null";
				int op = -1;
				int num;
				cout << "------------------------\n";
				cout << " VENCIMENTO\n";
				cout << "------------------------\n";
				cout << "\n1 - Maior do que...\n";
				cout << "\n2 - Menor do que...\n";
				cout << "\n3 - Entre ... e ...\n";
				cout << "\n4 - Igual a ...\n\n";
				cout << "------------------------\n";
				cout<<  "0 - VOLTAR AO MENU ANTERIOR\n";
				do
				{
					cout << endl;
					readOption(option, op);

				} while ( !validateOption(option, op, 4, 0, 0) );
				clearScreen();
				switch(op)
				{
				case 0:
					break;
				case 1:
				{
					lerNumero(num,proceed,3);
					if (proceed)
					{
						novaPesquisa.vencimento_inf = num+1;
						didSearch = true;
					}
					break;
				}
				case 2:
				{
					lerNumero(num,proceed,4);
					if (proceed)
					{
						novaPesquisa.vencimento_inf = 0;
						novaPesquisa.vencimento_sup = num-1;
						didSearch = true;
					}
					break;
				}
				case 3:
				{
					int x,y,tmp;
					lerNumero(x,proceed,11);
					if (proceed)
					{
						lerNumero(y,proceed,12);
						if(proceed)
						{
							if (x > y)
							{
								tmp = x;
								x = y;
								y = tmp;
							}
							novaPesquisa.vencimento_inf = x;
							novaPesquisa.vencimento_sup = y;
							didSearch = true;
						}
					}
					break;
				}
				case 4:
				{
					lerNumero(num,proceed,3);
					if (proceed)
					{
						novaPesquisa.vencimento_inf = num;
						novaPesquisa.vencimento_sup = num;
						didSearch = true;
					}
					break;
				}
				}
			}
		}
		break;
		}
	}while (op != 0);
}

/* ********************************************************
 *
 * FUNCOES RELACIONADAS COM O DISPLAY
 *
 * ********************************************************
 */

void showMenu(int option) //mostra menus especificos
{
	int x = 0; //coordenada x
	int y = 0; //coordenada y

	showFrames();

	switch(option)
	{
	case 1: // menu inicial do programa
	{
		x = 73;
		gotoxy(x,25); cout << "                             ";
		gotoxy(x,26); cout << "|    Area de Funcionarios    |";
		gotoxy(x,27); cout << "                             ";
		gotoxy(x,29); cout << "                             ";
		gotoxy(x,30); cout << "|      Area de Clientes      |";
		gotoxy(x,31); cout << "                             ";
		gotoxy(x,33); cout << "                             ";
		gotoxy(x,34); cout << "|      Area de Viaturas      |";
		gotoxy(x,35); cout << "                             ";
		gotoxy(x,37); cout << "                             ";
		gotoxy(x,38); cout << "|      Area de Alugueres     |";
		gotoxy(x,39); cout << "                             ";
		gotoxy(x,41); cout << "                             ";
		gotoxy(x,42); cout << "|            SAIR            |";
		gotoxy(x,43); cout << "                             ";
	}
	break;
	case 2: // area de funcionarios
	{
		x = 71;
		gotoxy(x,23); cout << "                                       ";
		gotoxy(x,24); cout << "|      Adicionar novo funcionario      |";
		gotoxy(x,25); cout << "                                       ";
		gotoxy(x,27); cout << "                                       ";
		gotoxy(x,28); cout << "|    Modificar funcionario existente   |";
		gotoxy(x,29); cout << "                                       ";
		gotoxy(x,31); cout << "                                       ";
		gotoxy(x,32); cout << "|     Mostrar todos os funcionarios    |";
		gotoxy(x,33); cout << "                                       ";
		gotoxy(x,35); cout << "                                       ";
		gotoxy(x,36); cout << "|         Pesquisar funcionario        |";
		gotoxy(x,37); cout << "                                       ";
		gotoxy(x,39); cout << "                                       ";
		gotoxy(x,40); cout << "|          Remover funcionario         |";
		gotoxy(x,41); cout << "                                       ";
		gotoxy(x,43); cout << "                                       ";
		gotoxy(x,44); cout << "|        VOLTAR AO MENU PRINCIPAL      |";
		gotoxy(x,45); cout << "                                       ";
	}
	break;
	case 3: // area de clientes
	{
		x = 71;
		gotoxy(x,19); cout << "                                       ";
		gotoxy(x,20); cout << "|       Adicionar novo cliente         |";
		gotoxy(x,21); cout << "                                       ";
		gotoxy(x,23); cout << "                                       ";
		gotoxy(x,24); cout << "|     Modificar cliente existente      |";
		gotoxy(x,25); cout << "                                       ";
		gotoxy(x,27); cout << "                                       ";
		gotoxy(x,28); cout << "|      Mostrar todos os clientes       |";
		gotoxy(x,29); cout << "                                       ";
		gotoxy(x,31); cout << "                                       ";
		gotoxy(x,32); cout << "|          Pesquisar cliente           |";
		gotoxy(x,33); cout << "                                       ";
		gotoxy(x,35); cout << "                                       ";
		gotoxy(x,36); cout << "|           Remover cliente            |";
		gotoxy(x,37); cout << "                                       ";
		gotoxy(x,39); cout << "                                       ";
		gotoxy(x,40); cout << "|      Area de clientes inactivos      |";
		gotoxy(x,41); cout << "                                       ";
		gotoxy(x,43); cout << "                                       ";
		gotoxy(x,44); cout << "|       VOLTAR AO MENU PRINCIPAL       |";
		gotoxy(x,45); cout << "                                       ";
	}
	break;
	case 4: // area de viaturas
	{
		x = 50;
		gotoxy(x,27); cout << "                                    ";
		gotoxy(x,28); cout << "|       Adicionar nova viatura      |";
		gotoxy(x,29); cout << "                                    ";
		gotoxy(x,31); cout << "                                    ";
		gotoxy(x,32); cout << "|        Catalogo de viaturas       |";
		gotoxy(x,33); cout << "                                    ";
		gotoxy(x,35); cout << "                                    ";
		gotoxy(x,36); cout << "|    Modificar viatura existente    |";
		gotoxy(x,37); cout << "                                    ";
		gotoxy(x,39); cout << "                                    ";
		gotoxy(x,40); cout << "|     Mostrar todos as viaturas     |";
		gotoxy(x,41); cout << "                                    ";

		x = 90;
		gotoxy(x,27); cout << "                                    ";
		gotoxy(x,28); cout << "|         Pesquisar viatura         |";
		gotoxy(x,29); cout << "                                    ";
		gotoxy(x,31); cout << "                                    ";
		gotoxy(x,32); cout << "|          Remover viatura          |";
		gotoxy(x,33); cout << "                                    ";
		gotoxy(x,35); cout << "                                    ";
		gotoxy(x,36); cout << "|              Oficinas             |";
		gotoxy(x,37); cout << "                                    ";
		gotoxy(x,39); cout << "                                    ";
		gotoxy(x,40); cout << "|      VOLTAR AO MENU PRINCIPAL     |";
		gotoxy(x,41); cout << "                                    ";
	}
	break;
	case 5: // modificar / remover aluguer
	{
		x = 73;
		gotoxy(x,27); cout << "                                      ";
		gotoxy(x,28); cout << "|      Mostrar todas os alugueres     |";
		gotoxy(x,29); cout << "                                      ";
		gotoxy(x,31); cout << "                                      ";
		gotoxy(x,32); cout << "|          Pesquisar aluguer          |";
		gotoxy(x,33); cout << "                                      ";
		gotoxy(x,35); cout << "                                      ";
		gotoxy(x,36); cout << "|      Introduzir ID do aluguer       |";
		gotoxy(x,37); cout << "                                      ";
		gotoxy(x,39); cout << "                                      ";
		gotoxy(x,40); cout << "|       VOLTAR AO MENU ANTERIOR       |";
		gotoxy(x,41); cout << "                                      ";
	}
	break;
	case 6: // modificar / remover funcionario
	{
		x = 73;
		gotoxy(x,27); cout << "                                      ";
		gotoxy(x,28); cout << "|    Mostrar todos os funcionarios    |";
		gotoxy(x,29); cout << "                                      ";
		gotoxy(x,31); cout << "                                      ";
		gotoxy(x,32); cout << "|        Pesquisar funcionario        |";
		gotoxy(x,33); cout << "                                      ";
		gotoxy(x,35); cout << "                                      ";
		gotoxy(x,36); cout << "|     Introduzir ID do funcionario    |";
		gotoxy(x,37); cout << "                                      ";
		gotoxy(x,39); cout << "                                      ";
		gotoxy(x,40); cout << "|       VOLTAR AO MENU ANTERIOR       |";
		gotoxy(x,41); cout << "                                      ";
	}
	break;
	case 7: // modificar / remover cliente
	{
		x = 73;
		gotoxy(x,27); cout << "                                      ";
		gotoxy(x,28); cout << "|      Mostrar todos os clientes      |";
		gotoxy(x,29); cout << "                                      ";
		gotoxy(x,31); cout << "                                      ";
		gotoxy(x,32); cout << "|          Pesquisar cliente          |";
		gotoxy(x,33); cout << "                                      ";
		gotoxy(x,35); cout << "                                      ";
		gotoxy(x,36); cout << "|       Introduzir ID do cliente      |";
		gotoxy(x,37); cout << "                                      ";
		gotoxy(x,39); cout << "                                      ";
		gotoxy(x,40); cout << "|       VOLTAR AO MENU ANTERIOR       |";
		gotoxy(x,41); cout << "                                      ";
	}
	break;
	case 8: // modificar / remover viatura
	{
		x = 73;
		gotoxy(x,27); cout << "                                      ";
		gotoxy(x,28); cout << "|       Mostrar todas as viaturas     |";
		gotoxy(x,29); cout << "                                      ";
		gotoxy(x,31); cout << "                                      ";
		gotoxy(x,32); cout << "|          Pesquisar viatura          |";
		gotoxy(x,33); cout << "                                      ";
		gotoxy(x,35); cout << "                                      ";
		gotoxy(x,36); cout << "|       Introduzir ID da viatura      |";
		gotoxy(x,37); cout << "                                      ";
		gotoxy(x,39); cout << "                                      ";
		gotoxy(x,40); cout << "|        VOLTAR AO MENU ANTERIOR      |";
		gotoxy(x,41); cout << "                                      ";
	}
	break;
	case 9: // area de catalogo de viaturas
	{
		x = 71;
		gotoxy(x,19); cout << "                                       ";
		gotoxy(x,20); cout << "|     Adicionar viatura ao catalogo    |";
		gotoxy(x,21); cout << "                                       ";
		gotoxy(x,23); cout << "                                       ";
		gotoxy(x,24); cout << "|      Modificar viatuta existente     |";
		gotoxy(x,25); cout << "                                       ";
		gotoxy(x,27); cout << "                                       ";
		gotoxy(x,28); cout << "|       Mostrar todos as viaturas      |";
		gotoxy(x,29); cout << "                                       ";
		gotoxy(x,31); cout << "                                       ";
		gotoxy(x,32); cout << "|           Pesquisar viatura          |";
		gotoxy(x,33); cout << "                                       ";
		gotoxy(x,35); cout << "                                       ";
		gotoxy(x,36); cout << "|            Comprar viatura           |";
		gotoxy(x,37); cout << "                                       ";
		gotoxy(x,39); cout << "                                       ";
		gotoxy(x,40); cout << "|      Remover viatura do catalogo     |";
		gotoxy(x,41); cout << "                                       ";
		gotoxy(x,43); cout << "                                       ";
		gotoxy(x,44); cout << "|        VOLTAR AO MENU ANTERIOR       |";
		gotoxy(x,45); cout << "                                       ";
	}
	break;
	case 10: // area de Oficinas
	{
		x = 73;
		gotoxy(x,23); cout << "                                       ";
		gotoxy(x,24); cout << "|        Adicionar nova oficina        |";
		gotoxy(x,25); cout << "                                       ";
		gotoxy(x,27); cout << "                                       ";
		gotoxy(x,28); cout << "|      Enviar viatura para reparar     |";
		gotoxy(x,29); cout << "                                       ";
		gotoxy(x,31); cout << "                                       ";
		gotoxy(x,32); cout << "|         Finalizar reparacao          |";
		gotoxy(x,33); cout << "                                       ";
		gotoxy(x,35); cout << "                                       ";
		gotoxy(x,36); cout << "|       Mostrar todas as oficinas      |";
		gotoxy(x,37); cout << "                                       ";
		gotoxy(x,39); cout << "                                       ";
		gotoxy(x,40); cout << "|          Modificar oficina           |";
		gotoxy(x,41); cout << "                                       ";
		gotoxy(x,43); cout << "                                       ";
		gotoxy(x,44); cout << "|           Remover oficina            |";
		gotoxy(x,45); cout << "                                       ";
		gotoxy(x,47); cout << "                                       ";
		gotoxy(x,48); cout << "|        VOLTAR AO MENU ANTERIOR       |";
		gotoxy(x,49); cout << "                                       ";
	}
	break;
	case 11: // modificar / remover oficina
	{
		x = 73;
		gotoxy(x,27); cout << "                                      ";
		gotoxy(x,28); cout << "|       Mostrar todas as oficinas     |";
		gotoxy(x,29); cout << "                                      ";
		gotoxy(x,31); cout << "                                      ";
		gotoxy(x,32); cout << "|          Pesquisar oficina          |";
		gotoxy(x,33); cout << "                                      ";
		gotoxy(x,35); cout << "                                      ";
		gotoxy(x,36); cout << "|       Introduzir ID da oficina      |";
		gotoxy(x,37); cout << "                                      ";
		gotoxy(x,39); cout << "                                      ";
		gotoxy(x,40); cout << "|        VOLTAR AO MENU ANTERIOR      |";
		gotoxy(x,41); cout << "                                      ";
	}
	break;
	case 12: // area de clientes inativos
	{
		x = 71;
		gotoxy(x,23); cout << "                                       ";
		gotoxy(x,24); cout << "|          Reactivar cliente           |";
		gotoxy(x,25); cout << "                                       ";
		gotoxy(x,27); cout << "                                       ";
		gotoxy(x,28); cout << "|      Modificar cliente inativo       |";
		gotoxy(x,29); cout << "                                       ";
		gotoxy(x,31); cout << "                                       ";
		gotoxy(x,32); cout << "|      Mostrar clientes inativos       |";
		gotoxy(x,33); cout << "                                       ";
		gotoxy(x,35); cout << "                                       ";
		gotoxy(x,36); cout << "|     Pesquisar clientes inativos      |";
		gotoxy(x,37); cout << "                                       ";
		gotoxy(x,39); cout << "                                       ";
		gotoxy(x,40); cout << "|       Remover cliente inativo        |";
		gotoxy(x,41); cout << "                                       ";
		gotoxy(x,43); cout << "                                       ";
		gotoxy(x,44); cout << "|       VOLTAR AO MENU  ANTERIOR       |";
		gotoxy(x,45); cout << "                                       ";
	}
	break;
	}
}

