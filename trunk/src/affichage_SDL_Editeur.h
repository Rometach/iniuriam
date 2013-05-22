#ifndef AFFICHAGE_SDL_Editeur_H
#define AFFICHAGE_SDL_Editeur_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>

#include "terrain.h"
#include "constante.h"
#include "scanf_SDL.h"
#include "objet_Editeur.h"


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

/**
* \brief Preconditions : police et ecran sont initalisés, 0<type<8
* <br /> Postconditions : affiche les différentes pages de l'éditeur d'objet, selon le type.
*/
void afficherEditeurObjet (SDL_Surface *ecran, char type,TTF_Font *police);

/**
* \brief Preconditions : SDL est initialisé
* <br /> Postconditions : gère les évenements de l'éditeur d'objet. Retourne le type d'event réalisé.
*/
char eventEditeurObjet();

/**
* \brief Preconditions : /
* <br /> Postconditions : permet d'éditer, de sauver et de charger des objets
*/
void editerObjet();

/**
* \brief Preconditions :
* <br /> Postconditions : permet d'éditer, de sauver et de charger des cartes
*/
void editerCarte ();

#endif
