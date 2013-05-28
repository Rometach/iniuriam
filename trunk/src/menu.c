#include "menu.h"


/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

void partieInit (Partie* jeu,char nom[50], Personnage* liste, int nbJoueur,char missionsAccomplies[30][50],int nbMission,char missionActuelle[50])
{
    int i;

    assert (nbJoueur<5&&nbJoueur>0);

    jeu->joueur=(Personnage**)malloc(nbJoueur*sizeof(Personnage*));
    strcpy(jeu->nom,nom);
    for (i=0;i<nbJoueur;i++)
    {
        jeu->joueur[i]=&liste[i];
    }
    jeu->nbJoueur=nbJoueur;
    for (i=0;i<nbMission;i++)
    {
        strcpy (jeu->missionsAccomplies[i],missionsAccomplies[i]);
    }
    jeu->nbMission=nbMission;
    strcpy(jeu->missionActuelle,missionActuelle);
}

void partieLibere (Partie* jeu)
{
    free (jeu->joueur);
    jeu->nbJoueur=0;
    jeu->nbMission=0;
}

Personnage** getPartieJoueurs (Partie* jeu)
{
    return jeu->joueur;
}

Personnage* getPartieJoueurI (Partie* jeu, int i)
{
    assert (i>=0&&i<4);
    return jeu->joueur[i];
}

int getPartieNbJoueur (Partie* jeu)
{
    return jeu->nbJoueur;
}

void getPartieMissionAccomplie (Partie* jeu,int i,char tampon [50])
{
    strcpy(tampon,jeu->missionsAccomplies[i]);
}

int getPartieNbMission (Partie* jeu)
{
    return jeu->nbMission;
}

void getPartieMissionActuelle (Partie* jeu,char tampon [50])
{
    strcpy(tampon,jeu->missionActuelle);
}

void supprimerPartie (char nom [50])
{
    int i=1;
    FILE* fPartie,*fTampon;
    char ligne[TAILLE_MAX_FICHIER];
    fPartie= fopen("data/Sauvegardes.txt", "r");
    fTampon= fopen("data/Tampon.txt", "w");
    do
    {
        if(fgets(ligne,TAILLE_MAX_FICHIER,fPartie)!=NULL)
        {
            fprintf(fTampon,"%s",ligne);
            ligne[strlen(ligne)-1]='\0';
        }
        else i=0;
    } while(strcmp(nom,ligne)!=0&&i);
    assert(i);

    for (i=0;i<28;i++)
    {
        fgets(ligne,TAILLE_MAX_FICHIER,fPartie);
    }
    fprintf(fTampon,"/0\n\n/\n/\n//\n//\n/\n\n/\n/\n//\n//\n/\n\n/\n/\n//\n//\n/\n\n/\n/\n//\n//\n/\n\n//\n\n");
    while (fgets(ligne,TAILLE_MAX_FICHIER,fPartie)!=NULL)
    {
        fprintf(fTampon,"%s",ligne);
    }
    fclose(fPartie);
    fclose(fTampon);
    copierFichier("data/Tampon.txt","data/Sauvegardes.txt");
    remove("data/Tampon.txt");
}

