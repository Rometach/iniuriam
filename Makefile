CC=gcc
CFLAGS= -Wall -ansi -ggdb -I libs/include
LDFLAGS=-L libs/lib/ `sdl-config --cflags --libs` -lSDL_ttf -lSDL_image -lfmodex

SRC= src/objet.c src/stock.c src/equipement.c src/inventaire.c src/competence.c src/capacite.c src/liste_perso.c src/personnage.c src/tile.c src/terrain.c src/scanf_SDL.c src/affichage_sdl.c src/parole.c src/deplacement.c src/combat.c src/mission.c src/menu.c src/main.c
OBJ= $(notdir $(SRC:.c=.o))

SRC2= src/objet_Editeur.c src/competence.c src/perso_Editeur.c src/tile.c src/terrain.c src/scanf_SDL.c src/affichage_SDL_Editeur.c src/main_Editeur.c
OBJ2= $(notdir $(SRC2:.c=.o))


all: Iniuriam Editeur

Iniuriam: $(OBJ)
	@$(CC) -o bin/$@ $(addprefix obj/, $^) $(LDFLAGS)

Editeur: $(OBJ2)
	@$(CC) -o bin/$@ $(addprefix obj/, $^) $(LDFLAGS)

%.o: src/%.c 
	@$(CC) -c -o obj/$@ $(CFLAGS) $<

clean:
	@rm -rf obj/*.o bin/Iniuriam bin/Editeur
