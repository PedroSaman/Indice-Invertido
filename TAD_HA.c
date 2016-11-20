#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "TAD_HA.h"
#include "TAD_GERAL.h"


int PreOrdem_ArvBin(ArvBin *raiz, TipoItem item, int numero_do_doc){
	
	if(*raiz == NULL){
		return 0;
	}

	if(*raiz != NULL){
		if(strcmp((*raiz)->item.Chave, item.Chave) == 0){
			(*raiz)->item.qnt_aparicoes[numero_do_doc] +=1;
			return 1;
		}
		PreOrdem_ArvBin(&((*raiz)->esq),item, numero_do_doc);
		PreOrdem_ArvBin(&((*raiz)->dir),item, numero_do_doc);
	}
}


int Pesquisa_na_arvore(TipoItem item, ArvBin* raiz[], int numero_do_doc){

	unsigned int i = 0;

	while(i<M){
		if(PreOrdem_ArvBin(raiz[i],item,numero_do_doc)){
			
			return 1;	
		}
		i++;
	}

	return 0;
}


int Insere_ArvBin (ArvBin *raiz, TipoItem x, int numero_do_doc){

	if (raiz == NULL){
		return 0;
	}
	struct NO* novo;
	novo = (struct NO*) malloc(sizeof(struct NO));
	if (novo == NULL){
		return 0;
	}
	novo->item = x;
	novo->item.qnt_aparicoes[numero_do_doc] += 1;
	novo->dir = NULL;
	novo->esq = NULL;

	if(*raiz == NULL){
		*raiz = novo;
	}
	else{
		struct NO* atual = *raiz;
		struct NO* ant = NULL;
		while(atual != NULL){
			ant = atual;
			if(strcmp(atual->item.Chave, x.Chave) == 0){
				free(novo);
				return 0;
			}
			if(strcmp(atual->item.Chave, x.Chave) > 0){
				atual = atual->esq;
			}else{
				atual = atual->dir;
			}
		}
		if ((strcmp(ant->item.Chave, x.Chave) > 0)){
			ant->esq = novo;
		}else
			ant->dir = novo;
	}
	return 1;
}


int PreOrdem_ArvBin_para_mostrar(ArvBin *raiz){
	
	int j;

	if(*raiz == NULL){
		return 0;
	}

	printf("%s\t",(*raiz)->item.Chave);
		
	for(j=0; j< N; j++){
		if(((*raiz)->item.qnt_aparicoes[j])!=0){	
			if(((*raiz)->item.qnt_aparicoes[j])==1){
				printf("aparece %d vez   no arquivo %d |",((*raiz)->item.qnt_aparicoes[j]), j+1);
			}else {
				printf("aparece %d vezes no arquivo %d |",((*raiz)->item.qnt_aparicoes[j]), j+1);
			}
		}
	}
	printf("\n");
	
	PreOrdem_ArvBin_para_mostrar(&((*raiz)->esq));
	PreOrdem_ArvBin_para_mostrar(&((*raiz)->dir));
	return 1;
}


void Mostra_arvore(ArvBin* raiz[]){

	int i = 0;

	while(i<M){
		PreOrdem_ArvBin_para_mostrar(raiz[i]);
		i++;
	}
}


void Inicializa_Arvores(ArvBin* raiz[]){

	int j, k;

	for (k=0 ; k<M; k++){
		raiz[k] = (ArvBin*) malloc(sizeof(ArvBin));	
		if(raiz[k] != NULL){
			(*raiz)[k] == NULL;
		}
		for (j=0; j<N; j++){
			(*raiz)[j]->item.qnt_aparicoes[j] = 0;
		}
	}
}


void CriaIndiceInvertidoHA(){

	int Numero_de_arquivos, i,j,k;
	char palavra[C], nome_do_arquivo[13];
	FILE *fp1 = NULL, *fp2 = NULL;
	TipoPesos p;
	TipoItem item;
	ArvBin* raiz[M];
	int Inicial;

	Inicializa_Arvores(raiz);

	fp1 = fopen("entrada.txt", "r");

	if(fp1 == NULL){
		printf("Não foi possível abrir o arquivo entrada.txt\n");
		EXIT_FAILURE;
	}

	fscanf(fp1,"%d",&Numero_de_arquivos);

	N = Numero_de_arquivos;

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
					if(Pesquisa_na_arvore(item, raiz, i)){
						/*Já existe tal palavra*/
					}else{
						Inicial = (Transformacao_de_chaves(item.Chave, p) % M);
						Insere_ArvBin(raiz[Inicial], item, i);		
					}
				}
				fgetc(fp2);
			}
		}
	}

	Mostra_arvore(raiz);

	fclose(fp1);
	fclose(fp2);
}
