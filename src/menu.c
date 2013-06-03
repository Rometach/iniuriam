#include "menu.h"


/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

void partieInit (Partie* jeu,char nom[50], Personnage* liste, int nbJoueur,int* missionsAccomplies,int nbMission,int missionActuelle,int numCarte)
{
    int i;

    assert (nbJoueur<5&&nbJoueur>0);

    jeu->joueur=(Personnage*)malloc(nbJoueur*sizeof(Personnage));
    strcpy(jeu->nom,nom);
    for (i=0;i<nbJoueur;i++)
    {
        copiePerso(&liste[i],&jeu->joueur[i]);
    }
    jeu->nbJoueur=nbJoueur;
    jeu->missionsAccomplies=(int*)malloc(nbMission*sizeof(int));
    for (i=0;i<nbMission;i++)
    {
        jeu->missionsAccomplies[i]=missionsAccomplies[i];
    }
    jeu->nbMission=nbMission;
    jeu->missionActuelle=missionActuelle;
    jeu->numCarte=numCarte;
}

void partieLibere (Partie* jeu)
{
    int i;
    for (i=0;i<jeu->nbJoueur;i++)
    {
        persoLibere (&jeu->joueur[i]);
    }
    free (jeu->joueur);
    free (jeu->missionsAccomplies);
    jeu->nbJoueur=0;
    jeu->nbMission=0;
}

void getPartieNom (Partie* jeu,char nom[50])
{
    strcpy(nom,jeu->nom);
}

Personnage* getPartieJoueurs (Partie* jeu)
{
    return jeu->joueur;
}

Personnage* getPartieJoueurI (Partie* jeu, int i)
{
    assert (i>=0&&i<4);
    return &jeu->joueur[i];
}

int getPartieNbJoueur (Partie* jeu)
{
    return jeu->nbJoueur;
}

int getPartieMissionAccomplie (Partie* jeu,int i)
{
   return jeu->missionsAccomplies[i];
}

int getPartieNbMission (Partie* jeu)
{
    return jeu->nbMission;
}

void getPartieMissionActuelle (Partie* jeu,Mission* mission,Objet* tabObjet)
{
    missionInit(mission);
    missionDefinir(mission,jeu->missionActuelle,tabObjet);
}

