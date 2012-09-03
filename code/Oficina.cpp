/*
 * Oficina.cpp
 *      Author: migueloliveira
 */

#include "Oficina.h"

int Reparacao::numReparacoes = 0;

// Construtor de objetos Reparacao

Reparacao::Reparacao(Viatura* viat, int& tipoReparacao) : tipoReparacao(tipoReparacao)
{
	ID = ++numReparacoes;

	// calcula o tempo de reparacao de acordo com o tipo
	switch(tipoReparacao)
	{
	case 1:
		tempoReparacao = 4;
		break;
	case 2:
	case 4:
	case 5:
	case 7:
		tempoReparacao = 1;
		break;
	case 3:
		tempoReparacao = 2;
		break;
	case 6:
		tempoReparacao = 3;
		break;
	}

	horaTermina =returnDataActual();

	if ( (horaTermina.getHora()+tempoReparacao) <= 23) // fica no mesmo dia
		horaTermina.setHora(horaTermina.getHora()+tempoReparacao);
	else
	{
		// nao interessa meter o dia, mes ou ano certo
		// so interessa se esta no mesmo dia ou nao
		horaTermina.setDia(horaTermina.getDia()+1);
		horaTermina.setHora( ((horaTermina.getHora()+tempoReparacao) - 23) - 1 );
	}

	// constroi a string marcaModeloMatricula
	ID_viatura = viat->getID();
	marcaModeloMatricula = viat->getMarca();
	marcaModeloMatricula += " ";
	marcaModeloMatricula += viat->getModelo();
	marcaModeloMatricula += ", matricula ";
	marcaModeloMatricula += viat->getMatricula();
	viat->setDisponivel(false); // o carro nao esta disponivel durante a reparacao
}

int Reparacao::getID() const
{
	return ID;
}

int Reparacao::getNumReparacoes()
{
	return numReparacoes;
}

int Reparacao::getTempoReparacao() const
{
	return tempoReparacao;
}

int Reparacao::getIDviatura() const
{
	return ID_viatura;
}

Data& Reparacao::getHoraTermina()
{
	return horaTermina;
}

int Reparacao::getTipo() const
{
	return tipoReparacao;
}

const string& Reparacao::getMarcaModeloMatricula () const
{
	return marcaModeloMatricula;
}

void Reparacao::setNumReparacoes(int n)
{
	numReparacoes = n;
}

void Reparacao::setHoraTermina(Data& d)
{
	horaTermina = d;
}

void Reparacao::setID(int ID)
{
	this->ID = ID;
}

void Reparacao::setIDviatura(int ID)
{
	ID_viatura = ID;
}

void Reparacao::setMMM(const string& mmm)
{
	marcaModeloMatricula = mmm;
}

void Reparacao::setTempo(int tipo)
{
	tipoReparacao = tipo;

	// calcula o tempo de reparacao de acordo com o tipo;
	switch(tipo)
	{
	case 1:
		tempoReparacao = 4;
		break;
	case 2:
	case 4:
	case 5:
	case 7:
		tempoReparacao = 1;
		break;
	case 3:
		tempoReparacao = 2;
		break;
	case 6:
		tempoReparacao = 3;
		break;
	}
}

bool Reparacao::operator < (const Reparacao& r2) const
{
	return (tempoReparacao < (r2.getTempoReparacao()) );
}


/**
 * OFICINAS
 */

int Oficina::numOficinas = 0;

Oficina::Oficina(const string& nome, const string& localizacao, const int& distancia, int& numeroFuncionarios) : nome(nome), localizacao(localizacao), distancia(distancia)
{
	ID = ++numOficinas;
	ocupacao_atual = 0;

	// cada operario fornece 8 horas de ocupacao
	ocupacao_maxima = 8*numeroFuncionarios;
}

Oficina::~Oficina()
{ }

const string& Oficina::getNome() const
{
	return nome;
}

const string& Oficina::getLocalizacao() const
{
	return localizacao;
}

