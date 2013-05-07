#ifndef TILE_H
#define TILE_H

# define TILE_LARGEUR  16
# define TILE_HAUTEUR 16

typedef struct
{
    unsigned int posX;
    unsigned int posY;
    unsigned char collision;

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
int getCollision(Tile t);

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
void setCollision(Tile* t, int collision);

#endif