void sauverPartie (char nom [50],Partie* jeu)
{
    int i=1,j;
    FILE* fPartie,*fTampon;
    char ligne[TAILLE_MAX_FICHIER], tampon [150];
    fPartie= fopen("data/Sauvegardes.txt", "r");
    fTampon= fopen("data/Tampon.txt", "w");
    do
    {
        if(fgets(ligne,TAILLE_MAX_FICHIER,fPartie)!=NULL)
        {
            fprintf(fTampon,"%s",ligne);
            ligne[strlen(ligne)-1]='\0';
        }
        else i=0;
    } while(strcmp(nom,ligne)!=0&&i);
    assert(i);

    for (i=0;i<28;i++)
    {
        fgets(ligne,TAILLE_MAX_FICHIER,fPartie);
    }

    fprintf(fTampon,"%s/%d",jeu->nom,jeu->nbJoueur);
    for (i=0;i<jeu->nbJoueur;i++)
    {
        fprintf(fTampon,"\n\n");
        getPersoNom(tampon,jeu->joueur[i]);
        fprintf(fTampon,"%s\n%d %d %d ",tampon,getPersoRace(jeu->joueur[i]),getPersoSexe(jeu->joueur[i]),getPersoFaction(jeu->joueur[i]));
        fprintf(fTampon,"%d %d %d %d %d %d %d %d %d %d %d\n",getPersoCarriere(jeu->joueur[i]),getPersoExperience(jeu->joueur[i]),getPersoArgent(jeu->joueur[i]),getPersoAttaque(jeu->joueur[i]),getPersoDefense(jeu->joueur[i]),getPersoIntelligence(jeu->joueur[i]),getPersoAgilite(jeu->joueur[i]),getPersoCharisme(jeu->joueur[i]),getPersoPtDeVie(jeu->joueur[i]),getPersoPosX(jeu->joueur[i]),getPersoPosY(jeu->joueur[i]));

        for (j=0;j<getCapaciteNbCompetence(getPersoCapacite2(jeu->joueur[i]));j++)
        {
            fprintf(fTampon,"%d %d/",getType(getCompetence(getPersoCapacite2(jeu->joueur[i]),j)),getExperience(getCompetence(getPersoCapacite2(jeu->joueur[i]),j)));
        }
        fprintf(fTampon,"/\n");

        for (j=0;j<getInventaireNbObjets(getPersoInventaire2(jeu->joueur[i]));j++)
        {
            fprintf(fTampon," %d/",getObjetType(getStockObjet(getInventaireStock(getPersoInventaire2(jeu->joueur[i]),j))));
        }
        fseek(fTampon,SEEK_CUR,-1);
        fprintf(fTampon,"/\n");

        if (getEquiTete(getPersoEquipement(jeu->joueur[i]))!=NULL)fprintf(fTampon,"%d ",getObjetType(getEquiTete(getPersoEquipement(jeu->joueur[i]))));
        else fprintf(fTampon,"0 ");
        if (getEquiTorse(getPersoEquipement(jeu->joueur[i]))!=NULL) fprintf(fTampon,"%d ",getObjetType(getEquiTorse(getPersoEquipement(jeu->joueur[i]))));
        else fprintf(fTampon,"0 ");
        if (getEquiBas(getPersoEquipement(jeu->joueur[i]))!=NULL) fprintf(fTampon,"%d ",getObjetType(getEquiBas(getPersoEquipement(jeu->joueur[i]))));
        else fprintf(fTampon,"0 ");
        if (getEquiMains(getPersoEquipement(jeu->joueur[i]))!=NULL)fprintf(fTampon,"%d ",getObjetType(getEquiMains(getPersoEquipement(jeu->joueur[i]))));
        else fprintf(fTampon,"0 ");
        if (getEquiPieds(getPersoEquipement(jeu->joueur[i]))!=NULL)fprintf(fTampon,"%d ",getObjetType(getEquiPieds(getPersoEquipement(jeu->joueur[i]))));
        if (getEquiMainGauche(getPersoEquipement(jeu->joueur[i]))!=NULL)fprintf(fTampon,"%d ",getObjetType(getEquiMainGauche(getPersoEquipement(jeu->joueur[i]))));
        else fprintf(fTampon,"0 ");
        for (j=0;j<3;j++)
        {
            if (getEquiMainDroite(getPersoEquipement(jeu->joueur[i]),j)!=NULL)fprintf(fTampon,"%d ",getObjetType(getEquiMainDroite(getPersoEquipement(jeu->joueur[i]),j)));
            else fprintf(fTampon,"0 ");
        }
    }
    fprintf(fTampon,"\n\n");

    for (i=jeu->nbJoueur;i<4;i++)
    {
        fprintf(fTampon,"/\n/\n/\n/\n\n");
    }

    for (i=0;i<jeu->nbMission;i++) fprintf(fTampon,"%s/",jeu->missionsAccomplies[i]);
    fprintf(fTampon,"/\n");

    fprintf(fTampon,"%s\n",jeu->missionActuelle);
    while (fgets(ligne,TAILLE_MAX_FICHIER,fPartie)!=NULL)
    {
        fprintf(fTampon,"%s",ligne);
    }
    fclose(fPartie);
    fclose(fTampon);
    copierFichier("data/Tampon.txt","data/Sauvegardes.txt");
    remove("data/Tampon.txt");
}

