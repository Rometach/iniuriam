#ifndef __personnage_h__
#define __personnage_h__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "inventaire.h"
#include "capacite.h"
#include "constante.h"
#include "equipement.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

typedef struct
{
    char nom [30];      /**Le nom du personnage*/
    char race;          /**0 : inconnu
                        1 : humain
                        2 : cyborg
                        3 : sicaris
                        4 : medarsins*/

    char sexe;          /**0 : inconnu
                        1 : homme
                        2 : femme*/

    char faction;       /**0 : inconnu
                        1 : Sistéen
                        2 : Heredian
                        3 : Marchand*/

    char carriere;      /**Correspond à la ligne où est décrite la carrière du personnage dans Carrieres.txt*/
    int argent;         /**Solde courant du porte-monnaie*/
    int experience;     /**Valeur d'expérience actuellement engrangée par le personnage*/
    int niveau;         /**Fonction (logarithmique) de l'expérience*/

    Capacite capacite;  /**Capacité (liste de Compétences) du Personnage*/

    char attaque;       /**Statistique du Personnage en attaque*/
    char defense;       /**Statistique du Personnage en défense*/
    char intelligence;  /**Statistique du Personnage en intelligence*/
    char agilite;       /**Statistique du Personnage en agilité*/
    char charisme;      /**Statistique du Personnage en charisme*/
    int ptDeVie;        /**Niveau actuel de santé du Personnage*/

    int posX;           /**Position en X actuelle du Personnage*/
    int posY;           /**Position en Y actuelle du Personnage*/

    Inventaire inventaire;  /**Inventaire (liste de Stocks) du Personnage*/

    Equipement equipement;  /**Décrit les différentes armes/armures équipées*/

	SDL_Surface* avatar;    /**Icône du Personnage*/

} Personnage;


/**
* \brief Preconditions : perso n'a pas déjà été initialisé
* <br /> Postconditions : perso est initialisé, vide
*/
void persoInit (Personnage* perso);

/**
* \brief Preconditions : perso n'est pas initialisé ou initialisé à vide
                        tab contient tous les objets du jeu
                        les autres paramètres respectent les critères imposés par la structure
* <br /> Postconditions : perso est initialisé et ses paramètres nom, race, sexe, carriere, et expérience sont fournis
*/
void nouveauPerso(Personnage *perso, const char nom[], const char race, const char sexe, const char faction, const char carriere, const int experience, const int argent, Objet* tab);

/**
* \brief Preconditions : perso n'est pas initialisé ou initialisé à vide
                         tous les paramètres respectent les critères imposés par la structure
* <br /> Postconditions : perso est initialisé avec tous les paramètres de sa structure.
*/
void chargerPerso (Personnage* perso, const char nom[50], const char race, const char sexe, const char faction, const char carriere, const int experience, const int argent, const char attaque, const char defense, const char intelligence,
                   const char agilite, const char charisme, const int ptDeVie, const int posX, const int posY, const Competence* liste, const int nbCompetence, const int* inventaire, const int nbObjet, const int armure[5], const int arme[3],Objet* tabObjet);

/**
* \brief Preconditions : /
* <br /> Postconditions : retourne le nombre de personnages dans PNJ.txt
*/
int getNbPNJ();

/**
* \brief Preconditions : /
* <br /> Postconditions : retourne le nombre de carrieres dans Carrieres.txt
*/
int getNbCarriere();

/**
* \brief Preconditions : perso n'est pas initialisé ou initialisé à vide, l<=getNbPNJ()
                        tab contient tous les objets du jeu
* <br /> Postconditions : perso est initialisé avec les paramètres du l-ième PNJ du fichier PNJ.txt
*/
void persoInitPNJ(Personnage *perso, const int l, Objet* tab);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : perso est libéré
*/
void persoLibere (Personnage *perso);

