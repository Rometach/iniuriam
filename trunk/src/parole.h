#ifndef __parole_h__
#define __parole_h__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "personnage.h"
#include "mission.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

typedef struct
{
    Personnage* perso1;     /**Le joueur*/
    Personnage* perso2;     /**Le PNJ*/
    char humeur;            /**Varie entre 0 et 100*/
} Dialogue;

/**
* \brief Preconditions : dialogue n'est pas initialisé
* <br /> Postconditions : dialogue est initialisé avec les personnages perso1 et perso2
*/
void dialogueInit (Dialogue* dialogue, Personnage* perso1, Personnage* perso2);

/**
* \brief Preconditions : dialogue est initialisé
* <br /> Postconditions : l'humeur de dialogue est modifiée pour correspondre à hum ; retourne la valeur courante de l'humeur
*/
char setDialogueHumeur (Dialogue* dialogue, const int hum);

/**
* \brief Preconditions : question est une chaîne de caractères présente dans le fichier ; reponse a une longueur d'au moins TAILLE_MAX_DIAL
* <br /> Postconditions : une réponse correspondant à question est copiée dans réponse
*/
void setReponse (const char* question, char* reponse);

/**
* \brief Preconditions : dialogue est initialisé, info a une longueur d'au moins TAILLE_MAX_DIAL
* <br /> Postconditions : copie dans info l'information (éventuellement la réponse négative) retournée ; retourne la valeur courante de l'humeur
*/
char obtenirInfo(Dialogue* dialogue, char* info, Mission* mission, Objet* tabObjets);

/**
* \brief Preconditions : dialogue est initialisé, info a une longueur d'au moins TAILLE_MAX_DIAL
                         le PNJ doit parler dans le cadre de la mission en cours
* <br /> Postconditions : copie dans info ce que dit le PNJ ; retourne la valeur courante de l'humeur
*/
char parlerQuete(Dialogue* dialogue, char* info);

/**
* \brief Preconditions : dialogue est initialisé, rep a une longueur d'au moins TAILLE_MAX_DIAL
* <br /> Postconditions : la somme argent est transférée d'un personnage vers l'autre, avec un éventuel effet sur l'humeur du second ;
*                          copie dans rep la reponse retournée ;
*                          retourne la valeur courante de l'humeur
*/
char soudoyer(Dialogue* dialogue, int argent, char* rep);

/**
* \brief Preconditions : dialogue est initialisé, rep a une longueur d'au moins TAILLE_MAX_DIAL
* <br /> Postconditions : le premier personnage menace le second, avec un éventuel effet sur son humeur ;
*                          copie dans rep la reponse retournée ;
*                          retourne la valeur courante de l'humeur
*/
char menacer(Dialogue* dialogue, char* rep);

/**
* \brief Preconditions : dialogue est initialisé, rep a une longueur d'au moins TAILLE_MAX_DIAL
* <br /> Postconditions : le premier personnage tente de séduire le second, avec un éventuel effet sur son humeur ;
*                          copie dans rep la reponse retournée ;
*                          retourne la valeur courante de l'humeur
*/
char seduire(Dialogue* dialogue, char* rep);

/**
* \brief Preconditions : dialogue est initialisé
* <br /> Postconditions : le premier personnage tente de négocier avec le second le prix d'un objet (valeur) ;
*                         valeur est modifiée en conséquence
*/
void marchander (Dialogue* dialogue, int* valeur);

/**
* \brief Preconditions : dialogue est initialisé, objet est dans l'inventaire du PNJ, rep a une longueur d'au moins TAILLE_MAX_DIAL
* <br /> Postconditions : l'objet objet est vendu par le PNJ au joueur si cela est possible, le joueur peut tenter de négocier le prix d'achat ;
*                          copie dans rep la reponse retournée ;
*                          retourne la valeur courante de l'humeur
*/
char acheter(Dialogue* dialogue, Objet* objet, char* rep);

/**
* \brief Preconditions : dialogue est initialisé, objet est dans l'inventaire du joueur, rep a une longueur d'au moins TAILLE_MAX_DIAL
* <br /> Postconditions : l'objet objet est acheté par le PNJ au joueur si cela est possible ; le joueur peut tenter de négocier le prix de vente ;
*                          copie dans rep la reponse retournée ;
*                          retourne la valeur courante de l'humeur
*/
char vendre(Dialogue* dialogue, Objet* objet, char* rep);


int mainParole ();
#endif