void chargerPartie (char nom [50],Partie* jeu)
{
    int i=1,j,k,nb,max1,max2,exp;
    FILE* fPartie;
    char ligne1[TAILLE_MAX_FICHIER],tampon[50],entier[9],type;
    Personnage* groupe;

    char race,sexe,faction,carriere;
    int experience,argent,ptDeVie, posX, posY,attaque,defense,intelligence,agilite,charisme;
    int armure[5],arme[3];
    int* inventaire;
    Competence* liste;

    fPartie= fopen("data/Sauvegardes.txt", "r");
    do
    {
        if(fgets(ligne1,TAILLE_MAX_FICHIER,fPartie)!=NULL) ligne1[strlen(ligne1)-1]='\0';
        else i=0;
    } while(strcmp(nom,ligne1)!=0&&i);
    assert(i);

    fgets (ligne1,TAILLE_MAX_FICHIER,fPartie);
    nb=ligne1[strlen(ligne1)-2]-'0';
    ligne1[strlen(ligne1)-3]='\0';
    strcpy(jeu->nom,ligne1);
    assert (nb<5&&nb>0);
    groupe=(Personnage*)malloc(nb*sizeof(Personnage));
    fgets (ligne1,TAILLE_MAX_FICHIER,fPartie);
    for (i=0;i<nb;i++)
    {
        fgets (ligne1,TAILLE_MAX_FICHIER,fPartie);
        strncpy(tampon,ligne1,strlen(ligne1)-1);
        tampon[strlen(ligne1)-1]='\0';

        fscanf(fPartie,"%c %c %c %c %d %d %d %d %d %d %d %d %d %d\n",&race,&sexe,&faction,&carriere,&experience,&argent,&attaque,&defense,&intelligence,&agilite,&charisme,&ptDeVie,&posX,&posY);
        race-='0';
        sexe-='0';
        faction-='0';
        carriere-='0';

        fgets (ligne1,TAILLE_MAX_FICHIER,fPartie);
        j=0;
        max1=0;
        while (ligne1[j]!='/'||ligne1[j+1]!='/')
        {
            if (ligne1[j]==' ')max1++;
            j++;
        }
        liste=(Competence*)malloc(max1*sizeof(Competence));
        j=0;
        k=0;
        while (max1!=0)
        {
            if (ligne1[j]==' ')
            {
                type=ligne1[j-1]-'0';
                strncpy(entier,ligne1+j,strchr(ligne1+j,'/')-ligne1-j);
                exp=atoi(entier);
                compInit(&liste[k],type,exp);
                k++;
                max1--;
            }
            j++;
        }

        fgets (ligne1,TAILLE_MAX_FICHIER,fPartie);
        j=0;
        max2=0;
        while (ligne1[j]!='/'||ligne1[j+1]!='/')
        {
            if (ligne1[j]==' ')max2++;
            j++;
        }
        inventaire=(int*)malloc(max2*sizeof(int));
        j=0;
        k=0;
        while (max2!=0)
        {
            if (ligne1[j]==' ')
            {
                strncpy(entier,ligne1+j,strchr(ligne1+j,'/')-ligne1-j);
                inventaire[k]=atoi(entier);
                k++;
                max2--;
            }
            j++;
        }
        fscanf(fPartie,"%d %d %d %d %d %d %d %d\n",&armure[0],&armure[1],&armure[2],&armure[3],&armure[4],&arme[0],&arme[1],&arme[2]);
        /*Misssions ...*/
        fgets (ligne1,TAILLE_MAX_FICHIER,fPartie);
        chargerPerso(&groupe[i],tampon,race,sexe,faction,carriere,experience,argent,attaque,defense,intelligence,agilite,charisme,ptDeVie,posX,posY,liste,max1,inventaire,max2,armure,arme);
        free (inventaire);
        free (liste);
    }
    for (i=0;i<nb;i++)
    {
        persoLibere(&groupe[i]);
    }
    free (groupe);
    fclose(fPartie);
}

char eventMenu()
{
    char action=0;
    char continuer=1;
    SDL_Event event;

    /*SDL_EnableKeyRepeat(10, 10);*/
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        action=1;
                        continuer=0;
                    break;
                    case SDLK_UP:
                        action=2;
                        continuer=0;
                    break;
                    case SDLK_LEFT:
                        action=2;
                        continuer=0;
                    break;
                    case SDLK_DOWN:
                        action=3;
                        continuer=0;
                    break;
                    case SDLK_RIGHT:
                        action=3;
                        continuer=0;
                    break;
                    case SDLK_RETURN:
                        action=5;
                        continuer=0;
                    default:
                    break;
                }
            break;
            case SDL_QUIT:
                continuer = 0;
            break;
            default:
            break;
        }
    }
    return action;
}

