#ifndef __deplacement_h__
#define __deplacement_h__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define TAILLE_MAX 22

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

/**
* \brief Preconditions : 0<=y<TAILLE_MAX
* <br /> Postconditions : vérifie l'accessibilité de la case y de tab : retourne 0 si inaccessible, 1 sinon.
*/
char deplacerCase (int y, char tab [TAILLE_MAX]);

/**
* \brief Preconditions : 0<=x<TAILLE_MAX
* <br /> Postconditions : vérifie si le déplacement vers la case (x) de tab est un retour en arrière : retourne 0 si c'est le cas, 1 sinon.
*/
char testRetour (int x, char tab [TAILLE_MAX]);

/**
* \brief Preconditions : 0<=col<TAILLE_MAX
* <br /> Postconditions : retourne la yième colonne de tab.
*/
void getColonne(int col, char tab[TAILLE_MAX][TAILLE_MAX], char*tamp);

/**
* \brief Preconditions : /
* <br /> Postconditions : retourne le minimum de a et b.
*/
char min (char a, char b);

/**
* \brief Preconditions : /
* <br /> Postconditions : affiche un tableau à 2 dimensions, ici tab.
*/
void afficherTab2D (char tab[TAILLE_MAX][TAILLE_MAX]);

/**
* \brief Preconditions : 0<=x<TAILLE_MAX, 0<=y<TAILLE_MAX, 0<i<=4
* <br /> Postconditions : retourne la case 2 ou 3 la plus proche de la case (x,y) de tab en tenant compte de la direction empruntée i.
*/
char chercher2 (char tab[TAILLE_MAX][TAILLE_MAX],int x, int y,char i);

/**
* \brief Preconditions : 0<=x<TAILLE_MAX, 0<=y<TAILLE_MAX, 0<i<=4
* <br /> Postconditions : bloque les cases adjacentes à la case (x,y) de tab qui ne correspondent pas à la direction empruntée i.
*/
void tunnel (int x, int y, char tab [TAILLE_MAX][TAILLE_MAX], int i);

/**
* \brief Preconditions : 0<=x<TAILLE_MAX, 0<=y<TAILLE_MAX, 0<i<=4
* <br /> Postconditions : libère les cases adjacentes à la case (x,y) de tab.
*/
void reinitTunnel (int x, int y, char tab [TAILLE_MAX][TAILLE_MAX]);

/**
* \brief Preconditions : /
* <br /> Postconditions : retourne le minimum de droite, gauche, haut et bas. L'ordre des paramètres détermine les priorités en cas d'égalité.
*/
char quatresChemins (char droite, char haut, char bas, char gauche);

/**
* \brief Preconditions : 0<=x<TAILLE_MAX, 0<=y<TAILLE_MAX, 0<=z<TAILLE_MAX, 0<=t<TAILLE_MAX
* <br /> Postconditions : rempli tab en faisant apparaitre un chemin pour aller de la case (x,y) à la case (z,t).
*/
char deplacementIA (int x, int y, int z, int t, char tab [TAILLE_MAX][TAILLE_MAX]);

/**
* \brief Preconditions : 0<=x<TAILLE_MAX, 0<=y<TAILLE_MAX, 0<=z<TAILLE_MAX, 0<=t<TAILLE_MAX
* <br /> Postconditions : trace un chemin dans tab pour aller de la case (x,y) à la case (z,t).
*/
void chemin (int x,int y, int z, int t, char tab[TAILLE_MAX][TAILLE_MAX]);

#endif
