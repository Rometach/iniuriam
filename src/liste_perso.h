#ifndef __listePersonnage_h__
#define __listePersonnage_h__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <SDL/SDL.h>
#include "inventaire.h"
#include "capacite.h"
#include "constante.h"
#include "equipement.h"
#include "personnage.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

typedef struct
{
    Personnage* perso;
    int nbrPerso;
}Liste_Perso;


/**
* \brief Preconditions : liste n'est pas initialisée
* <br /> Postconditions : initialise liste qui est prête à contenir nbr Personnages
*/
void listePersoInit(Liste_Perso* liste, int nbr);

/**
* \brief Preconditions : ?
* <br /> Postconditions : ?
*/
void tabListePerso(Liste_Perso* liste, int nbr);

/**
* \brief Preconditions : ?
* <br /> Postconditions : ?
*/
void tabListePersoInitPNJ(Liste_Perso* liste, Objet* tabObjets);

/**
* \brief Preconditions : ?
* <br /> Postconditions : ?
*/
void setListePerso(Liste_Perso* liste, Personnage* perso);

/**
* \brief Preconditions : liste est initialisée
* <br /> Postconditions : retourne le nombre de Personnages que liste peut contenir
*/
int getNbrPerso(Liste_Perso* liste);

/**
* \brief Preconditions : liste est initialisée
* <br /> Postconditions : change le nombre de Personnages que liste peut contenir pour i
*/
void setNbrPerso(Liste_Perso* liste, int i);

/**
* \brief Preconditions : liste est initialisée
* <br /> Postconditions : liste est libérée
*/
void listePersoLibere(Liste_Perso* liste);

/**
* \brief Preconditions : ?
* <br /> Postconditions : ?
*/
void tabListePersoLibere(Liste_Perso* liste);



/**
* \brief Preconditions : /
* <br /> Postconditions : retourne le nombre de Groupes définis dans GroupesPNJ.txt
*/
int getNbGroupesPNJ();

/**
* \brief Preconditions : tabPNJ est l'adresse d'un tableau de Liste_Perso, non initialisé
*                        tabObjets est le tableau de tous les Objets, bien initialisé
* <br /> Postconditions : tabPNJ est initialisé en un tableau de Liste_Perso
*                         chacune d'entre elles contient un groupe de personnages
*/
void initialiserTousLesPNJ2(Liste_Perso** tabPNJ, Objet* tabObjets);

/**
* \brief Preconditions : tabPNJ est initialisé
* <br /> Postconditions : tabPNJ est libéré
*/
void libererTousLesPNJ2(Liste_Perso** tabPNJ);


#endif
