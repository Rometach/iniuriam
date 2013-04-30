#ifndef TILE_H
# define TILE_H

# define TILE_LARGEUR  16
# define TILE_HAUTEUR 16

typedef struct
{
    int posX;
    int posY;
    int collision;

} Tile;

void initTile(Tile* t);

int getPosX(Tile t);

int getPosY(Tile t);

int getCollision(Tile t);

void setPosX(Tile* t, int x);

void setPosY(Tile* t, int y);

void setCollision(Tile* t, int collision);

#endif
