#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "objet.h"
#include "competence.h"
#include "personnage.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

#define TAILLE_MAX 500

void ajouterCompetence (Personnage* perso, Competence* comp)
{
    int i;
    while ((i<perso->capacite.nbCompetence)||(perso->capacite.comp[i].action!=comp->action))
    {
        i++;
    }
    if (perso->capacite.quantite==0);
    {
        Competence *tampon= perso->capacite.comp;

        perso->capacite.comp= (Competence*) malloc (2*(perso->capacite.nbCompetence)*sizeof(Competence));
        for (i=0; i<perso->capacite.nbCompetence; i++)
        {
            perso->capacite.comp [i]=tampon[i];
        }
        free (tampon);
        perso->capacite.quantite=perso->capacite.nbCompetence;
    }
    perso->capacite.quantite--;
    perso->capacite.comp[perso->capacite.nbCompetence]=*comp;
    perso->capacite.nbCompetence++;
}

void persoInit (Personnage *perso, char nom[], char race, char sexe, char carriere, int experience,int argent)
{
    int i=0;
    assert (strlen(nom)<30);
    strcpy(perso->nom,nom);
    perso->race= race;
    perso->sexe= sexe;

    perso->carriere=carriere;
    perso->capacite.comp= (Competence*) malloc (sizeof(Competence));
    FILE* fCarr= fopen("../data/Carrieres.txt", "r");
    perso->experience= experience;
    char *ligne = (char*) malloc (TAILLE_MAX*sizeof(char));
    Competence* tampon=NULL;
    if (fCarr!=NULL)
    {
        while (i<carriere+3)
        {
            fgets(ligne,TAILLE_MAX,fCarr);
            i++;
        }
        i= strchr (ligne, '/')-ligne;
        while (ligne[i+1]!='/')
        {
            i+=2;
            compInit (tampon,ligne[i], experience/10);
            ajouterCompetence (perso, tampon);
        }
        free(tampon);
        free(ligne);
        fclose(fCarr);
    }
    else
    {
        printf ("Impossible d'ouvrir le fichier Carrieres.txt");
    }
    perso->argent=argent;
    stockInit(perso->inventaire.obj);
    perso->inventaire.nbObjet=0;
    perso->inventaire.capacite=1;
}

void persoLibere (Personnage *perso)
{
    free (perso->inventaire.obj);
    perso->inventaire.nbObjet=0;
    perso->inventaire.capacite=0;
    free (perso->capacite.comp);
    perso->capacite.nbCompetence=0;
    perso->capacite.quantite=0;
}

void ajouterInventaire (Personnage *perso, Objet *obj)
{
    int i=0;

    while ((i<perso->inventaire.nbObjet)||(perso->inventaire.obj[i].objet->nom!=obj->nom))
    {
        i++;
    }
    if (i<perso->inventaire.nbObjet)
    {
        perso->inventaire.obj[i].quantite++;
    }
    else if (perso->inventaire.capacite==0);
    {
        Stock *tampon= perso->inventaire.obj;

        perso->inventaire.obj= (Stock*) malloc (2*(perso->inventaire.nbObjet)*sizeof(Stock));
        for (i=0; i<perso->inventaire.nbObjet; i++)
        {
            perso->inventaire.obj [i]=tampon[i];
        }
        free (tampon);
        perso->inventaire.capacite=perso->inventaire.nbObjet;
    }
    perso->inventaire.capacite--;
    perso->inventaire.obj[perso->inventaire.nbObjet].objet=obj;
    perso->inventaire.nbObjet++;
}

void utiliser (Personnage *perso, Objet *obj)
{
    int i;
    while ((i<perso->inventaire.nbObjet)&&(perso->inventaire.obj[i].objet->nom!=obj->nom))
    {
        i++;
    }
    perso->inventaire.obj[i].quantite--;
    //effet en fonction du type ...
}
