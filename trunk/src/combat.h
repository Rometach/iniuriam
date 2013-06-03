#ifndef __combat_h__
#define __combat_h__

#include <assert.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "personnage.h"
#include "terrain.h"
#include "constante.h"
#include "deplacement.h"


/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

typedef struct
{
    Personnage* perso;
    char camp;
    int ordre; /**Correspond à la position du combattant dans l'ordre de passage au début du combat
                 Est calculé grâce à l'agilité du personnage associé*/
    int posX;
    int posY;
    char orientation; /**Correspond à l'orientation du regard du combattant sur le terrain :
                        1 vers la gauche
                        2 vers le haut
                        3 vers le bas
                        4 vers la droite*/
    char derniereAction;    /**Correspond à la dernière action effectuée :
                            0 inconnu
                            1 attaque standard
                            2 attaque brutale
                            3 attaque prudente
                            4 feinte
                            5 visée
                            6 préparation de parade*/
    char arene [TAILLE_MAX_H][TAILLE_MAX_L];    /**L'arene du combat*/
} Combattant;


/**
* \brief Preconditions : terrain est initialisé
* <br /> Postconditions : initialise l'arene tab en fonction de terrain
*/
void areneInit (Terrain* terrain, char tab[TAILLE_MAX_H][TAILLE_MAX_L]);


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
* \brief Preconditions : combattant est initialisé
* <br /> Postconditions : retourne le personnage associé à combattant
*/
Personnage* getCombattantPerso(Combattant* combattant);

/**
* \brief Preconditions : combattant est initialisé
* <br /> Postconditions : retourne le camp de combattant
*/
char getCombattantCamp(Combattant* combattant);

/**
* \brief Preconditions : combattant est initialisé
* <br /> Postconditions : retourne l'ordre de combattant
*/
int getCombattantOrdre(Combattant* combattant);

/**
* \brief Preconditions : combattant est initialisé
* <br /> Postconditions : retourne la position en X de combattant sur l'arene
*/
int getCombattantPosX(Combattant* combattant);

/**
* \brief Preconditions : combattant est initialisé
* <br /> Postconditions : retourne la position en Y de combattant sur l'arene
*/
int getCombattantPosY(Combattant* combattant);

/**
* \brief Preconditions : combattant est initialisé
* <br /> Postconditions : retourne l'orientation de combattant
*/
char getCombattantOrientation(Combattant* combattant);

/**
* \brief Preconditions : combattant est initialisé
* <br /> Postconditions : retourne la dernière action de combattant
*/
char getCombattantDerniereAction(Combattant* combattant);

/**
* \brief Preconditions : combattant est initialisé
* <br /> Postconditions : copie l'arene de combattant dans arene
*/
void getCombattantArene(Combattant* combattant, char arene[TAILLE_MAX_H][TAILLE_MAX_L]);

/**
* \brief Preconditions : combattant est initialisé
* <br /> Postconditions : positionne le combattant en commençant par la case la plus en haut à gauche si possible
*/
void initPosGauche (Combattant* combattant, char arene[TAILLE_MAX_H][TAILLE_MAX_L]);


/**
* \brief Preconditions : combattant est initialisé
* <br /> Postconditions : positionne le combattant en commençant par la case la plus en bas à droite si possible
*/
void initPosDroite (Combattant* combattant, char arene[TAILLE_MAX_H][TAILLE_MAX_L]);


/**
* \brief Preconditions : les l combattants sont initialisés
* <br /> Postconditions : positionne les l combattant de liste dans l'arene
*/
void initPosCombattant (Combattant*liste, int l, char arene[TAILLE_MAX_H][TAILLE_MAX_L]);


/**
* \brief Preconditions : les l combattants sont initialisés
* <br /> Postconditions : les l combattants de liste sont ordonnés par ordre décroissant de leur agilité
*/
void ordreGroupe (Combattant* liste, int l);


