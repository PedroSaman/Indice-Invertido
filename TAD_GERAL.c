#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "TAD_GERAL.h"


int strPontos(char palavra[]){
	
	if ((palavra[0] == ',') || (palavra[0] == '.') || (palavra[0] == '?') || (palavra[0] == '!') || (palavra[0] == '-'))
		return 0;
	
	return 1;
} 


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
}


void NoCaps(char palavra[]){
	int index = 0;
	while(palavra[index] != '\0'){
		if((palavra[index] >= 'A') && (palavra[index] <= 'Z')){
			palavra[index] += 32;
		}
		index++;
	}
}


int Transformacao_de_chaves(TipoChave Chave, TipoPesos p){  
	
	int i;
	unsigned int Soma = 0;
	int comp = strlen(Chave);
	
	for(i = 0; i < comp; i++)
		Soma += (unsigned int)Chave[i] * p[i]; 
  	
  	return (Soma % M); 
}


void GeraPesos(TipoPesos p, int n){ 

/* Gera valores randomicos entre 1 e 10.000 */ 
	int i; 
	struct timeval semente; 

	gettimeofday(&semente,NULL);

	srand((int)(semente.tv_sec + 1000000*semente.tv_usec)); 
	for (i = 0; i < n; i++)
		p[i] =  1+(int) (10000.0*rand()/(RAND_MAX+1.0)); 
}
