#include <stdlib.h>
#include <stdio.h>
#include "tile.h"

void initTile(Tile* t)
{
    t->posX=0;
    t->posY=0;
    t->collision=0;
}

int getPosX(Tile t)
{
    return t.posX;
}

int getPosY(Tile t)
{
    return t.posY;
}

int getCollision(Tile t)
{
    return t.collision;
}

void setPosX(Tile* t, int x)
{
    t->posX=x;
}

void setPosY(Tile* t, int y)
{
    t->posY=y;
}

void setCollision(Tile* t, int collision)
{
    t->collision=collision;
}