/**
* \brief Preconditions : les l personnages sont initialisés
* <br /> Postconditions : les l personnages de la liste deviennent des combattants et sont placés sur l'arene
*/
void initCombat (Personnage* liste, int l, Combattant* groupe, char arene[TAILLE_MAX_H][TAILLE_MAX_L]);


/**
* \brief Preconditions : 0<=x<TAILLE_MAX, 0<=x<TAILLE_MAX, 0<=x<TAILLE_MAX, 0<=x<TAILLE_MAX, 0<orientation<=4
* <br /> Postconditions : renvoie 1 si les l membres du groupe sont dans le même camp, 0 sinon
*/
char estDansChampDeVision (char arene[TAILLE_MAX_H][TAILLE_MAX_L], int x, int y, int z, int t,char orientation);


/**
* \brief Preconditions : groupe est initialisé
* <br /> Postconditions : renvoie 1 si les l membres du groupe sont dans le même camp, 0 sinon
*/
char estLaFin (Combattant* groupe, int l, int campJoueur);

/**
* \brief Preconditions : comb1 est initialisé, pas comb2
* <br /> Postconditions : copie le contenu de comb1 dans comb2
*/
void copieCombattant (Combattant* comb1, Combattant* comb2);

/**
* \brief Preconditions : groupe est initialisé
* <br /> Postconditions : vérifie si des membres du groupe ont été tué et les retire de l'arene
*                         l correspond au nombre de combattant
*                         retourne le nombre de combattant restant
*/
int testNbCombattant (Combattant* groupe, int l, char arene [TAILLE_MAX_H][TAILLE_MAX_L]);

/**
* \brief Preconditions : attaquant, defenseur sont initialisés
* <br /> Postconditions : l'attaquant tente une attaque sur le defenseur, qui tente lui de se défendre, avec une arme infligeant en moyenne degats.
*                         type correspond au type d'attaque à effectuer: brutale,prudente,feinte,ou avec visée.
*                         distance permet de déterminer si l'attaque est à distance ou au corps à corps.
*                         les bonus influent directement sur les tentatives d'attaque et de défense.
*                         retourne les dégats infligés au defenseur.
*/
int attaquer (Combattant* attaquant, Combattant* defenseur, int degats, int bonusA, int bonusD, int bonusAg, int bonusEsc, int type,char distance);

/**
* \brief Preconditions : defenseur est initialisé
* <br /> Postconditions : vérifie si le defenseur a effectué une attaque prudente ou une parade au tour précedent
*/
void verifierDerniereAction (Combattant* defenseur,int* bonusDef,int* bonusEsc);

/**
* \brief Preconditions : attaquant et defenseur sont initialisés
* <br /> Postconditions : ajoute de l'expérience à la compétence type de l'attaquant ou à la compétence esquive du defenseur en fonction de rapport
*/
void ajouterCompetenceAttaque (Combattant* attaquant,Combattant* defenseur, int rapport, char type);

/**
* \brief Preconditions : attaquant et defenseur sont initialisés
* <br /> Postconditions : l'attaquant attaque brutalemment le défenseur, avec une arme infligeant en moyenne degat.
*                         type permet de déterminer si l'attaque est à distance ou au corps à corps.
*/
void attaqueBrutale (Combattant* attaquant, Combattant* defenseur, int degat, char type);

/**
* \brief Preconditions : attaquant et defenseur sont initialisés
* <br /> Postconditions : l'attaquant attaque prudemment le défenseur, avec une arme infligeant en moyenne degat.
*                         type permet de déterminer si l'attaque est à distance ou au corps à corps.
*/
void attaquePrudente (Combattant* attaquant, Combattant* defenseur, int degat,char type);

/**
* \brief Preconditions : attaquant et defenseur sont initialisés
* <br /> Postconditions : l'attaquant feint et attaque le défenseur, avec une arme infligeant en moyenne degat.
*                         type permet de déterminer si l'attaque est à distance ou au corps à corps.
*/
void feinte (Combattant* attaquant, Combattant* defenseur, int degat,char type);

