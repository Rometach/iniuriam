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
    Competence *comp;   /**Un tableau (dynamique) de compétences*/
    int nbCompetence;   /**Le nombre de cases utilisées du tableau*/
    int quantite;       /**Le nombre de cases disponibles*/
} Capacite;


/**
* \brief Preconditions : capacite n'est pas initialisée
* <br /> Postconditions : capacite est initialisée
*/
void capaciteInit (Capacite* capacite);


/**
* \brief Preconditions : capacite est initialisé
* <br /> Postconditions : capacite est libéré
*/
void capaciteLibere (Capacite* capacite);


/**
* \brief Preconditions : capacite est initialisé
* <br /> Postconditions : la compétence comp est ajoutée à capacité et l'expérience exp est ajoutée si la compétence est déjà dans capacite.
*/
void ajouterCompetenceCapacite (Capacite* capacite, const Competence* comp, const int exp);

/**
* \brief Preconditions : capacite1 est initialisée ; capacite2 aussi
* <br /> Postconditions : capacite2 est réinitialisée (son contenu est écrasé) et le contenu de capacite1 est copié dans capacite2
*/
void copieCapacite(const Capacite* capacite1, Capacite* capacite2);

/**
* \brief Preconditions : capacite est initialisé
* <br /> Postconditions : Recherche si la compétence type est dans capacite et retourne sa position s'il la trouve (-1 sinon)
*/
int chercherCompetence (const Capacite* capacite, const int type);

/**
* \brief Preconditions : capacite est initialisé
* <br /> Postconditions : retourne la ième compétence de capacité
*/
Competence* getCompetence (const Capacite* capacite, const int i);

/**
* \brief Preconditions : capacite est initialisé
* <br /> Postconditions : retourne la quantite de capacité
*/
int getCapaciteQuantite(const Capacite* capacite);

/**
* \brief Preconditions : capacite est initialisé
* <br /> Postconditions : retourne la quantite de capacité
*/
int getCapaciteNbCompetence(const Capacite* capacite);


/**
* \brief Preconditions : /
* <br /> Postconditions : teste les fonctions du module Competence
*/
int mainCapacite();

#endif
