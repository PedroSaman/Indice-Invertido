# make -f Makefile 
# ./Executaval_Principal

Executavel_Principal: main.o TAD_GERAL.o TAD_HA.o TAD_HS.o
	gcc -O2 -o Executavel_Principal main.o TAD_GERAL.o TAD_HA.o TAD_HS.c

TAD_GERAL.o: TAD_GERAL.c TAD_GERAL.h
	gcc -O2 -c TAD_GERAL.c

TAD_HA.o: TAD_HA.c TAD_GERAL.h TAD_HA.h
	gcc -O2 -c TAD_HA.c

TAD_HS.o: TAD_HS.c TAD_GERAL.h TAD_HS.h
	gcc -O2 -c TAD_HS.c

main.o: main.c TAD_GERAL.h TAD_HA.h TAD_HS.h
	gcc -O2 -c main.c
