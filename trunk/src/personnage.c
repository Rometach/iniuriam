#include "personnage.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

void persoInit (Personnage* perso)
{
    strcpy(perso->nom,"");
    perso->race=0;
    perso->sexe=0;
    perso->faction=0;
    perso->carriere=0;
    perso->argent=0;
    perso->experience=0;

    perso->attaque=0;
    perso->defense=0;
    perso->intelligence=0;
    perso->agilite=0;
    perso->charisme=0;
    perso->ptDeVie=0;

    perso->posX=0;
    perso->posY=0;
}

void nouveauPerso (Personnage *perso, const char nom[], const char race, const char sexe, const char faction, const char carriere, const int experience, const int argent, const Objet* tab)
{
    int i=0, j,k;
    FILE* fCarr,*fRace;
    Competence* compTampon;
    char ligne [TAILLE_MAX_FICHIER],tampon[2];

    assert (strlen(nom)<30);
    strcpy(perso->nom,nom);

    perso->race= race;
    perso->sexe= sexe;
    perso->faction= faction;
    perso->carriere=carriere;
    perso->argent=argent;
    perso->experience= experience;
    perso->niveau=calculNiveau(experience);

    inventaireInit(&(perso->inventaire));

    assert (fRace= fopen("data/Races.txt", "r"));
    if (fRace!=NULL)
    {
        while (i<race+3)
        {
            fgets(ligne,TAILLE_MAX_FICHIER,fRace);
            i++;
        }
        i= (int)(strchr (ligne, '/')-ligne);
        strncpy(tampon,ligne+i+2,2);
        perso->attaque =(char)atoi(tampon);
        strncpy(tampon,ligne+i+5,2);
        perso->defense =(char)atoi(tampon);
        strncpy(tampon,ligne+i+8,2);
        perso->intelligence =(char)atoi(tampon);
        strncpy(tampon,ligne+i+11,2);
        perso->agilite =(char)atoi(tampon);
        strncpy(tampon,ligne+i+14,2);
        perso->charisme =(char)atoi(tampon);
        perso->ptDeVie= 100-(40-perso->defense)*3;

        j=(int)(strchr (ligne, '!')-ligne);
        for (k=i+17;k<j;k+=3)
        {
            strncpy(tampon,ligne+k,2);
            ajouterObjetInventaire(&(perso->inventaire), tab+((char)atoi(tampon)));
        }
        equiInit(&perso->equipement);
        i=0;
        j=0;
        while(i<getInventaireNbObjets(&(perso->inventaire))&&j<3)
        {
            k=getObjetUtilite(getStockObjet(getInventaireStock(&(perso->inventaire),i)));
            if (k==1)/*l'objet est une arme*/
            {
                equiper (perso,getStockObjet(getInventaireStock(&(perso->inventaire),i)),j);
                j++;
            }
            else if (k==2) /*l'objet est une armure*/
            {
                equiper (perso,getStockObjet(getInventaireStock(&(perso->inventaire),i)),0);
            }
            i++;
        }
        fclose(fRace);
    }

    i=0;

    CapaciteInit(&(perso->capacite));

    assert(fCarr= fopen("data/Carrieres.txt", "r"));
    if (fCarr!=NULL)
    {
        while (i<carriere+3)
        {
            fgets(ligne,TAILLE_MAX_FICHIER,fCarr);
            i++;
        }
        i= (int)(strchr (ligne, '/')-ligne);
        j= (int)(strchr (ligne,'!')-ligne);
        compTampon=(Competence*)malloc(((j-i-1)/2)*sizeof(Competence));
        for (k=i; k+1<j;k+=2)
        {
            compInit (compTampon+(k-i)/2,ligne[k+2]-'0', experience);
            ajouterCompetenceCapacite (&(perso->capacite), compTampon+(k-i)/2,experience);
        }
        fclose(fCarr);
        free(compTampon);
    }
    else printf ("Impossible d'ouvrir le fichier Carrieres.txt\n");

    perso->posX=0;
    perso->posY=0;

    /*Initialiser SDL_Surface*/
}

