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
    st->objet= NULL;
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


void fusionStocks(Stock* stock1, Stock* stock2)
{
    assert((stock1->objet)==(stock2->objet));
    stock1->quantite+=stock2->quantite;
}



int mainStock ()
{
    Objet obj;
    objInit(&obj, 1);
    printf ("No problem \n");
    return 0;
}
