
#ifndef AFFICHAGE_SDL_H
# define AFFICHAGE_SDL_H

#include "SDL/SDL.h"
#include "tile.h"
#include <stdlib.h>
#include <stdio.h>
#include "terrain.h"
#include "personnage.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

/**
* \brief Preconditions : ter et ecran initalisé et remplis
* <br /> Postconditions : affiche le chipset
*/
void affChipset(Terrain* ter, SDL_Surface* ecran);

/**
* \brief Preconditions : ter et ecran initalisé et remplis
* <br /> Postconditions : affiche l'editeur de carte
*/
void affEditeur(Terrain* ter, SDL_Surface* ecran);

/**
* \brief Preconditions : ter et ecran initalisé et remplis
* <br /> Postconditions : affiche la carte
*/
void affCarte(Terrain* ter, SDL_Surface* ecran);

/**
* \brief Preconditions : hero, surfPerso et ecran initalisé et remplis
* <br /> Postconditions : affiche le hero
*/
void affPerso(Personnage* hero, SDL_Surface* ecran);

/**
* \brief Preconditions : ter et ecran initalisé et remplis
* <br /> Postconditions : gère les évenements de l'éditeur de carte
*/
void eventEditeurSDL(Terrain* ter, SDL_Surface* ecran);

/**
* \brief Preconditions : hero, ter, surfPerso et ecran initalisé et remplis
* <br /> Postconditions : gère les évenements en jeu
*/
void eventJeuSDL(Personnage* hero, Terrain* ter, SDL_Surface* ecran);

/**
* \brief Preconditions :
* <br /> Postconditions : permet d'éditer, de sauver et de charger des cartes
*/
void editerCarte ();

#endif