int Oficina::getNumOficinas()
{
	return numOficinas;
}

void Oficina::setNumOficinas (int n)
{
	numOficinas = n;
}

const int& Oficina::getDistancia() const
{
	return distancia;
}

int Oficina::getOcupacao() const
{
	return ocupacao_atual;
}

int Oficina::getDisponibilidade() const
{
	return (ocupacao_maxima - ocupacao_atual);
}

int Oficina::getID() const
{
	return ID;
}

Reparacao Oficina::getReparacaoById(int ID)
{
	vector<Reparacao> temp;

	// percorre todas as reparacoes da oficina
	while(!reparacoes.empty())
	{
		Reparacao r = reparacoes.top();
		reparacoes.pop();

		// se encontrar a certa
		if (r.getID() == ID)
		{
			// volta a colocar as reparacoes de temp para a fila
			for (size_t i = 0; i < temp.size(); i++)
				reparacoes.push(temp[i]);

			// retira-a da fila e devolve-a
			return r;
		}
		else
			temp.push_back(r);
	}

	// se nao encontrou, mete as reparacoes na fila
	for (size_t i = 0; i < temp.size(); i++)
		reparacoes.push(temp[i]);

	throw ReparacaoNaoExistente();
}

void Oficina::setNome(string& nome_)
{
	nome = nome_;
}

void Oficina::setLocalizacao(string& local)
{
	localizacao = local;
}

void Oficina::setDistancia (int dist)
{
	distancia = dist;
}

void Oficina::updateOcupacaoAtual (int ocupacao)
{
	ocupacao_atual -= ocupacao;
}

// funcao utilizada para alterar o numero de funcionarios da oficina
void Oficina::setOcupacaoMaxima (int numFuncionarios)
{
	// nao deixa alterar para um numero inferior ao necessario para a ocupacao atual
	if ( (numFuncionarios * 8) < ocupacao_atual )
		throw FaltaMaoDeObra();
	else
		ocupacao_maxima = (numFuncionarios*8);
}

void Oficina::anularOficina ()
{
	numOficinas--;
}

void Oficina::autoFinishRepairs(Data& atual, vector<int>& viaturasID)
{
	vector<Reparacao> temp;

	// percorre todas as reparacoes

	while (!reparacoes.empty())
	{
		Reparacao r = reparacoes.top();
		reparacoes.pop();

		// compara a data para terminar e a data atual para ver quais devem terminar

		if (r.getHoraTermina().getDia() == atual.getDia()) // se esta no mesmo dia
		{
			if (r.getHoraTermina().getHora() <= atual.getHora()) // ja acagou a reparacao
			{
				updateOcupacaoAtual (r.getTempoReparacao());
				viaturasID.push_back(r.getIDviatura());
			}
			else
				temp.push_back(r);
		}
		else
		{
			if ( r.getHoraTermina().getDia() < atual.getDia() )
			{
				updateOcupacaoAtual (r.getTempoReparacao());
				viaturasID.push_back(r.getIDviatura());
			}
			else if ( r.getHoraTermina().getDia() > atual.getDia() && 
						r.getHoraTermina().getMes() < atual.getMes() &&
						r.getHoraTermina().getAno() < atual.getAno() )
			{
				updateOcupacaoAtual (r.getTempoReparacao());
				viaturasID.push_back(r.getIDviatura());
			}
			else
				temp.push_back(r);
		}
	}

	// volta a meter as reparacoes que ainda nao acabaram na fila
	for (size_t i = 0; i < temp.size(); i++)
		reparacoes.push(temp[i]);
}

void Oficina::addReparacao (const Reparacao& novaReparacao)
{
	// adiciona a nova reparacao a oficina, caso esta tenha disponibilidade

	if ( getDisponibilidade() < (novaReparacao.getTempoReparacao()) )
		throw UltrapassadaOcupacaoMaxima();
	else
	{
		reparacoes.push(novaReparacao);
		ocupacao_atual += (novaReparacao.getTempoReparacao());
	}
}

