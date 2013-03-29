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
    i=0;
    while ((i<perso->capacite.nbCompetence)||(getAction(perso->capacite.comp+i)!=getAction(comp)))
    {
        i++;
    }
    if (i==perso->capacite.nbCompetence)
    {
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
}

void persoInit (Personnage *perso, char nom[], char race, char sexe, char carriere, int experience,int argent)
{
    int i=0, j;
    assert (strlen(nom)<30);
    strcpy(perso->nom,nom);
    perso->race= race;
    perso->sexe= sexe;

    perso->carriere=carriere;
    perso->capacite.comp= (Competence*) malloc (sizeof(Competence));
    FILE* fCarr;
    assert(fCarr= fopen("data/Carrieres.txt", "r"));
    perso->experience= experience;
    char ligne [TAILLE_MAX];
    Competence* tampon=NULL;
    if (fCarr!=NULL)
    {
        while (i<carriere+3)
        {
            fgets(ligne,TAILLE_MAX,fCarr);
            i++;
        }
        i= (int)(strchr (ligne, '/')-ligne);
        j= (int)(strchr (ligne,'!')-ligne);
        while (i+1<j)
        {
            i+=2;
            compInit (tampon,ligne[i]-'0', experience/10);
            ajouterCompetence (perso, tampon);
        }
        free(tampon);
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

void inventaireLibere (Inventaire* inventaire)
{
    free (inventaire->obj);
    inventaire->nbObjet=0;
    inventaire->capacite=0;
}

void CapaciteLibere (Capacite* capacite)
{
    free(capacite->comp);
    capacite->nbCompetence=0;
    capacite->quantite=0;
}

void persoLibere (Personnage *perso)
{
    inventaireLibere(&perso->inventaire);
    perso->inventaire.nbObjet=0;
    perso->inventaire.capacite=0;
    free (perso->capacite.comp);
    perso->capacite.nbCompetence=0;
    perso->capacite.quantite=0;
}

char* getPersoNom(Personnage *perso)
{
    return perso->nom;
}

char getPersoRace(Personnage *perso)
{
    return perso->race;
}

char getPersoSexe(Personnage *perso)
{
    return perso->sexe;
}

char getPersoCarriere(Personnage *perso)
{
    return perso->carriere;
}

void getCarriereNom(char carriere, char* s)
{
    int i;
    FILE* fCarr= fopen("/data/Carrieres.txt", "r");
    char ligne [TAILLE_MAX];
    for (i=0;i<carriere+3;i++)
    {
        fgets(ligne,TAILLE_MAX,fCarr);
    }
    i= strchr (ligne, '/')-ligne;
    strncpy(s,ligne,i);
    fclose(fCarr);
}

int getPersoArgent(Personnage *perso)
{
    return perso->argent;
}

int getPersoExperience(Personnage *perso)
{
    return perso->experience;
}

char getPersoAttaque(Personnage *perso)
{
    return perso->attaque;
}

char getPersoDefense(Personnage *perso)
{
    return perso->defense;
}

char getPersoIntelligence(Personnage *perso)
{
    return perso->intelligence;
}

char getPersoAgilite(Personnage *perso)
{
    return perso->agilite;
}

char getPersoCharisme(Personnage *perso)
{
    return perso->charisme;
}

char getPersoPtDeVie(Personnage *perso)
{
    return perso->charisme;
}

void getPersoInventaire(Personnage *perso, Inventaire* s)
{
    int i;
    free (s->obj);
    s->nbObjet=perso->inventaire.nbObjet;
    s->capacite=perso->inventaire.capacite;
    s->obj=(Stock*)malloc ((s->nbObjet) *sizeof(Stock));
    for (i=0; i<s->nbObjet;i++)
    {
        s->obj[i]=perso->inventaire.obj [i];
    }
}

void getPersoCapacite(Personnage *perso, Capacite* s)
{
    int i;
    free (s->comp);
    s->nbCompetence= perso->capacite.nbCompetence;
    s->quantite= perso->capacite.quantite;
    s->comp=(Competence*)malloc (sizeof(Competence));
    for (i=0;i<s->nbCompetence;i++)
    {
        s->comp[i]=perso->capacite.comp[i];
    }
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
    /*effet en fonction du type ...*/
}

int main()
{
    Personnage perso;
    persoInit (&perso, "Toromis", 1, 1, 1, 0, 100);
    persoLibere(&perso);
    return 0;
}
