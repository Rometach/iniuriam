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
* \brief Preconditions : inventaire n'est pas initialis� avec la capacit� capa
* <br /> Postconditions : inventaire est initialis�
*/
void inventaireInit (Inventaire* inventaire, int capa);

/**
* \brief Preconditions : inventaire est initialis�
* <br /> Postconditions : inventaire est lib�r�
*/
void inventaireLibere (Inventaire* inventaire);


#endif
