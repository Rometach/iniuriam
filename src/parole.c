#include "parole.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

void dialogueInit (Dialogue* dialogue, Personnage* perso1, Personnage* perso2)
{
    dialogue->perso1=perso1;
    dialogue->perso2=perso2;
    if (getPersoFaction(perso1)==getPersoFaction(perso2)) /*Les personnages sont alliés*/
    {
        dialogue->humeur=50;
    }
    else if ((getPersoFaction(perso1)==2)&&(getPersoFaction(perso2)==1))  /*Les personnages sont ennemis*/
    {
        dialogue->humeur=10;
    }
    else if ((getPersoFaction(perso1)==1)&&(getPersoFaction(perso2)==2))  /*Les personnages sont ennemis*/
    {
        dialogue->humeur=10;
    }
    else    /*L'un des personnages est marchand...*/
    {
        dialogue->humeur=25;
    }
}

char setDialogueHumeur (Dialogue* dialogue, int hum)
{
    if (hum<0)
    {
        dialogue->humeur=0;
    }
    else if (hum>100)
    {
        dialogue->humeur=100;
    }
    else
    {
        dialogue->humeur=hum;
    }
    return dialogue->humeur;
}

void setReponse (const char* question, char* reponse)
{
    FILE* fDial;
    int i;

    assert(fDial=fopen("data/Dialogues.txt", "r"));

    if (fDial!=NULL)
    {
        while(strcmp(question,fgets(reponse,TAILLE_MAX_DIAL,fDial))!=0)
        {}

        for(i=0;i<=(rand()%3);i++)  {fgets(reponse,TAILLE_MAX_DIAL,fDial);}

        fclose(fDial);
    }
    else
    {
        printf ("Impossible d'ouvrir le fichier Dialogues.txt");
    }
}

char obtenirInfo(Dialogue* dialogue, char* info, Mission* mission, Objet* tabObjets)
{
    int test, bonus=0;
    char nomPNJ[30];

    getPersoNom(nomPNJ, dialogue->perso2);

    bonus=chercherCompetence(getPersoCapacite2(dialogue->perso1),2);
    if (bonus>=0)bonus=getBonuschar(getCompetence(getPersoCapacite2(dialogue->perso1),bonus));
    else bonus=0;

    test=(rand()%100)-(int)(bonus/10);

    if(test<(dialogue->humeur))
    {
        strcat(nomPNJ," Info\n");
        setReponse(nomPNJ, info);
        ajouterCompetencePerso (dialogue->perso1,2,2);
        if(testMissionFaireParler( mission, dialogue->perso2))
        {
            missionAccomplir (mission ,tabObjets);
        }
    }
    else
    {
        setReponse("Refus info\n", info);
    }

    setDialogueHumeur(dialogue,dialogue->humeur-5);

    return dialogue->humeur;
}

char parlerQuete(Dialogue* dialogue, char* info)
{
    char nomPNJ[30];

    getPersoNom(nomPNJ, dialogue->perso2);

    strcat(nomPNJ," Mission\n");
    setReponse(nomPNJ, info);

    return dialogue->humeur;
}

char soudoyer(Dialogue* dialogue, int argent, char* rep)
{
    int test,bonus=0;

    if(getPersoArgent(dialogue->perso1)>argent)
    {
        setPersoArgent(dialogue->perso1, getPersoArgent(dialogue->perso1)-argent);
        setPersoArgent(dialogue->perso2, getPersoArgent(dialogue->perso2)+argent);

        bonus=chercherCompetence(getPersoCapacite2(dialogue->perso1),6);
        if (bonus>=0)bonus=getBonuschar(getCompetence(getPersoCapacite2(dialogue->perso1),bonus));
        else bonus=0;

        if(getPersoFaction(dialogue->perso1)==3)  /*C'est plus facile de soudoyer un marchand...*/
        {
            test=(rand()%((int)(argent/2)))-5+(int)(bonus/10);
        }
        else
        {
            test=(rand()%((int)(argent/10)))-5+(int)(bonus/10);
        }
        if (test>0)
        {
            setReponse("Soudoyer réussi\n",rep);
            ajouterCompetencePerso (dialogue->perso1,6,5);
        }
        else
        {
            setReponse("Soudoyer échoué\n",rep);
        }

        setDialogueHumeur(dialogue, dialogue->humeur+test);
        return dialogue->humeur;
    }
    else
    {
        strcpy(rep, "Vous n'avez pas assez d'argent");
        return dialogue->humeur;
    }
}

