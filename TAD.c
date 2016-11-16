#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "TAD.h"

int strPontos(char palavra[]){
	
	if ((palavra[0] == ',') || (palavra[0] == '.') || (palavra[0] == '?') || (palavra[0] == '!') || (palavra[0] == '-'))
		return 0;
	
	return 1;
} // OK

void concerta_palavra(char palavra[]){
	int i,tamanho;
	char *blank = " ";
	char word[C];
	int index = 0;

	while(palavra[index] != '\0'){
		if ((palavra[index] == ',') || (palavra[index] == '.') || (palavra[index] == '?') || (palavra[index] == '!'))
			palavra[index] = '\0';
			
		index++;
	}

	tamanho = strlen(palavra);

	while (tamanho < C)
	{
		strcat(palavra, blank);
		tamanho++;
	}
	if(tamanho > C){
		for(i=0; i<C; i++){
			word[i] = palavra[i];
		}
		strcpy(palavra,word);
		palavra[C] = '\0';
	}
}// OK

void NoCaps(char palavra[]){
	int index = 0;
	while(palavra[index] != '\0'){
		if((palavra[index] >= 'A') && (palavra[index] <= 'Z')){
			palavra[index] += 32;
		}
		index++;
	}
}// OK

int Transformacao_de_chaves(TipoChave Chave, TipoPesos p){  
	
	int i;
	unsigned int Soma = 0;
	int comp = strlen(Chave);
	
	for(i = 0; i < comp; i++)
		Soma += (unsigned int)Chave[i] * p[i]; 
  	
  	return (Soma % M); 
}// OK

Apontador Pesquisa(TipoChave Ch, TipoPesos p, TipoDicionario T, int numero_do_doc){ 

	int j;
	unsigned int i = 0;
	unsigned int Inicial;
	char Vazio[C];

	for(j = 0; j<C; j++){
		Vazio[j]='!';
	}
	Vazio[C] = '\0';
	
	Inicial = Transformacao_de_chaves(Ch, p);
	
	while ((strcmp ( T[(Inicial + i) % M].Chave, Ch) != 0)  && (i < M)){
		i++;
	}

	if (strcmp (T[(Inicial + i) % M].Chave,Ch) == 0){
		T[((Inicial + i) % M)].qnt_aparicoes[numero_do_doc] +=1;
		return ((Inicial + i) % M);
	}
	else {
		return M;/*Pesquisa sem sucesso*/ 
	}
}// OK 

void Insere(TipoItem x, TipoPesos p, TipoDicionario T, int numero_do_doc){    
	
	unsigned int i = 0;         
	unsigned int Inicial;
	char Vazio[C];

	for(i = 0; i<C; i++){
		Vazio[i]='!';
	}
	Vazio[C] = '\0';
	
	if (Pesquisa(x.Chave, p, T, numero_do_doc) < M)  {
		// Já existe tal palavra
		return;
	}

	Inicial = Transformacao_de_chaves(x.Chave, p);
	
	while ((strcmp(T[(Inicial + i) % M].Chave,Vazio) != 0)  &&	(i < M)) 
		i++;
  	if (i < M){
  		strcpy (T[(Inicial + i) % M].Chave, x.Chave);
  		T[(Inicial + i) % M].qnt_aparicoes[numero_do_doc] = 1;
  	} 
  	else 
		printf("Tabela cheia\n"); 
}// OK


void GeraPesos(TipoPesos p, int n){ 

/* Gera valores randomicos entre 1 e 10.000 */ 
	int i; 
	struct timeval semente; 

	gettimeofday(&semente,NULL);

	srand((int)(semente.tv_sec + 1000000*semente.tv_usec)); 
	for (i = 0; i < n; i++)
		p[i] =  1+(int) (10000.0*rand()/(RAND_MAX+1.0)); 
}// OK

void Inicializa_DicionarioHS(TipoDicionario T){  
	
	int i,j; 
	char Vazio[C];

	for(i = 0; i<C; i++){
		Vazio[i]='!';
	}
	Vazio[C]= '\0';
	
	for (i = 0; i < M; i++){
		memcpy(T[i].Chave, Vazio, C1);
		for(j=0; j<N; j++) {
			T[i].qnt_aparicoes[j]=0;
		}
	}
}// OK

void Mostra_Resultado(TipoDicionario T){
	
	char Vazio[C];
	int i, j;

	for(i = 0; i<C; i++){
		Vazio[i]='!';
	}
	Vazio[C] = '\0';

	for (i = 0; i < M; i++){
		if(strcmp(T[i].Chave,Vazio)){
			printf("%s\t",T[i].Chave);
	
			for(j=0; j< N; j++){
				if((T[i].qnt_aparicoes[j]) != 0){
					if((T[i].qnt_aparicoes[j])>1){
						printf("aparece %d vezes no arquivo %d |",T[i].qnt_aparicoes[j], j+1);
					}else {
						printf("aparece %d vez   no arquivo %d |",T[i].qnt_aparicoes[j], j+1);
					
					}
				}
			}
			printf("\n");
		}
	}
}// OK


void CriaIndiceInvertidoHS(){

	int Numero_de_arquivos, i,j;
	char palavra[C], nome_do_arquivo[13];
	FILE *fp1 = NULL, *fp2 = NULL;
	TipoPesos p;
	TipoItem item;
	TipoDicionario Dicionario;

	fp1 = fopen("entrada.txt", "r");

	if(fp1 == NULL){
		printf("Não foi possível abrir o arquivo entrada.txt\n");
		EXIT_FAILURE;
	}

	fscanf(fp1,"%d",&Numero_de_arquivos);

	N = Numero_de_arquivos;

	Inicializa_DicionarioHS(Dicionario);

	for(i=0;i<Numero_de_arquivos; i++){

		fscanf(fp1,"%s",nome_do_arquivo);

		fp2 = fopen(nome_do_arquivo,"r");

		if(fp2 == NULL){
			printf("Não foi possível abrir o arquivo %s, verifique se este está no\ndiretório\n",nome_do_arquivo);
		}

		if(fp2 != NULL){
			while(fscanf(fp2,"%[^' ' '\n']",palavra) != EOF){
				if(strPontos(palavra)){
					NoCaps(palavra);
					concerta_palavra(palavra);
					strcpy (item.Chave, palavra);
					GeraPesos(p, C);
					Insere(item, p, Dicionario, i);
				}
				fgetc(fp2);
			}
		}
	}


	Mostra_Resultado(Dicionario);

	fclose(fp1);
	fclose(fp2);
}// OK