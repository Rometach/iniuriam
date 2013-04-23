#ifndef __stock_h__
#define __stock_h__

#include <stdio.h>
#include <stdlib.h>
#include "objet.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

typedef struct
{
    int quantite;
    Objet *objet;
} Stock;

/**
* \brief Preconditions : st n'a pas déjà été initialisé
* <br /> Postconditions : st est initialisé avec l'objet obj
*/
void stockInit (Stock *st);

/**
* \brief Preconditions : st est initialisé
* <br /> Postconditions : st est libéré avec une quantite nulle
*/
void stockLibere (Stock *st);

/**
* \brief Preconditions : st est initialisé
* <br /> Postconditions : la quantité d'objets dans st est augmentée de n
*/
void incrementerStock(Stock *st, int n);

/**
* \brief Preconditions : st est initialisé
* <br /> Postconditions : la quantité d'objets dans st est diminuée de n
*/
void decrementerStock(Stock *st, int n);

/**
* \brief Preconditions : st est initialisé
* <br /> Postconditions : retourne l'adresse de l'objet enregistré dans st
*/
Objet* getStockObjet(Stock *st);

/**
* \brief Preconditions : st et obj sont initialisés
* <br /> Postconditions : initialise l'objet de st
*/
void setObjetStock (Stock *st, Objet* obj);

/**
* \brief Preconditions : st est initialisé
* <br /> Postconditions : retourne la quantite d'objet de st
*/
int getQuantiteStock(Stock* stock);

#endif
