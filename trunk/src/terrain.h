#ifndef TERRAIN_H
#define TERRAIN_H

#include "SDL/SDL.h"
#include "tile.h"
#include "stdlib.h"
#include "stdio.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

typedef struct
{
    unsigned int nbrTileChipset;        /** le nombre de tiles différente du chipset*/
    int decalageX;      /** Uniquement pour l'éditeur: décalage de la carte par rapport a l'affichage du chipset en case (0 en jeu)*/
    int defilY;         /** Uniquement pour l'éditeur: le défilement du chipset en case*/
    unsigned int tileSel;        /** Uniquement pour l'éditeur: la tile du chipset selectionner pour mettre sur la carte */

    unsigned int hauteurChipset;   /** hauteur en case */
    unsigned int largeurChipset;   /** largeur en case*/

    Tile* tabChipset;       /** le tableau des cases du chipset*/
    SDL_Surface* chipset;       /** le chipset*/

    unsigned int *carte;       /** le pointeur sur la carte*/

} Terrain;

/**
* \brief Preconditions : ter n'a pas déjà été initialisé
* <br /> Postconditions : ter est initialisé
*/
void terInit(Terrain* ter);

/**
* \brief Preconditions : ter est initialisé
* <br /> Postconditions : ter est remplis
*/
void terRemplirStruct(Terrain* ter);

/**
* \brief Preconditions : ter est initialisé
* <br /> Postconditions : on change nbrTile
*/
void setNbrTile(Terrain* ter, unsigned int nbrTile);

/**
* \brief Preconditions : ter est initialisé
* <br /> Postconditions : on change decalageX
*/
void setDecalageX(Terrain* ter, int x);

/**
* \brief Preconditions : ter est initialisé
* <br /> Postconditions : on change defilY
*/
void setDefilY(Terrain* ter, int y);

/**
* \brief Preconditions : ter est initialisé
* <br /> Postconditions : on change tileSel
*/
void setTileSel(Terrain* ter, unsigned int selec);

/**
* \brief Preconditions : ter est initialisé
* <br /> Postconditions : on change hauteur
*/
void setHauteur(Terrain* ter, unsigned int hauteur);

/**
* \brief Preconditions : ter est initialisé
* <br /> Postconditions : on change largeur
*/
void setLargeur(Terrain* ter, unsigned int largeur);

/**
* \brief Preconditions : ter est initialisé, 0 <= i <nbrTile
* <br /> Postconditions : on change la ième case de tabChipset
*/
void setTabChipset(Terrain* ter, int i, Tile* tile);

/**
* \brief Preconditions : ter est initialisé, 0<= i < ter->hauteur*ter->largeur
* <br /> Postconditions : on change la ième case de la carte
*/
void setCarte(Terrain *ter, int i, unsigned int numTile);

/**
* \brief Preconditions : ter est initialisé
* <br /> Postconditions : on récupère nbrTile
*/
unsigned int getNbrTile(Terrain* ter);

/**
* \brief Preconditions : ter est initialisé
* <br /> Postconditions : on récupère decalageX
*/
int getDecalageX(Terrain* ter);

/**
* \brief Preconditions : ter est initialisé
* <br /> Postconditions : on récupère defilY
*/
int getDefilY(Terrain* ter);

/**
* \brief Preconditions : ter est initialisé
* <br /> Postconditions : on récupère tileSel
*/
unsigned int getTileSel(Terrain* ter);

/**
* \brief Preconditions : ter est initialisé
* <br /> Postconditions : on récupère hauteur
*/
unsigned int getHauteur(Terrain* ter);

/**
* \brief Preconditions : ter est initialisé
* <br /> Postconditions : on récupère largeur
*/
unsigned int getLargeur(Terrain* ter);

/**
* \brief Preconditions : ter est initialisé, 0 <= i <nbrTile
* <br /> Postconditions : on récupère le ième case de tabChipset
*/
Tile* getTabChipset(Terrain* ter, int i);

/**
* \brief Preconditions : ter est initialisé, 0<= i < ter->hauteur*ter->largeur
* <br /> Postconditions : on récupère la ième case de la carte
*/
int getCarte(Terrain *ter, int i);

/**
* \brief Preconditions : ter est initialisé, nomChipset est le même que celui chargé dans remplirStructTerrain, nomFIchier non null
* <br /> Postconditions : on sauvegarde la structure ter dans un fichier binaire nomFichier
*/
void terSauvegarde(Terrain* ter, char* nomFichier, char* nomChipset);

/**
* \brief Preconditions : ter est initialisé, nomFichier non null et existe
* <br /> Postconditions : on charge le fihcier binaire nomFichier et on remplis la structure ter avec
*/
void terCharger(Terrain* ter, char* nomFichier);

/**
* \brief Preconditions : ter est initialisé
* <br /> Postconditions : on libère ter
*/
void terLibere(Terrain* ter);

#endif

