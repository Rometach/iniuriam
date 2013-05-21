#ifndef __objet_h__
#define __objet_h__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <SDL/SDL.h>
#include "constante.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

typedef struct
{
    char nom [30];
    char type;
    char utilite;     /*1 arme
                        2 armure
                        3 potion, nourriture
                        4 objet quête
                        5 autre
                       */
    char portee;      /*valable pour arme, potion (à voir)
                        armure : correspond à la partie du corps protégée
                        objet quête :
                       */
    char degats;      /*valable pour arme
                        potion : correspond au type de potion (soin, poison...)
                        armure :
                        objet quête :
                       */
    char protection;  /*valable pour armure, potion (pts de vie récupérés)
                        arme :
                        objet quête :
                       */
    char description [150];
    int valeur;

    SDL_Surface* icon;
} Objet;

/**
* \brief Preconditions : obj n'a pas déjà été initialisé, type <= au nombre max d'objet de Objets.txt
* <br /> Postconditions : obj est initialisé avec les paramètres de son type : nom, utilite, portee, degats, protection, description et valeur
*/
void objInit (Objet *obj, char type);

/**
* \brief Preconditions : obj est initialisé
* <br /> Postconditions : retourne le type d'obj
*/
char getObjetType(Objet *obj);

/**
* \brief Preconditions : obj est initialisé
* <br /> Postconditions : retourne l'utilité d'obj
*/
char getObjetUtilite(Objet *obj);

/**
* \brief Preconditions : obj est initialisé
* <br /> Postconditions : retourne l'utilité d'obj
*/
char* getObjetUtiliteNom(Objet *obj);

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
* \brief Preconditions : obj est initialisé
* <br /> Postconditions : retourne le nom d'obj
*/
char* getObjetNom(Objet *obj);

/**
* \brief Preconditions : obj est initialisé
* <br /> Postconditions : retourne la description d'obj
*/
char* getObjetDescription(Objet *obj);

/**
* \brief Preconditions : /
* <br /> Postconditions : change le nom d'obj pour nom
*/
void setObjetNom(Objet* obj,char* nom);

/**
* \brief Preconditions : /
* <br /> Postconditions : change la portée d'obj pour portee
*/
void setObjetPortee(Objet* obj,int portee);

/**
* \brief Preconditions : /
* <br /> Postconditions : change les degats d'obj pour degats
*/
void setObjetDegats(Objet* obj,int degats);

/**
* \brief Preconditions : /
* <br /> Postconditions : change la protection d'obj pour protection
*/
void setObjetProtection(Objet* obj,int protection);

/**
* \brief Preconditions : /
* <br /> Postconditions : change l'utilité d'obj pour utilite
*/
void setObjetUtilite(Objet* obj,int utilite);

/**
* \brief Preconditions : /
* <br /> Postconditions : change la valeur d'obj pour valeur
*/
void setObjetValeur(Objet* obj,int valeur);

/**
* \brief Preconditions : /
* <br /> Postconditions : change la description d'obj pour description
*/
void setObjetDescription(Objet* obj,char* description);

/**
* \brief Preconditions : /
* <br /> Postconditions : retourne le nombre d'objet dans Objets.txt +3
*/
int getNbObjet();

/**
* \brief Preconditions : tabObj n'est pas initialisé
* <br /> Postconditions : initialise tous les objets dans tabObj
*/
void initialiserTousLesObjets(Objet** tabObj);

/**
* \brief Preconditions : tabObj est initialisé
* <br /> Postconditions : libère tabObj
*/
void libererTousLesObjets(Objet** tabObj);

/**
* \brief Preconditions : obj est initialisé
* <br /> Postconditions : affiche les caractéristiques d'obj dans la console
*/
void afficherObjet(Objet* obj);

void copierFichier ();

#endif
