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
    Stock* st;      /**Tableau (dynamique) de Stocks*/
    int nbObjet;    /**Nombre de cases utilisées du tableau*/
    int capacite;   /**Nombre de cases disponibles*/
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
* <br /> Postconditions : l'objet obj est ajouté dans inventaire
*/
void ajouterObjetInventaire (Inventaire* inventaire, Objet* obj);


/**
* \brief Preconditions : inventaire est initialisé, obj fait partie d'inventaire
* <br /> Postconditions : 1 occurence d'obj est ôtée d'inventaire
*/
void enleverObjetInventaire (Inventaire* inventaire, const Objet* obj);

/**
* \brief Preconditions : inventaire2 est initialisé mais pas inventaire1
* <br /> Postconditions : inventaire2 est recopié dans inventaire1
*/
void copieInventaire (Inventaire* inventaire1, const Inventaire* inventaire2);


/**
* \brief Preconditions : inventaire est initialisé
* <br /> Postconditions : affiche le contenu de l'inventaire
*/
void afficherInventaire (const Inventaire* inventaire);


/**
* \brief Preconditions : inventaire est initialisé
* <br /> Postconditions : retourne 0 si obj n'est pas dans inventaire, et 1 si oui
*/
char estObjDansInv (const Inventaire* inventaire, const Objet* obj);


/**
* \brief Preconditions : inventaire est initialisé
* <br /> Postconditions : retourne le l'adresse du ième Stock d'inventaire
*/
Stock* getInventaireStock (const Inventaire* inventaire, const int i);


/**
* \brief Preconditions : inventaire est initialisé
* <br /> Postconditions : retourne le nombre d'objets d'inventaire
*/
int getInventaireNbObjets (const Inventaire* inventaire);


/**
* \brief Preconditions : inventaire est initialisé
* <br /> Postconditions : retourne la capacité d'inventaire
*/
int getInventaireCapacite (const Inventaire* inventaire);

#endif
