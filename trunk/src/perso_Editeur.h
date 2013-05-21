#ifndef __perso_Editeur_h__
#define __perso_Editeur_h__

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
    char race;/*0 : inconnu
                1 : humain
                2 : cyborg
                3 : sicaris
                4 : medarsins
                */
    char sexe;/*0 : inconnu
                1 : homme
                2 : femme*/
    char faction;/*0 : inconnu
                1 : Sistéen
                2 : Heredian
                3 : Marchand
                */
    char carriere;
    int argent;
    int experience;
    int niveau;

    char attaque;
    char defense;
    char intelligence;
    char agilite;
    char charisme;
    int ptDeVie;

    int posX;
    int posY;

	SDL_Surface* avatar;

} Personnage;

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne le nom de perso
*/
void getPersoNom(char* maChaine, Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne la race du perso
*/
char getPersoRace(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne la faction du perso
*/
char getPersoFaction(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : copie le nom de la faction de perso dans chaine
*/
void getPersoFactionNom(char* chaine, Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne le sexe du perso
*/
char getPersoSexe(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne la carriere du perso
*/
char getPersoCarriere(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne le nom de la carriere dans s
*/
void getCarriereNom(char carriere, char* s);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne l'argent du perso
*/
int getPersoArgent(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne l'experience du perso
*/
int getPersoExperience(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne l'attaque du perso
*/
char getPersoAttaque(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne la defense du perso
*/
char getPersoDefense(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne l'intelligence du perso
*/
char getPersoIntelligence(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne l'agilite du perso
*/
char getPersoAgilite(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne le charsime du perso
*/
char getPersoCharisme(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne les points de vie du perso
*/
int getPersoPtDeVie(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : change la position en X du perso
*/
void setPersoPosX(Personnage *perso, int x);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : récupère la position en X du perso
*/
int getPersoPosX(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : change la position en Y du perso
*/
void setPersoPosY(Personnage *perso, int y);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : récupère la position en Y du perso
*/
int getPersoPosX(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : fixe la somme d'argent du perso
*/
void setPersoArgent(Personnage *perso, int somme);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : ajoute pdv aux points de vie de perso
*/
void addPersoPtDeVie(Personnage *perso, int pdv);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : 1 obj est ajouté à l'inventaire de perso
*/

int getNbPNJ();

/**
* \brief Preconditions : tabPNJ n'est pas initialisé
* <br /> Postconditions : initialise tous les PNJ dans tabPNJ
*/
void initialiserTousLesPNJ(Personnage** tabPNJ);

/**
* \brief Preconditions : tabPNJ est initialisé
* <br /> Postconditions : libère tabPNJ
*/
void libererTousLesPNJ(Personnage* tabPNJ);
#endif

