#ifndef __inventaire_h__
#define __inventaire_h__

#include <stdio.h>
#include <stdlib.h>
#include "objet.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

typedef struct
{
    Stock* st;
    int nbObjet;
    int capacite;
} Inventaire;

/**
* \brief Preconditions : inventaire n'est pas initialis�
* <br /> Postconditions : inventaire est initialis�
*/
void inventaireInit (Inventaire* inventaire);

/**
* \brief Preconditions : inventaire est initialis�
* <br /> Postconditions : inventaire est lib�r�
*/
void inventaireLibere (Inventaire* inventaire);

/**
* \brief Preconditions : inventaire est initialis�
* <br /> Postconditions : st est ajout� dans inventaire
*/
void ajouterObjetInventaire (Inventaire* inventaire, Stock* st);

/**
* \brief Preconditions : inventaire2 est initialis� mais pas inventaire1
* <br /> Postconditions : inventaire1 est initialis� ; inventaire2 est recopi� dans inventaire1
*/
void copieInventaire (Inventaire* inventaire1, Inventaire* inventaire2);


#endif