void chargerPerso (Personnage* perso, const char nom[50], const char race, const char sexe, const char faction, const char carriere, const int experience, const int argent, const char attaque, const char defense, const char intelligence,
                   const char agilite, const char charisme, const int ptDeVie, const int posX, const int posY, const Competence* liste, const int nbCompetence, const int* inventaire, const int nbObjet, const int armure[5], const int arme[3])
{
    int i;
    Objet tampon;

    strcpy(perso->nom,nom);
    perso->race=race;
    perso->sexe=sexe;
    perso->faction=faction;
    perso->carriere=carriere;
    perso->experience=experience;
    perso->niveau=calculNiveau(experience);
    perso->argent=argent;
    perso->attaque=attaque;
    perso->defense=defense;
    perso->intelligence=intelligence;
    perso->agilite=agilite;
    perso->charisme=charisme;
    perso->ptDeVie=ptDeVie;
    perso->posX=posX;
    perso->posY=posY;
    CapaciteInit(&(perso->capacite));
    for (i=0;i<nbCompetence;i++)
    {
        ajouterCompetenceCapacite (&(perso->capacite), &liste[i],liste[i].experience);
    }
    inventaireInit(&(perso->inventaire));
    for (i=0;i<nbObjet;i++)
    {
        objInit(&tampon,inventaire[i]);
        ajouterObjetInventaire(&(perso->inventaire), &tampon);
    }
    equiInit(&perso->equipement);
    for (i=0;i<5;i++)
    {
        if (armure[i]!=0)
        {
            objInit(&tampon,armure[i]);
            equiper(perso,&tampon,0);
        }

    }
    for (i=0;i<3;i++)
    {
        if (arme[i]!=0)
        {
            objInit(&tampon,arme[i]);
            equiper(perso,&tampon,i);
        }
    }
}

int getNbPNJ()
{
    int max=0;
    FILE* fPNJ;
    char ligne[TAILLE_MAX_FICHIER];
    assert(fPNJ=fopen("data/PNJ.txt","r"));
    if (fPNJ!=NULL)
    {
        do
        {
            fgets(ligne,TAILLE_MAX_FICHIER,fPNJ);
            max++;
        }while (ligne[0]!='/'&&ligne[1]!='/');
    }
    fclose(fPNJ);

    assert(max%3==0);

    return ((max-3)/3);
}

int getNbCarriere()
{
    int max=0;
    FILE* fCarr;
    char ligne[TAILLE_MAX_FICHIER];
    assert(fCarr=fopen("data/Carrieres.txt","r"));
    if (fCarr!=NULL)
    {
        while (fgets(ligne,TAILLE_MAX_FICHIER,fCarr)!=NULL) max++;
    }
    fclose(fCarr);

    return max-3;
}

void persoInitPNJ(Personnage *perso, const int l, const Objet* tab)
{
    FILE* fPNJ;
    char ligne [TAILLE_MAX_FICHIER];
    int i;
    int race, sexe, faction, carriere, experience, argent;

    char nom[30];

    assert(fPNJ= fopen("data/PNJ.txt", "r"));

    for(i=0;i<(3*l)+1;i++)
    {
        fgets(ligne,TAILLE_MAX_FICHIER,fPNJ);
    }
    /*On va à la ligne qui nous intéresse*/

    strcpy(nom, ligne);
    fscanf(fPNJ, "%d %d %d %d %d %d", &race, &sexe, &faction, &carriere, &experience, &argent);

    fclose(fPNJ);

    nouveauPerso(perso, nom, (char) race, (char) sexe, (char) faction, (char) carriere, experience, argent, tab);

}



void persoLibere (Personnage *perso)
{
    inventaireLibere(&perso->inventaire);
    CapaciteLibere(&perso->capacite);
}


void getPersoNom(char* maChaine, const Personnage *perso)
{
    strcpy(maChaine,perso->nom);  /* Courageux, rajoutez un assert */
}


char getPersoRace(const Personnage *perso)
{
    return perso->race;
}

void getRaceNom(char* chaine, char race)
{
    switch(race)
    {
        case 1 :
            strcpy(chaine,"Humain");
        break;
        case 2 :
            strcpy(chaine,"Cyborg");
        break;
        case 3 :
            strcpy(chaine,"Sicari");
        break;
        case 4 :
            strcpy(chaine,"Medarsin");
        break;
        default :
            strcpy(chaine,"Non défini");
        break;
    }
}

char getPersoSexe(const Personnage *perso)
{
    return perso->sexe;
}

void getSexeNom(char* chaine,const char sexe)
{
    switch (sexe)
    {
        case 1:
            strcpy(chaine,"Masculin");
        break;
        case 2:
            strcpy(chaine,"Feminin");
        break;
        default:
            strcpy(chaine,"Indefini");
        break;
    }
}

char getPersoFaction(const Personnage *perso)
{
    return perso->faction;
}


