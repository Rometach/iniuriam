all:jdr.out

OPT = -Wall -ansi -pedantic -ggdb

jdr.out: menu.o jeu.o combat.o discuter.o terrain.o aleatoire.o personnage.o objet.o
	gcc bin/menu.o bin/jeu.o bin/jeu.o bin/jeu.o -o bin/jdr

menu.o: src/menu.c src/jeu.h
	gcc -c $(OPT) -o bin/menu.o src/menu.c 

jeu.o: src/jeu.c src/jeu.h src/discuter.h src/combat.h src/terrain.h
	gcc -c $(OPT) -o bin/jeu.o src/jeu.c

combat.o: src/combat.c src/combat.h src/aleatoire.h  src/personnage.h src/objet.h
	gcc -c $(OPT) -o bin/aleatoire.o src/aleatoire.c

terrain.o: src/terrain.c src/terrain.h src/aleatoire.h  src/personnage.h src/objet.h
	gcc -c $(OPT) -o bin/aleatoire.o src/aleatoire.c

discuter.o: src/discuter.c src/discuter.h src/aleatoire.h  src/personnage.h
	gcc -c $(OPT) -o bin/aleatoire.o src/aleatoire.c

personnage.o: src/personnage.c src/personnage.h src/objet.h
	gcc -c $(OPT) -o bin/personnage.o src/personnage.c

objet.o: src/objet.c src/objet.h
	gcc -c $(OPT) -o bin/objet.o src/objet.c 


clean:
	/bin/rm -rf *.o menu