int getPartieMissionActuelleType (Partie* jeu)
{
    return jeu->missionActuelle;
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
    fprintf(fTampon,"/0\n\n/\n/\n//\n//\n/\n\n/\n/\n//\n//\n/\n\n/\n/\n//\n//\n/\n\n/\n/\n//\n//\n/\n\n/\n\n");
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
    int i=1,j,max;
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
        getPersoNom(tampon,&jeu->joueur[i]);
        fprintf(fTampon,"%s\n%d %d %d ",tampon,getPersoRace(&jeu->joueur[i]),getPersoSexe(&jeu->joueur[i]),getPersoFaction(&jeu->joueur[i]));
        fprintf(fTampon,"%d %d %d %d %d %d %d %d %d %d %d\n",getPersoCarriere(&jeu->joueur[i]),getPersoExperience(&jeu->joueur[i]),
                getPersoArgent(&jeu->joueur[i]),getPersoAttaque(&jeu->joueur[i]),getPersoDefense(&jeu->joueur[i]),getPersoIntelligence(&jeu->joueur[i]),
                getPersoAgilite(&jeu->joueur[i]),getPersoCharisme(&jeu->joueur[i]),getPersoPtDeVie(&jeu->joueur[i]),getPersoPosX(&jeu->joueur[i]),getPersoPosY(&jeu->joueur[i]));

        max=getCapaciteNbCompetence(getPersoCapacite2(&jeu->joueur[i]));
        for (j=0;j<max;j++)
        {
            fprintf(fTampon,"%d %d/",getType(getCompetence(getPersoCapacite2(&jeu->joueur[i]),j)),getExperience(getCompetence(getPersoCapacite2(&jeu->joueur[i]),j)));
        }
        if(max==0)fprintf(fTampon,"/");
        fprintf(fTampon,"/\n");

        max=getInventaireNbObjets(getPersoInventaire2(&jeu->joueur[i]));
        for (j=0;j<max;j++)
        {
            fprintf(fTampon," %d/",getObjetType(getStockObjet(getInventaireStock(getPersoInventaire2(&jeu->joueur[i]),j))));
        }
        fseek(fTampon,SEEK_CUR,-1);
        if (max==0)fprintf(fTampon,"/");
        fprintf(fTampon,"/\n");

        if (getEquiTete(getPersoEquipement(&jeu->joueur[i]))!=NULL)fprintf(fTampon,"%d ",getObjetType(getEquiTete(getPersoEquipement(&jeu->joueur[i]))));
        else fprintf(fTampon,"0 ");
        if (getEquiTorse(getPersoEquipement(&jeu->joueur[i]))!=NULL) fprintf(fTampon,"%d ",getObjetType(getEquiTorse(getPersoEquipement(&jeu->joueur[i]))));
        else fprintf(fTampon,"0 ");
        if (getEquiBas(getPersoEquipement(&jeu->joueur[i]))!=NULL) fprintf(fTampon,"%d ",getObjetType(getEquiBas(getPersoEquipement(&jeu->joueur[i]))));
        else fprintf(fTampon,"0 ");
        if (getEquiMains(getPersoEquipement(&jeu->joueur[i]))!=NULL)fprintf(fTampon,"%d ",getObjetType(getEquiMains(getPersoEquipement(&jeu->joueur[i]))));
        else fprintf(fTampon,"0 ");
        if (getEquiPieds(getPersoEquipement(&jeu->joueur[i]))!=NULL)fprintf(fTampon,"%d ",getObjetType(getEquiPieds(getPersoEquipement(&jeu->joueur[i]))));
        if (getEquiMainGauche(getPersoEquipement(&jeu->joueur[i]))!=NULL)fprintf(fTampon,"%d ",getObjetType(getEquiMainGauche(getPersoEquipement(&jeu->joueur[i]))));
        else fprintf(fTampon,"0 ");
        for (j=0;j<3;j++)
        {
            if (getEquiMainDroite(getPersoEquipement(&jeu->joueur[i]),j)!=NULL)fprintf(fTampon,"%d ",getObjetType(getEquiMainDroite(getPersoEquipement(&jeu->joueur[i]),j)));
            else fprintf(fTampon,"0 ");
        }
    }
    fprintf(fTampon,"\n\n");

    for (i=jeu->nbJoueur;i<4;i++)
    {
        fprintf(fTampon,"/\n/\n/\n/\n/\n\n");
    }

    for (i=0;i<jeu->nbMission;i++)
    {
        if (jeu->missionsAccomplies[i]<10) fprintf(fTampon,"0");
        fprintf(fTampon,"%d ",jeu->missionsAccomplies[i]);
    }
    fprintf(fTampon,"/\n");

    fprintf(fTampon,"%d %d\n",jeu->missionActuelle, jeu->numCarte);
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
    char race,sexe,faction,carriere;
    int experience,argent,ptDeVie, posX, posY,attaque,defense,intelligence,agilite,charisme;
    int armure[5],arme[3];
    int* inventaire;
    Competence* liste;


    free (jeu->joueur);
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
    jeu->nbJoueur=nb;
    jeu->joueur=(Personnage*)malloc(nb*sizeof(Personnage));
    fgets (ligne1,TAILLE_MAX_FICHIER,fPartie);
    for (i=0;i<nb;i++)
    {
        fgets (ligne1,TAILLE_MAX_FICHIER,fPartie);
        strncpy(tampon,ligne1,strlen(ligne1)-1);
        tampon[strlen(ligne1)-1]='\0';

        fscanf(fPartie,"%c %c %c %c %d %d %d %d %d %d %d %d %d %d\n",&race,&sexe,&faction,&carriere,&experience,&argent,&attaque,&defense,&intelligence,
               &agilite,&charisme,&ptDeVie,&posX,&posY);
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
        chargerPerso(&jeu->joueur[i],tampon,race,sexe,faction,carriere,experience,argent,attaque,defense,intelligence,agilite,charisme,ptDeVie,posX,posY,liste,max1,inventaire,max2,armure,arme);
        free (inventaire);
        free (liste);
    }
    fgets (ligne1,TAILLE_MAX_FICHIER,fPartie);
    j=0;
    k=0;
    entier[2]='\0';
    while (ligne1[j]!='/')
    {
        strncpy(entier,ligne1+3*k,2);
        jeu->missionsAccomplies[k]=atoi(entier);
        k++;
        j+=3;
        jeu->nbMission++;
    }
    fgets (ligne1,TAILLE_MAX_FICHIER,fPartie);
    strncpy(entier,ligne1,2);
    jeu->missionActuelle=atoi(ligne1);
    strncpy(entier,ligne1+3,2);
    jeu->numCarte=atoi(entier);
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
                        action=4;
                        continuer=0;
                    break;
                    case SDLK_DOWN:
                        action=3;
                        continuer=0;
                    break;
                    case SDLK_RIGHT:
                        action=5;
                        continuer=0;
                    break;
                    case SDLK_RETURN:
                        action=6;
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

