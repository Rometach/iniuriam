#ifndef TILE_H
#define TILE_H
#include "constante.h"

typedef struct
{
    unsigned int posX;      /**Coordonnée en X*/
    unsigned int posY;      /**Coordonnée en Y*/
    char collision;         /**0 si la case est accseeible, 1 si elle ne l'est pas*/

} Tile;

/**
* \brief Preconditions : tile n'est pas initialisé
* <br /> Postconditions : tile est initialisé
*/
void initTile(Tile* t);

/**
* \brief Preconditions : tile est initialisé
* <br /> Postconditions : on récupère posX
*/
int getPosX(Tile t);

/**
* \brief Preconditions : tile est initialisé
* <br /> Postconditions : on récupère posY
*/
int getPosY(Tile t);

/**
* \brief Preconditions : tile est initialisé
* <br /> Postconditions : on récupère collision
*/
char getCollision(Tile t);

/**
* \brief Preconditions : tile est initialisé
* <br /> Postconditions : on change posX
*/
void setPosX(Tile* t, int x);

/**
* \brief Preconditions : tile est initialisé
* <br /> Postconditions : on change posY
*/
void setPosY(Tile* t, int y);

/**
* \brief Preconditions : tile est initialisé
* <br /> Postconditions : on change collision
*/
void setCollision(Tile* t, char collision);

#endif
