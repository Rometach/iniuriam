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
    char degats;      /*valable pour arme,armure
                        potion : correspond au type de potion (soin, poison...)
                        objet quête :
                       */
    char protection;  /*valable pour arme,armure, potion (pts de vie récupérés)
                        objet quête :
                       */
    char description [150];
    int valeur;

    SDL_Surface* icon;
} Objet;

/**
* \brief Preconditions : obj n'a pas déjà été initialisé, 0 <= type <= au nombre max d'objet de Objets.txt
* <br /> Postconditions : obj est initialisé avec les paramètres de son type : nom, utilite, portee, degats, protection, description et valeur
*/
void objInit (Objet *obj, const char type);

/**
* \brief Preconditions : obj est initialisé
* <br /> Postconditions : retourne le type d'obj
*/
char getObjetType(const Objet *obj);

/**
* \brief Preconditions : obj est initialisé
* <br /> Postconditions : retourne l'utilité d'obj
*/
char getObjetUtilite(const Objet *obj);

/**
* \brief Preconditions : obj est initialisé
* <br /> Postconditions : copie dans utilite l'utilité d'obj
*/
void getObjetUtiliteNom(char* utilite, const Objet *obj);

/**
* \brief Preconditions : obj est initialisé
* <br /> Postconditions : retourne la portée d'obj
*/
char getObjetPortee(const Objet *obj);

/**
* \brief Preconditions : obj est initialisé
* <br /> Postconditions : retourne la valeur de dégâts d'obj
*/
char getObjetDegats(const Objet *obj);

/**
* \brief Preconditions : obj est initialisé
* <br /> Postconditions : retourne la valeur de protection d'obj
*/
char getObjetProtection(const Objet *obj);

/**
* \brief Preconditions : obj est initialisé
* <br /> Postconditions : retourne la valeur (prix) d'obj
*/
int getObjetValeur(const Objet *obj);

/**
* \brief Preconditions : obj est initialisé ; nom est une chaine de longueur >=30
* <br /> Postconditions : retourne le nom d'obj
*/
void getObjetNom(char* nom, const Objet *obj);

/**
* \brief Preconditions : obj est initialisé, description est une chaine de longueur >=150
* <br /> Postconditions : copie dans description la description d'obj
*/
void getObjetDescription(char* description, const Objet *obj);

/**
* \brief Preconditions : nom est une chaine de longueur <30
* <br /> Postconditions : change le nom d'obj pour nom
*/
void setObjetNom(Objet* obj, const char* nom);

/**
* \brief Preconditions : /
* <br /> Postconditions : change la portée d'obj pour portee
*/
void setObjetPortee(Objet* obj, const int portee);

/**
* \brief Preconditions : /
* <br /> Postconditions : change les degats d'obj pour degats
*/
void setObjetDegats(Objet* obj, const int degats);

/**
* \brief Preconditions : /
* <br /> Postconditions : change la protection d'obj pour protection
*/
void setObjetProtection(Objet* obj, const int protection);

/**
* \brief Preconditions : /
* <br /> Postconditions : change l'utilité d'obj pour utilite
*/
void setObjetUtilite(Objet* obj, const int utilite);

/**
* \brief Preconditions : /
* <br /> Postconditions : change la valeur d'obj pour valeur
*/
void setObjetValeur(Objet* obj, const int valeur);

/**
* \brief Preconditions : nom est une chaine de longueur <150
* <br /> Postconditions : change la description d'obj pour description
*/
void setObjetDescription(Objet* obj, const char* description);

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
void afficherObjet(const Objet* obj);

/**
* \brief Preconditions : fichier1 et fichier2 sont des noms de fichiers accessibles au programme
* <br /> Postconditions : copie le contenu de fichier2 dans fichier1
*/
void copierFichier (char* fichier1, const char* fichier2);

#endif
