#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include "personnage.h"
#include "terrain.h"
#include "deplacement.h"
#include "combat.h"
#include "equipement.h"
#include "constante.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/


void areneInit (Terrain* terrain, char tab[TAILLE_MAX][TAILLE_MAX])
{
    int i,j;
    for (i=0; i<TAILLE_MAX;i++)
    {
        for (j=0;j<TAILLE_MAX;j++)
        {
            tab[i][j]=terrain->tabChipset[i*TAILLE_MAX+j].collision;
        }
    }
}

char tri (char* tab, char e, int l)
{
    int i,j;
    for (i=0;i<l;i++)
    {
       if (e>tab[i])
       {
           for (j=l;j>i;j--)
           {
               tab[j]=tab[j-1];
           }
           tab[i]=e;
           return i;
       }
    }
    tab[l]=e;
    return l;
}

void initCombattant (Personnage* liste, int l, Combattant* groupe)
{
    int i,j;
    char *tab = (char*) malloc(l*sizeof(char));
    for (i=0;i<l;i++)
    {
        groupe[i].perso=(&liste[i]);
        groupe[i].camp=getPersoFaction(&liste[i]);
        groupe[i].derniereAction=0;
        for (j=0;j<=i;j++)
        {
            groupe[i].ordre=tri(tab, getPersoAgilite(&liste[i]),i);
        }
    }
    free (tab);
}

Personnage* getCombattantPerso (Combattant* combattant)
{
    return combattant->perso;
}

char getCombattantCamp (Combattant* combattant)
{
    return combattant->camp;
}

int getCombattantOrdre (Combattant* combattant)
{
    return combattant->ordre;
}

int getCombattantPosX (Combattant* combattant)
{
    return combattant->posX;
}

int getCombattantPosY (Combattant* combattant)
{
    return combattant->posY;
}

char getCombattantOrientation (Combattant* combattant)
{
    return combattant->orientation;
}

char getCombattantDerniereAction (Combattant* combattant)
{
    return combattant->derniereAction;
}

void getCombattantArene (Combattant* combattant, char arene[TAILLE_MAX][TAILLE_MAX])
{
    copieTab2D(combattant->arene,arene);
}

void initPosGauche (Combattant* combattant, char arene[TAILLE_MAX][TAILLE_MAX])
{
    int i=1,j=1;
    char colonne [TAILLE_MAX], place=0;
    while ((place==0)&&(i<TAILLE_MAX))
    {
        getColonne(i,arene,colonne);
        while ((place==0)&&(j<TAILLE_MAX))
        {
            if (deplacerCase(j,colonne)!=0)
            {
                arene[i][j]=4;
                combattant->posX=i;
                combattant->posY=j;
                combattant->orientation=4;
                place=1;
            }
            j+=2;
        }
        i+=2;
    }
    if (place==0)
    {
        char nom [40];
        getPersoNom(nom,combattant->perso);
        printf ("Impossible de placer %s\n", nom);
    }

}

void initPosDroite (Combattant* combattant, char arene[TAILLE_MAX][TAILLE_MAX])
{
    int i=TAILLE_MAX-2,j=TAILLE_MAX-2;
    char colonne [TAILLE_MAX], place=0;
    while ((place==0)&&(i>0))
    {
        getColonne(i,arene,colonne);
        while ((place==0)&&(j>0))
        {
            if (deplacerCase(j,colonne)!=0)
            {
                arene[i][j]=4;
                combattant->posX=i;
                combattant->posY=j;
                combattant->orientation=1;
                place=1;
            }
            j-=2;
        }
        i-=2;
    }
    if (place==0)
    {
        char nom [40];
        getPersoNom(nom,combattant->perso);
        printf ("Impossible de placer %s\n", nom);
    }
}

void initPosCombattant (Combattant*liste, int l, char arene[TAILLE_MAX][TAILLE_MAX])
{
    int i;
    for (i=0;i<l;i++)
    {
        if (liste[i].camp==liste[0].camp) initPosGauche (&liste[i], arene);
        else initPosDroite (&liste[i],arene);
    }
}

