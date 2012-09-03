#include "mainHelper.h"
#include "mouse.h"
#include <vector>
#include <iterator>
#include <fstream>

#define COR_MENUS 15

void areaFuncionarios(Agencia& a);
void areaClientes(Agencia& a);
void areaViaturas(Agencia& a);
void areaOficina(Agencia& a);
void areaCatalogo(Agencia& a);
void areaAlugueres(Agencia& a, vector<Aluguer*>& terminamHoje);
void areaClientesInativos(Agencia& a);

enum requestMain {MAIN_FUNCIONARIOS = 0, MAIN_CLIENTES, MAIN_VIATURAS, MAIN_ALUGUERES, MAIN_EXIT};
enum requestFunc { NEW_FUNC = 0, MODIFY_FUNC, DISPLAY_FUNC, SEARCH_FUNC, REMOVE_FUNC, FUNC_EXIT};
enum requestClie { NEW_CLIE = 0, MODIFY_CLIE, DISPLAY_CLIE, SEARCH_CLIE, REMOVE_CLIE, INAC_CLIE, CLIE_EXIT};
enum requestViat { NEW_VIAT = 0, CATALOGUE_VIAT, MODIFY_VIAT, DISPLAY_VIAT, SEARCH_VIAT, REMOVE_VIAT, REPAIR_VIAT , VIAT_EXIT};
enum requestShop { NEW_SHOP = 0, SEND_CAR_SHOP, TERMINATE_REPAIR, DISPLAY_SHOP, MODIFY_SHOP, REMOVE_SHOP, SHOP_EXIT };
enum requestCatalogue { NEW_CAT = 0, MODIFY_CAT, DISPLAY_CAT, SEARCH_CAT, BUY_CAT, REMOVE_CAT, CAT_EXIT};
enum requestAlug { NEW_ALUG = 0, MODIFY_ALUG, DISPLAY_ALUG, SEARCH_ALUG, CANCEL_ALUG, FINAL_ALUG, DUE2DAY_ALUG};

/*enum request { NEW = 1, MODIFY, DISPLAY, SEARCH, REMOVE };*/

int main()
{
	Agencia agenciaFEUP;
	vector<Aluguer*> terminamHoje;
	agenciaFEUP.checkClientesInativos();
	int estado = 0;
	setcolor(COR_MENUS);

	do {
		/* se nao for a primeira vez que vai ao menu inicial e
		 * entretanto ja se tenha removido alugueres em atraso,
		 * o vector deve ser limpo
		 */
		terminamHoje.clear();

		// maximixa a janela de comandos e ajusta ao ecra
		maximizeScreenBufferAndConsole();
		ShowWindow(GetConsoleWindow(),SW_MAXIMIZE);

		// verifica se ha alugueres que terminam na data em que o programa esta a ser corrido
		bool terminamHoje_ = agenciaFEUP.hasFinishingToday();
		if (terminamHoje_)
			agenciaFEUP.getFinishingToday(terminamHoje); // carrega para o vector esses alugueres
		clearScreen();
		
		do {
			gotoxy(82,2); cout << "*** MENU ***";

			if (terminamHoje_) // deve mostrar um aviso quando ha alugueres em atraso
			{
				setcolor(4); // cor vermelha
				gotoxy(67,55); cout << "| AVISO - HA ALUGUERES QUE TERMINAM HOJE |";
				setcolor(COR_MENUS); // cor branca
			}

			// mostra o menu, e utiliza o rato para determinar o estado desejado
			showMenu(1);
			gotoxy(0,0);
			estado = mouseDoubleClick();

		} while ( estado == 100 ); // continua no loop enquanto nao se clicar nas posicoes certas

		switch (estado)
		{
		case MAIN_FUNCIONARIOS:
			areaFuncionarios(agenciaFEUP);
		break;
		case MAIN_CLIENTES:
			areaClientes(agenciaFEUP);
		break;
		case MAIN_VIATURAS:
			areaViaturas(agenciaFEUP);
		break;
		case MAIN_ALUGUERES:
			areaAlugueres(agenciaFEUP, terminamHoje);
		break;
		}
	} while (estado != MAIN_EXIT);

	agenciaFEUP.exitAgencia(); // grava informacoes da agencia
	return 0;
}