void getPersoFactionNom(char* chaine, const Personnage *perso)
{
    switch(perso->faction)
    {
        case 1 :
            strcpy(chaine,"Sistéen");
        case 2 :
            strcpy(chaine,"Heredian");
        case 3 :
            strcpy(chaine,"Marchand");
        default :
            strcpy(chaine,"Non défini");
    }
}


char getPersoCarriere(const Personnage *perso)
{
    return perso->carriere;
}


void getCarriereNom(const char carriere, char* s)
{
    int i;
    FILE* fCarr= fopen("data/Carrieres.txt", "r");
    if(fCarr!=NULL)
    {
        char ligne [TAILLE_MAX_FICHIER];
        for (i=0;i<carriere+3;i++)
        {
           fgets(ligne,TAILLE_MAX_FICHIER,fCarr);
        }
    i= strchr (ligne, '/')-ligne;
    strncpy(s,ligne,i);
    s[i]='\0';
    fclose(fCarr);
    }
    else
    {
        printf("Impossible d'ouvrir Carrieres.txt\n");
    }
}


int getPersoArgent(const Personnage *perso)
{
    return perso->argent;
}


int getPersoExperience(const Personnage *perso)
{
    return perso->experience;
}

char getPersoAttaque(const Personnage *perso)
{
    return perso->attaque;
}

char getPersoDefense(const Personnage *perso)
{
    return perso->defense;
}

char getPersoIntelligence(const Personnage *perso)
{
    return perso->intelligence;
}

char getPersoAgilite(const Personnage *perso)
{
    return perso->agilite;
}

char getPersoCharisme(const Personnage *perso)
{
    return perso->charisme;
}

int getPersoPtDeVie(const Personnage *perso)
{
    return perso->ptDeVie;
}

int getPersoPosX(const Personnage *perso)
{
    return perso->posX;
}

int getPersoPosY(const Personnage *perso)
{
    return perso->posY;
}

void setPersoPosX(Personnage *perso, const int x)
{
    perso->posX=x;
}

void setPersoPosY(Personnage *perso, const int y)
{
    perso->posY=y;
}

void getPersoInventaire(const Personnage *perso, Inventaire* inv)
{
    copieInventaire(inv,&perso->inventaire);
}

Inventaire* getPersoInventaire2(Personnage *perso)
{
    return &(perso->inventaire);
}

void getPersoCapacite(const Personnage *perso, Capacite* s)
{
    int i;
    free (s->comp);
    s->nbCompetence= perso->capacite.nbCompetence;
    s->quantite= perso->capacite.quantite;
    s->comp=(Competence*)malloc (sizeof(Competence));
    for (i=0;i<s->nbCompetence;i++)
    {
        s->comp[i]=perso->capacite.comp[i];
    }
}

Capacite* getPersoCapacite2(Personnage *perso)
{
    return &perso->capacite;
}

Equipement* getPersoEquipement(Personnage *perso)
{
    return &perso->equipement;
}


void setPersoArgent(Personnage *perso, const int somme)
{
    perso->argent=somme;
}


void addPersoPtDeVie(Personnage *perso, const int pdv)
{
    perso->ptDeVie+=pdv;
}

void addPersoExperience(Personnage *perso, const int exp)
{
    perso->experience+=exp;
}

int getPersoNiveau (Personnage* perso)
{
    return 1+perso->experience/10;
}

void ajouterInventaire (Personnage *perso, const Objet *obj)
{
    ajouterObjetInventaire(&perso->inventaire, obj);
}

void soustraireInventaire (Personnage *perso, const Objet *obj)
{
    enleverObjetInventaire(&(perso->inventaire),obj);
}

void ajouterCompetencePerso (Personnage *perso, const int type, const int exp)
{
    assert(type>0);
    Competence* compTampon;
    compTampon=(Competence*)malloc(sizeof(Competence));
    compInit (compTampon,type, exp);
    ajouterCompetenceCapacite (&(perso->capacite), compTampon,exp);
    free(compTampon);
}

void persoUtiliseObjet (Personnage *perso, Objet *obj, Personnage* cible)
{
     switch(getObjetUtilite(obj))
    {
        case 3:/*Medoc, Nourriture*/
            switch (getObjetDegats(obj))
            {
                case 1: /*Potion de soins, Nourriture bonne*/
                    addPersoPtDeVie(cible,getObjetProtection(obj));
                    soustraireInventaire(perso,obj);
                break;
                case 2: /*Poison*/
                     addPersoPtDeVie(cible,-getObjetProtection(obj));
                     soustraireInventaire(perso,obj);
                break;
                default: /*Souci*/
                    printf("Le type de votre objet est incoherent\n");
                break;
            }
        break;
        default: /*Autre*/
            printf("Vous ne pouvez vous utiliser cet objet.\n\n");
        break;

    }
}