void ordreGroupe (Combattant* liste, int l)
{
    int i;
    Combattant tampon;
    for (i=0; i<l-1; i++)
    {
        if (liste[i].ordre>liste[i+1].ordre)
        {
            tampon=liste[i];
            liste[i]=liste[i+1];
            liste[i+1]=tampon;
        }
    }
}

void initCombat (Personnage* liste, int l, Combattant* groupe, char arene[TAILLE_MAX][TAILLE_MAX])
{
    initCombattant(liste,l,groupe);
    initPosCombattant(groupe,l,arene);
    ordreGroupe(groupe,l);
}


char estDansChampDeVision (char arene[TAILLE_MAX][TAILLE_MAX], int x, int y, int z, int t,char orientation)
{
    int i,j,a,b,c,d,rayon=30;
    char vu=0;
    if (rayon>=(int)sqrt(pow((z-x),2)+pow((t-y),2)))
    {
        switch (orientation)
        {
            case 1: a=max(x-rayon,1);
                    b=min(rayon+x,TAILLE_MAX-1);
                    c=max(y-rayon,1);
                    d=y;
                    break;
            case 2: a=max(x-rayon,1);
                    b=x;
                    c=max(y-rayon,1);
                    d=min(y+rayon,TAILLE_MAX-1);
                    break;
            case 4: a=max(x-rayon,1);
                    b=min(rayon+x,TAILLE_MAX-1);
                    c=y;
                    d=min(y+rayon,TAILLE_MAX-1);
                    break;
            case 3: a=x;
                    b=min(rayon+x,TAILLE_MAX-1);
                    c=max(y-rayon,1);
                    d=min(y+rayon,TAILLE_MAX-1);
                    break;
            default: break;
        }
        for (i=a;i<b;i++)
        {
            for (j=c;j<d;j++)
            {
                if ((int)sqrt(pow((j-y),2)+pow((i-x),2))<=rayon) /*Verifie que la case est bien dans le demi cercle de centre (x,y) et de rayon rayon*/
                {
                    if (i==z&&j==t) vu=1;
                    else if (i==x&&j==y){} /*Case sur laquelle se trouve l'IA*/
                    else if (deplacerCase(j,arene[i])==0)
                    {
                        if (i==x)
                        {
                            if((x==z)&&(fabs(x-i)<fabs(x-z))) return 0;
                            /*La case occulte el l'IA sont alignés selon l'axe des ordonnées
                              vérifie donc si la cible est sur le même axe et si la case occulte est entre l'IA et sa cible*/
                        }
                        else if (j==y)
                        {
                            if ((y==t)&&(fabs(i-x)<fabs(i-z))) return 0;
                            /*La case occulte el l'IA sont alignés selon l'axe des abscisses
                              vérifie donc si la cible est sur le même axe et si la case occulte est entre l'IA et sa cible*/
                        }
                        else if ((int)((j-y)/(i-x)*z)==t) /*Vérifie si la case occulte, l'IA et la cible sont alignés et si la case occulte est entre l'IA et sa cible*/
                        {
                            return 0;
                        }
                    }
                }
            }
        }
        if (vu==1)
        {
            return 1;
        }
    }
    else return 0;
    return 0;
}

char estLaFin (Combattant* groupe,int l)
{
    int i;
    if (l==1) return 1;
    else
    {
        for (i=1;i<l;i++)
        {
            if (groupe[i].camp!=groupe[0].camp) return 0;
        }
    }
    return 1;
}

void copieCombattant (Combattant* comb1, Combattant* comb2)
{
    comb2->perso=comb1->perso;
    comb2->camp=comb1->camp;
    comb2->posX=comb1->posX;
    comb2->posY=comb1->posY;
    comb2->orientation=comb1->orientation;
    comb2->derniereAction=comb1->derniereAction;
    copieTab2D(comb1->arene,comb2->arene);
}



