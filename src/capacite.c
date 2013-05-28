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
    printf("111\n");
    free(capacite->comp);
    capacite->nbCompetence=0;
    capacite->quantite=0;
}

/* En mode tableau dynamique*/
void ajouterCompetenceCapacite (Capacite* capacite, Competence* comp,int exp)
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

void copieCapacite(Capacite* capacite1, Capacite** capacite2)
{
    int i;
    *capacite2=(Capacite*)malloc((capacite1->quantite)*sizeof(Capacite));
    for (i=0;i<capacite1->nbCompetence;i++)
    {
        copieCompetence(&((*capacite2)->comp[i]), &(capacite1->comp[i]));
    }
    (*capacite2)->nbCompetence=capacite1->nbCompetence;
    (*capacite2)->quantite=capacite1->quantite;
}

int chercherCompetence (Capacite* capacite, int type)
{
    int i;
    for (i=0; i<capacite->nbCompetence;i++)
    {
        if (capacite->comp[i].type==type) return i;
    }
    return -1;
}

Competence* getCompetence (Capacite* capacite, int i)
{
    return &(capacite->comp[i]);
}

int getCapaciteQuantite(Capacite* capacite)
{
    return capacite->quantite;
}

int getCapaciteNbCompetence(Capacite* capacite)
{
    return capacite->nbCompetence;
}



int mainCapacite()
{
    int i,j;
    char action[30];
    Competence comp[10];
    Competence *pointcomp;
    Capacite capacite;
    Capacite *capacite2;

    for(i=0;i<10;i++)
    {
        compInit (&comp[i], i+1, 10);
    }


    for(i=0;i<1;i++)
    {
        CapaciteInit (&capacite);

        for(j=0;j<9;j++)
        {
            ajouterCompetenceCapacite (&capacite, &comp[j], 10);
        }

        copieCapacite(&capacite, &capacite2);

        printf("1=%d\n0=%d\n", chercherCompetence(&capacite,7), chercherCompetence (&capacite,8));

        for(j=0;j<getCapaciteNbCompetence(&capacite);j++)
        {
            pointcomp=getCompetence(&capacite, j);
            strcpy(action, getAction(pointcomp));
            printf("%s\n",action);
        }

        printf("Il y a %d competences sur %d\n", getCapaciteNbCompetence(&capacite), getCapaciteQuantite(&capacite));

        CapaciteLibere (&capacite);
        CapaciteLibere (capacite2);
    }

    return EXIT_SUCCESS;
}