void areaFuncionarios(Agencia& a)
{
	bool proceed = true;
	int estado = 0, input;

	do {
		clearScreen();
		do {
			int x = 67, y = 24; // coordenadas para as setas iniciais

			gotoxy(42,60); cout << "AVISO - QUALQUER OPCAO COM '(*)' ATRAS, DEIXE VAZIA E PRIMA ENTER PARA VOLTAR AO MENU ANTERIOR";
			gotoxy(77,2); cout << "*** AREA DE FUNCIONARIOS ***";

			y = (y+4*estado); // calculo de coordenada y de acordo com o estado atual

			displayMenuPlusArrows(x,45,y,2,input,estado,6); // mostrar menus e setas na posicao certa

		} while ( input != ENTER && input != ESC ); // enquanto nao se clicar em ENTER ou ESC

		switch (estado)
		{
		case NEW_FUNC:
		{
			clearScreen();
			if (addNovoFuncionario(a))
				pressEnter();
		}
		break;
		case MODIFY_FUNC: // modifica funcionario
		{
			if(a.getNumFuncionarios() != 0) // se tem funcionarios registados
				ModifyRemoveFuncionario(a, proceed, 1);
			else
			{
				gotoxy(58,49); cout << "Nao ha funcionarios registados na agencia. ";
				pressEnter();
			}
		}
		break;
		case DISPLAY_FUNC: // mostrar funcionarios
		{
			if(a.getNumFuncionarios() != 0) // se tem funcionarios registados
			{
				a.showFuncionarios(a.getFuncionarios());
				if ( a.getNumFuncionarios() <= 52 ) // se consegue mostrar numa pagina so
				{
					gotoxy(10,62); pressEnter();
				}
			}
			else
			{
				gotoxy(58,49); cout << "Nao ha funcionarios registados na agencia. ";
				pressEnter();
			}

		}
		break;
		case SEARCH_FUNC: // pesquisar funcionario
		{
			if(a.getNumFuncionarios() != 0) // se tem funcionarios registados na agencia
			{
				bool didSearch = false;
				Funcionario* f = searchFuncionario(a, proceed, didSearch); // faz a pesquisa
				if (f != NULL) // se a pesquisa retornou um apontador nao nulo
				{
					showCF(f); // mostra info do cliente
					pressEnter();
				}
				else if (didSearch && proceed)
				{
					cout << "Nao foram encontrados resultados. ";
					pressEnter();
				}
			}
			else
			{
				gotoxy(58,49); cout << "Nao ha funcionarios registados na agencia. ";
				pressEnter();
			}
		}
		break;
		case REMOVE_FUNC: // remove funcionario
		{
			if(a.getNumFuncionarios() != 0) // se tem funcionarios registados na agencia
				ModifyRemoveFuncionario(a, proceed, 2);
			else
			{
				gotoxy(58,49); cout << "Nao ha funcionarios registados na agencia. ";
				pressEnter();
			}
		}
		break;
        }
    } while (estado != FUNC_EXIT);
}