int testNbCombattant (Combattant* groupe, int l, char arene [TAILLE_MAX][TAILLE_MAX])
{
    Combattant* tampon;
    int i,j,n=l;
    for (i=0;i<n;i++)
    {
        if (getPersoPtDeVie(groupe[i].perso)<=0)
        {
            n--;
            if (n==1) printf("And the winner is %s !\nT'es fier(e) de toi ?\n\n",groupe[0].perso->nom);
            /*Cas où il ne reste plus qu'un survivant*/

            else if (groupe[i].camp==groupe[0].camp) printf("C'était un(e) de vos potes ?\nEn tout cas c'est la fin pour %s\n\n",groupe[i].perso->nom);
            /*Cas où le mort est un des joueurs*/

            else printf ("Il avait peut-être une femme et des gosses !!\n... mais ça évidemment tu t'en soucies pas !\n\n");
            /*Cas où le mort est une IA*/

            tampon=(Combattant*)malloc(sizeof(Combattant));
            copieCombattant(&groupe[i],tampon);
            for (j=i;j<n;j++)
            {
                groupe[j]=groupe[j+1];
            }
            copieCombattant(tampon,&groupe[n]); /*le mort est placé a la fin du tableau de combattant*/
            free (tampon);
            arene[groupe[n].posX][groupe[n].posY]=1; /*le mort est retiré de l'arene*/

        }
    }
    return n;
}

int attaquer (Personnage* attaquant, Personnage* defenseur, int degats, int bonusA, int bonusD, int bonusAg, int bonusEsc, int type, char distance)
{
    int testA, testD=0;
    int deg=0;
    Equipement* armure;
    if (distance) testA=getPersoAttaque(attaquant)+bonusAg-rand()%100;/*Si l'attaque est au corps à corps le test d'attaque porte sur l'attaque de l'attaquant*/
    else testA=getPersoAgilite(attaquant)+bonusAg-rand()%100;/*Si l'attaque est à distance le test d'attaque porte sur l'agilite de l'attaquant*/

    if (testA>=0)
    {
        armure=getPersoEquipement(attaquant); /*la défense augmente si le personnage porte des pièces d'armure*/
        if (armure->tete!=NULL)testD+=getObjetProtection(armure->tete);
        if (armure->torse!=NULL)testD+=getObjetProtection(armure->torse);
        if (armure->bas!=NULL)testD+=getObjetProtection(armure->bas);
        if (armure->pieds!=NULL)testD+=getObjetProtection(armure->pieds);
        if (armure->mains!=NULL)testD+=getObjetProtection(armure->mains);
        if (armure->armeGauche!=NULL)testD+=getObjetProtection(armure->armeGauche);

        testD+=getPersoDefense(defenseur)+bonusD+bonusEsc-rand()%100;

        testA=testA-max(testD,0)+bonusA;
        if(testA>=30)
        {
            printf("Coup critique\n");
            ajouterCompetencePerso (attaquant,type,4);
            deg=4*degats;
        }
        else if(testA>=20)
        {
            printf("Coup qui fait mal\n");
            ajouterCompetencePerso (attaquant,type,3);
            deg=3*degats;
        }
        else if(testA>=10)
        {
            printf("Beigne\n");
            ajouterCompetencePerso (attaquant,type,2);
            deg=2*degats;
        }
        else if(testA>=0)
        {
            printf("Touche, mais de justesse\n");
            ajouterCompetencePerso (attaquant,type,1);
            deg=degats;
        }
        else
        {
            printf("Epic parade.\n");
        }
    }
    else
    {
        printf("Rate.\n");
    }
    addPersoPtDeVie(defenseur, -deg);
    printf("%d\n",getPersoPtDeVie(defenseur));
    return deg;
}

void verifierDerniereAction (Combattant* defenseur,int* bonusDef,int* bonusEsc)
{
    int i;
    if (defenseur->derniereAction==3) /*Verifie si la dernière action du défenseur est une attaque prudente*/
    {
        bonusDef+=5;
        i=chercherCompetence(getPersoCapacite2(defenseur->perso),17); /*Cherche si le defenseur à de l'expérience dans l'attaque prudente*/
        if (i>=0)
        {
            i=getBonusdef(getCompetence(getPersoCapacite2(defenseur->perso),i));
            bonusDef+=i;
        }
        ajouterCompetencePerso (defenseur->perso,17,2); /*L'expérience du défenseur dans l'attaque prudente augmente*/
    }
    else if(defenseur->derniereAction==6) /*Verifie si la dernière action du défenseur est une préparation à la parade*/
    {
        bonusDef+=5;
        bonusEsc+=5;
        i=chercherCompetence(getPersoCapacite2(defenseur->perso),13); /*Cherche si le defenseur à de l'expérience dans la parade*/
        if (i>=0)
        {
            i=getBonusdef(getCompetence(getPersoCapacite2(defenseur->perso),i));
            bonusDef+=i;
            i=getBonusagi(getCompetence(getPersoCapacite2(defenseur->perso),i));
            bonusEsc+=i;
        }
        ajouterCompetencePerso (defenseur->perso,13,2); /*L'expérience du défenseur dans la parade augmente*/
    }
}

