OPT = -Wall -ansi -pedantic -ggdb

perso.out: main.o competence.o objet.o capacite.o inventaire.o case.o terrain.o 
	gcc bin/competence.o bin/objet.o bin/capacite.o bin/inventaire.o bin/main.o bin/terrain.o bin/\case.o -o bin/perso.out

main.o: src/main.c src/terrain.h src/case.h
	gcc -c $(OPT) -o bin/main.o src/main.c

capacite.o: src/capacite.c src/capacite.h src/competence.h
	gcc -c $(OPT) -o bin/capacite.o src/capacite.c

competence.o: src/competence.c src/competence.h
	gcc -c $(OPT) -o bin/competence.o src/competence.c

inventaire.o: src/inventaire.c src/inventaire.h src/objet.h
	gcc -c $(OPT) -o bin/inventaire.o src/inventaire.c

objet.o: src/objet.c src/objet.h
	gcc -c $(OPT) -o bin/objet.o src/objet.c

terrain.o: src/terrain.c src/terrain.h src/case.h
	gcc -c $(OPT) -o bin/terrain.o src/terrain.c

case.o: src/case.c src/case.h
	gcc -c $(OPT) -o bin/\case.o src/\case.c