void copiePerso (Personnage* perso1, Personnage* perso2)
{
    strcpy(perso2->nom,perso1->nom);
    perso2->race=perso1->race;
    perso2->sexe=perso1->sexe;
    perso2->faction=perso1->faction;
    perso2->carriere=perso1->carriere;
    perso2->argent=perso1->argent;
    perso2->experience=perso1->experience;

    CapaciteInit (&perso2->capacite);
    copieCapacite(&perso1->capacite,&perso2->capacite);

    perso2->attaque=perso1->attaque;
    perso2->defense=perso1->defense;
    perso2->intelligence=perso1->intelligence;
    perso2->agilite=perso1->agilite;
    perso2->charisme=perso1->charisme;
    perso2->ptDeVie=perso1->ptDeVie;

    perso2->posX=perso1->posX;
    perso2->posY=perso1->posY;

    inventaireInit(&perso2->inventaire);
    copieInventaire(&perso2->inventaire,&perso1->inventaire);
    copieEquipement(&perso1->equipement,&perso2->equipement);
    /*Initialiser SDL_Surface*/
}

void equiper (Personnage* perso, Objet* obj, const int i)
{
    switch(getObjetUtilite(obj))
    {
        case 1: /*Arme*/
            assert (i>=0&&i<3);
            setMainDroite (&perso->equipement,obj,i);
        break;

        case 2:/*Armure*/
            switch (getObjetPortee(obj))
            {
                case 1: /*Casque*/
                    setEquiTete(&perso->equipement, obj);
                break;
                case 2: /*Plastron*/
                    setEquiTorse(&perso->equipement, obj);
                break;
                case 3: /*Jambières*/
                    setEquiBas(&perso->equipement, obj);
                break;
                case 4: /*Gants*/
                    setEquiMains(&perso->equipement, obj);
                break;
                case 5: /*Sandales*/
                    setEquiPieds(&perso->equipement, obj);
                break;
                case 6: /*Bouclier (main gauche)*/
                    setMainGauche(&perso->equipement, obj);
                break;
                default: /*Souci*/
                    printf("Le type de votre objet est incoherent\n");
                break;
            }
        break;
        default: /*Autre*/
            printf("Vous ne pouvez vous équiper de cet objet.\n\n");
        break;

    }
}



void initialiserTousLesPNJ(Personnage** tabPNJ, const Objet* tabObjets)
{
    int i;
    int max = getNbPNJ();

    (*tabPNJ)=(Personnage*)malloc(max*sizeof(Personnage));


    for(i=1;i<=max;i++)
        {
            persoInitPNJ(&((*tabPNJ)[i-1]),i,tabObjets);
        }
}

void libererTousLesPNJ(Personnage** tabPNJ)
{
    free(*tabPNJ);
}


int calculNiveau (const int experience)
{
    assert (experience>=0);
    return (int)log(experience+1);
}



int mainPerso()
{
    char nom[30];
    char carriere[100];
    int i;
    Personnage perso;

    Objet *tabObjets=NULL;
    initialiserTousLesObjets(&tabObjets);

    for(i=0;i<100;i++)
    {
        nouveauPerso (&perso, "Toromis", 1, 1, 1, 1, 0, 100, tabObjets);
        getPersoNom(nom, &perso);
        printf("\n%s\n",nom);
        printf("\n%d\n",getPersoRace(&perso));
        printf("\n%d\n",getPersoSexe(&perso));

        printf("\n%d\n",getPersoCarriere(&perso));

        getCarriereNom(getPersoCarriere(&perso), carriere);
        printf("\n%s\n",carriere);

        printf("\n%d\n",getPersoArgent(&perso));
        printf("\n%d\n",getPersoExperience(&perso));
        printf("\n%d\n",getPersoAttaque(&perso));
        printf("\n%d\n",getPersoDefense(&perso));
        printf("\n%d\n",getPersoIntelligence(&perso));
        printf("\n%d\n",getPersoAgilite(&perso));
        printf("\n%d\n",getPersoCharisme(&perso));
        printf("\n%d\n",getPersoPtDeVie(&perso));

        persoLibere(&perso);
    }



    Personnage* tabPNJ;

    for(i=0;i<10;i++)
    {
        initialiserTousLesPNJ(&tabPNJ, tabObjets);
        libererTousLesPNJ(&tabPNJ);
    }

    libererTousLesObjets(&tabObjets);

    return 0;
}