int afficherPage (SDL_Surface *ecran,TTF_Font *police, char texte_SDL[10][150],int nb,int choix,int position,int* haut,int* bas,int* page)
{
    int i,j,decalage=0,taille,valeur;
    char chaine1[50],chaine2[50];
    SDL_Surface *cadre=NULL,*rectangle=NULL,*texte=NULL;
    SDL_Rect position_rect;
    SDL_Color couleur_texte= {255, 255, 255},couleur_rect= {10, 10, 10};

    assert(position);

    if (nb>5)*page=max(*haut,0);
    else
    {
        *haut=0;
        *page=0;
    }
    for (i=*page;i<min(nb,(*bas));i++)/*Page visible*/
    {
        if (i==choix) /*Affichage du cadre*/
        {
            cadre = SDL_CreateRGBSurface(SDL_HWSURFACE, 310, 60, 32, 0, 0, 0, 0);
            SDL_FillRect(cadre, NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
            position_rect.x=TAILLE_FENETRE_L/position-155;
            position_rect.y=TAILLE_FENETRE_H/3-5+(50+(100/nb))*(i-*haut)+50*(decalage);
            SDL_BlitSurface(cadre, NULL, ecran, &position_rect);
            SDL_FreeSurface(cadre);
        }

        taille=0;
        position_rect.x=TAILLE_FENETRE_L/position-150;
        position_rect.y=TAILLE_FENETRE_H/3+(50+(100/nb))*(i-*haut)+50*(decalage);
        if (strlen(texte_SDL[i])>=18)
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
                    valeur=17;
                    strncpy(chaine2,chaine1,17);
                    chaine2[17]='-';
                    chaine2[18]='\0';

                }
                if (i==choix) /*Affichage d'un cadre suplémentaire*/
                {
                    cadre = SDL_CreateRGBSurface(SDL_HWSURFACE, 310, 60, 32, 0, 0, 0, 0);
                    SDL_FillRect(cadre, NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
                    position_rect.x=TAILLE_FENETRE_L/position-155;
                    position_rect.y=TAILLE_FENETRE_H/3-5+(50+(100/nb))*(i-*haut)+50*(decalage+taille);
                    SDL_BlitSurface(cadre, NULL, ecran, &position_rect);
                    SDL_FreeSurface(cadre);
                    position_rect.x+=5;
                    position_rect.y-=45;
                }

                rectangle= SDL_CreateRGBSurface(SDL_HWSURFACE, 300, 50, 32, 0, 0, 0, 0);
                SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 10, 10, 10));
                SDL_BlitSurface(rectangle, NULL, ecran, &position_rect);
                SDL_FreeSurface(rectangle);

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
        rectangle= SDL_CreateRGBSurface(SDL_HWSURFACE, 300, 50, 32, 0, 0, 0, 0);
        SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 10, 10, 10));

        position_rect.y=TAILLE_FENETRE_H/3+(50+(100/nb))*(i-*haut)+50*(decalage);
        SDL_BlitSurface(rectangle, NULL, ecran, &position_rect);
        SDL_FreeSurface(rectangle);

        position_rect.x+= 25;
        position_rect.y=TAILLE_FENETRE_H/3+(50+(100/nb))*(i-*haut)+50*(decalage);
        texte=TTF_RenderText_Shaded(police, texte_SDL[i], couleur_texte,couleur_rect);
        SDL_BlitSurface(texte, NULL, ecran, &position_rect);
        SDL_FreeSurface(texte);
        if (*page+decalage<*haut+7)(*page)++;
    }
    *bas=*page;
    return decalage;
}