void areaClientes(Agencia& a)
{
	bool proceed = true;
	int estado = 0, input;

	do {
		clearScreen();
		do {
			int x = 67, y = 20; // coordenadas para as setas iniciais

			gotoxy(42,60); cout << "AVISO - QUALQUER OPCAO COM '(*)' ATRAS, DEIXE VAZIA E PRIMA ENTER PARA VOLTAR AO MENU ANTERIOR";
			gotoxy(75,2); cout << "*** AREA DE CLIENTES ***";

			y = (y+4*estado); // calculo de coordenada y de acordo com o estado atual

			displayMenuPlusArrows(x,45,y,3,input,estado,7); // mostrar menus e setas na posicao certa

		} while ( input != ENTER && input != ESC ); // enquanto nao se clicar em ENTER ou ESC

		switch (estado)
		{
		case NEW_CLIE: // novo cliente
		{
			clearScreen();
			if (addNovoCliente(a))
				pressEnter();
		}
		break;
		case MODIFY_CLIE: // modificar cliente
		{
			if(a.getNumClientes() != 0) // se tem clientes registados
				ModifyRemoveCliente(a, proceed, 1);
			else
			{
				gotoxy(58,49); cout << "Nao ha clientes registados na agencia. ";
				pressEnter();
			}
		}
		break;
		case DISPLAY_CLIE: // mostrar clientes
		{
			if(a.getNumClientes() != 0) // se tem clientes registados
			{
				a.showClientes(a.getClientes());
				if ( a.getNumClientes() <= 52 ) // se consegues mostrar numa pagina so
				{
					gotoxy(10,62); pressEnter();
				}
			}
			else
			{
				gotoxy(58,49); cout << "Nao ha clientes registados na agencia. ";
				pressEnter();
			}
		}
		break;
		case SEARCH_CLIE: // procurar cliente
		{
			if(a.getNumClientes() != 0) // se tem clientes registados
			{
				bool didSearch = false;
				Cliente* c = searchCliente(a, proceed, didSearch, true);
				if (c != NULL) // se a pesquisa retornou um apontador nao nulo
				{
					showCF(c); // mostra info do cliente
					pressEnter();
				}
				else if (didSearch && proceed)
				{
					cout << "Nao foram encontrados resultados.\n";
					pressEnter();
				}
				cout << endl;
			}
			else
			{
				gotoxy(58,49); cout << "Nao ha clientes registados na agencia. ";
				pressEnter();
			}
		}
		break;
		case REMOVE_CLIE: // remove cliente
		{
			if(a.getNumClientes() != 0) // se tem clientes registados 
				ModifyRemoveCliente(a,proceed,2);
			else
			{
				gotoxy(58,49); cout << "Nao ha clientes registados na agencia. ";
				pressEnter();
			}
		}
		break;
		case INAC_CLIE: // area de clientes inactivos
		{
			if (a.hasClientesInativos()) // se tem clientes inativos
			{
				areaClientesInativos(a);
			}
			else
			{
				gotoxy(58,49); cout << "Nao ha clientes inativos na agencia. ";
				pressEnter();
			}
		}
		break;
		}
	} while (estado != CLIE_EXIT);
}

void areaClientesInativos(Agencia& a)
{
	bool proceed = true;
	int estado = 0, input;

	do {
		clearScreen();
		do {
			int x = 67, y = 24; // coordenadas para as setas iniciais

			gotoxy(42,60); cout << "AVISO - QUALQUER OPCAO COM '(*)' ATRAS, DEIXE VAZIA E PRIMA ENTER PARA VOLTAR AO MENU ANTERIOR";
			gotoxy(72,2); cout << "*** AREA DE CLIENTES INATIVOS ***";

			y = (y+4*estado); // calculo de coordenada y de acordo com o estado atual

			displayMenuPlusArrows(x,45,y,12,input,estado,6); // mostrar menus e setas na posicao certa

		} while ( input != ENTER && input != ESC );

		switch(estado)
		{
		case 0: // reativar cliente
		{
			if (a.hasClientesInativos()) // se existem clientes inactivos
				reativarCliente(a,proceed);
			else
			{
				gotoxy(58,49); cout << "Nao ha clientes inativos na base de dados. ";
				pressEnter();
			}
		}
		break;
		case 1: // modificar cliente
		{
			if (a.hasClientesInativos())
				ModifyRemoveClienteInativo(a,proceed,1);
			else
			{
				gotoxy(58,49); cout << "Nao ha clientes inativos na agencia. ";
				pressEnter();
			}
		}
		break;
		case 2: // mostrar clientes inativos
		{
			if(a.hasClientesInativos())
			{
				a.showClientesInativos(a.getTabelaInativos().getClientesInativos());
				if ( a.getTabelaInativos().getNumInativos() <= 52 )
				{
					gotoxy(10,62); pressEnter();
				}
			}
			else
			{
				gotoxy(58,49); cout << "Nao ha clientes inativos na agencia. ";
				pressEnter();
			}
		}
		break;
		case 3: // pesquisar clientes inativos
		{
			if(a.hasClientesInativos())
			{
				bool didSearch = false;
				Cliente* c = searchCliente(a, proceed, didSearch, false);
				if (c != NULL)
				{
					showCF(c);
					cout << endl;
					pressEnter();
				}
				else if (didSearch && proceed) // se fez pesquisa e nao quis voltar ao menu anterior
				{
					cout << "Nao foram encontrados resultados.\n";
					pressEnter();
				}
			}
			else
			{
				gotoxy(58,49); cout << "Nao ha clientes inativos na agencia. ";
				pressEnter();
			}
		}
		break;
		case 4: // remover cliente inativo
		{
			if (a.hasClientesInativos())
				ModifyRemoveClienteInativo(a,proceed,2);
			else
			{
				gotoxy(58,49); cout << "Nao ha clientes inativos na agencia. ";
				pressEnter();
			}
		}
		break;
		}
	} while (estado != 5);
}

