#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TAD_HS.h"
#include "TAD_HA.h"
#include "TAD_GERAL.h"

int main(int argc, char *argv[]){

	int systemRet;
	int x, Tamanho_Max;
	struct rusage uso_inicio, uso_final;    
	struct timeval inicio, fim;             /*Variáveis para calcular tempo de execução e uso de memória*/

	getrusage(RUSAGE_SELF, &uso_inicio);
	while((x = getopt(argc, argv, "t:n:h"))!=-1){
		switch(x){
			case 't':
				Tamanho_Max = atoi(optarg);
				C = Tamanho_Max;
				break;
			case 'n':
				if (strcmp (optarg,"HS") == 0){
					systemRet = system("clear");
					if(systemRet == -1){
					  // The system method failed
					}
					printf("Hash Simples\n");
					gettimeofday(&inicio, NULL);
					CriaIndiceInvertidoHS();
					gettimeofday(&fim, NULL);
					getrusage(RUSAGE_SELF, &uso_final);
					printf("\n\n\tMemória usada em Kbytes: %ld\n", uso_final.ru_maxrss);
					printf("\tTempo de execução %.7lfs\n", difftime(fim.tv_sec, inicio.tv_sec)
																+ (double) (fim.tv_usec - inicio.tv_usec)/1000000);
				}else if(strcmp (optarg,"HA") == 0){
					systemRet = system("clear");
					if(systemRet == -1){
					  // The system method failed
					}
					printf("Hash Árvore\n");
					CriaIndiceInvertidoHA();
				}
				break;
			case 'h':
					systemRet = system("clear");
					if(systemRet == -1){
					  // The system method failed
					}
					printf("***************************************************\n***********************Ajuda***********************\n***************************************************\n");
					printf("\t -n Informa qual TAD será utilizado. Disponíveis:\n\tHash Aberto Simples (HS).\n\tHash Arvore (HA).\t");
					printf("\n\t -t Informa qual o tamanho da maior palavra dentro dos textos\n");
				break;			
			default:
                printf("Opção invalida ou faltando argumento, digite -h para mostrar ajuda\n") ;
                return -1;
		}
	}

	return 0;
}
