#ifndef __objet_h__
#define __objet_h__

#include <stdio.h>
#include <stdlib.h>
#include "competence.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
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
* <br /> Postconditions : obj est initialisé avec les paramètres de son type : nom, portee, degats, protection, description et valeur
*/
void objInit (Objet *obj, char type);

/**
* \brief Preconditions : st n'a pas déjà été initialisé
* <br /> Postconditions : st est initialisé avec une quantite nulle
*/
void stockInit (Stock *st);

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
* \brief Preconditions : stock1 et stock2 sont initialisés et font référence au même objet
* <br /> Postconditions : les deux Stocks sont fusionnés dans stock1 ; stock2 est libéré
*/
void fusionStocks(Stock* stock1, Stock* stock2);

/**
* \brief Preconditions : obj est initialisé
* <br /> Postconditions : retourne le type d'obj
*/
char getObjetType(Objet *obj);

/**
* \brief Preconditions : obj est initialisé
* <br /> Postconditions : retourne la portée d'obj
*/
char getObjetPortee(Objet *obj);

/**
* \brief Preconditions : obj est initialisé
* <br /> Postconditions : retourne la valeur de dégâts d'obj
*/
char getObjetDegats(Objet *obj);

/**
* \brief Preconditions : obj est initialisé
* <br /> Postconditions : retourne la valeur de protection d'obj
*/
char getObjetProtection(Objet *obj);

/**
* \brief Preconditions : obj est initialisé
* <br /> Postconditions : retourne la valeur (prix) d'obj
*/
int getObjetValeur(Objet *obj);

/**
* \brief Preconditions : obj est initialisé, s est une chaîne d'au moins 30 caractères
* <br /> Postconditions : copie le nom d'obj dans s
*/
char* getObjetNom(Objet *obj);

/**
* \brief Preconditions : obj est initialisé, s est une chaîne d'au moins 100 caractères
* <br /> Postconditions : copie la description d'obj dans s
*/
void getObjetDescription(char* s, Objet *obj);

#endif
