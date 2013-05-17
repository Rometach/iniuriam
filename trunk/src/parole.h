#ifndef __parole_h__
#define __parole_h__

#include <stdio.h>
#include <stdlib.h>
#include "personnage.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

typedef struct
{
    Personnage* perso1;     /*Le joueur*/
    Personnage* perso2;     /*Le PNJ*/
    char humeur;            /*entre 0 et 100*/
} Dialogue;

/**
* \brief Preconditions : dialogue n'est pas initialis�
* <br /> Postconditions : dialogue est initialis� avec les personnages perso1 et perso2
*/
void dialogueInit (Dialogue* dialogue, Personnage* perso1, Personnage* perso2);

/**
* \brief Preconditions : dialogue est initialis�
* <br /> Postconditions : l'humeur de dialogue est modifi�e pour correspondre � hum ; retourne la valeur courante de l'humeur
*/
char setDialogueHumeur (Dialogue* dialogue, int hum);

/**
* \brief Preconditions : question est une cha�ne de caract�res pr�sente dans le fichier ; reponse a une longueur d'au moins TAILLE_MAX_DIAL
* <br /> Postconditions : une r�ponse correspondant � question est copi�e dans r�ponse
*/
void setReponse (char* question, char* reponse);

/**
* \brief Preconditions : dialogue est initialis�, info a une longueur d'au moins TAILLE_MAX_DIAL
* <br /> Postconditions : copie dans info l'information (�ventuellement la r�ponse n�gative) retourn�e ; retourne la valeur courante de l'humeur
*/
char obtenirInfo(Dialogue* dialogue, char* info, SDL_Surface* ecran);

/**
* \brief Preconditions : dialogue est initialis�, info a une longueur d'au moins TAILLE_MAX_DIAL
                         le PNJ doit parler dans le cadre de la mission en cours
* <br /> Postconditions : copie dans info ce que dit le PNJ ; retourne la valeur courante de l'humeur
*/
char parlerQuete(Dialogue* dialogue, char* info, SDL_Surface* ecran);

/**
* \brief Preconditions : dialogue est initialis�, rep a une longueur d'au moins TAILLE_MAX_DIAL
* <br /> Postconditions : la somme argent est transf�r�e d'un personnage vers l'autre, avec un �ventuel effet sur l'humeur du second ;
*                          copie dans rep la reponse retourn�e ;
*                          retourne la valeur courante de l'humeur
*/
char soudoyer(Dialogue* dialogue, int argent, char* rep, SDL_Surface* ecran);

/**
* \brief Preconditions : dialogue est initialis�, rep a une longueur d'au moins TAILLE_MAX_DIAL
* <br /> Postconditions : le premier personnage menace le second, avec un �ventuel effet sur son humeur ;
*                          copie dans rep la reponse retourn�e ;
*                          retourne la valeur courante de l'humeur
*/
char menacer(Dialogue* dialogue, char* rep, SDL_Surface* ecran);

/**
* \brief Preconditions : dialogue est initialis�, rep a une longueur d'au moins TAILLE_MAX_DIAL
* <br /> Postconditions : le premier personnage tente de s�duire le second, avec un �ventuel effet sur son humeur ;
*                          copie dans rep la reponse retourn�e ;
*                          retourne la valeur courante de l'humeur
*/
char seduire(Dialogue* dialogue, char* rep, SDL_Surface* ecran);

/**
* \brief Preconditions : dialogue est initialis�
* <br /> Postconditions : le premier personnage tente de n�gotier avec le second le prix d'un objet (valeur) ;
*                          retourne la valeur finale apr�s negotiation
*/
int marchander (Dialogue* dialogue, int valeur);

/**
* \brief Preconditions : dialogue est initialis�, objet est dans l'inventaire du PNJ, rep a une longueur d'au moins TAILLE_MAX_DIAL
* <br /> Postconditions : l'objet objet est vendu par le PNJ au joueur si cela est possible, le joueur peut tenter de n�gotier le prix d'achat ;
*                          copie dans rep la reponse retourn�e ;
*                          retourne la valeur courante de l'humeur
*/
char acheter(Dialogue* dialogue, Objet* objet, char* rep, SDL_Surface* ecran);

/**
* \brief Preconditions : dialogue est initialis�, objet est dans l'inventaire du joueur, rep a une longueur d'au moins TAILLE_MAX_DIAL
* <br /> Postconditions : l'objet objet est achet� par le PNJ au joueur si cela est possible , le joueur peut tenter de n�gotier le prix de vente ;
*                          copie dans rep la reponse retourn�e ;
*                          retourne la valeur courante de l'humeur
*/
char vendre(Dialogue* dialogue, Objet* objet, char* rep, SDL_Surface* ecran);


int mainParole ();
#endif