void areaViaturas(Agencia& a)
{
	bool proceed = true;
	int estado = 0, estadoAnterior, input;

	do
	{
		clearScreen();
		do
		{
			int x = 46, y = 28; // coordenadas iniciais das setas

			gotoxy(42,60); cout << "AVISO - QUALQUER OPCAO COM '(*)' ATRAS, DEIXE VAZIA E PRIMA ENTER PARA VOLTAR AO MENU ANTERIOR";
			gotoxy(77,2); cout << "*** AREA DE VIATURAS ***";

            // calculo do y
             if ( estado <= 3 )
                y = y+4*estado;
             else if ( estado >= 4 )
                y = y+4*(estado-4);

			estadoAnterior = estado; // memoriza o estado para ser utilizado para mudar de coluna

			setcolor(9);
			if (estado >= 4)
			{
				x = 128;
				gotoxy(x,y); cout << "<==";
			}
			else
			{
				gotoxy(x,y); cout << "==>";
			}
			setcolor(15);

			showMenu(4);
			gotoxy(0,0);

			input = getArrowKeys(); // le qual a seta direcional pressionada
			estado = stateMachine(8,input, estado); // actualiza o estado da maquina

			if (estado >= 4)
			{
				if (estadoAnterior == 3) // se mudou do estado 3 para o 4
				{ 
					gotoxy(46,40); cout << "   "; // apaga a seta do estado 3
				}
				else if (estadoAnterior == 0) // se mudou do estado 0 para o 7
				{
					gotoxy(46,28); cout << "   "; // apaga a seta do estado 0
				}
				else // esta a mudar entre os estados da coluna a direita
				{
				x = 128;
				gotoxy(x,y); cout << "   "; // apaga a seta do estado que saiu
				}
			}
			else
			{
				if (estadoAnterior == 7) // se mudou do estado 7 para o 0
				{
					gotoxy(128,40); cout << "   "; // apaga seta do estado 7
				}
				else
				{
					gotoxy(x,y); cout << "   "; 
				}
			}
		} while ( input != ENTER && input != ESC );

		switch (estado)
		{
		case NEW_VIAT:
		{
			clearScreen();
			if (addNovaViatura(a,1))
				pressEnter();
		}
		break;
		case CATALOGUE_VIAT: // ver catalogo de viaturas
		{
			areaCatalogo(a);
		}
		break;
		case MODIFY_VIAT: // modificar viatura existente
		{
			if (a.getNumViaturas() != 0)
				ModifyRemoveViatura(a,proceed,1);
			else
			{
				gotoxy(58,49); cout << "Nao ha viaturas registadas na agencia. ";
				pressEnter();
			}
		}
		break;
		case DISPLAY_VIAT: // mostrar todas as viaturas
		{
			if (a.getNumViaturas() != 0)
			{
				a.showViaturas(a.getViaturas());
				if ( a.getNumViaturas() <= 52 )
				{
					gotoxy(10,62); pressEnter();
				}
			}
			else
			{
				gotoxy(58,49); cout << "Nao ha viaturas registadas na agencia. ";
				pressEnter();
			}
		}
		break;
		case SEARCH_VIAT: // pesquisar viatura
		{
			if(a.getNumViaturas() != 0)
			{
				bool didSearch = false;
				Viatura* v = searchViatura(a, proceed,1,didSearch);
				if (v != NULL)
				{
					v->showInfo();
					pressEnter();
				}
				else if (didSearch && proceed)
				{
					cout << "Nao foram encontrados resultados. ";
					pressEnter();
				}
			}
			else
			{
				gotoxy(58,49); cout << "Nao ha viaturas registados na agencia. ";
				pressEnter();
			}
		}
		break;
		case REMOVE_VIAT: // remove viatura
		{
			if (a.getNumViaturas() != 0)
				ModifyRemoveViatura(a,proceed,2);
			else
			{
				gotoxy(58,49); cout << "Nao ha viaturas registados na agencia. ";
				pressEnter();
			}
		}
		break;
		case REPAIR_VIAT: // area de oficinas
		{
			areaOficina(a);
		}
		break;
		}
	} while (estado != VIAT_EXIT);
}