char menacer(Dialogue* dialogue, char* rep)
{
    int test,bonus=0;

    bonus=chercherCompetence(getPersoCapacite2(dialogue->perso1),7);
    if (bonus>=0)bonus=getBonusatt(getCompetence(getPersoCapacite2(dialogue->perso1),bonus));
    else bonus=0;

    test=rand()%(getPersoAttaque(dialogue->perso1)+getPersoCharisme(dialogue->perso1))-rand()%(getPersoDefense(dialogue->perso2)+getPersoIntelligence(dialogue->perso2))+(dialogue->humeur)+(int)(bonus/10);

    if(test>0)
    {
        setReponse("Menacer réussi\n", rep);
        ajouterCompetencePerso (dialogue->perso1,7,5);
    }
    else
    {
        setReponse("Menacer échoué\n", rep);
    }

    setDialogueHumeur(dialogue,dialogue->humeur+test);

    return dialogue->humeur;
}

char seduire(Dialogue* dialogue, char* rep)
{
    int test, charisme, intelligence, bonus=0;
    charisme=getPersoCharisme(dialogue->perso1);
    intelligence=getPersoIntelligence(dialogue->perso2);

    bonus=chercherCompetence(getPersoCapacite2(dialogue->perso1),5);
    if (bonus>=0)bonus=getBonuschar(getCompetence(getPersoCapacite2(dialogue->perso1),bonus));
    else bonus=0;

    if (getPersoSexe(dialogue->perso2)==getPersoSexe(dialogue->perso1))     /*Quand on est de même sexe, il n'est pas judicieux de se séduire.*/
    {
        if (charisme==0) test=-10;
        else test=(rand()%charisme)+(dialogue->humeur)-100+(int)(bonus/10);
    }
    else
    {
        if (charisme==0&&intelligence==0) test=dialogue->humeur;
        else if (charisme==0) test=-(rand()%intelligence)+(dialogue->humeur);
        else if (intelligence==0) test=(rand()%charisme)+(dialogue->humeur)+(int)(bonus/10);
        else test=(rand()%charisme)-(rand()%intelligence)+(dialogue->humeur)+(int)(bonus/10);
    }

    if(test>0)
    {
        setReponse("Séduire réussi\n", rep);
        ajouterCompetencePerso (dialogue->perso1,5,10);
    }
    else
    {
        setReponse("Séduire échoué\n", rep);
    }

    setDialogueHumeur(dialogue,dialogue->humeur+test);

    return dialogue->humeur;
}

void marchander (Dialogue* dialogue, int* valeur)
{
    int bonusCh, bonusIn;
    bonusCh=chercherCompetence(getPersoCapacite2(dialogue->perso1),1);
    if (bonusCh>=0) bonusCh=getBonuschar(getCompetence(getPersoCapacite2(dialogue->perso1),bonusCh))+rand()%100;
    bonusIn=chercherCompetence(getPersoCapacite2(dialogue->perso2),1);
    if (bonusIn>=0) bonusIn=getBonusint(getCompetence(getPersoCapacite2(dialogue->perso2),bonusIn))+rand()%100;

    if (bonusCh-bonusIn>0) ajouterCompetencePerso (dialogue->perso1,1,(bonusIn-bonusCh)/10);
    *valeur+=(int)((*valeur)*(bonusIn-bonusCh)/10);
}

