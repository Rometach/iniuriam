#ifndef AFFICHAGE_SDL_Editeur_H
#define AFFICHAGE_SDL_Editeur_H

#include "SDL/SDL.h"
#include "tile.h"
#include <stdlib.h>
#include <stdio.h>
#include "constante.h"
#include "terrain.h"
#include "SDL/SDL_ttf.h"
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
* \brief Preconditions : ter et ecran initalisé et remplis
* <br /> Postconditions : gère les évenements de l'éditeur de carte
*/
void eventEditeurSDL(Terrain* ter, SDL_Surface* ecran);

void editerObjet();

/**
* \brief Preconditions :
* <br /> Postconditions : permet d'éditer, de sauver et de charger des cartes
*/
void editerCarte ();

#endif
