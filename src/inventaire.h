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
void ajouterObjetInventaire (Inventaire* inventaire, Objet* obj);


/**
* \brief Preconditions : inventaire est initialis�, st fait partie de inventaire
* <br /> Postconditions : 1 stock est �t� de inventaire
*/
void enleverObjetInventaire (Inventaire* inventaire, Objet* obj);

/**
* \brief Preconditions : inventaire2 est initialis� mais pas inventaire1
* <br /> Postconditions : inventaire2 est recopi� dans inventaire1
*/
void copieInventaire (Inventaire* inventaire1, Inventaire* inventaire2);


/**
* \brief Preconditions : inventaire est initialis�
* <br /> Postconditions : affiche le contenu de l'inventaire
*/
void afficherInventaire (Inventaire* inventaire);


/**
* \brief Preconditions : inventaire est initialis�
* <br /> Postconditions : retourne 0 si obj n'est pas dans inv, et 1 sinon
*/
char estObjDansInv (Inventaire* inventaire, Objet* obj);


/**
* \brief Preconditions : inventaire est initialis�
* <br /> Postconditions : retourne le i�me tableau de Stocks de inventaire
*/
Stock* getInventaireStock (Inventaire* inventaire, int i);


/**
* \brief Preconditions : inventaire est initialis�
* <br /> Postconditions : retourne le nombre d'objets de inventaire
*/
int getInventaireNbObjets (Inventaire* inventaire);


/**
* \brief Preconditions : inventaire est initialis�
* <br /> Postconditions : retourne la capacit� de inventaire
*/
int getInventaireCapacite (Inventaire* inventaire);

#endif
