
#ifndef AFFICHAGE_SDL_H
#define AFFICHAGE_SDL_H

#include "SDL/SDL.h"
#include "tile.h"
#include <stdlib.h>
#include <stdio.h>
#include "constante.h"
#include "terrain.h"
#include "SDL/SDL_ttf.h"
#include "personnage.h"
#include "parole.h"

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
void affCarte(const Terrain* ter, SDL_Surface* ecran);

/**
* \brief Preconditions : hero, et ecran initalisé et remplis
* <br /> Postconditions : affiche le hero
*/
void affPerso(const Personnage* hero, const Personnage* pnjs, const Personnage* ennemis, SDL_Surface* ecran);

/**
* \brief Preconditions : Texte, ter initalisé et remplis
* <br /> Postconditions : affiche du texte
*/
void affDialogue( char* dialoguetab, SDL_Surface* ecran);

/**
* \brief Preconditions : Texte, ter initalisé et remplis
* <br /> Postconditions : affiche le menu du dialogue
*/
void affDialogue( char* dialoguetab,SDL_Surface* ecran);

/**
* \brief Preconditions : hero, ecran initalisé et remplis
* <br /> Postconditions :affiche l'inventaire
*/
void affInventaire(Personnage* hero, SDL_Surface* ecran);

/**
* \brief Preconditions : position, objet et ecran initalisé et remplis
* <br /> Postconditions :affiche les informations d'un objet
*/
void affInfOb(SDL_Rect* position, Objet* objet, SDL_Surface* ecran);

/**
* \brief Preconditions : hero, ecran initalisé et remplis
* <br /> Postconditions : gère les évements de l'inventaire
*/
void eventInventaireSDL(Personnage* hero, SDL_Surface* ecran);

/**
* \brief Preconditions : ter et ecran initalisé et remplis
* <br /> Postconditions : gère les évenements de l'éditeur de carte
*/
void eventEditeurSDL(Terrain* ter, SDL_Surface* ecran);

/**
* \brief Preconditions : hero, pnj, ter et ecran initalisé et remplis
* <br /> Postconditions : gère les évenements en jeu
*/
void eventJeuSDL(Personnage* hero, Personnage* pnj, Personnage* ennemi, Terrain* ter, Dialogue* dialogue, SDL_Surface* ecran);

/**
* \brief Preconditions : hero, pnj et ecran initalisé et remplis
* <br /> Postconditions : gère les évenements du dialogue
*/
void eventDialogueSDL( Dialogue* dialogue, const Personnage* hero, const Personnage* pnjs, const Personnage* ennemis, Terrain* ter, SDL_Surface*ecran);

/**
* \brief Preconditions :
* <br /> Postconditions : permet d'éditer, de sauver et de charger des cartes
*/
void editerCarte ();

#endif