void areaOficina(Agencia& a)
{
	bool proceed = true;
	int estado = 0, input;
	a.autoFinishRepairs();

	do {
		clearScreen();
		do {
			int x = 69, y = 24;

			gotoxy(42,60); cout << "AVISO - QUALQUER OPCAO COM '(*)' ATRAS, DEIXE VAZIA E PRIMA ENTER PARA VOLTAR AO MENU ANTERIOR";
			gotoxy(77,2); cout << "*** AREA DE OFICINAS ***";

			y = (y+4*estado);

			displayMenuPlusArrows(x,45,y,10,input,estado,7);

		} while ( input != ENTER && input != ESC );

		switch(estado)
		{
		case NEW_SHOP: // adicionar nova oficina
		{
			clearScreen();
			if (addNovaOficina(a))
				pressEnter();
		}
		break;
		case SEND_CAR_SHOP: // enviar carro para reparar
		{
			if (a.hasOficinas())
				sendCarToShop(a);
			else
			{
				gotoxy(58,54); cout << "Nao ha oficinas disponiveis na base de dados. ";
				pressEnter();
			}
		}
		break;
		case TERMINATE_REPAIR: // terminar reparacao
		{
			if (a.hasOficinas()) // precisa de ver se mesmo tendo oficinas se tem reparacoes em alguma delas.
				removeReparacao(a,proceed);
			else
			{
				gotoxy(58,54); cout << "Nao ha oficinas disponiveis na base de dados. ";
				pressEnter();
			}
		}
		break;
		case DISPLAY_SHOP: // mostrar oficinas
		{
			if (a.hasOficinas())
			{
				clearScreen();
				cout << endl;
				a.showOficinas();
			}
			else
			{
				gotoxy(58,54); cout << "Nao ha oficinas disponiveis na base de dados. ";
			}
			pressEnter();
		}
		break;
		case MODIFY_SHOP: // modificar oficina
		{
			if (a.hasOficinas())
				ModifyRemoveOficina(a,proceed,1);
			else
			{
				gotoxy(58,54); cout << "Nao ha oficinas disponiveis na base de dados. ";
				pressEnter();
			}
		}
		break;
		case REMOVE_SHOP: // remover oficina
		{
			if (a.hasOficinas())
				ModifyRemoveOficina(a,proceed,2);
			else
			{
				gotoxy(58,54); cout << "Nao ha oficinas disponiveis na base de dados. ";
				pressEnter();
			}
		}
		break;
		}
	} while (estado != SHOP_EXIT);
	}

