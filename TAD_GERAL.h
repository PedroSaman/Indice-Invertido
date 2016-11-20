#ifndef TAD_GERAL
#define TAD_GERAL
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	//	C define o tamanho máximo das palavras(parametro recebido pelo terminal).
	// 	N define a quantidade de arquivos que serão lidos .
	//	Estas constanstes que são realmente usadas no programa.
	
	int C, N;

	//	Não sei fazer de um jeito melhor \/ foi necessário assim para conseguir
	//	criar os structs utilizados no programa.
	//	C1 será o tamanho maximo das palavras.
	#define C1 50
	//	N1 será o máximo de arquivos texto que podem ser lidos.
	#define N1 50

	// Tamanho do HASH(não sei como fazer isso de forma melhor)
	#define M 10000

	typedef char TipoChave[C1];
	
	typedef unsigned TipoPesos[C1];

	typedef struct{
		TipoChave Chave;
		int qnt_aparicoes[N1];
	}TipoItem;

	//	Gera os pesos para cada letra da palavra, números aleatórios.
	void GeraPesos(TipoPesos p, int n);

	// Transforma a chave string em int com os pesos dados.
	int Transformacao_de_chaves(TipoChave Chave, TipoPesos p);

	//	Função que recebe string e retorna 0 se for uma pontuação e 1 caso 
	//	contrario.
	int strPontos(char palavra[]);

	//	Função que recebe string verifica se há pontuação ao final da palavra
	//	se sim tira tal pontuação, então completa com espaços em branco até C 
	//	caracteres se já não tiver.
	void concerta_palavra(char palavra[]);

	//	Funcao que transforma MAIUSCULAS em minusculas.
	void NoCaps(char palavra[]);

#endif