void ajouterCompetenceAttaque (Combattant* attaquant,Combattant* defenseur, int rapport, char type)
{
    int i;
    if (type) i=15; /*Attaque au corps à corps*/
    else i=14; /*Attaque à distance*/
    switch (rapport)
    {
        case 0:
            if (defenseur->derniereAction==6) /*Verifie si la dernière action du défenseur est une parade*/
            {
                ajouterCompetencePerso (defenseur->perso,13,2); /*L'expérience du défenseur dans la parade augmente*/
            }
            else if (defenseur->derniereAction==3) /*Verifie si la dernière action du défenseur est une attaque prudente*/
            {
                ajouterCompetencePerso (defenseur->perso,17,2); /*L'expérience du défenseur dans l'attaque prudente augmente*/
            }
            ajouterCompetencePerso (defenseur->perso,12,1); /*L'expérience du défenseur dans l'esquive augmente*/
        break;

        case 1:
            ajouterCompetencePerso (attaquant->perso,i,1);
        break;

        case 2:
            ajouterCompetencePerso (attaquant->perso,i,2);
        break;

        case 3:
            ajouterCompetencePerso (attaquant->perso,i,3);
        break;

        case 4:
            ajouterCompetencePerso (attaquant->perso,i,4);
        break;
        /*Les cas précédent ajoute de l'expérience à l'attaquant en fonction de la réussite de son attaque à distance/au corps à corps*/
        default:
        break;
    }
}

void attaqueBrutale(Combattant* attaquant, Combattant* defenseur, int degat,char type)
{
    int deg, i,bonusDef=0,bonusEsc=0;

    verifierDerniereAction(defenseur,&bonusDef,&bonusEsc);

    i=chercherCompetence(getPersoCapacite2(attaquant->perso),16); /*Cherche si l'attaquant a de l'expérience dans l'attaque brutale*/
    if (i<0) deg=attaquer (attaquant->perso,defenseur->perso,degat,0,bonusDef,0,bonusEsc,16,type);
    else deg=attaquer (attaquant->perso,defenseur->perso,degat,getBonusatt(getCompetence(getPersoCapacite2(attaquant->perso),i)),bonusDef,0,bonusEsc,16,type);
    /*L'attaquant bénificie d'un bonus d'attaque en fonction de son expérience dans l'attaque brutale*/

    ajouterCompetenceAttaque(attaquant,defenseur,(int)deg/degat,type);

    attaquant->derniereAction=2;
}

void attaquePrudente (Combattant* attaquant, Combattant* defenseur, int degat,char type)
{
    int deg,bonusDef=0, bonusEsc=0;

    verifierDerniereAction(defenseur,&bonusDef,&bonusEsc);

    deg=attaquer (attaquant->perso,defenseur->perso,degat,0,bonusDef,0,bonusEsc,17,type);

    ajouterCompetenceAttaque(attaquant,defenseur,(int)deg/degat,type);

    attaquant->derniereAction=3;
}

void feinte (Combattant* attaquant, Combattant* defenseur, int degat,char type)
{
    int deg, i,bonusDef=0,bonusEsc=0;

    verifierDerniereAction(defenseur,&bonusDef,&bonusEsc);

    i=chercherCompetence(getPersoCapacite2(attaquant->perso),18); /*Cherche si l'attaquant a de l'expérience dans l'attaque feintée*/
    if (i<0) deg=attaquer (attaquant->perso,defenseur->perso,degat,0,bonusDef,0,bonusEsc,18,type);
    else deg=attaquer (attaquant->perso,defenseur->perso,degat,getBonusint(getCompetence(getPersoCapacite2(attaquant->perso),i)),bonusDef,0,bonusEsc,18,type);
    /*L'attaquant bénificie d'un bonus d'attaque en fonction de son expérience dans l'attaque feintée*/

    ajouterCompetenceAttaque(attaquant,defenseur,(int)deg/degat,type);

    attaquant->derniereAction=4;
}

