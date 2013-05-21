#ifndef __scanf_SDL_h__
#define __scanf_SDL_h__

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include "constante.h"

char eventScanf (SDL_Surface* ecran,char chiffre);

void scanfSDL (char* string,SDL_Surface* ecran,int longueur, char * action,TTF_Font *police, char chiffre);

#endif
