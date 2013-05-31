#include "equipement.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

void equiInit(Equipement* equi)
{
    int i;
    equi->tete=NULL;
    equi->torse=NULL;
    equi->bas=NULL;
    equi->mains=NULL;
    equi->pieds=NULL;
    equi->armeGauche=NULL;
    for (i=0;i<3;i++) equi->armeDroite[i]=NULL;
}

void setEquiTete(Equipement* equi, Objet* tete)
{
    equi->tete=tete;
}

void setEquiTorse(Equipement* equi, Objet* torse)
{
    equi->torse=torse;
}

void setEquiBas(Equipement* equi, Objet* bas)
{
    equi->bas=bas;
}

void setEquiMains(Equipement* equi, Objet* mains)
{
    equi->mains=mains;
}

void setEquiPieds(Equipement* equi, Objet* pieds)
{
    equi->pieds=pieds;
}

void setMainGauche(Equipement* equi, Objet* bouclier)
{
    equi->armeGauche=bouclier;
}

void setMainDroite(Equipement* equi, Objet* arme,int i)
{
    assert (i>=0&&i<3);
    equi->armeDroite[i]=arme;
}

Objet* getEquiTete(Equipement* equi)
{
    return equi->tete;
}

Objet* getEquiTorse(Equipement* equi)
{
    return equi->torse;
}

Objet* getEquiBas(Equipement* equi)
{
    return equi->bas;
}

Objet* getEquiMains(Equipement* equi)
{
    return equi->mains;
}

Objet* getEquiPieds(Equipement* equi)
{
    return equi->pieds;
}

Objet* getEquiMainGauche(Equipement* equi)
{
    return equi->armeGauche;
}

Objet* getEquiMainDroite(Equipement* equi, int i)
{
    assert (i>=0&&i<3);
    return equi->armeDroite[i];
}

void copieEquipement (Equipement* equi1, Equipement* equi2)
{
    equiInit(equi2);
    if (equi1->tete!=NULL)equi2->tete=equi1->tete;
    if (equi1->torse!=NULL)equi2->torse=equi1->torse;
    if (equi1->bas!=NULL)equi2->bas=equi1->bas;
    if (equi1->pieds!=NULL)equi2->pieds=equi1->pieds;
    if (equi1->armeGauche!=NULL)equi2->armeGauche=equi1->armeGauche;
    if (equi1->armeDroite[0]!=NULL)equi2->armeDroite[0]=equi1->armeDroite[0];
    if (equi1->armeDroite[1]!=NULL)equi2->armeDroite[1]=equi1->armeDroite[1];
    if (equi1->armeDroite[2]!=NULL)equi2->armeDroite[2]=equi1->armeDroite[2];
}
