#ifndef TAD_HA
#define TAD_HA
	#include "TAD_GERAL.h"

	typedef struct NO* ArvBin;

	struct NO{
		TipoItem item;
		struct NO *esq;
		struct NO *dir;
	};

	//	Função recursíva para percorrer a árvore dada em pré ordem procurando por uma chave igual
	//	a dada retorna 1 se achar, e 0 quando chegar a uma folha sem achar a palavra, se achar
	//	adiciona 1 ao contador da palavra.
	int PreOrdem_ArvBin(ArvBin *raiz, TipoItem item, int numero_do_doc);


	//	Função que chama a PreOrdem_ArvBin para buscar por uma palavra dada em todas posições do
	//	Hash Arvore retorna 1 se achar a palavra dada e 0 se não.
	int Pesquisa_na_arvore(TipoItem item, ArvBin* raiz[], int numero_do_doc);


	//	Função que adiciona na árvore um item dado levando a ordem alfabética como critério de
	//	direcionamento para a adição. Retorna 0 se a adição não foi sucedida e 1 caso contrário.
	int Insere_ArvBin (ArvBin *raiz, TipoItem x, int numero_do_doc);


	//	Função recursíva para percorer a árvore  dada em pré ordem para mostrar na tela as chaves
	//	e as frêquencias das mesmas.
	int PreOrdem_ArvBin_para_mostrar(ArvBin *raiz);

	
	//	Função que chama a PreOrdem_ArvBin_para_mostrar dando como argumento cada árvore de cada
	//	posição do Hash Arvore.
	void Mostra_arvore(ArvBin* raiz[]);


	//	Função que aloca memória para a raiz de cada espaço do Hash Árvore.
	void Inicializa_Arvores(ArvBin* raiz[]);


	//	Chama as funções para criar o Dicionario com Hash Arvore.
	void CriaIndiceInvertidoHA();

#endif
