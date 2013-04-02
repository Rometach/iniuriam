OPT = -Wall -ansi -pedantic -ggdb

perso.out: personnage.o competence.o objet.o capacite.o inventaire.o
	gcc bin/personnage.o bin/competence.o bin/objet.o bin/capacite.o bin/inventaire.o -o bin/perso.out

personnage.o: src/personnage.c src/personnage.h src/capacite.h src/inventaire.h
	gcc -c $(OPT) -o bin/personnage.o src/personnage.c

capacite.o: src/capacite.c src/capacite.h src/competence.h
	gcc -c $(OPT) -o bin/capacite.o src/capacite.c

competence.o: src/competence.c src/competence.h
	gcc -c $(OPT) -o bin/competence.o src/competence.c

inventaire.o: src/inventaire.c src/inventaire.h src/objet.h
	gcc -c $(OPT) -o bin/inventaire.o src/inventaire.c

objet.o: src/objet.c src/objet.h
	gcc -c $(OPT) -o bin/objet.o src/objet.c
