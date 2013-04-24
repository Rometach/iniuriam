#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "objet.h"
#include "stock.h"
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
    int i;
    for (i=0;i<inventaire->nbObjet;i++)
    {
        stockLibere (&(inventaire->st[i]));
    }
    inventaire->nbObjet=0;
    inventaire->capacite=0;
}


void ajouterObjetInventaire (Inventaire* inventaire, Objet* obj)
{
    int i;
    char ajoute=0;
    for(i=0;i<inventaire->nbObjet;i++)
    {
        if(inventaire->st[i].objet->type==obj->type)
        {
            incrementerStock(&inventaire->st[i],1);
            ajoute=1;
        }
    }
    if (ajoute==0)
    {
        if((inventaire->nbObjet)==(inventaire->capacite))
        {
            Inventaire *tampon;
            tampon=(Inventaire*)malloc(sizeof(Inventaire));
            inventaireInit(tampon);
            copieInventaire(tampon,inventaire);
            inventaire->st=(Stock*) malloc((2*inventaire->capacite)*sizeof(Stock));
            for (i=0;i<inventaire->capacite;i++)
            {
                stockInit(&(inventaire->st[i]));
                copieStock(&(inventaire->st[i]),&(tampon->st[i]));
            }
            inventaire->capacite*=2;
            free(tampon);
        }
        stockInit(&(inventaire->st[inventaire->nbObjet]));
        setObjetStock(&(inventaire->st[inventaire->nbObjet]),obj);
        inventaire->nbObjet++;
    }
}

/**Cette fonction doit être codée proprement*/
/*void eneleverObjetInventaire (Inventaire* inventaire, Stock* st)
{
    int i;
    while ((i<inventaire->nbObjet)&&(inventaire->st[i].objet->nom!=obj->nom))
    {
        i++;
    }
    inventaire.st[i].quantite--;
}*/



void copieInventaire (Inventaire* inventaire1, Inventaire* inventaire2)
{
    int i;
    inventaire1->st=(Stock*)malloc((inventaire2->capacite)*sizeof(Stock));

    for (i=0;i<inventaire2->nbObjet;i++)
    {
        stockInit(&(inventaire1->st[i]));
        copieStock(&(inventaire1->st[i]),&(inventaire2->st[i]));
    }
    inventaire1->nbObjet=inventaire2->nbObjet;
    inventaire1->capacite=inventaire2->capacite;
}
