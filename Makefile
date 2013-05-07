all: Iniuriam Editeur

OPT = -Wall -ansi -pedantic -ggdb
SDL=`sdl-config --cflags --libs`

Iniuriam: main.o combat.o terrain.o tile.o deplacement.o parole.o personnage.o capacite.o competence.o inventaire.o stock.o objet.o
	gcc bin/main.o bin/combat.o bin/terrain.o bin/tile.o bin/deplacement.o bin/parole.o bin/personnage.o bin/capacite.o bin/competence.o bin/inventaire.o bin/stock.o bin/objet.o $(SDL) -o bin/Iniuriam

Editeur: Editeur_Carte.o affichage_sdl.o terrain.o tile.o
	gcc bin/Editeur_Carte.o bin/affichage_sdl.o bin/terrain.o bin/tile.o $(SDL) -o bin/Editeur

main.o: src/parole.h src/combat.h src/terrain.h src/main.c
	gcc -c $(OPT) -o bin/main.o src/main.c

combat.o: src/personnage.h src/terrain.h src/deplacement.h src/combat.h src/combat.c
	gcc -c $(OPT) -o bin/combat.o src/combat.c

Editeur_Carte.o: src/affichage_sdl.h src/terrain.h src/Editeur_Carte.c
	gcc -c $(OPT) $(SDL) -o bin/Editeur_Carte.o src/Editeur_Carte.c

affichage_sdl.o: src/terrain.h src/tile.h src/affichage_sdl.c
	gcc -c $(OPT) $(SDL) -o bin/affichage_sdl.o src/affichage_sdl.c

terrain.o: src/tile.h src/terrain.h src/terrain.c
	gcc -c $(OPT) $(SDL) -o bin/terrain.o src/terrain.c

tile.o: src/tile.h src/tile.c
	gcc -c $(OPT) -o bin/tile.o src/tile.c

deplacement.o: src/deplacement.h src/deplacement.c
	gcc -c $(OPT) -o bin/deplacement.o src/deplacement.c

parole.o: src/personnage.h src/parole.h src/parole.c
	gcc -c $(OPT) -o bin/parole.o src/parole.c

personnage.o: src/personnage.h src/inventaire.h src/capacite.h src/personnage.c
	gcc -c $(OPT) -o bin/personnage.o src/personnage.c

capacite.o: src/capacite.h src/competence.h src/capacite.c
	gcc -c $(OPT) -o bin/capacite.o src/capacite.c

competence.o: src/competence.h src/competence.c
	gcc -c $(OPT) -o bin/competence.o src/competence.c

inventaire.o: src/inventaire.h src/stock.h src/inventaire.c
	gcc -c $(OPT) -o bin/inventaire.o src/inventaire.c

stock.o: src/stock.h src/objet.h src/stock.c
	gcc -c $(OPT) -o bin/stock.o src/stock.c

objet.o: src/objet.h src/objet.c
	gcc -c $(OPT) -o bin/objet.o src/objet.c

clean:
	rm -rf bin/*.o bin/Iniuriam bin/Editeur



