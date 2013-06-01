#ifndef AFFICHAGE_SDL_H
#define AFFICHAGE_SDL_H

#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_ttf.h>
#include <assert.h>

#include "deplacement.h"
#include "constante.h"
#include "combat.h"
#include "parole.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

/**
* \brief Preconditions : ter et ecran initalisé et remplis
* <br /> Postconditions : affiche le chipset
*/
void affChipset(Terrain* ter, SDL_Surface* ecran);

/**
* \brief Preconditions : ter et ecran initalisé et remplis
* <br /> Postconditions : affiche l'editeur de carte
*/
void affEditeur(Terrain* ter, SDL_Surface* ecran);

/**
* \brief Preconditions : ter et ecran initalisé et remplis
* <br /> Postconditions : affiche la carte
*/
void affCarte(const Terrain* ter, SDL_Surface* ecran);

/**
* \brief Preconditions : hero, et ecran initalisé et remplis
* <br /> Postconditions : affiche le hero
*/
void affPerso(const Personnage* hero, const Personnage* pnjs, const Personnage* ennemis, SDL_Surface* ecran);

/**
* \brief Preconditions : Texte, ter initalisé et remplis
* <br /> Postconditions : affiche du texte
*/
void affDialogue( char* dialoguetab, SDL_Surface* ecran);

/**
* \brief Preconditions : Texte, ter initalisé et remplis
* <br /> Postconditions : affiche le menu du dialogue
*/
void affMenuDialogue( char* dialoguetab, int curseur, SDL_Surface* ecran);

/**
* \brief Preconditions : Texte, ter initalisé et remplis
* <br /> Postconditions : affiche les choix que l'on peut faire lorsque l'on soudoie
*/
void affSoudoyer(char* dialoguetab, int curseur, SDL_Surface* ecran);

/**
* \brief Preconditions : hero, ecran initalisé et remplis
* <br /> Postconditions :affiche l'inventaire
*/
void affInventaire(Personnage* hero, SDL_Surface* ecran);

/**
* \brief Preconditions : hero, ecran initalisé et remplis
* <br /> Postconditions :affiche le profil
*/
void affProfil(Personnage* hero, SDL_Surface* ecran);

/**
* \brief Preconditions : position, objet et ecran initalisé et remplis
* <br /> Postconditions :affiche les informations d'un objet
*/
void affInfOb(SDL_Rect* position, Objet* objet, SDL_Surface* ecran);

/**
* \brief Preconditions : combattant, choix et ecran initalisé et remplis
* <br /> Postconditions : affiche la selection de l'arme en combat
*/
void affArmesEqui(Combattant* hero, int choix, SDL_Surface* ecran);

/**
* \brief Preconditions : combattant et ecran initalisé et remplis
* <br /> Postconditions : gère la selection de l'arme en combat et retourne le choix qu'on a fait
*/
int eventArmesEquiSDL(Combattant* combattant, int choix, SDL_Surface* ecran);

/**
* \brief Preconditions : hero, ecran initalisé et remplis
* <br /> Postconditions : gère les évements de l'inventaire
*/
void eventInventaireSDL(Personnage* hero, SDL_Surface* ecran);

/**
* \brief Preconditions : hero, ecran initalisé et remplis
* <br /> Postconditions : gère les évements du profil
*/
void eventProfilSDL(Personnage* hero, SDL_Surface* ecran);

/**
* \brief Preconditions : hero, ecran initalisé et remplis
* <br /> Postconditions : gère les évements du journa de qetes
*/
void eventJournalSDL(Personnage* hero, Mission* mission, SDL_Surface* ecran);

/**
* \brief Preconditions : ter et ecran initalisé et remplis
* <br /> Postconditions : gère les évenements de l'éditeur de carte
*/
void eventEditeurSDL(Terrain* ter, SDL_Surface* ecran);

/**
* \brief Preconditions : hero, pnj, ter et ecran initalisé et remplis
* <br /> Postconditions : gère les évenements en jeu
*/
void eventJeuSDL(Personnage* hero, Personnage* pnj, Personnage* ennemi, Mission* mission, Objet* tabObjets, Terrain* ter, Dialogue* dialogue, SDL_Surface* ecran);

/**
* \brief Preconditions : hero, pnj et ecran initalisé et remplis
* <br /> Postconditions : gère les évenements du dialogue
*/
void eventDialogueSDL( Dialogue* dialogue, const Personnage* hero, const Personnage* pnjs, const Personnage* ennemis, char repondre[400], Mission* mission, Objet* tabObjets, Terrain* ter, SDL_Surface*ecran);

/**
* \brief Preconditions : dialogue, reponse et ecran initialisés
* <br /> Postconditions : gère les évenements de l'achat
*/
void eventAcheterSDL(Dialogue* dialogue, char* reponse, SDL_Surface* ecran);

/**
* \brief Preconditions : dialogue, reponse et ecran initialisés
* <br /> Postconditions : gère les évenements de la vente
*/
void eventVendreSDL(Dialogue* dialogue, char* reponse, SDL_Surface* ecran);

/**
* \brief Preconditions : hero, ennemi, ter et ecran initialisés
* <br /> Postconditions : gère les évenements lors du combat
*/
int eventCombatSDL(Personnage* hero, Personnage* ennemi, Terrain* ter, SDL_Surface* ecran);

/**
* \brief Preconditions :groupe, j, l et arene sont initialisés
* <br /> Postconditions : gère les évenements lors du tour de combat du joueur
*/
void eventTourJoueurSDL(Combattant* groupe, int j, int l, char arene [TAILLE_MAX_H][TAILLE_MAX_L], Terrain* ter, SDL_Surface* ecran);

void eventTourIASDL(Combattant* groupe, int j, int l, char arene [TAILLE_MAX_H][TAILLE_MAX_L]);

/**
* \brief Preconditions :
* <br /> Postconditions : permet d'éditer, de sauver et de charger des cartes
*/
void editerCarte ();

#endif
