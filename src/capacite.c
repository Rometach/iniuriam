#include "capacite.h"


/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

void CapaciteInit (Capacite* capacite)
{
    capacite->comp=(Competence*)malloc(sizeof(Competence));
    capacite->nbCompetence=0;
    capacite->quantite=1;
}


void CapaciteLibere (Capacite* capacite)
{
    free(capacite->comp);
    capacite->nbCompetence=0;
    capacite->quantite=0;
}

/* En mode tableau dynamique*/
void ajouterCompetenceCapacite (Capacite* capacite, const Competence* comp, const int exp)
{
    int i;
    int compAcquise=0;
    Competence* compTampon;

    for(i=0;i<capacite->nbCompetence;i++)
    {
        if(getType(&(capacite->comp)[i])==getType(comp))
        {
            compAcquise=1;
            compExp(&(capacite->comp[i]),exp);
        }
    }

    if (compAcquise==0)
    {
        if ((capacite->quantite)==(capacite->nbCompetence))
        {

            compTampon=(Competence*)malloc(2*(capacite->quantite)*sizeof(Competence));
            for(i=0;i<capacite->quantite;i++)
            {
                copieCompetence(&compTampon[i],&capacite->comp[i]);
            }
            free(capacite->comp);
            capacite->comp=compTampon;
            capacite->quantite*=2;
        }
        capacite->comp[capacite->nbCompetence]=*comp;
        capacite->nbCompetence++;
    }
}

void copieCapacite(const Capacite* capacite1, Capacite* capacite2)
{
    int i;

    CapaciteLibere(capacite2);

    capacite2->comp=malloc((capacite1->quantite)*sizeof(Competence));
    capacite2->nbCompetence=capacite1->nbCompetence;
    capacite2->quantite=capacite1->quantite;

    for (i=0;i<capacite1->nbCompetence;i++)
    {
        copieCompetence(&(capacite2->comp[i]), &(capacite1->comp[i]));
    }
}

int chercherCompetence (const Capacite* capacite, const int type)
{
    int i;
    for (i=0; i<capacite->nbCompetence;i++)
    {
        if (capacite->comp[i].type==type) return i;
    }
    return -1;
}

Competence* getCompetence (const Capacite* capacite, const int i)
{
    return &(capacite->comp[i]);
}

int getCapaciteQuantite(const Capacite* capacite)
{
    return capacite->quantite;
}

int getCapaciteNbCompetence(const Capacite* capacite)
{
    return capacite->nbCompetence;
}



int mainCapacite()
{
    int i,j;
    char action[30];
    Competence comp[10];
    Competence *pointcomp;
    Capacite capacite, capacite2;


    for(i=0;i<10;i++)
    {
        compInit (&comp[i], i+1, 10);
    }


    for(i=0;i<100;i++)
    {
        CapaciteInit (&capacite);
        CapaciteInit (&capacite2);

        for(j=0;j<9;j++)
        {
            ajouterCompetenceCapacite (&capacite, &comp[j], 10);
        }

        copieCapacite(&capacite, &capacite2);

        printf("8=%d\n-1=%d\n", chercherCompetence(&capacite2,9), chercherCompetence (&capacite2,10));

        for(j=0;j<getCapaciteNbCompetence(&capacite2);j++)
        {
            pointcomp=getCompetence(&capacite2, j);
            getAction(pointcomp,action);
            printf("%s\n",action);
        }

        printf("Il y a %d competences sur %d\n", getCapaciteNbCompetence(&capacite2), getCapaciteQuantite(&capacite2));

        CapaciteLibere (&capacite);
        CapaciteLibere (&capacite2);
    }

    return EXIT_SUCCESS;
}
