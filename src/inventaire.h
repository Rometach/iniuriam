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
* \brief Preconditions : inventaire n'est pas initialisé avec la capacité capa
* <br /> Postconditions : inventaire est initialisé
*/
void inventaireInit (Inventaire* inventaire, int capa);

/**
* \brief Preconditions : inventaire est initialisé
* <br /> Postconditions : inventaire est libéré
*/
void inventaireLibere (Inventaire* inventaire);


#endif