void afficherMenu (SDL_Surface *ecran, char jeu,TTF_Font *police,Partie* partie)
{
    char action,selection=0,type=1,lettre;
    int nb=0,choix=0,decalage=0,taille,i,j,valeur;
    char ligne[TAILLE_MAX_FICHIER], chaine1 [150], chaine2[150],tampon[50];
    char texte_SDL [10][150];
    FILE *fPartie;

    SDL_Surface *titre=NULL,*nom=NULL, **rectangle=NULL,*texte=NULL, *cadre=NULL,*sauvegarde=NULL;
    SDL_Rect position,position_rect;
    SDL_Color couleur_texte= {255, 255, 255},couleur_rect= {10, 10, 10};

    while (action)
    {
        titre = SDL_CreateRGBSurface(SDL_HWSURFACE, 400, 100, 32, 0, 0, 0, 0);
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 6, 29, 38));
        SDL_FillRect(titre, NULL, SDL_MapRGB(ecran->format, 10, 10, 10));

        position.x=TAILLE_FENETRE/2-200;
        position.y=TAILLE_FENETRE/20;
        SDL_BlitSurface(titre, NULL, ecran, &position);
        SDL_FreeSurface(titre);
        nb=0;
        switch (action)
        {
            case 1:/*Touche Echap*/
                if (jeu)
                {
                    switch (type)
                    {
                        case 5:/*Retour menu précédent*/
                            switch (selection)
                            {
                                case 0:/*Retour Sauver partie*/
                                    type=2;
                                    strcpy(chaine1,"Sauver partie");
                                    choix=0;
                                break;
                                case 1:/*Retour à Charger partie*/
                                    type=2;
                                    strcpy(chaine1,"Charger partie");
                                    choix=0;
                                break;
                                default:
                                break;
                            }
                        break;
                        case 6:/*Confirmation*/
                        break;
                        default:
                            type=1;
                            choix=0;
                        break;
                    }
                }
                else
                {
                    switch (type)
                    {
                        case 5:/*Retour menu parties*/
                            type=2;
                            strcpy(chaine1,"Iniuriam");
                            choix=0;
                        break;
                        case 6:/*Confirmation*/
                        break;
                        case 7:
                            type=5;
                            strcpy(chaine2,"Sauvegarde ");
                            switch (lettre)
                            {
                                case 0:
                                    strcat(chaine2,"A");
                                break;
                                case 1:
                                    strcat(chaine2,"B");
                                break;
                                case 2:
                                    strcat(chaine2,"C");
                                break;
                                default:
                                break;
                            }
                            choix=0;
                        break;
                        default:
                            type=1;
                            choix=0;
                        break;
                    }
                }

            break;
            case 2:/*Touche Flèche haut/gauche*/
                choix--;
            break;
            case 3:/*Touche Flèche bas/droite*/
                choix++;
            break;
            case 5:/*Touche Entrée*/
                if (jeu) /*Menu pause*/
                {
                    switch (type)
                    {
                        case 1: /*Menu principal*/
                            switch (choix)
                            {
                                case 0:/*Retour jeu*/
                                    action=0;
                                    type=0;
                                break;
                                case 1:/*Sauver Partie*/
                                    choix=0;
                                    selection=0;
                                    type=2;
                                    strcpy(chaine1,"Sauver");
                                break;
                                case 2:/*Charger Partie*/
                                    choix=0;
                                    selection=1;
                                    type=2;
                                    strcpy(chaine1,"Charger");
                                break;
                                case 3:/*Options*/
                                    choix=0;
                                    type=4;
                                break;
                                case 4:/*Quitter*/
                                    type=0;
                                    action=0;
                                break;
                                default:
                                break;
                            }
                        break;
                        case 2: /*Sauver/Charger partie*/
                            if (choix==3)
                            {
                                type=1;
                                choix=0;
                            }
                            else
                            {
                                type=5;
                                strcpy(chaine2,"Sauvegarde ");
                                switch (choix)
                                {
                                    case 0:
                                        strcat(chaine2,"A");
                                    break;
                                    case 1:
                                        strcat(chaine2,"B");
                                    break;
                                    case 2:
                                        strcat(chaine2,"C");
                                    break;
                                    default:
                                    break;
                                }
                                choix=0;
                            }
                        break;
                        case 4:/*Options*/
                        break;
                        case 5:/*Actions partie*/
                            if (choix==2||((choix==1)&&(strcmp(chaine1,"(Vide)")==0)))
                            {
                                choix=0;
                                type=2;
                                if (selection) strcpy(chaine1,"Charger");
                                else strcpy(chaine1,"Sauver");
                            }
                            else if (choix==0)
                            {
                                if (selection)
                                {
                                    chargerPartie(chaine2,partie);
                                    choix=0;
                                    action=0;
                                    type=0;
                                }
                                else
                                {
                                    sauverPartie(chaine2,partie);
                                    choix=0;
                                    type=1;
                                }
                            }
                            else {supprimerPartie(chaine2);}
                        break;
                        case 6:/*Confirmation*/
                            if (choix)
                            {
                                type=2;
                                choix=0;
                            }
                            else (supprimerPartie(tampon));
                        break;
                        default:
                        break;
                    }
                }
                else /*Menu principal*/
                {
                    switch (type)
                    {
                        case 1: /*Menu principal*/
                            switch (choix)
                            {
                                case 0:/*Jouer*/
                                    choix=0;
                                    type=2;
                                    strcpy(chaine1,"Iniuriam");
                                break;
                                case 1:/*Options*/
                                    choix=0;
                                    type=4;
                                break;
                                case 2:/*Quitter*/
                                    type=0;
                                    action=0;
                                break;
                                default:
                                break;
                            }
                        break;
                        case 2: /*Menu parties*/
                            if (choix==3)
                            {
                                type=1;
                                choix=0;
                            }
                            else
                            {
                                type=5;
                                strcpy(chaine2,"Sauvegarde ");
                                switch (choix)
                                {
                                    case 0:
                                        strcat(chaine2,"A");
                                    break;
                                    case 1:
                                        strcat(chaine2,"B");
                                    break;
                                    case 2:
                                        strcat(chaine2,"C");
                                    break;
                                    default:
                                    break;
                                }
                                lettre=choix;
                                choix=0;
                            }
                        break;
                        case 4:/*Option*/
                        break;
                        case 5:/*Actions partie*/
                            if (choix==0)
                            {
                                type=7;
                                choix=0;
                            }
                            if (choix==3||((choix==1)&&(strcmp(chaine1,"(Vide)")==0)))
                            {
                                strcpy(chaine1,"Iniuriam");
                                choix=0;
                                type=2;
                            }
                            else if (choix==2)/*Supprimer*/
                            {
                                strcpy(chaine1,tampon);
                                strcpy(tampon,chaine2);
                                strcpy(chaine2,"Supprimer ");
                                type=6;
                                choix=1;
                            }
                        break;
                        case 6:/*Confirmation*/
                            if (choix)
                            {
                                strcpy(chaine2,tampon);
                                type=5;
                                choix=0;
                            }
                            else
                            {
                                strcpy(chaine2,tampon);
                                type=5;
                                choix=0;
                                supprimerPartie(tampon);
                            }
                        break;
                        case 7:

                        break;
                        default:
                        break;
                    }
                }
            break;
            default:
            break;
        }
        switch (type)
        {
            case 1:/*Menu Principal*/
                if (jeu)
                {
                    nb=5;
                    strcpy(chaine1,"Pause");
                    strcpy(texte_SDL[0],"Retour");
                    strcpy(texte_SDL[1],"Sauver");
                    strcpy(texte_SDL[2],"Charger");
                    strcpy(texte_SDL[3],"Options");
                    strcpy(texte_SDL[4],"Quitter");
                }
                else
                {
                    nb=3;
                    strcpy(texte_SDL[0],"Jouer");
                    strcpy(texte_SDL[1],"Options");
                    strcpy(texte_SDL[2],"Quitter");
                    strcpy(chaine1,"Iniuriam");
                }
                nom = TTF_RenderText_Shaded(police, chaine1, couleur_texte,couleur_rect);
                position.x=TAILLE_FENETRE/2-100;
                position.y=TAILLE_FENETRE/20+25;
                SDL_BlitSurface(nom, NULL, ecran, &position);
                SDL_FreeSurface(nom);

                rectangle=(SDL_Surface**)malloc(nb*sizeof(SDL_Surface*));
            break;
            case 2:/*Menu parties*/
                nb=4;
                nom = TTF_RenderText_Shaded(police, chaine1, couleur_texte,couleur_rect);
                position.x=TAILLE_FENETRE/2-100;
                position.y=TAILLE_FENETRE/20+25;
                SDL_BlitSurface(nom, NULL, ecran, &position);
                SDL_FreeSurface(nom);

                strcpy(texte_SDL[0],"Sauvegarde A");
                strcpy(texte_SDL[1],"Sauvegarde B");
                strcpy(texte_SDL[2],"Sauvegarde C");
                strcpy(texte_SDL[3],"Retour");

                rectangle=(SDL_Surface**)malloc(nb*sizeof(SDL_Surface*));
            break;
            case 4:/*Options*/
                /*Crédits ...*/
            break;
            case 5:/*Actions partie*/
                nb=3;
                sauvegarde=SDL_CreateRGBSurface(SDL_HWSURFACE, 400, 200, 32, 0, 0, 0, 0);
                SDL_FillRect(sauvegarde, NULL, SDL_MapRGB(ecran->format, 10, 10, 10));
                fPartie=fopen("data/Sauvegardes.txt","r");
                do
                {
                    fgets(ligne,TAILLE_MAX_FICHIER,fPartie);
                    ligne[strlen(ligne)-1]='\0';
                } while(strcmp(chaine2,ligne)!=0);

                nom = TTF_RenderText_Shaded(police, chaine2, couleur_texte,couleur_rect);
                position.x=TAILLE_FENETRE/2-100;
                position.y=TAILLE_FENETRE/20+25;
                SDL_BlitSurface(nom, NULL, ecran, &position);
                SDL_FreeSurface(nom);
                SDL_Flip(ecran);
                getchar();

                fgets (chaine1,TAILLE_MAX_FICHIER,fPartie);
                valeur=chaine1[strlen(chaine1)-2]-'0';
                if (jeu)
                {
                    if (selection)
                    {
                        sprintf(texte_SDL[0],"%s","Charger");
                    }
                    else
                    {
                        strcpy(texte_SDL[0],"Sauver");
                    }
                    if (valeur==0)
                    {
                        strcpy(texte_SDL[1],"Retour");
                        strcpy (chaine1, "(Vide)");
                        nb--;
                    }
                    else
                    {
                        strcpy(texte_SDL[1],"Effacer");
                        strcpy(texte_SDL[2],"Retour");
                        chaine1[strlen(chaine1)-3]='\0';
                    }
                }
                else
                {
                    sprintf(texte_SDL[0],"%s","Jouer");
                    if (valeur==0)
                    {
                        strcpy(texte_SDL[1],"Retour");
                        strcpy (chaine1, "(Vide)");
                        nb--;
                    }
                    else
                    {
                        strcpy(texte_SDL[1],"Recommencer");
                        strcpy(texte_SDL[2],"Effacer");
                        strcpy(texte_SDL[3],"Retour");
                        nb++;
                        chaine1[strlen(chaine1)-3]='\0';
                        strcpy(tampon,chaine1);
                    }
                }
                position.x=TAILLE_FENETRE/2-200;
                position.y+=145;
                SDL_BlitSurface(sauvegarde, NULL, ecran, &position);

                SDL_FreeSurface(sauvegarde);
                /*Nom de la sauvegarde*/
                nom = TTF_RenderText_Shaded(police, chaine1, couleur_texte,couleur_rect);
                position.x=TAILLE_FENETRE/2-80;
                position.y+=10;
                SDL_BlitSurface(nom, NULL, ecran, &position);
                SDL_FreeSurface(nom);

                if (strcmp(chaine1,"(Vide)"))/*Ecriture du nom des joueurs*/
                {
                    for (j=0;j<valeur;j++)
                    {
                        fgets (ligne,TAILLE_MAX_FICHIER,fPartie);
                        fgets(ligne,TAILLE_MAX_FICHIER,fPartie);
                        strncpy(chaine1,ligne,strlen(ligne-1));
                        chaine1[strlen(ligne)-1]='\0';
                        nom = TTF_RenderText_Shaded(police, chaine1, couleur_texte,couleur_rect);
                        position.x=TAILLE_FENETRE/2-200;
                        position.y+=35;
                        SDL_BlitSurface(nom, NULL, ecran, &position);
                        SDL_FreeSurface(nom);

                        for (i=0;i<4;i++) fgets(ligne,TAILLE_MAX_FICHIER,fPartie);
                    }
                }

                fclose (fPartie);
                if (choix<0)/*aller à la dernière page et au dernier choix*/
                {
                    choix=nb-1;
                }
                else if (choix>nb-1)/*aller à la première page et au premier choix*/
                {
                    choix=0;
                }

                rectangle=(SDL_Surface**)malloc(nb*sizeof(SDL_Surface*));
                for (i=0;i<nb;i++)/*Page visible*/
                {
                    if (i==choix) /*Affichage du cadre*/
                    {
                        cadre = SDL_CreateRGBSurface(SDL_HWSURFACE, 160, 60, 32, 0, 0, 0, 0);
                        SDL_FillRect(cadre, NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
                        position_rect.x=TAILLE_FENETRE/(nb+6)+(180)*i;
                        position_rect.y=TAILLE_FENETRE/2+195;
                        SDL_BlitSurface(cadre, NULL, ecran, &position_rect);
                        SDL_FreeSurface(cadre);
                    }
                    rectangle[i]= SDL_CreateRGBSurface(SDL_HWSURFACE, 150, 50, 32, 0, 0, 0, 0);
                    SDL_FillRect(rectangle[i], NULL, SDL_MapRGB(ecran->format, 10, 10, 10));

                    position_rect.x=TAILLE_FENETRE/(nb+6)+(180)*i+5;
                    position_rect.y=TAILLE_FENETRE/2+200;
                    SDL_BlitSurface(rectangle[i], NULL, ecran, &position_rect);
                    SDL_FreeSurface(rectangle[i]);

                    position_rect.x+= 25;
                    texte=TTF_RenderText_Shaded(police, texte_SDL[i], couleur_texte,couleur_rect);
                    SDL_BlitSurface(texte, NULL, ecran, &position_rect);
                    SDL_FreeSurface(texte);
                }
            break;
            case 6: /*Confirmation*/
                nb=2;
                sprintf(ligne,"%s %s ?",chaine2,chaine1);
                nom = TTF_RenderText_Shaded(police,ligne, couleur_texte,couleur_rect);
                position.x=TAILLE_FENETRE/2-100;
                position.y=TAILLE_FENETRE/20+25;
                SDL_BlitSurface(nom, NULL, ecran, &position);
                SDL_FreeSurface(nom);

                strcpy(texte_SDL[0],"Oui");
                strcpy(texte_SDL[1],"Non");

                rectangle=(SDL_Surface**)malloc(2*sizeof(SDL_Surface*));
            break;
            case 7:/*Nouvelle Partie*/
                nom = TTF_RenderText_Shaded(police,"Nouvelle partie", couleur_texte,couleur_rect);
                position.x=TAILLE_FENETRE/2-100;
                position.y=TAILLE_FENETRE/20+25;
                SDL_BlitSurface(nom, NULL, ecran, &position);
                SDL_FreeSurface(nom);
            break;
            default:
            break;
        }
        if (nb==0) choix=0;
        else if (choix<0)/*aller à la dernière page et au dernier choix*/
        {
            choix=nb-1;
        }
        else if (choix>nb-1)/*aller à la première page et au premier choix*/
        {
            choix=0;
        }
        else if (choix==9)/*avancer d'une page*/
        {
        }
        else if (choix==0)/*reculer d'une page*/
        {
        }

        /*if (nb==0) Cas où on a besoin d'un scanf
        {
            rectangle=(SDL_Surface**)malloc(sizeof(SDL_Surface*));
            *rectangle= SDL_CreateRGBSurface(SDL_HWSURFACE, 500, 50, 32, 0, 0, 0, 0);
            SDL_FillRect(*rectangle, NULL, SDL_MapRGB(ecran->format, 10, 10, 10));
            position_rect.x=TAILLE_FENETRE/2-250;
            position_rect.y=TAILLE_FENETRE/3+200;
            SDL_BlitSurface(*rectangle, NULL, ecran, &position_rect);
            SDL_FreeSurface(*rectangle);
            free (rectangle);
        }*/
        decalage=0;
        if (type!=5)
        {
            for (i=0;i<nb;i++)/*Page visible*/
            {
                if (i==choix) /*Affichage du cadre*/
                {
                    cadre = SDL_CreateRGBSurface(SDL_HWSURFACE, 310, 60, 32, 0, 0, 0, 0);
                    SDL_FillRect(cadre, NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
                    position_rect.x=TAILLE_FENETRE/2-155;
                    position_rect.y=TAILLE_FENETRE/3-5+(50+(100/nb))*i+50*(decalage);
                    SDL_BlitSurface(cadre, NULL, ecran, &position_rect);
                    SDL_FreeSurface(cadre);
                }

                taille=0;
                position_rect.x=TAILLE_FENETRE/2-150;
                position_rect.y=TAILLE_FENETRE/3+(50+(100/nb))*i+50*(decalage);
                if (strlen(texte_SDL[i])>18)
                {
                    strcpy(chaine1,texte_SDL[i]);
                    while (strlen(chaine1)>=18)
                    {
                        taille++;
                        j=17;
                        while (j>=1&&chaine1[j]!=' ') j--;
                        if (j!=0)
                        {
                            valeur=j;
                            strncpy(chaine2,chaine1,valeur);
                            chaine2[valeur]='\0';
                        }
                        else
                        {
                            strncpy(chaine2,chaine1,17);
                            chaine2[17]='-';
                            chaine2[18]='\0';

                        }
                        if (i==choix) /*Affichage d'un cadre suplémentaire*/
                        {
                            cadre = SDL_CreateRGBSurface(SDL_HWSURFACE, 310, 60, 32, 0, 0, 0, 0);
                            SDL_FillRect(cadre, NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
                            position_rect.x=TAILLE_FENETRE/2-155;
                            position_rect.y=TAILLE_FENETRE/3-5+(50+(100/nb))*i+50*(decalage+taille);
                            SDL_BlitSurface(cadre, NULL, ecran, &position_rect);
                            SDL_FreeSurface(cadre);
                            position_rect.x+=5;
                            position_rect.y-=45;
                        }

                        rectangle[i]= SDL_CreateRGBSurface(SDL_HWSURFACE, 300, 50, 32, 0, 0, 0, 0);
                        SDL_FillRect(rectangle[i], NULL, SDL_MapRGB(ecran->format, 10, 10, 10));
                        SDL_BlitSurface(rectangle[i], NULL, ecran, &position_rect);
                        SDL_FreeSurface(rectangle[i]);

                        position_rect.x+= 25;
                        texte=TTF_RenderText_Shaded(police, chaine2, couleur_texte,couleur_rect);
                        SDL_BlitSurface(texte, NULL, ecran, &position_rect);
                        SDL_FreeSurface(texte);
                        position_rect.x-= 25;
                        position_rect.y+=50;
                        for (j=0;j<strlen(texte_SDL[i])-valeur+1;j++)
                        {
                            chaine1[j]=chaine1[valeur+j];
                        }
                    }
                    strcpy(texte_SDL[i],chaine1);
                    decalage+=taille;
                }
                rectangle[i]= SDL_CreateRGBSurface(SDL_HWSURFACE, 300, 50, 32, 0, 0, 0, 0);
                SDL_FillRect(rectangle[i], NULL, SDL_MapRGB(ecran->format, 10, 10, 10));

                position_rect.y=TAILLE_FENETRE/3+(50+(100/nb))*i+50*(decalage);
                SDL_BlitSurface(rectangle[i], NULL, ecran, &position_rect);
                SDL_FreeSurface(rectangle[i]);

                position_rect.x+= 25;
                position_rect.y=TAILLE_FENETRE/3+(50+(100/nb))*i+50*(decalage);
                texte=TTF_RenderText_Shaded(police, texte_SDL[i], couleur_texte,couleur_rect);
                SDL_BlitSurface(texte, NULL, ecran, &position_rect);
                SDL_FreeSurface(texte);
            }
        }

        SDL_Flip(ecran);
        if (action)
        {
            action=eventMenu();
            free (rectangle);
        }
    }
}

int mainMenu ()
{
    int i;
    Partie jeu;
    Personnage liste[4];
    Objet *tab=NULL;
    SDL_Surface* ecran = NULL;
    TTF_Font *police = NULL;

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    initialiserTousLesObjets(&tab);

    nouveauPerso (&liste[0], "Kylaste", 1, 0, 1, 1, 0, 100,tab);
    nouveauPerso (&liste[1], "Rometach", 2, 1, 1, 1, 0, 100,tab);
    nouveauPerso (&liste[2], "Toromis", 3, 1, 1, 1, 0, 100,tab);
    nouveauPerso (&liste[3], "Babar", 4, 1, 1, 1, 0, 100,tab);

    partieInit(&jeu,"The A company",liste, 4, NULL,0,"");

    police = TTF_OpenFont("data/Jester.ttf", 30);
    ecran=SDL_SetVideoMode(TAILLE_FENETRE, TAILLE_FENETRE_OBJET, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("Iniuriam",NULL);
    afficherMenu(ecran,0,police,&jeu);/*Affichage de l'écran principal*/

    partieLibere (&jeu);
    free (tab);
    for (i=0; i<4;i++)
    {
        persoLibere(&liste[i]);
    }
    SDL_FreeSurface(ecran);
    TTF_CloseFont(police);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
