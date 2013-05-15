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
    inventaire->nbObjet=0;
    inventaire->capacite=1;
}


void inventaireLibere (Inventaire* inventaire)
{
    int i;
    for (i=inventaire->nbObjet-1;i>=0;i--)
    {
        stockLibere (&(inventaire->st[i]));
    }
    free (inventaire->st);
    inventaire->nbObjet=0;
    inventaire->capacite=0;
}


void ajouterObjetInventaire (Inventaire* inventaire, Objet* obj)
{
    int i;
    char ajoute=0;
    Stock *tampon;

    for(i=0;i<inventaire->nbObjet;i++)
    {
        if(inventaire->st[i].objet->type==obj->type)
        {
            incrementerStock(&inventaire->st[i],1);  /*L'objet est déjà dans l'inventaire*/
            ajoute=1;
        }
    }

    if (ajoute==0)
    {
        if((inventaire->nbObjet)==(inventaire->capacite)) /*Double la capacite de l'inventaire*/
        {
            tampon=(Stock*) malloc((2*inventaire->capacite)*sizeof(Stock));
            for (i=0;i<inventaire->capacite;i++)
            {
                copieStock(&tampon[i],&(inventaire->st[i]));
            }
            free(inventaire->st);
            inventaire->st=tampon;
            inventaire->capacite*=2;
        }
        stockInit(&(inventaire->st[inventaire->nbObjet]),obj);
        inventaire->nbObjet++;
    }
}


void enleverObjetInventaire (Inventaire* inventaire, Objet* obj)
{
    int i, j;
    i=0;

    while ((i<inventaire->nbObjet)&&(inventaire->st[i].objet->type!=obj->type)) i++;
    assert(i!=inventaire->nbObjet);
    if (getStockQuantite((inventaire->st)+i)>1)
    {
        incrementerStock((inventaire->st)+i,-1);
    }
    else
    {
        for(j=i;j<inventaire->nbObjet-1;j++)
        {
            copieStock((inventaire->st)+j,(inventaire->st)+j+1);
        }
        stockLibere((inventaire->st)+(inventaire->nbObjet));
    }
}



void copieInventaire (Inventaire* inventaire1, Inventaire* inventaire2)
{
    int i;
    inventaire1->st=(Stock*)malloc((inventaire2->capacite)*sizeof(Stock));

    for (i=0;i<inventaire2->nbObjet;i++)
    {
        copieStock(&(inventaire1->st[i]),&(inventaire2->st[i]));
    }
    inventaire1->nbObjet=inventaire2->nbObjet;
    inventaire1->capacite=inventaire2->capacite;
}

void afficherInventaire (Inventaire* inventaire)
{
    int i;
    printf("\nInventaire :\n");
    for(i=0;i<inventaire->nbObjet;i++)
    {
        printf("i=%d  %s (%d) : %s\n", i, getObjetNom(getStockObjet(&(inventaire->st[i]))), getStockQuantite(&(inventaire->st[i])), getObjetDescription(getStockObjet(&(inventaire->st[i]))));
    }
    printf("NbObjet=%d \n Capacite=%d\n\n", inventaire->nbObjet, inventaire->capacite);
}



char estObjDansInv (Inventaire* inventaire, Objet* obj)
{
    int i;

    for(i=0;i<inventaire->nbObjet;i++)
    {
        if((getObjetType(getStockObjet(&inventaire->st[i])))==(getObjetType(obj))) return 1;
    }

    return 0;
}


Stock* getInventaireStock (Inventaire* inventaire,int i)
{
    return &(inventaire->st[i]);
}


int getInventaireNbObjets (Inventaire* inventaire)
{
    return inventaire->nbObjet;
}


int getInventaireCapacite (Inventaire* inventaire)
{
    return inventaire->capacite;
}