/**
* \brief Preconditions : attaquant et defenseur sont initialisés
* <br /> Postconditions : l'attaquant vise et attaque le défenseur, avec une arme infligeant en moyenne degat.
*                         type permet de déterminer si l'attaque est à distance ou au corps à corps.
*/
void viserPourAttaque (Combattant* attaquant, Combattant* defenseur, int degat,char type);

/**
* \brief Preconditions : attaquant est initialisé
* <br /> Postconditions : l'attaquant prépare une parade pour une éventuelle prochaine attaque.
*/
void preparerParade (Combattant* attaquant);

/**
* \brief Preconditions : les l combattants de groupe sont initialisés,0<=j<l.
* <br /> Postconditions : l'ordinateur execute le tour de l'IA dans le combat.
*/
void tourIA (Combattant* groupe, int j, int l, char arene [TAILLE_MAX_H][TAILLE_MAX_L]);

/**
* \brief Preconditions : les l combattants de groupe sont initialisés,0<=j<l.
* <br /> Postconditions : correspond au tour du joueur dans le combat.
*/
void tourJoueur (Combattant* groupe, int j, int l, char arene [TAILLE_MAX_H][TAILLE_MAX_L]);

/**
* \brief Preconditions : les l personnages de liste sont initialisés
* <br /> Postconditions : un combat s'engage entre les personnage jusqu'à ce que l'un des camp l'emporte.
*/
void combat (Personnage* liste, int l, char arene [TAILLE_MAX_H][TAILLE_MAX_L]);

/**
* \brief Preconditions : arene,attaquant et defenseurs sont initialisés.
* <br /> Postconditions : retourne 1 si le defenseur est à portee de l'attaquant, 0 sinon.
*/
char estAPortee (char arene[TAILLE_MAX_H][TAILLE_MAX_L],Combattant* attaquant, Combattant* defenseur,int portee);

/**
* \brief Preconditions : arene et perso sont initialisés.
* <br /> Postconditions : affiche la portee de l'arme de perso.
*/
void afficherPortee (char arene[TAILLE_MAX_H][TAILLE_MAX_L],Combattant* perso, int portee);

void effacerPortee (char arene[TAILLE_MAX_H][TAILLE_MAX_L],Combattant* perso, int portee);

/**
* \brief Preconditions : combattant, nbDeplacement, arene initialisé
* <br /> Postconditions : teste si la case est accesible et si on a encore des déplacements, puis déplacement le personnage d'une case vers la droite
*/
int deplaceCombDroite( Combattant* combattant, int nbDeplacement, char arene[TAILLE_MAX_H][TAILLE_MAX_L]);

/**
* \brief Preconditions : combattant, nbDeplacement, arene initialisé
* <br /> Postconditions : teste si la case est accesible et si on a encore des déplacements, puis déplacement le personnage d'une case vers la gauche
*/
int deplaceCombGauche( Combattant* combattant, int nbDeplacement, char arene[TAILLE_MAX_H][TAILLE_MAX_L]);

/**
* \brief Preconditions : combattant, nbDeplacement, arene initialisé
* <br /> Postconditions : teste si la case est accesible et si on a encore des déplacements, puis déplacement le personnage d'une case vers le bas
*/
int deplaceCombBas( Combattant* combattant, int nbDeplacement, char arene[TAILLE_MAX_H][TAILLE_MAX_L]);

/**
* \brief Preconditions : combattant, nbDeplacement, arene initialisé
* <br /> Postconditions : teste si la case est accesible et si on a encore des déplacements, puis déplacement le personnage d'une case vers le haut
*/
int deplaceCombHaut( Combattant* combattant, int nbDeplacement, char arene[TAILLE_MAX_H][TAILLE_MAX_L]);


int mainCombat();

#endif