bool Oficina::temReparacoes() const
{
	 return (!reparacoes.empty());
}

void Oficina::saveInfo(fstream& outFile) const
{
	outFile << ID << '\n';
	outFile << nome << '\n';
	outFile << localizacao << '\n';
	outFile << distancia << '\n';
	outFile << ocupacao_atual << ' ' << ocupacao_maxima << '\n';
	outFile << reparacoes.size() << '\n';

	HEAP_REPAIR buffer = reparacoes;

	// guarda a info de todas as reparacoes

	while (!buffer.empty())
	{
		outFile << buffer.top().getID() << '\n';
		outFile << buffer.top().getIDviatura() << '\n';
		outFile << buffer.top().getMarcaModeloMatricula() << '\n';
		outFile << buffer.top().getTipo() << '\n';
		buffer.top().getHoraTermina().saveData(outFile);
		buffer.pop();
	}
}

void Oficina::loadInfo(fstream& inFile)
{
	string mmm;
	int numRepairs, idR, idViat, tipo;

	inFile >> ID; inFile.ignore(1,'\n');
	getline(inFile, nome);
	getline(inFile, localizacao);
	inFile >> distancia; inFile.ignore(1,'\n');
	inFile >> ocupacao_atual >> ocupacao_maxima; inFile.ignore(1,'\n');
	inFile >> numRepairs; inFile.ignore(1,'\n');

	// enquanto houver reparacoes para carregar

	while ( numRepairs > 0 )
	{
		Reparacao r;
		inFile >> idR; inFile.ignore(1,'\n');
		r.setID(idR);
		inFile >> idViat; inFile.ignore(1,'\n');
		r.setIDviatura(idViat);
		getline(inFile,mmm); r.setMMM(mmm);
		inFile >> tipo; inFile.ignore(1,'\n');
		Data d; d.loadData(inFile); r.setHoraTermina(d);
		r.setTempo(tipo);
		reparacoes.push(r);
		numRepairs--;
	}
}

bool Oficina::operator <(const Oficina& o2) const
{
	if ( ocupacao_atual == (o2.getOcupacao()) )
		return distancia > o2.getDistancia();
	else
		return ocupacao_atual > o2.getOcupacao();
}


ostream& operator << (ostream& out, const Oficina& of)
{
	out << "ID: " << of.ID;
	out <<" Oficina \"" << of.nome << "\", localizada em " << of.localizacao << ", dista " << of.distancia << " km da Agencia.\n";
	out << "Possui uma ocupacao maxima de " << of.ocupacao_maxima << " horas, estando com uma ocupacao atual de " << of.ocupacao_atual << " horas.\n";
	if (of.getOcupacao() != 0) // existem reparacoes na oficina
	{
		out << "Reparacoes:\n";
		HEAP_REPAIR buffer = of.reparacoes;

		while (!buffer.empty())
		{
			out << endl << "  -> ID: " << buffer.top().getID() << ", ID viatura: ";
			out << buffer.top().getIDviatura() << ", " << buffer.top().getMarcaModeloMatricula() << ", ";
			switch(buffer.top().getTipo())
			{
			case 1:
				out << "Revisao programada da marca (4 horas).";
				break;
			case 2:
				out << "Inspeccao periodica obrigatoria (1 hora).";
				break;
			case 3:
				out << "Mudar oleo, filtro e liquido da refrigeracao (2 horas).";
				break;
			case 4:
				out << "Recarregadr ar condicionado e/ou reparar fugas (1 hora).";
				break;
			case 5:
				out << "Substituir bateria (1 hora).";
				break;
			case 6:
				out << "Substituir pastilhas dos travoes e/ou discos (3 horas).";
				break;
			case 7:
				out << "Alinhar a direccao (1 hora).";
				break;
			}
			out << endl;
			buffer.pop();
		}
	}
	return out;
}

