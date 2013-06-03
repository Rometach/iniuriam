#ifndef menu_H
#define menu_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <FMOD/fmod.h>

#include "constante.h"
#include "scanf_SDL.h"
#include "personnage.h"
#include "mission.h"
#include "deplacement.h"

typedef struct
{
    char nom [50];
    Personnage* joueur;
    int nbJoueur;
    int* missionsAccomplies;
    int nbMission;
    int missionActuelle;
    char numCarte;
} Partie;


/**
* \brief Preconditions : jeu n'est pas initialisé, 0<nbJoueur<5, nbMission<nombre de missions dans Missions.txt, missionActuelle est une mission de Missions.txt.
* <br /> Postconditions : initialise jeu avec les paramètres nom, liste, nbJoueur, missionsAccomplies, nbMission, missionActuelle.
*/
void partieInit (Partie* jeu,char nom [50], Personnage* liste, int nbJoueur,int* missionsAccomplies,int nbMission,int missionActuelle,int numCarte);

/**
* \brief Preconditions : jeu est initialisé.
* <br /> Postconditions : jeu est libéré.
*/
void partieLibere (Partie* jeu);

/**
* \brief Preconditions : jeu est initialisé.
* <br /> Postconditions : retourne le nombre de joueur de jeu.
*/
void getPartieNom (Partie* jeu,char nom[50]);

/**
* \brief Preconditions : jeu est initialisé.
* <br /> Postconditions : retourne la liste des joueurs de jeu.
*/
Personnage* getPartieJoueurs (Partie* jeu);

/**
* \brief Preconditions : jeu est initialisé,0<=i<4.
* <br /> Postconditions : retourne le ieme joueur de jeu.
*/
Personnage* getPartieJoueurI (Partie* jeu, int i);

/**
* \brief Preconditions : jeu est initialisé.
* <br /> Postconditions : retourne le nombre de joueur de jeu.
*/
int getPartieNbJoueur (Partie* jeu);

/**
* \brief Preconditions : jeu est initialisé,0<=i<nombre max de mission dans Missions.txt.
* <br /> Postconditions : retourne la ieme mission accomplie de jeu.
*/
int getPartieMissionAccomplie (Partie* jeu,int i);

/**
* \brief Preconditions : jeu est initialisé.
* <br /> Postconditions : retourne le nombre de missions accomplies de jeu.
*/
int getPartieNbMission (Partie* jeu);

/**
* \brief Preconditions : jeu est initialisé, mission ne l'est pas, et tabObj contient tous les objet de Iniuriam.
* <br /> Postconditions : copie la mission actuelle de jeu dans mission.
*/
void getPartieMissionActuelle (Partie* jeu,Mission* mission, Objet* tabObj);

/**
* \brief Preconditions : jeu est initialisé.
* <br /> Postconditions : copie la mission actuelle de jeu dans mission.
*/
int getPartieMissionActuelleType (Partie* jeu);

/**
* \brief Preconditions : SDL est initialisé
* <br /> Postconditions : gère les évenements du menu principal du jeu. Retourne le type d'event réalisé.
*/
char eventMenu();

/**
* \brief Preconditions : police et ecran sont initalisés.
*                        nb<10, 0<=choix<nb, position>0
* <br /> Postconditions : affiche les différentes pages du menu de création de partie d'Iniuriam.
*                         retourne 0 si l'utilisateur quitte SDL, 7 sinon.
*/
int afficherPage (SDL_Surface *ecran,TTF_Font *police, char texte_SDL[10][150],int nb,int choix,int position,int* haut,int* bas,int* page);

/**
* \brief Preconditions : police, jeu et ecran sont initalisés.
*                        sauvegarde correspond à la chaine "Sauvegarde X" ou X=A, B ou C
* <br /> Postconditions : affiche les différentes pages du menu de création de partie d'Iniuriam.
*                         retourne 0 si l'utilisateur quitte SDL, 7 sinon.
*/
char nouvellePartie (SDL_Surface *ecran,TTF_Font *police,Partie* jeu,char* sauvegarde,FMOD_SYSTEM *system);

/**
* \brief Preconditions : police, ecran, systeme et musique sont initalisés.
* <br /> Postconditions : affiche les différentes pages du menu options d'Iniuriam.
*                         retourne 0 si l'utilisateur quitte SDL, 7 sinon.
*/
char afficherOptions(SDL_Surface *ecran,TTF_Font *police,FMOD_SYSTEM *system,FMOD_SOUND **musique);

/**
* \brief Preconditions : police, partie et ecran sont initalisés.
* <br /> Postconditions : affiche les différentes pages du menu principal si jeu=0 ou du menu pause d'Iniuriam sinon.
*                         retourne 0 si l'utilisateur quitte le jeu ou SDL, 9 sinon.
*/
char afficherMenu (SDL_Surface *ecran, char jeu,TTF_Font *police,Partie* partie);

void testMemoire();

int mainMenu();
#endif
