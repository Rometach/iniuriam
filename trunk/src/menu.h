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

typedef struct
{
    char nom [50];
    Personnage** joueur;
    int nbJoueur;
    char missionsAccomplies [30][50];
    int nbMission;
    char missionActuelle[50];
} Partie;


/**
* \brief Preconditions : jeu n'est pas initialisé, 0<nbJoueur<5, nbMission<nombre de missions dans Missions.txt, missionActuelle est une mission de Missions.txt.
* <br /> Postconditions : initialise jeu avec les paramètres nom, liste, nbJoueur, missionsAccomplies, nbMission, missionActuelle.
*/
void partieInit (Partie* jeu,char nom [50], Personnage* liste, int nbJoueur,char missionsAccomplies[30][50],int nbMission,char missionActuelle[50]);

/**
* \brief Preconditions : jeu est initialisé.
* <br /> Postconditions : jeu est libéré.
*/
void partieLibere (Partie* jeu);

/**
* \brief Preconditions : jeu est initialisé.
* <br /> Postconditions : retourne la liste des joueurs de jeu.
*/
Personnage** getPartieJoueurs (Partie* jeu);

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
* <br /> Postconditions : copie la ieme mission accomplie de jeu dans tampon.
*/
void getPartieMissionAccomplie (Partie* jeu,int i,char tampon [50]);

/**
* \brief Preconditions : jeu est initialisé.
* <br /> Postconditions : retourne le nombre de missions accomplies de jeu.
*/
int getPartieNbMission (Partie* jeu);

/**
* \brief Preconditions : jeu est initialisé.
* <br /> Postconditions : copie la mission actuelle de jeu dans tampon.
*/
void getPartieMissionActuelle (Partie* jeu,char tampon [50]);

/**
* \brief Preconditions : SDL est initialisé
* <br /> Postconditions : gère les évenements du menu principal du jeu. Retourne le type d'event réalisé.
*/
char eventMenu();

/**
* \brief Preconditions : police et ecran sont initalisés,
* <br /> Postconditions : affiche les différentes pages du menu principal d'Iniuriam, selon le type.
*/
void afficherMenu (SDL_Surface *ecran, char jeu,TTF_Font *police,Partie* partie);

int mainMenu();
#endif
