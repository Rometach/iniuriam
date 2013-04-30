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

/**
* \brief Preconditions : obj n'a pas déjà été initialisé
* <br /> Postconditions : obj est initialisé avec les paramètres de son type : nom, portee, degats, protection, description et valeur
*/
void objInit (Objet *obj, char type);

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

/**
* \brief Preconditions : tabObjet est un tableau de longueur >= au nombre d'obejts dans objets.txt  ||| a changer si on implémente avec malloc
* <br /> Postconditions : initialise tous les objets dans tabObjet
*/
void initialiserTousLesObjets(Objet* tabObj);

#endif
