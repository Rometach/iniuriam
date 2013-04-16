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
    int i, j;
    int compAcquise=0;
    Competence* compTampon;

    for(i=0;i<capacite->nbCompetence;i++)
    {
        if(getType(&(capacite->comp)[i])!=getType(comp)) {compAcquise=1;}
    }

    if ((i==capacite->nbCompetence)||(!compAcquise))
    {
        if (capacite->nbCompetence!=capacite->quantite)
        {
            (capacite->comp)[i]=*comp;
        }
        else
        {
            compTampon=(Competence*)malloc(2*(capacite->quantite)*sizeof(Competence));
            for(j=0;j<capacite->quantite;j++)
            {
                compTampon[j]=capacite->comp[j];
            }
            compTampon[j]=*comp;

            capacite->quantite*=2;
            capacite->nbCompetence++;
            free(capacite->comp);
            capacite->comp=compTampon;
        }
    }
}