char acheter(Dialogue* dialogue, Objet* objet, char* rep,  Mission* mission, Objet* tabObjets)
{
/*    char c;*/
    int bonus=0,valeur=getObjetValeur(objet);
    Inventaire inv;
    getPersoInventaire(dialogue->perso2,&inv);

    if(estObjDansInv(&inv,objet))
    {
       /* printf ("Essayer de marchander ? (y=oui n=non)\n");
        c=getchar();
        switch (c)
        {
            case 'y':
                marchander(dialogue,&valeur);
            break;
            default: break;
        }*/
        if ((getPersoArgent(dialogue->perso1))>=valeur)
            {
                bonus=chercherCompetence(getPersoCapacite2(dialogue->perso1),5);
                if (bonus>=0)bonus=getBonuschar(getCompetence(getPersoCapacite2(dialogue->perso1),bonus));
                else bonus=0;

                soustraireInventaire(dialogue->perso2,objet);
                ajouterInventaire(dialogue->perso1,objet);

                setPersoArgent(dialogue->perso2,getPersoArgent(dialogue->perso2)+(int)((valeur*100-bonus)/100));
                setPersoArgent(dialogue->perso1,getPersoArgent(dialogue->perso1)-(int)((valeur*100-bonus)/100));

                strcpy(rep,"Vendu !\n");

                ajouterCompetencePerso (dialogue->perso1,3,2);
                if (testMissionObtenir( mission, objet))
                {
                    missionAccomplir(mission, tabObjets);
                }
            }

        else
            {
                strcpy(rep,"Je suis au regret de vous annoncer que vous n'avez pas les moyens d'effectuer cette transaction...\n");
            }
        }
    else
    {
        strcpy(rep,"Malheureusement cet objet n'est pas en ma possession.\n");
    }

    inventaireLibere(&inv);

    return(dialogue->humeur);
}

char vendre(Dialogue* dialogue, Objet* objet, char* rep)
{
/*    char c;*/
    int bonus=0,valeur=getObjetValeur(objet);
    Inventaire inv;
    getPersoInventaire(dialogue->perso1,&inv);

    if(estObjDansInv(&inv,objet))
    {
      /*  printf ("Essayer de marchander ? (y=oui n=non)\n");
        c=getchar();
        switch (c)
        {
            case 'y':
                marchander(dialogue,&valeur);
            break;
            default: break;
        }*/
        if ((getPersoArgent(dialogue->perso2))>=valeur)
            {
                bonus=chercherCompetence(getPersoCapacite2(dialogue->perso1),5);
                if (bonus>=0)bonus=getBonuschar(getCompetence(getPersoCapacite2(dialogue->perso1),bonus));
                else bonus=0;

                soustraireInventaire(dialogue->perso1,objet);
                ajouterInventaire(dialogue->perso2,objet);

                setPersoArgent(dialogue->perso1,getPersoArgent(dialogue->perso1)+(int)((valeur*100+bonus)/100));
                setPersoArgent(dialogue->perso2,getPersoArgent(dialogue->perso2)-(int)((valeur*100+bonus)/100));

                strcpy(rep,"Merci ! Je suis très content de cette aquisition !\n");

                ajouterCompetencePerso (dialogue->perso1,4,2);
            }

            else
            {
                strcpy(rep,"Hélas, je n'ai pas les moyens pour une telle transaction...\n");
            }
    }
    else
    {
        strcpy(rep,"Malheureusement cet objet n'est pas en ma possession.\n");
    }

    inventaireLibere(&inv);
    return(dialogue->humeur);
}

/*
int mainParole ()
{
    int k;
    Dialogue dial;
    Personnage perso;
    Personnage pnj;
    char information[TAILLE_MAX_DIAL];
    Objet *tab;

    initialiserTousLesObjets(tab);

    srand(time(NULL));
    nouveauPerso (&perso, "Toromis", 1, 1, 1, 1, 0, 100,tab);
    nouveauPerso (&pnj, "Babar", 2, 1, 1, 1, 0, 100,tab);
    setPersoArgent(&perso,1000);
    dialogueInit(&dial,&perso,&pnj);

    afficherInventaire(&perso.inventaire);
    afficherInventaire(&pnj.inventaire);

    acheter(&dial, &tab[1], information);

    afficherInventaire(&perso.inventaire);
    afficherInventaire(&pnj.inventaire);

    vendre(&dial, &tab[1], information);

    afficherInventaire(&perso.inventaire);
    afficherInventaire(&pnj.inventaire);

    for(k=0;k<10;k++)
    {
        printf("\n\n");
        obtenirInfo(&dial, information);
        soudoyer(&dial, 100, information);
        seduire(&dial, information);
        menacer(&dial, information);
    }

    persoLibere (&perso);
    persoLibere (&pnj);
    free(tab);
    return 0;
}*/
