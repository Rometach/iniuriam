#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "objet.h"
#include "inventaire.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/
void inventaireInit (Inventaire* inventaire, int capa)
{
    inventaire->st=(Stock*)malloc(capa*sizeof(Stock));
    stockInit(inventaire->st);
    inventaire->nbObjet=0;
    inventaire->capacite=capa;
}


void inventaireLibere (Inventaire* inventaire)
{
    free (inventaire->st);
    inventaire->nbObjet=0;
    inventaire->capacite=0;
}
