#include "stock.h"


/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

void stockInit (Stock *st, Objet* obj)
{
    st->objet=obj;
    st->quantite=1;
}

void stockLibere (Stock *st)
{
    st->objet=NULL;
    st->quantite=0;
}

void incrementerStock(Stock *st, const int n)
{
	st->quantite+=n;
}

Objet* getStockObjet(const Stock *st)
{
    return st->objet;
}

int getStockQuantite(const Stock* stock)
{
    return stock->quantite;
}

void setStockObjet (Stock *st, Objet* obj)
{
    st->objet=obj;
}

void copieStock (Stock *st1, const Stock *st2)
{
    setStockObjet(st1,st2->objet);
    st1->quantite=st2->quantite;
}

int mainStock ()
{
    Objet obj;
    objInit(&obj, 1);
    objLibere(&obj);
    printf ("No problem \n");
    return 0;
}
