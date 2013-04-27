#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "capacite.h"
#include "competence.h"

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
void ajouterCompetenceCapacite (Capacite* capacite, Competence* comp)
{
    int i;
    int compAcquise=0;

    for(i=0;i<capacite->nbCompetence;i++)
    {
        if(getType(&(capacite->comp)[i])==getType(comp)) {compAcquise=1;}
    }

    if (compAcquise==0)
    {
        if ((capacite->quantite)==(capacite->nbCompetence))
        {
            Competence* compTampon;
            compTampon=(Competence*)malloc((capacite->quantite)*sizeof(Competence));
            for(i=0;i<capacite->quantite;i++)
            {
                compTampon[i]=capacite->comp[i];
            }
            capacite->comp=(Competence*)malloc(2*(capacite->quantite)*sizeof(Competence));
            for(i=0;i<capacite->quantite;i++)
            {
                capacite->comp[i]=compTampon[i];
            }
            capacite->quantite*=2;
            free (compTampon);
        }
        capacite->comp[capacite->nbCompetence]=*comp;
        capacite->nbCompetence++;
    }
}
