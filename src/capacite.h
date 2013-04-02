#ifndef __capacite_h__
#define __capacite_h__

#include <stdio.h>
#include <stdlib.h>
#include "competence.h"


/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

typedef struct
{
    Competence *comp;
    int nbCompetence;
    int quantite;
} Capacite;


/**
* \brief Preconditions : capacite n'est pas initialisée
* <br /> Postconditions : capacite est initialisée
*/
void CapaciteInit (Capacite* capacite);


/**
* \brief Preconditions : capacite est initialisé
* <br /> Postconditions : capacite est libéré
*/
void CapaciteLibere (Capacite* capacite);


/**
* \brief Preconditions : capacite est initialisé
* <br /> Postconditions : la compétence comp est ajoutée à capacité
*/
void ajouterCompetenceCapacite (Capacite* capacite, Competence* comp);


#endif