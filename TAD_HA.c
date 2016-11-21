#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <math.h>
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

int PreOrdem_Somar_termos(ArvBin *raiz, int numero_do_doc, int *contador){

	if(*raiz == NULL){
		return 0;
	}

	if(*raiz != NULL){
		if(((*raiz)->item.qnt_aparicoes[numero_do_doc])!=0){
			*contador += 1;
		}
		return PreOrdem_Somar_termos(&((*raiz)->esq),numero_do_doc,contador);
		return PreOrdem_Somar_termos(&((*raiz)->dir),numero_do_doc,contador);
	}
	return 1;
}

int PreOrdem_Pesquisa(ArvBin* raiz, int doc_atual, TipoChave termo, int *quantos_doc_tem){

	int i;

	if(*raiz == NULL){
		return 0;
	}

	if(*raiz != NULL){
		if(strcmp((*raiz)->item.Chave, termo) == 0){
			for(i = 0; i<N; i++){
				if((*raiz)->item.qnt_aparicoes[i] != 0){
					*quantos_doc_tem += 1;
				}
			}
			return (*raiz)->item.qnt_aparicoes[doc_atual];
		}
		PreOrdem_Pesquisa(&((*raiz)->esq), doc_atual, termo, &quantos_doc_tem);
		PreOrdem_Pesquisa(&((*raiz)->dir), doc_atual, termo, &quantos_doc_tem);
	}
}


float calcula_peso(TipoChave termo, ArvBin* raiz[], int doc_atual){

	unsigned int i = 0;
	int quantos_doc_tem = 0, peso;
	float frequencia,aux;

	while(i<M){

		aux = (PreOrdem_Pesquisa(raiz[i], doc_atual, termo, &quantos_doc_tem));
		if(aux){
			frequencia = aux;
			return log10(N)*(frequencia/quantos_doc_tem);
		}
		i++;
	}

	return 0;


}

float calcula_relevancia_doc(ArvBin* raiz[], Lista* li, int num_termos, int doc_atual){

	int Termos_Distintos = 0, i;
	float peso_da_palavra[num_termos], relevancia = 0;
	TipoChave termo;

	for (i = 0; i < M; i++){
		PreOrdem_Somar_termos(raiz[i],doc_atual,&Termos_Distintos);
	}

	if(Termos_Distintos == 0){
		return 0;
	}else{
		for(i = 0; i<num_termos; i++){
			peso_da_palavra[i] = 0;
			consulta_lista_pos(li, i+1, termo);
			peso_da_palavra[i] = calcula_peso(termo, raiz, doc_atual);
			}

		for(i=0; i<num_termos; i++){
			relevancia += (peso_da_palavra[i]);
		}
		return relevancia/Termos_Distintos; 
	}
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


int documento_mais_relevante(float documentos[]){
	
	int indicie, i;
	float maior = 0;

	for(i=0;i<N;i++){
		if(documentos[i] > maior){
			maior = documentos[i];
			indicie = i;
		}
	}
	return indicie;
}


void CriaIndiceInvertidoHA(){

	struct rusage uso_inicio, uso_final;    
	struct timeval inicio, fim;             /*Variáveis para calcular tempo de execução e uso de memória*/
	gettimeofday(&inicio, NULL);
	int Numero_de_arquivos, i,j,k;
	char palavra[C], nome_do_arquivo[13];
	FILE *fp1 = NULL, *fp2 = NULL;
	TipoPesos p;
	TipoItem item;
	ArvBin* raiz[M];
	int Inicial;
	Lista *li;
	float Relevancia_por_doc[N];

	Inicializa_Arvores(raiz);

	fp1 = fopen("entrada.txt", "r");

	if(fp1 == NULL){
		printf("Não foi possível abrir o arquivo entrada.txt\n");
		return;
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

	gettimeofday(&fim, NULL);
	getrusage(RUSAGE_SELF, &uso_final);
	printf("\n\n\tMemória usada em Kbytes: %ld\n", uso_final.ru_maxrss);
	printf("\tTempo de execução %.7lfs\n", difftime(fim.tv_sec, inicio.tv_sec)
															+ (double) (fim.tv_usec - inicio.tv_usec)/1000000);

	printf("Digite o numero de termos para realizar a busca por relevância(0 para sair)\n");
	scanf("%d",&k);


	if(k>0){
		j = k;

		li = cria_lista();

		while(j>0){
			scanf("%s",palavra);
			strcpy (item.Chave, palavra);
			strPontos(palavra);
			NoCaps(palavra);
			concerta_palavra(palavra);
			insere_lista_inicio(li, palavra);
			j--;
		}

		for(i=0; i<N; i++){
			//	SOMAR UM NA HR DE MOSTRAR (AQUI ESTA DE 0 A MENOR Q N NA HR DE MOSTRAR TEM Q SER DE 1 A N)
			
			Relevancia_por_doc[i] = calcula_relevancia_doc(raiz, li, k, i);
			printf("relevancia da busca no doc %d = %.4f\n", i+1,Relevancia_por_doc[i] );
		}	
		
		k = documento_mais_relevante(Relevancia_por_doc);	

		printf("o documento arquivo%d.txt é o mais relevante com valor: %f \n",k+1, Relevancia_por_doc[k]);
	}

	fclose(fp1);
	fclose(fp2);
	libera_lista(li);
}
