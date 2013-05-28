#ifndef __capacite_h__
#define __capacite_h__

#include <assert.h>
#include <string.h>
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
* <br /> Postconditions : la compétence comp est ajoutée à capacité et l'expérience exp est ajoutée si la compétence est déjà dans capacite.
*/
void ajouterCompetenceCapacite (Capacite* capacite, Competence* comp, int exp);

/**
* \brief Preconditions : capacite1 est initialisée mais pas capacite2
* <br /> Postconditions : capacite2 est initialisée ; le contenu de capacite1 est copié dans capacite2
*/
void copieCapacite(Capacite* capacite1, Capacite** capacite2);

/**
* \brief Preconditions : capacite est initialisé
* <br /> Postconditions : Recherche si la compétence type est dans capacite et retourne sa position s'il la trouve (-1 sinon)
*/
int chercherCompetence (Capacite* capacite, int type);

/**
* \brief Preconditions : capacite est initialisé
* <br /> Postconditions : retourne la ième compétence de capacité
*/
Competence* getCompetence (Capacite* capacite, int i);

/**
* \brief Preconditions : capacite est initialisé
* <br /> Postconditions : retourne la quantite de capacité
*/
int getCapaciteQuantite(Capacite* capacite);

/**
* \brief Preconditions : capacite est initialisé
* <br /> Postconditions : retourne la quantite de capacité
*/
int getCapaciteNbCompetence(Capacite* capacite);


/**
* \brief Preconditions : /
* <br /> Postconditions : teste les fonctions du module Competence
*/
int mainCapacite();

#endif
