/*
 * Oficina.h
 *
 *      Author: migueloliveira
 */

#ifndef OFICINA_H_
#define OFICINA_H_

#include <string>
#include <queue>
#include <vector>
#include "Viatura.h"

#include <iostream>
using namespace std;

/**
 * @brief Classe que representa os objectos do tipo Oficina
 */

class Reparacao {
	static int numReparacoes;
	int ID;
	int ID_viatura;
	string marcaModeloMatricula;
	int tipoReparacao;
	int tempoReparacao;
	Data horaTermina;
public:
	Reparacao() {}
	/**
	 * @brief Construtor de objecto Reparacao
	 *
	 * Construtor de objeto Reparacao, recebe 2 argumentos,
	 * a viatura que esta a ser reparada e o tipo de reparacao
	 *
	 * @param Viatura* viat Viatura que vai sofrer a reparacao
	 * @param int& tipoReparacao inteiro que permite ver quanto tempo demora a reparacao
	 */
	Reparacao (Viatura* viat, int& tipoReparacao);

	/**
	 * @brief Retorna o ID da Reparacao
	 * @return int ID
	 */
	int getID() const;

	/**
	 * @brief Retorna o numero de objetos Reparacoes ja criados
	 * @return int numReparacoes
	 */
	static int getNumReparacoes();

	/**
	 * @brief Retorna o tempo da reparacao
	 * @return int tempoReparacao
	 */
	int getTempoReparacao() const;

	/**
	 * @brief Retorna o ID da viatura a que corresponde a reparacao
	 * @return int ID_viatura
	 */
	int getIDviatura() const;

	/**
	 * @brief Retorna o objeto Data que contem a data a que termina a reparacao
	 * @return Data& data a que termina a reparacao
	 */
	Data& getHoraTermina();

	/**
	 * @brief Retorna o tipo da reparacao
	 * @return int tipoReparacao
	 */
	int getTipo() const;

	/**
	 * @brief Retorna a string que contem a info da marca, modelo e matricula da viatura
	 * @return const string& marcaModeloMatricula
	 */
	const string& getMarcaModeloMatricula () const;

	/**
	 * @brief Recebe um inteiro, define o numReparacoes como esse inteiro
	 *
	 * @param int numero novo de reparacoes
	 */
	static void setNumReparacoes(int n);

	/**
	 * @brief Recebe um objeto Data, iguala a hora de terminar a essa
	 *
	 * @param Data& nova data para terminar reparacao
	 */
	void setHoraTermina(Data& d);

	/**
	 * @brief Recebe um inteiro, define o ID da reparacao
	 *
	 * @param int ID a definir
	 */
	void setID(int ID);

	/**
	 * @brief Recebe um inteiro, define o ID da viatura a ser reparada
	 *
	 * @param int ID da viatura
	 */
	void setIDviatura(int ID);

	/**
	 * @brief Recebe uma string com a marca,modelo e matricula da viatura
	 *
	 * @param string marca,modelo matricula da viatura
	 */
	void setMMM(const string& mmm);

	/**
	 * @brief Recebe um inteiro com o tipo de reparacao, define o tempo de reparacao
	 *
	 * @param int ID tipo de reparacao
	 */
	void setTempo(int tipo);

	bool operator < (const Reparacao& r2) const;

};


typedef priority_queue<Reparacao> HEAP_REPAIR;

/*
 * Classe que representa os objetos do tipo Oficina
 */

class Oficina {
	static int numOficinas;
	int ID;
	string nome;
	string localizacao;
	int distancia;
	int ocupacao_atual;
	int ocupacao_maxima;

	HEAP_REPAIR reparacoes;

public:
	Oficina() { ID = -1; }

	/**
	 * @brief Construtor de objecto Oficina
	 *
	 * Construtor de objeto Oficina, recebe 4 argumentos,
	 * o nome da oficina, a localizacao, a distancia ate a agencia
	 * e o numero de funcionarios
	 *
	 * @param const string& nome da oficina
	 * @param const string& localizacao da oficina
	 * @param const int& distancia da oficina
	 * @param int& numero de funcionarios
	 */
	Oficina(const string& nome, const string& localizacao, const int& distancia, int& numeroFuncionarios); // de acordo com o numero de funcionarios, a ocupacao maxima e menor ou maior
	~Oficina();

