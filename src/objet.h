#ifndef __objet_h__
#define __objet_h__

#include <stdio.h>
#include <stdlib.h>
#include "carriere.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, Isabelle
*/

typedef struct
{
    char nom [30];
    char type;
    char portee;
    char degats;
    char protection;
    char description [100];
    int valeur;
} Objet;

typedef struct
{
    int quantite;
    Objet *objet;
} Stock;

/**
* \brief Preconditions : obj n'a pas déjà été initialisé
* <br /> Postconditions : obj est initialisé avec pour paramètres nom, type portee, degats, protection, description et valeur
*/
void objInit (Objet *obj, char nom[], char type, char portee, char degats, char protection, char description [], int valeur);

/**
* \brief Preconditions : obj n'a pas déjà été initialisé
* <br /> Postconditions : obj est initialisé avec une quantite nulle
*/
void stockInit (Stock *obj);

/**
* \brief Preconditions : obj est initialisé
* <br /> Postconditions : obj est libéré
*/
void stockLibere (Stock *obj);



#endif