void viserPourAttaque (Combattant* attaquant, Combattant* defenseur, int degat,char type)
{
    int deg, i,bonusDef=0,bonusEsc=0;

    verifierDerniereAction(defenseur,&bonusDef,&bonusEsc);

    i=chercherCompetence(getPersoCapacite2(attaquant->perso),19); /*Cherche si l'attaquant a de l'expérience dans l'attaque visée*/
    if (i<0) deg=attaquer (attaquant->perso,defenseur->perso,degat,0,bonusDef,0,bonusEsc,19,type);
    else deg=attaquer (attaquant->perso,defenseur->perso,degat,0,bonusDef,getBonusagi(getCompetence(getPersoCapacite2(attaquant->perso),i)),bonusEsc,19,type);
    /*L'attaquant bénificie d'un bonus d'attaque en fonction de son expérience dans l'attaque brutale*/

    ajouterCompetenceAttaque(attaquant,defenseur,(int)deg/degat,type);

    attaquant->derniereAction=5;
}

void preparerParade (Combattant* attaquant)
{
    attaquant->derniereAction=6;
}

void tourIA (Combattant* groupe, int j, int l, char arene [TAILLE_MAX][TAILLE_MAX])
{
    int i, cible=j, arme=0,coord,rayon;
    char distance=100, degats=0,tampon, arene2[TAILLE_MAX][TAILLE_MAX],deplacementsRestants=NB_DEPLACEMENTS, portee;
    for (i=0;i<l;i++)
    {
        /*Cherche les ennemis dans le champ de vision de l'IA*/
        if ((i!=j)&&(groupe[j].camp!=groupe[i].camp)&&(estDansChampDeVision(arene,groupe[j].posX,groupe[j].posY,groupe[i].posX,groupe[i].posY,groupe[j].orientation)!=0))
        {
            copieTab2D(arene,arene2);
            tampon=chemin(groupe[j].posX,groupe[j].posY,groupe[i].posX,groupe[i].posY,arene2);
            /*Cherche un chemin menant à la cible*/
            if (tampon!=0)
            {
                if (tampon<=distance)/*Compare les distances qui séparent l'IA des ennemis pour attaquer le plus proche*/
                {
                    copieTab2D (arene2,groupe[j].arene);
                    distance=tampon;
                    /*Correspond à la distance en case à parcourir pour atteindre la cible*/
                    cible=i;
                    rayon=(int)(sqrt(pow(groupe[j].posX-groupe[i].posX,2)+pow(groupe[j].posY-groupe[i].posY,2)));
                    /*Correspond à la distance exacte entre l'IA et la cible*/
                }
            }
        }
    }
    if (cible!=j) /*Si l'IA a une cible*/
    {
        for (i=0;i<3;i++)
        {
            if (getEquiMainDroite(getPersoEquipement(groupe[j].perso),i)!=NULL)
            {
                portee=getObjetPortee(getEquiMainDroite(getPersoEquipement(groupe[j].perso),i));
                if ((rayon>=portee-NB_DEPLACEMENTS-5)&&(rayon<=portee+NB_DEPLACEMENTS))
                {
                    tampon=getObjetDegats(getEquiMainDroite(getPersoEquipement(groupe[j].perso),i));
                    /*Cherche l'arme équipée infligeant le plus de dégats et dont la portée est suffisante pour toucher la cible*/
                    if (tampon>degats)
                    {
                        arme=i+1;
                        degats=tampon;
                    }
                }
            }
        }
        if (arme!=0) /*Si l'IA est à portée de la cible en comptant ses déplacements*/
        {
            tampon=1;
            portee=getObjetPortee(getEquiMainDroite(getPersoEquipement(groupe[j].perso),arme-1));
            while (portee<rayon&&tampon) /*L'IA doit se rapprocher pour être juste à portée de la cible*/
            {
                coord=seRapprocher(groupe[j].arene,groupe[j].posX,groupe[j].posY,1,&(groupe[j].orientation));
                if (coord)
                {
                    arene[groupe[j].posX][groupe[j].posY]=1;
                    groupe[j].posY=coord%TAILLE_MAX;
                    groupe[j].posX=(coord-coord%TAILLE_MAX)/TAILLE_MAX;
                    arene[groupe[j].posX][groupe[j].posY]=4;
                    deplacementsRestants--;
                    rayon=(int)(sqrt(pow(groupe[j].posX-groupe[cible].posX,2)+pow(groupe[j].posY-groupe[cible].posY,2)));
                }
                else
                {
                    printf("Impossible de se rapprocher plus\n");
                    tampon=0;
                }
            }
            if (portee-5>rayon) /*L'IA doit s'écarter pour être à la portée de la cible si possible*/
            {
                coord=sEloigner(groupe[j].arene,groupe[j].posX,groupe[j].posY,min(NB_DEPLACEMENTS,portee-5-rayon),&(groupe[j].orientation));
                if (coord)
                {
                    arene[groupe[j].posX][groupe[j].posY]=1;
                    groupe[j].posY=coord%TAILLE_MAX;
                    groupe[j].posX=(coord-coord%TAILLE_MAX)/TAILLE_MAX;
                    arene[groupe[j].posX][groupe[j].posY]=4;
                    deplacementsRestants-=min(NB_DEPLACEMENTS,portee-5-rayon);
                    rayon+=5;
                }
                else
                {
                    /*L'IA est trop proche de sa cible pour se servir de sa meilleure arme et elle ne peut pas s'écarter.
                      Elle cherche dans son équipement l'arme ayant la plus petite portée.
                      Par défaut toutes les IA sont équipées au moins d'une arme de corps à corps (portee=1)*/
                    for (i=0;i<3;i++)
                    {
                        if (getEquiMainDroite(getPersoEquipement(groupe[j].perso),i)!=NULL)
                        {
                            tampon=getObjetPortee(getEquiMainDroite(getPersoEquipement(groupe[j].perso),i));
                            if (tampon<portee)
                            {
                                portee=tampon;
                                degats=getObjetDegats(getEquiMainDroite(getPersoEquipement(groupe[j].perso),i));
                            }
                        }
                    }
                    tampon=1;
                    while (portee<rayon&&tampon) /*L'IA doit se rapprocher pour être à portée de la cible avec sa nouvelle arme*/
                    {
                        coord=seRapprocher(groupe[j].arene,groupe[j].posX,groupe[j].posY,1,&(groupe[j].orientation));
                        if (coord)
                        {
                            arene[groupe[j].posX][groupe[j].posY]=1;
                            groupe[j].posY=coord%TAILLE_MAX;
                            groupe[j].posX=(coord-coord%TAILLE_MAX)/TAILLE_MAX;
                            arene[groupe[j].posX][groupe[j].posY]=4;
                            deplacementsRestants--;
                            rayon=(int)(sqrt(pow(groupe[j].posX-groupe[cible].posX,2)+pow(groupe[j].posY-groupe[cible].posY,2)));
                        }
                        else
                        {
                            printf("Impossible de se rapprocher plus\n");
                            tampon=0;
                        }
                    }
                }
            }
            if (rayon<=portee) /*L'IA est à portée de la cible*/
            {
                        if (rayon>3)
                        {
                            attaquer(groupe[j].perso,groupe[cible].perso,degats,0,0,0,0,14,0);
                            /*L'IA attaque le joueur à distance*/
                        }
                        else
                        {
                            attaquer(groupe[j].perso,groupe[cible].perso,degats,0,0,0,0,15,1);
                            /*L'IA attaque le joueur au corps à corps*/
                        }

                        if (getPersoPtDeVie(groupe[cible].perso)<=0) copieTab2D(arene,groupe[j].arene);
                        /*Réinitialise l'arene de l'IA lorsque sa cible meure*/
            }
        }
        else
        {
            /*L'IA est trop loin de la cible pour pouvoir l'attaquer
              elle se rapproche donc pour attaquer la cible qu'elle a vue*/
            coord=seRapprocher(groupe[j].arene,groupe[j].posX,groupe[j].posY,NB_DEPLACEMENTS,&(groupe[j].orientation));

            if (coord)
            {
                arene[groupe[j].posX][groupe[j].posY]=1;
                groupe[j].posY=coord%TAILLE_MAX;
                groupe[j].posX=(coord-coord%TAILLE_MAX)/TAILLE_MAX;
                arene[groupe[j].posX][groupe[j].posY]=4;
            }
            else printf("Impossible de se rapprocher \n");
        }
    }
    else
    {
        if (estDifferentTab2D(groupe[j].arene,arene))
        {
            /*Si l'IA a repéré un ennemi mais que celui-ci n'est plus visible,
              elle se rapproche du dernier endroit où elle a vu la cible et regarde après chaque déplacement si un ennemi est en vue*/
            while (deplacementsRestants-1)
            {
                coord=seRapprocher(groupe[j].arene,groupe[j].posX,groupe[j].posY,1,&(groupe[j].orientation));
                i=coord%TAILLE_MAX;
                if (deplacerCase(i,arene[(coord-i)/TAILLE_MAX]))
                {
                    arene[groupe[j].posX][groupe[j].posY]=1;
                    groupe[j].posY=i;
                    groupe[j].posX=(coord-coord%TAILLE_MAX)/TAILLE_MAX;
                    arene[groupe[j].posX][groupe[j].posY]=4;
                    deplacementsRestants--;
                }
                else
                {
                    groupe[j].arene[(coord-i)/TAILLE_MAX][i]=2;
                    deplacementsRestants=0;
                }
            }
        }
        else printf("Aucune cible repérée\n");
    }
}