	/**
	 * @brief Retorna o nome da oficina
	 * @return const string& nome oficina
	 */
	const string& getNome() const;

	/**
	 * @brief Retorna a localizacao da oficina
	 * @return const string& localizacao
	 */
	const string& getLocalizacao() const;

	/**
	 * @brief Retorna o numero de objetos oficinas ja criados
	 * @return int numOficinas criadas ate agora
	 */
	static int getNumOficinas();

	/**
	 * @brief Recebe um inteiro, define o numero de oficinas ja criadas
	 * @param int numeroOficinas
	 */
	static void setNumOficinas (int n);

	/**
	 * @brief Retorna a distancia da oficina
	 * @return const int& distancia
	 */
	const int& getDistancia() const;

	/**
	 * @brief Retorna a ocupacao atual da oficina
	 * @return int ocupacao_atual
	 */
	int getOcupacao() const;

	/**
	 * @brief Retorna a disponibilidade atual da oficina
	 * @return int disponibilidade
	 */
	int getDisponibilidade () const;

	/**
	 * @brief Retorna o ID da oficina
	 * @return int ID oficina
	 */
	int getID() const;

	/**
	 * @brief Retorna a Reparacao com o ID igual ao recebido
	 * @param int ID de reparacao
	 * @return Reparacao
	 */
	Reparacao getReparacaoById(int ID);

	/**
	 * @brief Define o nome da oficina
	 * @param string& nome
	 */
	void setNome(string& nome);

	/**
	 * @brief Define a localizacao da oficina
	 * @param string& localizacao
	 */
	void setLocalizacao (string& local);

	/**
	 * @brief Define a distancia
	 * @param int distancia
	 */
	void setDistancia(int dist);

	/**
	 * @brief Atualiza a ocupacao atual, recebe um inteiro com as horas a diminuir
	 * @param int ocupacao a retirar
	 */
	void updateOcupacaoAtual (int ocupacao);

	/**
	 * @brief Define a ocupacao maxima da oficina de acordo com o numero de funcionarios
	 * @param int numero de funcionarios
	 */
	void setOcupacaoMaxima (int numFuncionarios);

	/**
	 * @brief Anula a criacao de uma oficina.
	 *
	 * Qunando uma oficina e criada, mas depois nao e valida e
	 * necessario diminuir o numero de oficinas criadas.
	 *
	 */
	static void anularOficina ();

	/**
	 * @brief Termina automaticamente as reparacoes que ja foram realizadas
	 *
	 * Recebe uma Data que corresponde a data atual da execucao do programa
	 * e um vector de inteiros para preencher com os IDs das viaturas que
	 * ja foram reparados. Ve se a data de terminar da reparacao e menor que
	 * a data atual.
	 *
	 * @param Data& data atual
	 * @param vector<int>& viaturasID vector a preencher com os IDs das viaturas
	 */
	void autoFinishRepairs(Data& atual, vector<int>& viaturasID);

	/**
	 * @brief Adiciona uma nova reparacao a oficina
	 * @param const Reparacao& nova reparacao a adicionar
	 */
	void addReparacao(const Reparacao& novaReparacao);

	/**
	 * @brief Devolve true se a oficina tiver reparacoes na fila, false se nao
	 * @return bool
	 */
	bool temReparacoes() const;

	/**
	 * @brief Grava a informacao da oficina num ficheiro
	 * @param fstream& outFile ficheiro onde vai gravar os dados
	 */
	void saveInfo(fstream& outFile) const;

	/**
	 * @brief Carrega os dados para o oficina de um ficheiro
	 * @param fstream& inFile ficheiro de onde vai ler os dados
	 */
	void loadInfo(fstream& inFile);


	bool operator <(const Oficina& o2) const;

	// Excecoes utilizadas por algumas funcoes da class Oficina
	class UltrapassadaOcupacaoMaxima {};
	class FaltaMaoDeObra {};
	class ReparacaoNaoExistente {};

	friend ostream& operator << (ostream& out, const Oficina& of);
};

class ReparacaoNaoExiste {
	int id;
public:
	ReparacaoNaoExiste (int id) : id(id) {}
	int getID() const {return id;}
};

#endif /* OFICINA_H_ */
