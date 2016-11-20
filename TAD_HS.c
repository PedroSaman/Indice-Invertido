#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "TAD_HS.h"
#include "TAD_GERAL.h"


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
} 


void InsereHS(TipoItem x, TipoPesos p, TipoDicionario T, int numero_do_doc){    
	
	unsigned int i = 0;         
	unsigned int Inicial;
	char Vazio[C];
	int posicao;

	for(i = 0; i<C; i++){
		Vazio[i]='!';
	}
	Vazio[C] = '\0';
	
	posicao = Pesquisa(x.Chave, p, T, numero_do_doc);

	if (posicao < M)  {
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
}


void Inicializa_Dicionario(TipoDicionario T){  
	
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
}


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
}


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

	Inicializa_Dicionario(Dicionario);

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
					InsereHS(item, p, Dicionario, i);
				}
				fgetc(fp2);
			}
		}
	}

	Mostra_Resultado(Dicionario);

	fclose(fp1);
	fclose(fp2);
}
