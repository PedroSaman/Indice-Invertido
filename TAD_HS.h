#ifndef TAD_HS
#define TAD_HS
	#include "TAD_GERAL.h"
// PRIMITIVAS PARA O DICIONARIO COM HASH SIMPLES.

	typedef unsigned int Apontador; 

	typedef unsigned int Indice;

	typedef TipoItem TipoDicionario[M];

	// 	Faz a pesquisa no dicionario, retorna a posição caso a palavra dada 
	//	exista no dicionario ou o tamanho do dicionario caso contrario.
	Apontador Pesquisa(TipoChave Ch, TipoPesos p, TipoDicionario T, int numero_do_doc);


	//	Insere o item dado no dicionario dado, chama a função pesquisa para 
	//	verificar se a palavra já existe no dicionario, chama a função de
	//	transformação para adicionar no dicionario, não permite adicionar mais
	// 	do que o dicionario tem espaço.
	void Insere(TipoItem x, TipoPesos p, TipoDicionario T, int numero_do_doc);


	//	Cria o dicionario com todas posições vazias e com frequência 0.
	void Inicializa_Dicionario(TipoDicionario T);


	//	Mostra, após montar o dicionario com a coleção de arquivos, todas
	// 	entradas e respectivas frequências.
	void Mostra_Resultado(TipoDicionario T);


	//	Chama as funções para criar o Dicionario com Hash simples.
	void CriaIndiceInvertidoHS();


#endif
