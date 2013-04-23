#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "stock.h"
#include "objet.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

void stockInit (Stock *st)
{
    st->objet=(Objet*)malloc(sizeof(Objet));
    st->quantite=1;
}

void stockLibere (Stock *st)
{
    free(st->objet);
    st->quantite=0;
}

void incrementerStock(Stock *st, int n)
{
	st->quantite+=n;
}


void decrementerStock(Stock *st, int n)
{
	st->quantite-=n;
}


Objet* getStockObjet(Stock *st)
{
    return st->objet;
}

void setObjetStock (Stock *st, Objet* obj)
{
    st->objet=obj;
}

int getQuantiteStock(Stock* stock)
{
    return stock->quantite;
}

int mainStock ()
{
    Objet obj;
    objInit(&obj, 1);
    printf ("No problem \n");
    return 0;
}
