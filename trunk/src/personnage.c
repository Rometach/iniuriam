#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "objet.h"
#include "personnage.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

void persoInit (Personnage *perso, char nom[], char race, char sexe, char carriere, int experience,int argent)
{

    assert (strlen(nom)<30);
    strcpy(perso->nom,nom);
    perso->race= race;
    perso->sexe= sexe;
    perso->carriere=carriere;
    perso->liste= (Competence*) malloc (sizeof(Competence));

    perso->experience= experience;
    perso->argent=argent;
    stockInit(perso->inventaire);
    perso->nbObjet=0;
    perso->capacite=1;
}

void persoLibere (Personnage *perso)
{
    free (perso->inventaire);
    perso->nbObjet=0;
    perso->capacite=0;
    free (perso->liste);
}

void ajouterInventaire (Personnage *perso, Objet *obj)
{
    int i=0;

    while ((i<perso->nbObjet)||(perso->inventaire[i].objet->nom!=obj->nom))
    {
        i++;
    }
    if (i<perso->nbObjet)
    {
        perso->inventaire[i].quantite++;
    }
    else if (perso->capacite==0);
    {
        Stock *tampon= perso->inventaire;

        perso->inventaire= (Stock*) malloc (2*(perso->nbObjet)*sizeof(Stock));
        for (i=0; i<perso->nbObjet; i++)
        {
            perso->inventaire [i]=tampon[i];
        }
        free (tampon);
        perso->capacite=perso->nbObjet;
    }
    perso->capacite--;
    perso->inventaire[perso->nbObjet].objet=obj;
    perso->nbObjet++;
}

void utiliser (Personnage *perso, Objet *obj)
{
    int i;
    while ((i<perso->nbObjet)&&(perso->inventaire[i].objet->nom!=obj->nom))
    {
        i++;
    }
    perso->inventaire[i].quantite--;
    //effet en fonction du type ...
}
