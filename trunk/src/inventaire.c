#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "objet.h"
#include "inventaire.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/
void inventaireInit (Inventaire* inventaire)
{
    inventaire->st=(Stock*)malloc(sizeof(Stock));
    stockInit(inventaire->st);
    inventaire->nbObjet=0;
    inventaire->capacite=1;
}


void inventaireLibere (Inventaire* inventaire)
{
    free (inventaire->st);
    inventaire->nbObjet=0;
    inventaire->capacite=0;
}


void ajouterObjetInventaire (Inventaire* inventaire, Stock* st)
{
    int i;
    char ajoute=0;
    /*Stock* stockTampon;*/

    for(i=0;i<=inventaire->nbObjet;i++)
    {
        if(getStockObjet(&inventaire->st[i])==getStockObjet(st))
        {
            fusionStocks(&inventaire->st[i], st);
            ajoute=1;
        }
    }
    if (ajoute==0)
    {
        if((inventaire->nbObjet)==(inventaire->capacite))
        {
            /*stockTampon=malloc(2*(inventaire->capacite)*sizeof(Stock));
            for(i=0;i<=inventaire->nbObjet;i++)
            {
               STILL TO BE CODE
            }*/
        }
        else
        {
            inventaire->st[inventaire->nbObjet].objet=getStockObjet(st);     /*Améliorable*/
            inventaire->nbObjet++;
        }
    }
}


void copieInventaire (Inventaire* inventaire1, Inventaire* inventaire2)
{
    int i;
    inventaire1->st=(Stock*)malloc((inventaire2->capacite)*sizeof(Stock));
    stockInit(inventaire1->st);

    for (i=0;i<inventaire2->nbObjet;i++)
    {
        inventaire1->st[i]=inventaire2->st[i];
    }
    inventaire1->nbObjet=inventaire2->nbObjet;
    inventaire1->capacite=inventaire2->capacite;
}