void areaCatalogo(Agencia& a)
{
	bool proceed = true;
	int estado = 0, input;

	do {
		clearScreen();
		do {
			int x = 67, y = 20;

			gotoxy(42,60); cout << "AVISO - QUALQUER OPCAO COM '(*)' ATRAS, DEIXE VAZIA E PRIMA ENTER PARA VOLTAR AO MENU ANTERIOR";
			gotoxy(77,2); cout << "*** CATALOGO DE VIATURAS ***";

			y = (y+4*estado);

			displayMenuPlusArrows(x,45,y,9,input,estado,7);

		} while ( input != ENTER && input != ESC );

		switch(estado)
		{
		case NEW_CAT:
		{
			clearScreen();
			if (addNovaViatura(a,2))
				pressEnter();
		}
		break;
		case MODIFY_CAT:
		{
			if (!a.catalogoEmpty())
			{
				ModifyRemoveViatura(a,proceed,3);
			}
			else
			{
				gotoxy(58,49); cout << "Nao ha viaturas para venda no catalogo. ";
				pressEnter();
			}
		}
		break;
		case DISPLAY_CAT:
		{
			if (!a.catalogoEmpty())
			{
				clearScreen();
				a.showCatalogo();
				cout << endl;
				pressEnter();
			}
			else
			{
				gotoxy(58,49); cout << "Nao ha viaturas para venda no catalogo. ";
				pressEnter();
			}
		}
		break;
		case SEARCH_CAT:
		{
			if (!a.catalogoEmpty())
			{
				bool didSearch = false;
				Viatura* v = searchViatura(a,proceed,2,didSearch);

				if (proceed)
				if (v != NULL)
				{
						v->showInfo();
						pressEnter();
						cout << endl;
				}
				else if (didSearch && proceed)
				{
					cout << "Nao foram encontrados resultados. ";
					pressEnter();
				}
			}
			else
			{
				gotoxy(58,49); cout << "Nao ha viaturas para venda no catalogo. ";
				pressEnter();
			}
		}
		break;
		case BUY_CAT: // comprar viatura
		{
			if (!a.catalogoEmpty())
			{
				ModifyRemoveViatura(a,proceed,5);
			}
			else
			{
				gotoxy(58,49); cout << "Nao ha viaturas para venda no catalogo. ";
				pressEnter();
			}
		}
		break;
		case REMOVE_CAT: // remover viatura
		{
			if (!a.catalogoEmpty())
			{
				ModifyRemoveViatura(a,proceed,4);
			}
			else
			{
				gotoxy(58,49); cout << "Nao ha viaturas para venda no catalogo. ";
				pressEnter();
			}
		}
		break;
		}
	} while (estado != CAT_EXIT);
}