char nouvellePartie (SDL_Surface *ecran,TTF_Font *police,Partie* jeu,char* sauvegarde,FMOD_SYSTEM *system)
{
    FMOD_SOUND *error = NULL;
    char action=8,type=1,j;
    int choix=0,nb,i,selection,decalage=2, haut=0,bas=9,page,valeur;
    SDL_Surface *rectangle,*texte,*images,*fond;
    SDL_Rect position;
    SDL_Color couleur_texte= {255, 255, 255},couleur_rect= {10, 10, 10};
    Objet *tab=NULL;

    nb=getNbCarriere();
    char texte_SDL [nb][150],chaine1[50],tampon[150],caractere[2];

    initialiserTousLesObjets(&tab);
    caractere[1]='\0';
    FMOD_System_CreateSound(system, "data/Media/error.wav", FMOD_CREATESAMPLE, 0, &error);

    char nom[50]="",nom_perso[50]="",race=0,sexe=0,carriere=0;
    int nbJoueur=0;
    Personnage groupe [4];
    for (i=0;i<4;i++) persoInit(&groupe[i]);

    while (action!=0&&action!=7&&action!=9)
    {
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 6, 29, 38));

        fond = IMG_Load("data/Media/menu.jpg");
        position.x=0;
        position.y=0;
        SDL_BlitSurface(fond, NULL, ecran, &position);
        SDL_FreeSurface(fond);

        rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, 400, 100, 32, 0, 0, 0, 0);
        SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 10, 10, 10));
        position.x=TAILLE_FENETRE_L/2-200;
        position.y=TAILLE_FENETRE_H/20;
        SDL_BlitSurface(rectangle, NULL, ecran, &position);
        SDL_FreeSurface(rectangle);

        switch(action)
        {
            case 1:/*Echap*/
                if (type==1)
                {
                    action=7;
                    type=0;
                }
                if (type==6||(type==2&&j==0))
                {
                    type=3;
                    choix=0;
                    bas=6;
                }
                if (type>3&&type<6)
                {
                    bas=6;
                    type--;
                    choix=0;
                }
                else
                {
                    type=1;
                    choix=0;
                }
            break;
            case 2:/*Touche Flèche haut*/
                choix--;
            break;
            case 3:/*Touche Flèche bas*/
                choix++;
            break;
            case 4:/*Touche Flèche gauche*/
                choix--;
            break;
            case 5:/*Touche Flèche droite*/
                choix++;
            break;
            case 6:/*Touche Entrée*/
                switch(type)
                {
                    case 1:/*Nouvelle partie*/
                        if(choix==0) /*Nom Partie*/
                        {
                            type=2;
                            selection=4;
                            strcpy(chaine1,"Nom du Groupe");
                            j=1;
                        }
                        else if (choix==nb-2)/*Valider*/
                        {
                            getPersoNom(nom_perso,&groupe[0]);
                            if (strlen(nom)&&strlen(nom_perso))
                            {
                                type=7;
                                selection=4;
                            }
                            else FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, error, 0, NULL);
                        }
                        else if (choix==nb-1)/*Return*/
                        {
                            action=7;
                            type=0;
                            selection=4;
                        }
                        else/*Perso*/
                        {
                            type=3;
                            bas=6;
                            selection=choix-1;
                            caractere[0]='0'+choix;
                        }
                        if (selection<4)
                        {
                            getPersoNom(nom_perso,&groupe[selection]);
                            race=getPersoRace(&groupe[selection]);
                            sexe=getPersoSexe(&groupe[selection]);
                            carriere=getPersoCarriere(&groupe[selection]);
                        }
                        choix=0;
                    break;
                    case 2:/*scanf*/
                        if (j)/*scanf du nom du groupe*/
                        {
                            choix=0;
                            type=1;
                            strncpy(nom,tampon,strlen(tampon));
                            nom[strlen(tampon)]='\0';
                        }
                        else/*scanf du nom du Joueur*/
                        {
                            choix=0;
                            type=3;
                            strncpy(nom_perso,tampon,strlen(tampon));
                            nom_perso[strlen(tampon)]='\0';
                        }
                    break;
                    case 3:/*Création perso*/
                        switch(choix)
                        {
                            case 0:/*Modif nom*/
                                type=2;
                                choix=0;
                                j=0;
                                strcpy(chaine1,"Nom du joueur");
                            break;
                            case 1:/*Modif Race et Sexe*/
                                type=4;
                                choix=0;
                            break;
                            case 2:/*Modif Carriere*/
                                type=6;
                                choix=0;
                                bas=8;
                            break;
                            case 3:/*Valider*/
                                if (strlen(nom_perso)&&race&&sexe&&carriere)/*L'utilisateur a tout rempli*/
                                {
                                    j=1;
                                    for (i=0;i<4;i++)/*Vérifie si le perso n'a pas le même nom qu'un autre joueur*/
                                    {
                                        getPersoNom(tampon,&groupe[i]);
                                        if (i!=selection&&strcmp(nom_perso,tampon)==0)j=0;
                                    }
                                    if(j)
                                    {
                                        persoLibere(&groupe[selection]);
                                        nouveauPerso(&groupe[selection],nom_perso,race,sexe,0,carriere,0,100,tab);
                                        choix=selection+1;
                                        type=1;
                                    }
                                    else FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, error, 0, NULL);
                                }
                                else FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, error, 0, NULL);
                            break;
                            case 4: /*Annuler*/
                                type=1;
                                choix=0;
                            default:
                            break;
                        }
                    break;
                    case 4:/*Choix Race*/
                        if (choix!=4)
                        {
                            race=choix+1;
                            type=5;
                        }
                        else
                        {
                            type=3;
                            bas=6;
                        }
                        choix=0;
                    break;
                    case 5:/*Choix Sexe*/
                        if (choix!=3)
                        {
                            sexe=choix+1;
                            type=3;
                            bas=6;
                        }
                        else type=4;
                        choix=0;
                    break;
                    case 6:/*Choix Carriere*/
                        carriere=choix+1;
                        type=3;
                        bas=6;
                        choix=0;
                    break;
                    case 7:/*Choix Faction*/
                        if (choix==2)
                        {
                            choix=0;
                            action=8;
                            type=1;
                        }
                        else
                        {
                            action=9;
                            type=0;
                            for (i=0;i<nbJoueur;i++)
                            {
                                setPersoFaction(&groupe[i],choix+1);
                            }
                            partieLibere(jeu);
                            partieInit(jeu,nom,groupe,nbJoueur,NULL,0,1,1);
                            sauverPartie(sauvegarde,jeu);
                        }

                    break;
                    default:
                    break;
                }
            default:
            break;
        }

        switch (type)
        {
            case 1:/*Nouvelle Partie*/
                nb=3;
                nbJoueur=0;
                decalage=2;
                strcpy(chaine1,"Nouvelle Partie");
                if(strlen(nom)==0) strcpy(texte_SDL[0],"Nom de votre groupe");
                else strcpy(texte_SDL[0],nom);
                do
                {
                    getPersoNom(nom_perso,&groupe[nb-3]);
                    if (strlen(nom_perso))
                    {
                        strcpy(texte_SDL[nb-2],nom_perso);
                        nbJoueur++;
                    }
                    nb++;
                }
                while (strlen(nom_perso)&&nb<=7);
                if (nb==8)
                {
                    nb--;
                    nbJoueur--;
                }
                else if (nb<8)strcpy(texte_SDL[nb-3],"Ajouter Joueur");
                strcpy(texte_SDL[nb-2],"Valider");
                strcpy(texte_SDL[nb-1],"Annuler");
            break;
            case 2:/*scanf*/
                nb=0;
            break;
            case 3:/*Création perso*/
                nb=5;
                decalage=2;
                strcpy(chaine1,"Joueur ");
                strcat(chaine1,caractere);
                if(strlen(nom_perso)==0) strcpy(texte_SDL[0],"Nom");
                else strcpy(texte_SDL[0],nom_perso);
                if(race==0)strcpy(texte_SDL[1],"Race et Sexe");
                else
                {
                    getRaceNom(texte_SDL[1],race);
                    strcat(texte_SDL[1]," ");
                    getSexeNom(tampon,sexe);
                    strcat(texte_SDL[1],tampon);
                }
                if (carriere==0)strcpy(texte_SDL[2],"Carriere");
                else getCarriereNom(carriere,texte_SDL[2]);
                strcpy(texte_SDL[3],"Valider");
                strcpy(texte_SDL[4],"Annuler");
            break;
            case 4:/*Choix de la race*/
                strcpy(chaine1,"Race du joueur");
                nb=5;
                bas=nb+1;
                decalage=4;
                strcpy(texte_SDL[0],"Humains");
                strcpy(texte_SDL[1],"Cyborgs");
                strcpy(texte_SDL[2],"Sicaris");
                strcpy(texte_SDL[3],"Medarsins");
                strcpy(texte_SDL[4],"Annuler");
                switch(choix)
                {
                    case 0: images=IMG_Load("data/Media/human man.jpg");break;
                    case 1: images=IMG_Load("data/Media/cyborg man.jpg");break;
                    case 2: images=IMG_Load("data/Media/sicari man.jpg");break;
                    case 3: images=IMG_Load("data/Media/medarsin man.jpg");break;
                    default:break;
                }
                position.x=TAILLE_FENETRE_L/1.5;
                position.y=0;
                SDL_BlitSurface(images, NULL, ecran, &position);
                SDL_FreeSurface(images);
            break;
            case 5:/*Choix du sexe*/
                strcpy(chaine1,"Sexe du joueur");
                nb=3;
                bas=nb+1;
                decalage=4;
                strcpy(texte_SDL[0],"Masculin");
                strcpy(texte_SDL[1],"Feminin");
                strcpy(texte_SDL[2],"Annuler");

                switch(race)
                {
                    case 0: strcpy(tampon,"data/Media/human ");break;
                    case 1: strcpy(tampon,"data/Media/cyborg ");break;
                    case 2: strcpy(tampon,"data/Media/sicari ");break;
                    case 3: strcpy(tampon,"data/Media/medarsin ");break;
                    default:break;
                }
                if (choix==0) strcat(tampon,"man.jpg");
                else if(choix==1) strcat(tampon,"woman.jpg");
                images=IMG_Load(tampon);
                position.x=TAILLE_FENETRE_L/1.5;
                position.y=0;
                SDL_BlitSurface(images, NULL, ecran, &position);
                SDL_FreeSurface(images);
            break;
            case 6:/*Choix de carriere*/
                strcpy(chaine1,"Carriere");
                nb=getNbCarriere();
                decalage=2;
                for (i=0;i<nb;i++)
                {
                    getCarriereNom(i+1,texte_SDL[i]);
                }
            break;
            case 7:/*Choix de faction*/
                strcpy(chaine1,"Faction");
                nb=3;
                bas=nb+1;
                strcpy(texte_SDL[0],"Siste");
                strcpy(texte_SDL[1],"Heredia");
                strcpy(texte_SDL[2],"Annuler");
                decalage=2;
            default:
            break;
        }

        texte = TTF_RenderText_Shaded(police, chaine1, couleur_texte,couleur_rect);
        position.x=TAILLE_FENETRE_L/2-100;
        position.y=TAILLE_FENETRE_H/20+25;
        SDL_BlitSurface(texte, NULL, ecran, &position);
        SDL_FreeSurface(texte);

        if (choix<0)/*aller à la dernière page et au dernier choix*/
        {
            choix=nb-1;
            haut=nb-2;
            bas=nb;
        }
        else if (choix>nb-1)/*aller à la première page et au premier choix*/
        {
            choix=0;
            haut=0;
            bas=8;
        }
        else if (choix>bas-1)/*avancer d'une page*/
        {
            valeur=(int)strlen(texte_SDL[haut])/19;
            if ((int)strlen(texte_SDL[choix])/19>=valeur) haut+=(int)1+strlen(texte_SDL[choix])/19-valeur;
            else haut++;

            if(valeur>(int)strlen(texte_SDL[choix])/19) bas+=1+valeur;
            else bas+=(int)1+strlen(texte_SDL[choix])/19;
        }
        else if (choix<haut)/*reculer d'une page*/
        {
            haut--;
            /*bas--;*/
        }
        if (nb) afficherPage (ecran,police,texte_SDL,nb,choix,decalage,&haut,&bas,&page);

        SDL_Flip(ecran);
        if (action&&action!=7&&action!=9&&nb) action=eventMenu();

        else if (nb==0)/*scanf*/
        {
            if (j)scanfSDL(tampon,ecran,49,&action,police,0);/*scanf du groupe*/
            else scanfSDL(tampon,ecran,29,&action,police,0);/*scanf du nom du perso*/
            if (action!=0)action=6;
        }
    }
    for (i=0;i<4;i++)
    {
        persoLibere(&groupe[i]);
    }
    libererTousLesObjets(&tab);
    FMOD_Sound_Release(error);
    return action;
}

