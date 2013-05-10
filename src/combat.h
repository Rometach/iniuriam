#ifndef __combat_h__
#define __combat_h__

#include <stdio.h>
#include <stdlib.h>
#include "personnage.h"
#include "terrain.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

typedef struct
{
    Personnage* perso;
    char camp;
    int ordre;
    int posX;
    int posY;
    char orientation; /*Correspond à l'orientation du regard du combattant sur le terrain :
                        1 vers la gauche
                        2 vers le haut
                        3 vers la bas
                        4 vers le droite*/
    char derniereAction;    /*Correspond à la dernière action effectuée :
                            0 inconnu
                            1 attaque standard
                            2 attaque brutale
                            3 attaque prudente
                            4 feinte
                            3 visée
                            3 préparation de parade*/
    char arene [TAILLE_MAX][TAILLE_MAX];
} Combattant;


/**
* \brief Preconditions : ???
* <br /> Postconditions : initialise l'arene tab en fonction de terrain
*/
void areneInit (Terrain* terrain, char tab[TAILLE_MAX][TAILLE_MAX]);




/**
* \brief Preconditions : tab est un tableau de longueur l-1, trié dans l'ordre croissant
* <br /> Postconditions : l'élément e est inséré dans tab, qui est toujours trié dans l'ordre croissant
*/
char tri (char* tab, char e, int l);


/**
* \brief Preconditions : liste contient l personnages prêts à combattre, groupe est un tableau de longueur l non-initialisé
* <br /> Postconditions : les Combattants de groupe sont initialisés avec les personnages de liste
*/
void initCombattant (Personnage* liste, int l, Combattant* groupe);


/**
* \brief Preconditions : ???
* <br /> Postconditions : ???
*/
void initPosGauche (Combattant* combattant, char arene[TAILLE_MAX][TAILLE_MAX]);


/**
* \brief Preconditions : ???
* <br /> Postconditions : ???
*/
void initPosDroite (Combattant* combattant, char arene[TAILLE_MAX][TAILLE_MAX]);


/**
* \brief Preconditions : ???
* <br /> Postconditions : ???
*/
void initPosCombattant (Combattant*liste, int l, char arene[TAILLE_MAX][TAILLE_MAX]);


/**
* \brief Preconditions : ???
* <br /> Postconditions : ???
*/
void ordreGroupe (Combattant* liste, int l);


/**
* \brief Preconditions : ???
* <br /> Postconditions : ???
*/
void initCombat (Personnage* liste, int l, Combattant* groupe, char arene[TAILLE_MAX][TAILLE_MAX]);


/**
* \brief Preconditions : ???
* <br /> Postconditions : ???
*/
char estDansChampDeVision (char arene[TAILLE_MAX][TAILLE_MAX], int x, int y, int z, int t,char orientation);


/**
* \brief Preconditions : ???
* <br /> Postconditions : ???
*/
char estLaFin (Combattant* groupe,int l);


/**
* \brief Preconditions : ???
* <br /> Postconditions : ???
*/
int testNbCombattant (Combattant* groupe, int l, char arene [TAILLE_MAX][TAILLE_MAX]);





/**
* \brief Preconditions : ???
* <br /> Postconditions : ???
*/
int attaquer (Personnage* attaquant, Personnage* defenseur, int degat, int bonusA, int bonusD);

/**
* \brief Preconditions : ???
* <br /> Postconditions : ???
*/
int attaqueBrutale (Personnage* attaquant, Personnage* defenseur, int degat, int bonusA, int bonusD);

/**
* \brief Preconditions : ???
* <br /> Postconditions : ???
*/
int attaquePrudente (Personnage* attaquant, Personnage* defenseur, int degat, int bonusA, int bonusD);

/**
* \brief Preconditions : ???
* <br /> Postconditions : ???
*/
int preparerParade (Personnage* attaquant, Personnage* defenseur, int degat, int bonusA, int bonusD);

/**
* \brief Preconditions : ???
* <br /> Postconditions : ???
*/
int viserPourAttaque (Personnage* attaquant, Personnage* defenseur, int degat, int bonusA, int bonusD);

/**
* \brief Preconditions : ???
* <br /> Postconditions : ???
*/
int feinte (Personnage* attaquant, Personnage* defenseur, int degat, int bonusA, int bonusD);




/**
* \brief Preconditions : ???
* <br /> Postconditions : ???
*/
void tourIA (Combattant* groupe, int j, int l, char arene [TAILLE_MAX][TAILLE_MAX]);


/**
* \brief Preconditions : ???
* <br /> Postconditions : ???
*/
void tourJoueur (Combattant* groupe, int j, int l, char arene [TAILLE_MAX][TAILLE_MAX]);


/**
* \brief Preconditions : ???
* <br /> Postconditions : ???
*/
void combat (Combattant* groupe, int l, char arene [TAILLE_MAX][TAILLE_MAX]);


int mainCombat();

#endif