void areaAlugueres(Agencia& a, vector<Aluguer*>& terminamHoje)
{
	int estadoAtual = 0, estados, input;
	bool proceed = true, leave = false, terminarHoje;

	do {
		clearScreen();
		estados = 7;
		terminarHoje = false;
		if (a.hasFinishingToday())
			if (!terminamHoje.empty() )
			{
				terminarHoje = true;
				estados = 8;
			}
		do {
			int x = 66, y = 23;

			gotoxy(42,60); cout << "AVISO - QUALQUER OPCAO COM '(*)' ATRAS, DEIXE VAZIA E PRIMA ENTER PARA VOLTAR AO MENU ANTERIOR";
			gotoxy(77,2); cout << "*** AREA DE ALUGUERES ***";

			y = (y+4*estadoAtual); // calculo de coordenada y de acordo com o estado atual

			setcolor(9); gotoxy(x,y); cout << "==>";
			gotoxy(x+45,y); cout << "<=="; setcolor(15);
			showFrames();

			int	x_menu = 70,y_menu;
			gotoxy(x_menu,22); cout << "                                       ";
			gotoxy(x_menu,23); cout << "|             Novo aluguer             |";
			gotoxy(x_menu,24); cout << "                                       ";
			gotoxy(x_menu,26); cout << "                                       ";
			gotoxy(x_menu,27); cout << "|      Modificar aluguer existente     |";
			gotoxy(x_menu,28); cout << "                                       ";
			gotoxy(x_menu,30); cout << "                                       ";
			gotoxy(x_menu,31); cout << "|       Mostrar todos os alugueres     |";
			gotoxy(x_menu,32); cout << "                                       ";
			gotoxy(x_menu,34); cout << "                                       ";
			gotoxy(x_menu,35); cout << "|           Pesquisar aluguer          |";
			gotoxy(x_menu,36); cout << "                                       ";
			gotoxy(x_menu,38); cout << "                                       ";
			gotoxy(x_menu,39); cout << "|           Cancelar aluguer           |";
			gotoxy(x_menu,40); cout << "                                       ";
			gotoxy(x_menu,42); cout << "                                       ";
			gotoxy(x_menu,43); cout << "|           Finalizar aluguer          |";
			gotoxy(x_menu,44); cout << "                                       ";
			y_menu = 44;
			if (a.hasFinishingToday())
				if (!terminamHoje.empty())
				{
					y_menu += 2;
					setcolor(4);
					gotoxy(x_menu,y_menu);   cout << "                                       ";
					gotoxy(x_menu,++y_menu); cout << "|       Alugueres a terminar hoje      |";
					gotoxy(x_menu,++y_menu); cout << "                                       ";
					setcolor(15);
				}
			y_menu += 2;
			gotoxy(x_menu,y_menu);   cout << "                                       ";
			gotoxy(x_menu,++y_menu); cout << "|       VOLTAR AO MENU PRINCIPAL       |";
			gotoxy(x_menu,++y_menu); cout << "                                       ";
			gotoxy(0,0);

			input = getArrowKeys();
			estadoAtual = stateMachine (estados,input,estadoAtual);

			gotoxy(x,y); cout << "   ";
			gotoxy(x+45,y); cout << "   ";

		} while ( input != ENTER && input != ESC );

		if (a.hasFinishingToday())
		{
			if (!terminamHoje.empty() && estadoAtual == 7)
				leave = true;
		}
		else if (estadoAtual == 6)
			leave = true;


		switch (estadoAtual)
		{
		case NEW_ALUG: // novo aluguer
		{
			if (a.getNumFuncionarios() == 0)
			{
				gotoxy(58,56); cout << "Nao ha funcionarios registados na agencia. ";
				pressEnter();
			}
			else if (a.getNumViaturas() == 0)
			{
				gotoxy(58,56); cout << "Nao ha viaturas registados na agencia. ";
				pressEnter();
			}
			else if (a.getNumViaturasDisponiveis() == 0)
			{
				gotoxy(58,56); cout << "Nao ha viaturas disponiveis na agencia. ";
				pressEnter();
			}
			else if (a.getNumClientes() == 0)
			{
				gotoxy(58,56); cout << "Noa ha clientes registados na agencia. ";
				pressEnter();
			}
			else
			{
				clearScreen();
				if (addNovoAluguer(a))
					pressEnter();
			}
		}
		break;
		case MODIFY_ALUG: // modificar aluguer
		{
			if (a.getNumAlugueresActivos() != 0)
				ModifyCancelFinishAluguer(a,proceed,1);
			else
			{
				gotoxy(58,56); cout << "Nao ha alugueres activos na agencia. ";
				pressEnter();
			}
		}
		break;
		case DISPLAY_ALUG: // mostrar alugueres
		{
			if (a.getNumAlugueresActivos() != 0)
			{
				a.showAlugueres(a.getAlugueres());
				if ( a.getNumAlugueresActivos() <= 52 )
				{
					gotoxy(10,62); pressEnter();
				}
			}
			else
			{
				gotoxy(58,56); cout << "Nao ha alugueres activos na agencia. ";
				pressEnter();
			}
		}
		break;
		case SEARCH_ALUG: // pesquisar aluguer
		{
			if(a.getNumAlugueresActivos() != 0)
			{
				bool didSearch = false;
				Aluguer* al = searchAluguer(a, proceed, didSearch);
				if (al != NULL)
				{
					al->showInfo();
					pressEnter();
					cout << endl;
				}
				else if (proceed && didSearch)
				{
					cout << "Nao foram encontrados resultados. ";
					pressEnter();
				}
			}
			else
			{
				gotoxy(58,56); cout << "Nao ha alugueres activos na agencia. ";
				pressEnter();
			}
		}
		break;
		case CANCEL_ALUG: // cancelar aluguer
		{
			if (a.getNumAlugueresActivos() != 0)
				ModifyCancelFinishAluguer(a,proceed,2);
			else
			{
				gotoxy(58,56); cout << "Nao ha alugueres activos na agencia. ";
				pressEnter();
			}
		}
		break;
		case FINAL_ALUG: // finalizar aluguer
		{
			if (a.getNumAlugueresActivos() != 0)
				ModifyCancelFinishAluguer(a,proceed,3);
			else
			{
				gotoxy(58,56); cout << "Nao ha alugueres activos na agencia. ";
				pressEnter();
			}
		}
		break;
		case DUE2DAY_ALUG: // visualizar alugueres que terminam na data atual
		{
			if (terminarHoje)
			{
				a.showAlugueres(terminamHoje);
				gotoxy(10,62); pressEnter();
			}
		}
		break;
		}
	} while (!leave);
}