char afficherOptions(SDL_Surface *ecran,TTF_Font *police,FMOD_SYSTEM *system,FMOD_SOUND **musique)
{
    char action=8,type=1;
    int choix=0,nb, choix_son=10,choix_musique=0,decalage,haut=0,page=0;

    FMOD_CHANNELGROUP *canal;
    float  volume=0.0;
    FMOD_System_GetMasterChannelGroup(system, &canal);

    char texte_SDL [5][150],chaine1[50]="Options",chaine2[50];
    SDL_Surface **rectangle,*curseur,*texte,*fond,*son;
    SDL_Rect position,position_curs;
    SDL_Color couleur_texte= {255, 255, 255},couleur_rect= {10, 10, 10};

    char chanson[3][100]={"GRAMATIK-Muy tranquilo.mp3","GRAMATIK-Just Jammin'.mp3","GRAMATIK-The swing of justice.mp3"};

    while (action!=0&&action!=7)
    {
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 6, 29, 38));

        fond = IMG_Load("data/Media/menu.jpg");
        position.x=0;
        position.y=0;
        SDL_BlitSurface(fond, NULL, ecran, &position);
        SDL_FreeSurface(fond);

        rectangle=(SDL_Surface**)malloc(sizeof(SDL_Surface*));
        rectangle[0] = SDL_CreateRGBSurface(SDL_HWSURFACE, 400, 100, 32, 0, 0, 0, 0);
        SDL_FillRect(rectangle[0], NULL, SDL_MapRGB(ecran->format, 10, 10, 10));
        position.x=TAILLE_FENETRE_L/2-200;
        position.y=TAILLE_FENETRE_H/20;
        SDL_BlitSurface(rectangle[0], NULL, ecran, &position);
        SDL_FreeSurface(rectangle[0]);
        free(rectangle);
        switch (action)
        {
            case 1:/*Echap*/
                if (type==1)
                {
                    action=7;
                    type=0;
                }
                else
                {
                    type=1;
                    choix=0;
                    strcpy(chaine1,"Options");
                }
            break;
            case 2:/*Touche Flèche haut*/
                choix--;
            break;
            case 3:/*Touche Flèche bas*/
                choix++;
            break;
            case 4:/*Touche Flèche gauche*/
                if (type==2)
                {
                    if (choix==0)
                    {
                        choix_musique--;
                        if (choix_musique<0)choix_musique=0;
                        strcpy(chaine2,"data/Media/");
                        strcat(chaine2,chanson[choix_musique]);
                        FMOD_Sound_Release(*musique);
                        FMOD_System_CreateSound(system, chaine2, FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, musique);
                        FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, *musique, 0, NULL);
                    }
                    else if (choix==1)
                    {
                        choix_son--;
                        if (choix_son<0)choix_son=0;
                        volume=(float)choix_son/10;
                        FMOD_ChannelGroup_SetVolume(canal,volume);
                    }
                }
            break;
            case 5:/*Touche Flèche droite*/
                if (type==2)
                {
                    if (choix==0)
                    {
                        choix_musique++;
                        if (choix_musique>2)choix_musique=2;
                        strcpy(chaine2,"data/Media/");
                        strcat(chaine2,chanson[choix_musique]);
                        FMOD_Sound_Release(*musique);
                        FMOD_System_CreateStream(system, chaine2, FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, musique);
                        FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, *musique, 0, NULL);

                    }
                    else if (choix==1)
                    {
                        choix_son++;
                        if (choix_son>10)choix_son=10;
                        volume=(float)choix_son/10;
                        FMOD_ChannelGroup_SetVolume(canal,volume);
                    }
                }
            break;
            case 6:/*Touche Entrée*/
                switch(type)
                {
                    case 1:/*Options*/
                        switch (choix)
                        {
                            case 0:/*Audio*/
                                type=2;
                                choix=0;
                                strcpy(chaine1,"Audio");
                            break;
                            case 1:/*Credits*/
                                type=3;
                                strcpy(chaine1,"Credits");
                            break;
                            case 2:/*Return*/
                                action=7;
                                type=0;
                            break;
                        }
                    break;
                    case 2:/*Audio*/
                        if (choix==2)
                        {
                            type=1;
                            choix=0;
                            strcpy(chaine1,"Options");
                        }
                    break;
                    case 3:/*Credits*/
                        type=1;
                        choix=0;
                        strcpy(chaine1,"Options");
                    break;
                    default:
                    break;
                }
            default:
            break;
        }

        texte = TTF_RenderText_Shaded(police, chaine1, couleur_texte,couleur_rect);
        position.x=TAILLE_FENETRE_L/2-100;
        position.y=TAILLE_FENETRE_H/20+25;
        SDL_BlitSurface(texte, NULL, ecran, &position);
        SDL_FreeSurface(texte);

        switch (type)
        {
            case 1:/*Options*/
                nb=3;
                strcpy(texte_SDL[0],"Audio");
                strcpy(texte_SDL[1],"Credits");
                strcpy(texte_SDL[2],"Retour");
            break;
            case 2:/*Audio*/
                nb=3;
                strcpy(texte_SDL[0],"Musique : ");
                strcat (texte_SDL[0],chanson[choix_musique]);
                strcpy(texte_SDL[1],"");
                strcpy(texte_SDL[2],"Retour");

            break;
            case 3:/*Credits*/
                nb=0;
            break;
            default:
            break;
        }

        if (choix<0) choix=nb-1;/*aller à la dernière page et au dernier choix*/
        else if (choix>nb-1) choix=0;/*aller à la première page et au premier choix*/

        decalage=afficherPage (ecran,police,texte_SDL,nb,choix,2,&haut,&nb,&page);

        if (type==2)
        {
            /*Affichage du curseur*/
            curseur = SDL_CreateRGBSurface(SDL_HWSURFACE, 30, 50, 32, 0, 0, 0, 0);
            SDL_FillRect(curseur, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
            position_curs.x=TAILLE_FENETRE_L/2-150+choix_son*30/1.1;
            position_curs.y=TAILLE_FENETRE_H/3+(50+(100/nb)+50*decalage);
            SDL_BlitSurface(curseur, NULL, ecran, &position_curs);
            SDL_FreeSurface(curseur);

            /*Affichage du volume*/
            if (volume==0)son = IMG_Load("data/Media/volume-mute.jpg");
            else if (volume>0&&volume<0.34)son = IMG_Load("data/Media/volume-mute.jpg");
            else if (volume>=0.34&&volume<0.8)son = IMG_Load("data/Media/volume-mute.jpg");
            else son = IMG_Load("data/Media/volume-high.jpg");
            position.x=TAILLE_FENETRE_L/2-170;
            SDL_BlitSurface(son, NULL, ecran, &position);
            SDL_FreeSurface(son);
        }

        SDL_Flip(ecran);
        if (action&&action!=7) action=eventMenu();
    }
    return action;
}