/**
* \brief Preconditions : perso est initialisé, maChaine a une longueur >= 30
* <br /> Postconditions : copie le nom de perso dans maChaine
*/
void getPersoNom(char* maChaine, const Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne la race du perso
*/
char getPersoRace(const Personnage *perso);

/**
* \brief Preconditions : /
* <br /> Postconditions : copie le nom associé à race dans chaine
*/
void getRaceNom(char* chaine,char race);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne la faction du perso
*/
char getPersoFaction(const Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : copie le nom de la faction de perso dans chaine
*/
void getPersoFactionNom(char* chaine, const Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : fixe la faction du perso
*/
void setPersoFaction(Personnage *perso, const char faction);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne le sexe du perso
*/
char getPersoSexe(const Personnage *perso);

/**
* \brief Preconditions : /
* <br /> Postconditions : copie le nom associé à sexe dans chaine
*/
void getSexeNom(char* chaine,char sexe);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne la carriere du perso
*/
char getPersoCarriere(const Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : copie le nom de la carriere carriere dans s
*/
void getCarriereNom(const char carriere, char* s);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne l'argent du perso
*/
int getPersoArgent(const const Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne l'experience du perso
*/
int getPersoExperience(const Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne l'attaque du perso
*/
char getPersoAttaque(const Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne la defense du perso
*/
char getPersoDefense(const Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne l'intelligence du perso
*/
char getPersoIntelligence(const Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne l'agilite du perso
*/
char getPersoAgilite(const Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne le charsime du perso
*/
char getPersoCharisme(const Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne les points de vie du perso
*/
int getPersoPtDeVie(const Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : récupère la position en X du perso
*/
int getPersoPosX(const Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : récupère la position en Y du perso
*/

int getPersoPosY(const Personnage *perso);
/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : change la position en X du perso
*/
void setPersoPosX(Personnage *perso, const int x);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : change la position en Y du perso
*/
void setPersoPosY(Personnage *perso, const int y);

/**
* \brief Preconditions : perso est initialisé mais pas inv
* <br /> Postconditions : copie l'inventaire du perso dans inv
*/
void getPersoInventaire(const Personnage *perso, Inventaire* inv);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne l'adresse de l'inventaire du perso
*/
Inventaire* getPersoInventaire2(Personnage *perso);

/**
* \brief Preconditions : perso et s sont initialisés
* <br /> Postconditions : retourne l'ensemble des capacite du perso dans s
*/
void getPersoCapacite(const Personnage *perso, Capacite* s);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne l'adresse de la Capacite de perso
*/
Capacite* getPersoCapacite2(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne l'adresse de l'Equipement de perso
*/
Equipement* getPersoEquipement(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : fixe la somme d'argent du perso
*/
void setPersoArgent(Personnage *perso, const int somme);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : ajoute pdv aux points de vie de perso
*/
void addPersoPtDeVie(Personnage *perso, const int pdv);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : 1 obj est ajouté à l'inventaire de perso
*/
void ajouterInventaire (Personnage *perso, Objet *obj);

/**
* \brief Preconditions : perso est initialisé, obj est dans l'inventaire de perso
* <br /> Postconditions : 1 obj est retiré de l'inventaire de perso
*/
void soustraireInventaire (Personnage *perso, const Objet *obj);

/**
* \brief Preconditions : perso est initialisé, type >0
* <br /> Postconditions : ajoute la compétence associée à type (avec l'expérience exp) à perso
*/
void ajouterCompetencePerso (Personnage *perso, const int type, const int exp);

/**
* \brief Preconditions : perso est initialisé, obj est dans l'inventaire de perso
                        éventuellement, cible correspond au personnage visé, initialisé
* <br /> Postconditions : obj est utilisé et si besoin retiré de l'inventaire de perso
*/
void persoUtiliseObjet (Personnage *perso, Objet *obj, Personnage* cible);

/**
* \brief Preconditions: perso1 est initialisé, mais pas perso2
*   <br /> Postconditions : le contenu de avatar1 est copié dans avatar2
*/
void copieAvatar(SDL_Surface* avatar1, SDL_Surface* avatar2);

/**
* \brief Preconditions : perso1 est initialisé, mais pas perso2
* <br /> Postconditions : le contenu de perso1 est copié dans perso2
*/
void copiePerso (Personnage* perso1, Personnage* perso2);

/**
* \brief Preconditions : perso est initialisé, obj appartient à l'inventaire de perso, 0<=i<3
* <br /> Postconditions : obj est équipé (à la ième place s'il s'agit d'une arme)
*/
void equiper (Personnage* perso, Objet* obj, const int i);

/**
* \brief Preconditions : tabPNJ n'est pas initialisé
                        tabObjets contient tous les objets
* <br /> Postconditions : initialise tous les PNJ dans tabPNJ
*/
void initialiserTousLesPNJ(Personnage** tabPNJ, Objet* tabObjets);

/**
* \brief Preconditions : tabPNJ est initialisé
* <br /> Postconditions : libère tabPNJ
*/
void libererTousLesPNJ(Personnage** tabPNJ);

/**
* \brief Preconditions : experience>=0
* <br /> Postconditions : retourne le niveau lié à experience
*/
int calculNiveau(const int experience);

/**
* \brief Preconditions : perso est initialise
* <br /> Postconditions : retourne l'experience totale du perso.
*/
int calculPersoExperience (Personnage* perso);

/**
* \brief Preconditions : /
* <br /> Postconditions : Fonction de test de non-regression du module Personnage ; retourne 0 si tout s'est bien passé
*/
int mainPerso();


#endif
