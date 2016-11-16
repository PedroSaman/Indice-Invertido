#ifndef TAD
#define TAD

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

	// Tamanho do dicionário(não sei como fazer isso de forma melhor)
	#define M 10000

	// Funções para o dicionario com endereçamento aberto
	typedef unsigned int Apontador;

	typedef char TipoChave[C1]; 

	typedef unsigned TipoPesos[C1];
		
	typedef struct{
		TipoChave Chave;
		int qnt_aparicoes[N1];
	}TipoItem;

	typedef unsigned int Indice;

	typedef TipoItem TipoDicionario[M];

	//	Gera os pesos para cada letra da palavra, números aleatórios.
	void GeraPesos(TipoPesos p, int n);

	// Transforma a chave string em int com os pesos dados.
	int Transformacao_de_chaves(TipoChave Chave, TipoPesos p);

	// 	Faz a pesquisa no dicionario, retorna a posição caso a palavra dada 
	//	exista no dicionario ou o tamanho do dicionario caso contrario.
	Apontador Pesquisa(TipoChave Ch, TipoPesos p, TipoDicionario T, int numero_do_doc);

	//	Insere o item dado no dicionario dado, chama a função pesquisa para 
	//	verificar se a palavra já existe no dicionario, chama a função de
	//	transformação para adicionar no dicionario, não permite adicionar mais
	// 	do que o dicionario tem espaço.
	void Insere(TipoItem x, TipoPesos p, TipoDicionario T, int numero_do_doc);

	//	Cria o dicionario com todas posições vazias e com frequência 0.
	void Inicializa_DicionarioHS(TipoDicionario T);

	//	Mostra, após montar o dicionario com a coleção de arquivos, todas
	// 	entradas e respectivas frequências.
	void Mostra_Resultado(TipoDicionario T);

	//	Chama as funções para criar o Dicionario com Hash simples.
	void CriaIndiceInvertidoHS();

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