char afficherMenu (SDL_Surface *ecran, char jeu,TTF_Font *police,Partie* partie)
{
    char action=8,selection=0,type=1,lettre;
    int nb=0,choix=0,i,j,valeur,page=0,haut=0;
    char ligne[TAILLE_MAX_FICHIER], chaine1 [150], chaine2[150],tampon[50];
    char texte_SDL [10][150];
    FILE *fPartie;
    FMOD_SYSTEM *system;
    FMOD_SOUND *musique;

    FMOD_System_Create(&system);
    FMOD_System_Init(system, 2, FMOD_INIT_NORMAL, NULL);
    FMOD_System_CreateStream(system, "data/Media/GRAMATIK-Muy tranquilo.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
    FMOD_Sound_SetLoopCount(musique, -1);
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);

    SDL_Surface *nom=NULL, *rectangle=NULL,*cadre,*texte=NULL, *sauvegarde=NULL,*fond=NULL;
    SDL_Rect position;
    SDL_Color couleur_texte= {255, 255, 255},couleur_rect= {10, 10, 10};

    while (action!=0&&action!=9)
    {
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 6, 29, 38));
        fond = IMG_Load("data/Media/menu.jpg");
        position.x=0;
        position.y=0;
        SDL_BlitSurface(fond, NULL, ecran, &position);
        SDL_FreeSurface(fond);

        rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, 400, 100, 32, 0, 0, 0, 0);
        SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 10, 10, 10));
        position.x=TAILLE_FENETRE_L/2-200;
        position.y=TAILLE_FENETRE_H/20;
        SDL_BlitSurface(rectangle, NULL, ecran, &position);
        SDL_FreeSurface(rectangle);

        nb=0;
        switch (action)
        {
            case 1:/*Touche Echap*/
                if (jeu)
                {
                    switch (type)
                    {
                        case 1:/*Menu pause*/
                            action=9;
                            type=0;
                        break;
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
            case 2:/*Touche Flèche haut*/
                choix--;
            break;
            case 3:/*Touche Flèche bas*/
                choix++;
            break;
            case 4:/*Touche Flèche gauche*/
                choix--;
            break;
            case 5:/*Touche Flèche droite*/
                choix++;
            break;
            case 6:/*Touche Entrée*/
                if (jeu) /*Menu pause*/
                {
                    switch (type)
                    {
                        case 1: /*Menu principal*/
                            switch (choix)
                            {
                                case 0:/*Retour jeu*/
                                    action=9;
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
                            type=4;
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
                                    action=9;
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
                        case 4:/*Options*/
                            type=4;
                        break;
                        case 5:/*Actions partie*/
                            if (choix==0&&(strcmp(chaine1,"(Vide)")==0))/*Nouvelle partie*/
                            {
                                action=nouvellePartie (ecran, police, partie,chaine2,system);
                                choix=0;
                            }
                            else if(choix==0)/*Charger partie*/
                            {
                                chargerPartie(chaine2,partie);
                                action=9;
                                type=0;
                            }
                            if (choix==3||((choix==1)&&(strcmp(chaine1,"(Vide)")==0)))
                            {
                                strcpy(chaine1,"Iniuriam");
                                choix=0;
                                type=2;
                            }
                            else if (choix==1)/*Recommencer*/
                            {
                                action=nouvellePartie (ecran, police, partie,chaine2,system);
                                choix=0;
                            }
                            else if (choix==2)/*Supprimer*/
                            {
                                strcpy(chaine1,tampon);
                                if (strlen(chaine1)>25)
                                {
                                    chaine1[25]='.';
                                    chaine1[26]='.';
                                    chaine1[27]='.';
                                    chaine1[28]='\0';
                                }
                                strcat(chaine1," ?");

                                strcpy(tampon,chaine2);
                                strcpy(chaine2,"Supprimer");
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
                position.x=TAILLE_FENETRE_L/2-100;
                position.y=TAILLE_FENETRE_H/20+25;
                SDL_BlitSurface(nom, NULL, ecran, &position);
                SDL_FreeSurface(nom);
            break;
            case 2:/*Menu parties*/
                nb=4;
                nom = TTF_RenderText_Shaded(police, chaine1, couleur_texte,couleur_rect);
                position.x=TAILLE_FENETRE_L/2-100;
                position.y=TAILLE_FENETRE_H/20+25;
                SDL_BlitSurface(nom, NULL, ecran, &position);
                SDL_FreeSurface(nom);

                strcpy(texte_SDL[0],"Sauvegarde A");
                strcpy(texte_SDL[1],"Sauvegarde B");
                strcpy(texte_SDL[2],"Sauvegarde C");
                strcpy(texte_SDL[3],"Retour");
            break;
            case 4:/*Options*/
                nb=0;
                action=afficherOptions(ecran,police,system,&musique);
                type=1;
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
                position.x=TAILLE_FENETRE_L/2-100;
                position.y=TAILLE_FENETRE_H/20+25;
                SDL_BlitSurface(nom, NULL, ecran, &position);
                SDL_FreeSurface(nom);

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
                position.x=TAILLE_FENETRE_L/2-200;
                position.y+=145;
                SDL_BlitSurface(sauvegarde, NULL, ecran, &position);
                SDL_FreeSurface(sauvegarde);
                /*Nom de la sauvegarde*/
                if (strlen(chaine1)>25)
                {
                    chaine1[25]='.';
                    chaine1[26]='.';
                    chaine1[27]='.';
                    chaine1[28]='\0';
                }
                nom = TTF_RenderText_Shaded(police, chaine1, couleur_texte,couleur_rect);
                position.x=TAILLE_FENETRE_L/2-180;
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
                        position.x=TAILLE_FENETRE_L/2-200;
                        position.y+=40;
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

                for (i=0;i<nb;i++)/*Page visible*/
                {
                    if (i==choix) /*Affichage du cadre*/
                    {
                        cadre = SDL_CreateRGBSurface(SDL_HWSURFACE, 210, 60, 32, 0, 0, 0, 0);
                        SDL_FillRect(cadre, NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
                        position.x=TAILLE_FENETRE_L/(nb+10)+(220)*i;
                        position.y=TAILLE_FENETRE_H/2+195;
                        SDL_BlitSurface(cadre, NULL, ecran, &position);
                        SDL_FreeSurface(cadre);
                    }
                    rectangle= SDL_CreateRGBSurface(SDL_HWSURFACE, 200, 50, 32, 0, 0, 0, 0);
                    SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 10, 10, 10));

                    position.x=TAILLE_FENETRE_L/(nb+10)+(220)*i+5;
                    position.y=TAILLE_FENETRE_H/2+200;
                    SDL_BlitSurface(rectangle, NULL, ecran, &position);
                    SDL_FreeSurface(rectangle);

                    position.x+= 10;
                    texte=TTF_RenderText_Shaded(police, texte_SDL[i], couleur_texte,couleur_rect);
                    SDL_BlitSurface(texte, NULL, ecran, &position);
                    SDL_FreeSurface(texte);
                }
            break;
            case 6: /*Confirmation*/
                nb=2;
                nom = TTF_RenderText_Shaded(police,chaine2, couleur_texte,couleur_rect);
                position.x=TAILLE_FENETRE_L/2-100;
                position.y=TAILLE_FENETRE_H/20;
                SDL_BlitSurface(nom, NULL, ecran, &position);
                SDL_FreeSurface(nom);

                nom = TTF_RenderText_Shaded(police,chaine1, couleur_texte,couleur_rect);
                position.x-=90;
                position.y+=50;
                SDL_BlitSurface(nom, NULL, ecran, &position);
                SDL_FreeSurface(nom);

                strcpy(texte_SDL[0],"Oui");
                strcpy(texte_SDL[1],"Non");
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

        if (type!=5)
        {
            afficherPage (ecran,police,texte_SDL,nb,choix,2,&haut,&nb,&page);
        }

        SDL_Flip(ecran);
        if (action==7)
        {
            action=8;
        }
        else if (action&&action!=7&&action!=9)
        {
            action=eventMenu();
        }
    }
    FMOD_Sound_Release(musique);
    FMOD_System_Close(system);
    FMOD_System_Release(system);
    return action;
}

void testMemoire()
{
    SDL_Surface* ecran = NULL;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetCaption("Iniuriam",NULL);
    ecran=SDL_SetVideoMode(TAILLE_FENETRE_L, TAILLE_FENETRE_H, 32, SDL_HWSURFACE);
    FMOD_SYSTEM *system;
    FMOD_SOUND *musique;
    FMOD_System_Create(&system);
    FMOD_System_Init(system, 2, FMOD_INIT_NORMAL, NULL);
    FMOD_System_CreateStream(system, "data/Media/GRAMATIK-Muy tranquilo.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
    FMOD_Sound_SetLoopCount(musique, -1);
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);

    getchar();

    SDL_FreeSurface(ecran);
    SDL_Quit();
    FMOD_Sound_Release(musique);
    FMOD_System_Close(system);
    FMOD_System_Release(system);
}

int mainMenu ()
{
    int i;
    char nom [50],c=0;
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
    nouveauPerso (&liste[2], "Toromis", 2, 1, 1, 1, 0, 100,tab);
    nouveauPerso (&liste[3], "Babar", 1, 1, 1, 1, 0, 100,tab);
    partieInit(&jeu,"The A company",liste, 4, NULL,0,0,0);
    for (i=0; i<4;i++)
    {
        persoLibere(&liste[i]);
    }
    police = TTF_OpenFont("data/Jester.ttf", 30);
    ecran=SDL_SetVideoMode(TAILLE_FENETRE_L, TAILLE_FENETRE_H, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("Iniuriam",NULL);

    c=afficherMenu(ecran,0,police,&jeu);/*Affichage de l'écran principal*/

    if (c)
    {
        printf("Retour au jeu\n");
    }
    else printf("Quitter le jeu\n");

    getPartieNom(&jeu,nom);

    printf("\n%s\n\n%d Joueur(s) :\n",nom,getPartieNbJoueur(&jeu));
    for (i=0;i<getPartieNbJoueur(&jeu);i++)
    {
        getPersoNom(nom,getPartieJoueurI(&jeu,i));
        printf("%s\n",nom);
    }
    printf("\n");
    for (i=0;i<getPartieNbMission(&jeu);i++) printf("%d\n",getPartieMissionAccomplie(&jeu,i));
    printf("%d\n",getPartieMissionActuelleType(&jeu));


    partieLibere (&jeu);
    libererTousLesObjets(&tab);
    SDL_FreeSurface(ecran);
    TTF_CloseFont(police);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
