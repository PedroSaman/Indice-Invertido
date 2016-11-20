# make -f Makefile 
# ./Executaval_Principal

Executavel_Principal: main.o TAD_GERAL.o TAD_HA.o TAD_HS.o
	gcc -o Executavel_Principal main.o TAD_GERAL.o TAD_HA.o TAD_HS.c -lm

TAD_GERAL.o: TAD_GERAL.c TAD_GERAL.h
	gcc -c TAD_GERAL.c

TAD_HA.o: TAD_HA.c TAD_GERAL.h TAD_HA.h
	gcc -c TAD_HA.c -lm

TAD_HS.o: TAD_HS.c TAD_GERAL.h TAD_HS.h
	gcc -c TAD_HS.c

main.o: main.c TAD_GERAL.h TAD_HA.h TAD_HS.h
	gcc -c main.c
