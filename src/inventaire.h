#ifndef __inventaire_h__
#define __inventaire_h__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <SDL/SDL.h>
#include "stock.h"

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
* \brief Preconditions : inventaire n'est pas initialisé
* <br /> Postconditions : inventaire est initialisé
*/
void inventaireInit (Inventaire* inventaire);

/**
* \brief Preconditions : inventaire est initialisé
* <br /> Postconditions : inventaire est libéré
*/
void inventaireLibere (Inventaire* inventaire);

/**
* \brief Preconditions : inventaire est initialisé
* <br /> Postconditions : st est ajouté dans inventaire
*/
void ajouterObjetInventaire (Inventaire* inventaire, Objet* obj);


/**
* \brief Preconditions : inventaire est initialisé, st fait partie de inventaire
* <br /> Postconditions : 1 stock est ôté de inventaire
*/
void enleverObjetInventaire (Inventaire* inventaire, Objet* obj);

/**
* \brief Preconditions : inventaire2 est initialisé mais pas inventaire1
* <br /> Postconditions : inventaire2 est recopié dans inventaire1
*/
void copieInventaire (Inventaire* inventaire1, Inventaire* inventaire2);


/**
* \brief Preconditions : inventaire est initialisé
* <br /> Postconditions : affiche le contenu de l'inventaire
*/
void afficherInventaire (Inventaire* inventaire);


/**
* \brief Preconditions : inventaire est initialisé
* <br /> Postconditions : retourne 0 si obj n'est pas dans inv, et 1 sinon
*/
char estObjDansInv (Inventaire* inventaire, Objet* obj);


/**
* \brief Preconditions : inventaire est initialisé
* <br /> Postconditions : retourne le ième tableau de Stocks de inventaire
*/
Stock* getInventaireStock (Inventaire* inventaire, int i);


/**
* \brief Preconditions : inventaire est initialisé
* <br /> Postconditions : retourne le nombre d'objets de inventaire
*/
int getInventaireNbObjets (Inventaire* inventaire);


/**
* \brief Preconditions : inventaire est initialisé
* <br /> Postconditions : retourne la capacité de inventaire
*/
int getInventaireCapacite (Inventaire* inventaire);

#endif
