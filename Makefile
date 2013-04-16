all: deplacement.out parole.out

OPT = -Wall -ansi -pedantic -ggdb

deplacement.out: deplacement.o
	gcc bin/deplacement.o -o bin/deplacement.out

parole.out: parole.o personnage.o inventaire.o capacite.o stock.o competence.o objet.o
	gcc bin/parole.o bin/personnage.o bin/inventaire.o bin/capacite.o bin/stock.o bin/competence.o bin/objet.o -o bin/parole.out

deplacement.o: src/deplacement.h src/deplacement.c
	gcc -c $(OPT) -o bin/deplacement.o src/deplacement.c

parole.o: src/personnage.h src/parole.h src/parole.c
	gcc -c $(OPT) -o bin/parole.o src/parole.c

personnage.o: src/personnage.h src/inventaire.h src/capacite.h src/personnage.c
	gcc -c $(OPT) -o bin/personnage.o src/personnage.c

inventaire.o: src/inventaire.h src/stock.h src/inventaire.c
	gcc -c $(OPT) -o bin/inventaire.o src/inventaire.c

capacite.o: src/capacite.h src/competence.h src/capacite.c
	gcc -c $(OPT) -o bin/capacite.o src/capacite.c

stock.o: src/stock.h src/objet.h src/stock.c
	gcc -c $(OPT) -o bin/stock.o src/stock.c

competence.o: src/competence.h src/competence.c
	gcc -c $(OPT) -o bin/competence.o src/competence.c

objet.o: src/objet.h src/objet.c
	gcc -c $(OPT) -o bin/objet.o src/objet.c

clean:
	rm -rf bin/*.o bin/deplacement.out bin/parole.out