void tourJoueur (Combattant* groupe, int j, int l, char arene [TAILLE_MAX][TAILLE_MAX])
{

}


void combat (Personnage* liste, int l, char arene [TAILLE_MAX][TAILLE_MAX])
{
    int i,nb=l;
    Combattant* groupe;
    groupe=(Combattant*)malloc(l*sizeof(Combattant));

    initCombat(liste,l,groupe,arene);
    while (estLaFin(groupe, nb)==0)
    {
        for (i=0;i<nb;i++)
        {
            if(groupe[i].camp==groupe[0].camp)
            {
                tourJoueur(groupe,i,nb,arene);
                nb=testNbCombattant(groupe,nb,arene);
            }
            else
            {
                tourIA(groupe,i,nb,arene);
                nb=testNbCombattant(groupe,nb,arene);
                afficherTab2D(arene);
                /*getchar();*/
            }
        }
    }
    /*Ajouter expérience fin de combat*/
    free (groupe);
}




int mainCombat ()
{
    Personnage liste[4];
    Objet *tab=NULL;
    int i,j,type=1;
    char arene [TAILLE_MAX][TAILLE_MAX],ligne [TAILLE_MAX+2];

    srand(time(NULL));

    initialiserTousLesObjets(&tab);

    nouveauPerso (&liste[0], "Toromis", 1, 1, 1, 1, 0, 100,tab);
    nouveauPerso (&liste[1], "Rometach", 1, 1, 1, 1, 0, 100,tab);
    nouveauPerso (&liste[2], "Babar", 2, 1, 2, 1, 0, 100,tab);
    nouveauPerso (&liste[3], "BabarII", 2, 1, 2, 1, 0, 100,tab);

    FILE* fTerr=fopen("data/Terrains.txt", "r");

    if (fTerr!=NULL)
    {
        for (i=0; i<4;i++)
        {
            fgets(ligne,TAILLE_MAX+2,fTerr);
        }
        for (i=0;i<(TAILLE_MAX+2)*(type-1);i++)
        {
            fgets(ligne,TAILLE_MAX+2,fTerr);
        }
        for (i=0;i<TAILLE_MAX;i++)
        {
            fgets(ligne,TAILLE_MAX+2,fTerr);
            for (j=0;j<TAILLE_MAX;j++)
            {
                arene[i][j]=ligne[j]-'0';
            }
        }
        fclose (fTerr);

        afficherTab2D (arene);
        combat (liste,4,arene);

    }
    persoLibere(&liste[0]);
    persoLibere(&liste[1]);
    persoLibere(&liste[2]);
    persoLibere(&liste[3]);

    libererTousLesObjets(&tab);
    return 0;
}
