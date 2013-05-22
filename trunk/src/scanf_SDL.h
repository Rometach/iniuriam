#ifndef __scanf_SDL_h__
#define __scanf_SDL_h__

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include "constante.h"

/**
* \brief Preconditions : ecran est initialisé
* <br /> Postconditions : retourne le caractère saisi par l'utilisateur, ne tient compte que des chiffres si chiffre!=0
*/
char eventScanf (SDL_Surface* ecran,char chiffre);

/**
* \brief Preconditions : ecran et police sont initalisés, chaine peut contenir l caractères.
* <br /> Postconditions : rempli chaine avec au plus l caractères saisis par l'utilisateur.
*                         retourne l'état de saisie dans action : action=0 ->SDL_QUIT
*                                                                 action=1 ->Echap
*                                                                 action=2 ->Chaine saisie
*/
void scanfSDL (char* chaine,SDL_Surface* ecran,int longueur, char * action,TTF_Font *police, char chiffre);

#endif
