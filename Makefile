# make -f Makefile 
# ./Executaval_Principal

all: Executaval_Principal
Executaval_Principal: TAD.o main.o 
	gcc -o Executaval_Principal TAD.o main.o
TAD.o: TAD.c
	gcc -o TAD.o -c TAD.c -W
main.o: main.c TAD.h 
	gcc -o main.o -c main.c -W