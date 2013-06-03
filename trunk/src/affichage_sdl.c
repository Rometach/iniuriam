#include "affichage_sdl.h"


/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

void affCarte(const Terrain* ter, SDL_Surface* ecran)
{
    SDL_Rect position;
    SDL_Rect tile;
    unsigned int i;

    position.x = 0;
    position.y = 0;
    tile.w=TILE_LARGEUR;
    tile.h=TILE_HAUTEUR;

     for(i= 0; i<CARTE_HAUTEUR*CARTE_LARGEUR; i++)
     {
            tile.x=getPosX(ter->tabChipset[ter->carte[i]]);
            tile.y=getPosY(ter->tabChipset[ter->carte[i]]);
            SDL_BlitSurface(ter->chipset, &tile, ecran, &position);

            position.x+= TILE_LARGEUR;
            if(position.x>=CARTE_LARGEUR*TILE_LARGEUR)
            {
                position.y+= TILE_HAUTEUR;
                position.x=0;

            }
    }
    SDL_Flip(ecran);
}

void affPerso(const Personnage* heros, const Liste_Perso* pnjs, const int nbrPnj, SDL_Surface* ecran)
{
    SDL_Rect position;
    SDL_Surface* surface=NULL;
    int i;
    char info[255];
    TTF_Init();
    TTF_Font *police = NULL;
    SDL_Color color = { 0, 0, 0};

    police = TTF_OpenFont("data/Jester.ttf", 15);
    position.x = 4;
    position.y = 2;

    sprintf (info, "X: %d", heros->posX/TILE_LARGEUR );
    surface=TTF_RenderText_Solid(police, info, color);
    SDL_BlitSurface(surface, NULL, ecran, &position);
    position.y += TILE_HAUTEUR;
    sprintf (info, "Y: %d", heros->posY/TILE_HAUTEUR );
    surface=TTF_RenderText_Solid(police, info, color);
    SDL_BlitSurface(surface, NULL, ecran, &position);

    position.x = heros->posX;
    position.y = heros->posY;
    SDL_BlitSurface(heros->avatar, NULL, ecran, &position);

    for(i=0; i<nbrPnj; i++)
    {
        position.x = pnjs[i].perso->posX;
        position.y = pnjs[i].perso->posY;
        SDL_BlitSurface(pnjs[i].perso->avatar, NULL, ecran, &position);
    }

    SDL_Flip(ecran);
    SDL_FreeSurface(surface);
     TTF_CloseFont(police);
    TTF_Quit();
}

void affInventaire(Personnage* perso, SDL_Surface* ecran)
{
    SDL_Surface* cadreInventaire;
    SDL_Rect position;
    unsigned int i;
    char quantiteChar[255];

    TTF_Init();
    TTF_Font *police = NULL;
    police = TTF_OpenFont("data/Jester.ttf", 15);
    SDL_Surface* quantite=NULL;
    SDL_Color color = { 0, 225, 0};

    position.x = 0;
    position.y = 0;

    cadreInventaire = IMG_Load("data/Media/inventaire.jpg");
    SDL_BlitSurface(cadreInventaire, NULL, ecran,&position);

    position.x = TAILLE_FENETRE_L/6;
    position.y = TILE_HAUTEUR;
    quantite = TTF_RenderText_Solid(police,  "Inventaire", color);
    SDL_BlitSurface(quantite, NULL, ecran,&position);

    position.x= 2*TILE_LARGEUR;
    position.y= 3*TILE_HAUTEUR;

     for(i=0; i<perso->inventaire.capacite; i++)
     {
         if(i<perso->inventaire.nbObjet && position.y<TAILLE_FENETRE_H-3*TILE_HAUTEUR)
        {
        SDL_BlitSurface(perso->inventaire.st[i].objet->icon, NULL, ecran, &position);
        sprintf (quantiteChar, "%d", perso->inventaire.st[i].quantite );
        quantite = TTF_RenderText_Solid(police,  quantiteChar, color);
        SDL_BlitSurface(quantite, NULL, ecran, &position);

        position.x+= TILE_LARGEUR;
            if(position.x>=TAILLE_FENETRE_L/2-TILE_LARGEUR)
            {
                position.y+= TILE_HAUTEUR;
                position.x= 2*TILE_LARGEUR;
            }
        }
     }

    position.x = TAILLE_FENETRE_L*2/3;
    position.y = TILE_HAUTEUR;
    quantite = TTF_RenderText_Solid(police,  "Equipement", color);
    SDL_BlitSurface(quantite, NULL, ecran,&position);

    position.x= TAILLE_FENETRE_L*2/3+2*TILE_LARGEUR;
    position.y= 3*TILE_HAUTEUR;
    if(perso->equipement.tete!=NULL)
    {
         SDL_BlitSurface(perso->equipement.tete->icon, NULL, ecran, &position);
    }
    position.y+= TILE_HAUTEUR;
    if(perso->equipement.torse!=NULL)
    {
         SDL_BlitSurface(perso->equipement.torse->icon, NULL, ecran, &position);
    }
    position.y+= TILE_HAUTEUR;
    if(perso->equipement.bas!=NULL)
    {
         SDL_BlitSurface(perso->equipement.bas->icon, NULL, ecran, &position);
    }
     position.y+= TILE_HAUTEUR;
    if(perso->equipement.pieds!=NULL)
    {
         SDL_BlitSurface(perso->equipement.pieds->icon, NULL, ecran, &position);
    }
    position.x= TAILLE_FENETRE_L*2/3+3*TILE_LARGEUR;
    position.y= 3*TILE_HAUTEUR;
    for(i=0; i<3;i++)
    {
        if(perso->equipement.armeDroite[i]!=NULL)
        {
             SDL_BlitSurface(perso->equipement.armeDroite[i]->icon, NULL, ecran, &position);
             position.y+= TILE_HAUTEUR;
        }
        else {position.y+= TILE_HAUTEUR;}
    }


    position.x= TAILLE_FENETRE_L*2/3+TILE_LARGEUR;
    position.y= 3*TILE_HAUTEUR;

        if(perso->equipement.armeGauche!=NULL)
        {
             SDL_BlitSurface(perso->equipement.armeGauche->icon, NULL, ecran, &position);

        }
    position.y+= TILE_HAUTEUR;
        if(perso->equipement.mains!=NULL)
        {
             SDL_BlitSurface(perso->equipement.mains->icon, NULL, ecran, &position);

        }

    position.y= TAILLE_FENETRE_H-2*TILE_HAUTEUR;
    position.x= 2*TILE_LARGEUR;
    sprintf (quantiteChar, "Argent: %d ", perso->argent );
    quantite = TTF_RenderText_Solid(police,  quantiteChar, color);
    SDL_BlitSurface(quantite, NULL, ecran, &position);


    SDL_Flip(ecran);
    SDL_FreeSurface(cadreInventaire);
    SDL_FreeSurface(quantite);
    TTF_CloseFont(police);
    TTF_Quit();
}

void affProfil(Personnage* perso, SDL_Surface* ecran)
{
    SDL_Surface* cadreProfil;
    SDL_Rect position;
    char parametre[255];
    char info[255];

    TTF_Init();
    TTF_Font *police = NULL;
    police = TTF_OpenFont("data/Jester.ttf", 25);
    SDL_Surface* quantite=NULL;
    SDL_Color couleur = { 0, 255, 0};

    position.x = 0;
    position.y = 0;

    cadreProfil = IMG_Load("data/Media/fond.jpg");
    SDL_BlitSurface(cadreProfil, NULL, ecran,&position);

    position.x = TAILLE_FENETRE_L/3;
    position.y = TAILLE_FENETRE_H/10;
    quantite = TTF_RenderText_Solid(police, perso->nom, couleur);
    SDL_BlitSurface(quantite, NULL, ecran,&position);

    position.x=TAILLE_FENETRE_L/6;
    position.y=TAILLE_FENETRE_H/6;
    police = TTF_OpenFont("data/Jester.ttf", 15);
    getRaceNom(info, getPersoRace(perso));
    quantite = TTF_RenderText_Solid(police, info, couleur);
    SDL_BlitSurface(quantite, NULL, ecran,&position);

    position.y+= 25;
    strcpy(parametre, "Sexe: ");
    getSexeNom(info, getPersoSexe(perso));
    strcat(parametre, info);
    quantite = TTF_RenderText_Solid(police, parametre, couleur);
    SDL_BlitSurface(quantite, NULL, ecran,&position);

    position.y+= 25;
    strcpy(parametre, "Faction: ");
    getPersoFactionNom( info, perso);
    strcat(parametre, info);
    quantite = TTF_RenderText_Solid(police,  parametre, couleur);
    SDL_BlitSurface(quantite, NULL, ecran,&position);

    position.y+= 25;
    strcpy(parametre, "Carriere: ");
    getCarriereNom(getPersoCarriere(perso), info);
    strcat(parametre, info);
    quantite = TTF_RenderText_Solid(police, parametre, couleur);
    SDL_BlitSurface(quantite, NULL, ecran,&position);

    position.x=TAILLE_FENETRE_L/2;
    position.y=TAILLE_FENETRE_H/6;
    sprintf(info, "Experience: %d", perso->experience);
    quantite = TTF_RenderText_Solid(police,  info, couleur);
    SDL_BlitSurface(quantite, NULL, ecran,&position);

    position.y+=25;
    sprintf(info, "Niveau: %d", perso->niveau);
    quantite = TTF_RenderText_Solid(police,  info, couleur);
    SDL_BlitSurface(quantite, NULL, ecran,&position);

    position.y+=25;
    sprintf(info, "Points de vie: %d", perso->ptDeVie);
    quantite = TTF_RenderText_Solid(police,  info, couleur);
    SDL_BlitSurface(quantite, NULL, ecran,&position);

    position.x=TAILLE_FENETRE_L/6;
    position.y=TAILLE_FENETRE_H*3/7;
    sprintf(info, "Attaque: %d", perso->attaque);
    quantite = TTF_RenderText_Solid(police,  info, couleur);
    SDL_BlitSurface(quantite, NULL, ecran,&position);

    position.y += 25;
    sprintf(info, "Defense: %d", perso->defense);
    quantite = TTF_RenderText_Solid(police,  info, couleur);
    SDL_BlitSurface(quantite, NULL, ecran, &position);

    position.y += 25;
    sprintf(info, "Intelligence: %d", perso->intelligence);
    quantite = TTF_RenderText_Solid(police,  info, couleur);
    SDL_BlitSurface(quantite, NULL, ecran, &position);

    position.y += 25;
    sprintf(info, "Agilite: %d", perso->agilite);
    quantite = TTF_RenderText_Solid(police,  info, couleur);
    SDL_BlitSurface(quantite, NULL, ecran, &position);

    position.y += 25;
    sprintf(info, "Charisme: %d", perso->charisme);
    quantite = TTF_RenderText_Solid(police,  info, couleur);
    SDL_BlitSurface(quantite, NULL, ecran, &position);


    SDL_Flip(ecran);
    SDL_FreeSurface(cadreProfil);
    SDL_FreeSurface(quantite);
    TTF_CloseFont(police);
    TTF_Quit();
}

void affJournal(Personnage* perso, Mission* mission, SDL_Surface* ecran)
{
SDL_Surface* cadreProfil;
    SDL_Rect position;
    char info[255];

    TTF_Init();
    TTF_Font *police = NULL;
    police = TTF_OpenFont("data/Jester.ttf", 15);
    SDL_Surface* texte=NULL;
    SDL_Color couleur = { 0, 255, 0};

    position.x = 0;
    position.y = 0;

    cadreProfil =IMG_Load("data/Media/fond.jpg");
    SDL_BlitSurface(cadreProfil, NULL, ecran,&position);

    position.x = TAILLE_FENETRE_L/3;
    position.y = TAILLE_FENETRE_H/10;
    texte = TTF_RenderText_Solid(police,  "Journal de quetes", couleur);
    SDL_BlitSurface(texte, NULL, ecran,&position);

    position.x=TAILLE_FENETRE_L/6;
    position.y=TAILLE_FENETRE_H/6;

    texte = TTF_RenderText_Solid(police, mission->nom, couleur);
    SDL_BlitSurface(texte, NULL, ecran,&position);

    position.y+= 25;
    switch(mission->type)
    {
        case 1:
        texte = TTF_RenderText_Solid(police,  "Type: Parler à quelqu'un", couleur);
        SDL_BlitSurface(texte, NULL, ecran,&position);
        break;

        case 2:
        texte = TTF_RenderText_Solid(police,  "Type: Obtenir des infos", couleur);
        SDL_BlitSurface(texte, NULL, ecran,&position);
        break;

        case 3:
        texte = TTF_RenderText_Solid(police,  "Type: Tuer quelqu'un", couleur);
        SDL_BlitSurface(texte, NULL, ecran,&position);
        break;

        case 4:
        texte = TTF_RenderText_Solid(police,  "Type: Obtenir un objet", couleur);
        SDL_BlitSurface(texte, NULL, ecran,&position);
        break;

        case 5:
        texte = TTF_RenderText_Solid(police,  "Type: Se rendre à un certain endroit", couleur);
        SDL_BlitSurface(texte, NULL, ecran,&position);
        break;

        default:
        break;
    }
   if(&mission->posXCible!=NULL)
   {
        position.y+= 25;
        sprintf(info,"%d", mission->posXCible);
        texte = TTF_RenderText_Solid(police, info , couleur);
        SDL_BlitSurface(texte, NULL, ecran,&position);
   }
     if(&mission->posYCible!=NULL)
   {
       position.y+= 25;
        sprintf(info,"%d", mission->posYCible);
        texte = TTF_RenderText_Solid(police, info , couleur);
        SDL_BlitSurface(texte, NULL, ecran,&position);
   }
    if(mission->nomPerso!=NULL)
    {   position.y+= 25;
        sprintf(info, "Nom du personnage: %s",mission->nomPerso);
        texte = TTF_RenderText_Solid(police, info, couleur);
        SDL_BlitSurface(texte, NULL, ecran,&position);
    }
    if(mission->objCible!=NULL)
    {   position.y+= 25;
        sprintf(info, "Objet a trouver: %s", mission->objCible->nom);
        texte = TTF_RenderText_Solid(police, mission->objCible->nom , couleur);
        SDL_BlitSurface(texte, NULL, ecran,&position);
    }



    SDL_Flip(ecran);
    SDL_FreeSurface(cadreProfil);
    SDL_FreeSurface(texte);
    TTF_CloseFont(police);
    TTF_Quit();
}

void affMenuDialogue(char* info, int curseur, SDL_Surface* ecran)
{
    int i;
    SDL_Surface* dialogue=NULL;
    SDL_Surface* texte = NULL;
    SDL_Rect position;
    SDL_Color couleur = { 0, 255, 0};
    char menu[6][20];
    strcpy(menu[0], "Obtenir des infos");
    strcpy(menu[1], "Soudoyer");
    strcpy(menu[2], "Menacer");
    strcpy(menu[3], "Seduire");
    strcpy(menu[4], "Acheter");
    strcpy(menu[5],  "Vendre");

    TTF_Init();
    TTF_Font *police = NULL;
    police = TTF_OpenFont("data/Jester.ttf", 15);

    dialogue = SDL_CreateRGBSurface(SDL_HWSURFACE, (CARTE_LARGEUR-4)*TILE_LARGEUR, 4*TILE_HAUTEUR, 32, 0, 0, 0, 0);
    position.x = 2*TILE_LARGEUR;
    position.y = (CARTE_HAUTEUR-5)*TILE_HAUTEUR;

    SDL_FillRect(dialogue, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    SDL_BlitSurface(dialogue, NULL, ecran,&position);

    for(i=0;i<6;i++)
    {
        if(i==curseur)
            {
                position.x = 2*TILE_LARGEUR;
                position.y = (CARTE_HAUTEUR-5)*TILE_HAUTEUR+i*TILE_HAUTEUR/2;
                texte = TTF_RenderText_Solid(police, "*", couleur);
                SDL_BlitSurface(texte, NULL, ecran, &position);
            }
        position.x = 3*TILE_LARGEUR;
        position.y = (CARTE_HAUTEUR-5)*TILE_HAUTEUR+i*TILE_HAUTEUR/2;
        texte = TTF_RenderText_Solid(police, menu[i], couleur);
        SDL_BlitSurface(texte, NULL, ecran, &position);
    }

    SDL_Flip(ecran);

    SDL_FreeSurface(dialogue);
    SDL_FreeSurface(texte);
    TTF_CloseFont(police);
    TTF_Quit();
}

void affDialogue( Personnage* perso, char* info, SDL_Surface* ecran)
{
    SDL_Surface* cadreNom;
    SDL_Surface* cadreDialogue;
    SDL_Surface* texte = NULL;
    SDL_Rect position;
    char* tampon;
    char * phrase;
    TTF_Init();
    TTF_Font *police = NULL;
    int i=1, j;
    police = TTF_OpenFont("data/Jester.ttf", 15);

    SDL_Color couleur = { 0, 225, 0};
    tampon=malloc(400*sizeof(char));
    phrase = malloc(400*sizeof(char));
    cadreDialogue = SDL_CreateRGBSurface(SDL_HWSURFACE, (CARTE_LARGEUR-4)*TILE_LARGEUR, 4*TILE_HAUTEUR, 32, 0, 0, 0, 0);
    cadreNom = SDL_CreateRGBSurface(SDL_HWSURFACE, (CARTE_LARGEUR-4)*TILE_LARGEUR, TILE_HAUTEUR, 32, 0, 0, 0, 0);

    position.x = 2*TILE_LARGEUR;
    position.y = (CARTE_HAUTEUR-6)*TILE_HAUTEUR;
    SDL_FillRect(cadreNom, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    SDL_BlitSurface(cadreNom, NULL, ecran,&position);

    strcpy(tampon, perso->nom);
    texte = TTF_RenderText_Solid(police, tampon, couleur);
    SDL_BlitSurface(texte, NULL, ecran,&position);
    position.x = 2*TILE_LARGEUR;
    position.y = (CARTE_HAUTEUR-5)*TILE_HAUTEUR;

    SDL_FillRect(cadreDialogue, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    SDL_BlitSurface(cadreDialogue, NULL, ecran,&position);

    strcpy(tampon, &info[0]);
    texte = TTF_RenderText_Solid(police, tampon, couleur);
    j= strlen(tampon);
    while (j>=1&&tampon[j]!=' ') j--;
    if (j!=0)
    {
        strncpy(phrase,tampon,j);
        phrase[j]='\0';
    }
    else
    {
        j=strlen(tampon);
        strncpy(phrase, tampon, strlen(tampon));
        phrase[strlen(tampon)-1]='-';
        phrase[strlen(tampon)]='\0';
    }
/*             phrase=(tampon - strrchr(tampon, (int)" "));
            printf("%s \n", phrase);*/
     texte = TTF_RenderText_Solid(police, tampon, couleur);
    SDL_BlitSurface(texte, NULL, ecran, &position);
    SDL_Flip(ecran);

    SDL_FreeSurface(cadreNom);
    SDL_FreeSurface(cadreDialogue);
    SDL_FreeSurface(texte);
    TTF_CloseFont(police);
    TTF_Quit();
}

void affSoudoyer( Personnage* perso, int curseur, SDL_Surface* ecran)
{
    int i;
    SDL_Surface* dialogue=NULL;
    SDL_Surface* texte = NULL;
    SDL_Rect position;
    SDL_Color couleur = { 0, 255, 0};
    char menu[3][20]={"10", "50", "100"};
     TTF_Init();
    TTF_Font *police = NULL;
    police = TTF_OpenFont("data/Jester.ttf", 15);

    affDialogue(perso, "Combien souhaitez-vous donnez?", ecran);

    position.x = 3*TILE_LARGEUR;
    position.y = (CARTE_HAUTEUR-5)*TILE_HAUTEUR;


    for(i=0;i<3;i++)
    {
        if(i==curseur)
            {
                position.x = 2*TILE_LARGEUR;
                position.y = (CARTE_HAUTEUR-4)*TILE_HAUTEUR+i*TILE_HAUTEUR/2;
                texte = TTF_RenderText_Solid(police, "*", couleur);
                SDL_BlitSurface(texte, NULL, ecran, &position);
            }
        position.x = 3*TILE_LARGEUR;
        position.y = (CARTE_HAUTEUR-4)*TILE_HAUTEUR+i*TILE_HAUTEUR/2;
        texte = TTF_RenderText_Solid(police, menu[i], couleur);
        SDL_BlitSurface(texte, NULL, ecran, &position);
    }

    SDL_Flip(ecran);

    SDL_FreeSurface(dialogue);
    SDL_FreeSurface(texte);
    TTF_CloseFont(police);
    TTF_Quit();
}

void affInvPnj(Personnage* pnj, SDL_Surface* ecran)
{
    SDL_Surface* inventaire;
    SDL_Surface* info;
    SDL_Rect position;
    unsigned int i;
    char infoChar[255];

    TTF_Init();
    TTF_Font *police = NULL;


    SDL_Color couleur = { 0, 255, 0};

    police = TTF_OpenFont("data/Jester.ttf", 15);
    position.x = 0;
    position.y = 0;

    inventaire = IMG_Load("data/Media/fond.jpg");
    SDL_BlitSurface(inventaire, NULL, ecran,&position);

    position.x = 3*TILE_LARGEUR;
    position.y = TILE_HAUTEUR;
    info = TTF_RenderText_Solid(police,  "Vous trouvez des objets sur le corps", couleur);
    SDL_BlitSurface(info, NULL, ecran,&position);

    position.x= 2*TILE_LARGEUR;
    position.y= 3*TILE_HAUTEUR;

     for(i=0; i<pnj->inventaire.capacite && position.y<((TILE_HAUTEUR-4)*CARTE_HAUTEUR); i++)
     {
         if(i<pnj->inventaire.nbObjet)
        {
            SDL_BlitSurface(pnj->inventaire.st[i].objet->icon, NULL, ecran, &position);
            sprintf (infoChar, "%d", pnj->inventaire.st[i].quantite );
            info = TTF_RenderText_Solid(police, infoChar, couleur);
            SDL_BlitSurface(info, NULL, ecran, &position);

            position.x+= TILE_LARGEUR;
            if(position.x>=(CARTE_LARGEUR-5)*TILE_LARGEUR)
            {
                position.y+= TILE_HAUTEUR;
                position.x= 2*TILE_LARGEUR;
            }
        }
     }

    position.x = (CARTE_LARGEUR-5)*TILE_LARGEUR;
    position.y = 3*TILE_HAUTEUR;
    sprintf (infoChar, "%d", pnj->argent);
    info = TTF_RenderText_Solid(police,  infoChar, couleur);
    SDL_BlitSurface(info, NULL, ecran, &position);

    SDL_Flip(ecran);

    SDL_FreeSurface(inventaire);
    TTF_CloseFont(police);
    TTF_Quit();

}

void affAcheter(Dialogue* dialogue, Objet* objet, SDL_Surface* ecran)
{
    SDL_Surface* inventaire;
    SDL_Rect position;
    unsigned int i;
    char infoChar[255];

    TTF_Init();
    TTF_Font *police = NULL;

    SDL_Surface* info=NULL;
    SDL_Color couleur = { 0, 255, 0};

    police = TTF_OpenFont("data/Jester.ttf", 15);
    position.x = 0;
    position.y = 0;

    inventaire = IMG_Load("data/Media/fond.jpg");
    SDL_BlitSurface(inventaire, NULL, ecran,&position);

    position.x = 3*TILE_LARGEUR;
    position.y = TILE_HAUTEUR;
    info = TTF_RenderText_Solid(police,  "Acheter", couleur);
    SDL_BlitSurface(info, NULL, ecran,&position);

    position.x= 2*TILE_LARGEUR;
    position.y= 3*TILE_HAUTEUR;

     for(i=0; i<dialogue->perso2->inventaire.capacite && position.y<((TILE_HAUTEUR-4)*CARTE_HAUTEUR); i++)
     {
         if(i<dialogue->perso2->inventaire.nbObjet)
        {
            SDL_BlitSurface(dialogue->perso2->inventaire.st[i].objet->icon, NULL, ecran, &position);
            sprintf (infoChar, "%d", dialogue->perso2->inventaire.st[i].quantite );
            info = TTF_RenderText_Solid(police, infoChar, couleur);
            SDL_BlitSurface(info, NULL, ecran, &position);

            position.x+= TILE_LARGEUR;
            if(position.x>=(CARTE_LARGEUR-5)*TILE_LARGEUR)
            {
                position.y+= TILE_HAUTEUR;
                position.x= 2*TILE_LARGEUR;
            }
        }
     }

    position.x = (CARTE_LARGEUR-5)*TILE_LARGEUR;
    position.y = 3*TILE_HAUTEUR;
    sprintf (infoChar, "%d", dialogue->perso1->argent);
    info = TTF_RenderText_Solid(police,  infoChar, couleur);
    SDL_BlitSurface(info, NULL, ecran, &position);

    SDL_Flip(ecran);
    SDL_FreeSurface(inventaire);
    SDL_FreeSurface(info);
    TTF_CloseFont(police);
    TTF_Quit();

}

void affVendre(Dialogue* dialogue, Objet* objet, SDL_Surface* ecran)
{
    SDL_Surface* inventaire;
    SDL_Rect position;
    unsigned int i;
    char infoChar[255];

    TTF_Init();
    TTF_Font *police = NULL;

    SDL_Surface* info=NULL;
    SDL_Color couleur = { 0, 255, 0};

    police = TTF_OpenFont("data/Jester.ttf", 15);
    position.x = 0;
    position.y = 0;

    inventaire = IMG_Load("data/Media/fond.jpg");
    SDL_BlitSurface(inventaire, NULL, ecran,&position);

    position.x = 3*TILE_LARGEUR;
    position.y = TILE_HAUTEUR;
    info = TTF_RenderText_Solid(police,  "Vendre", couleur);
    SDL_BlitSurface(info, NULL, ecran,&position);

    position.x= 2*TILE_LARGEUR;
    position.y= 3*TILE_HAUTEUR;

     for(i=0; i<dialogue->perso1->inventaire.capacite && position.y<((TILE_HAUTEUR-4)*CARTE_HAUTEUR); i++)
     {
         if(i<dialogue->perso1->inventaire.nbObjet)
        {
        SDL_BlitSurface(dialogue->perso1->inventaire.st[i].objet->icon, NULL, ecran, &position);
        sprintf (infoChar, "%d", dialogue->perso1->inventaire.st[i].quantite );
        info = TTF_RenderText_Solid(police,  infoChar, couleur);
        SDL_BlitSurface(info, NULL, ecran, &position);

        position.x+= TILE_LARGEUR;
            if(position.x>=(CARTE_LARGEUR-5)*TILE_LARGEUR)
            {
                position.y+= TILE_HAUTEUR;
                position.x= 2*TILE_LARGEUR;
            }
        }
     }

    position.x = (CARTE_LARGEUR-5)*TILE_LARGEUR;
    position.y = 3*TILE_HAUTEUR;
    sprintf (infoChar, "%d", dialogue->perso1->argent);
    info = TTF_RenderText_Solid(police,  infoChar, couleur);
    SDL_BlitSurface(info, NULL, ecran, &position);

    SDL_Flip(ecran);
    SDL_FreeSurface(inventaire);
    SDL_FreeSurface(info);
    TTF_CloseFont(police);
    TTF_Quit();
}

void affInfOb(SDL_Rect* position, Objet* objet, SDL_Surface* ecran)
{
    SDL_Surface* cadre;
    char infoChar[255];

    TTF_Init();
    TTF_Font *police = NULL;

    SDL_Surface* info=NULL;
    SDL_Color couleur = { 0, 255, 0};

    police = TTF_OpenFont("data/Jester.ttf", 15);
    cadre = IMG_Load("data/Media/objetInfo.jpg");
    SDL_BlitSurface(cadre, NULL, ecran, position);


    position->x+= 12;
    position->y+= 12;
    sprintf(infoChar,"%s", objet->nom);
    info=TTF_RenderText_Solid(police,  infoChar, couleur);
    SDL_BlitSurface(info, NULL, ecran, position);
    position->y+=12;

    switch(objet->utilite)
    {
       case 1: info=TTF_RenderText_Solid(police,  "arme", couleur);
                SDL_BlitSurface(info, NULL, ecran, position);
                 position->y+=12;
                sprintf(infoChar,"%d", objet->portee);
                info=TTF_RenderText_Solid(police,infoChar, couleur);
                SDL_BlitSurface(info, NULL, ecran, position);
                position->y+=12;
                sprintf(infoChar,"%d", objet->degats);
                info=TTF_RenderText_Solid(police,infoChar, couleur);
        break;

        case 2: info=TTF_RenderText_Solid(police,  "armure", couleur);
                SDL_BlitSurface(info, NULL, ecran, position);
                position->y+=12;
                sprintf(infoChar,"%d", objet->protection);
                info=TTF_RenderText_Solid(police,infoChar, couleur);
        break;

        case 3: info=TTF_RenderText_Solid(police,  "potion/nourriture", couleur);
                SDL_BlitSurface(info, NULL, ecran, position);
                position->y+=12;
                sprintf(infoChar,"%d", objet->portee);
                info=TTF_RenderText_Solid(police,infoChar, couleur);
                SDL_BlitSurface(info, NULL, ecran, position);
                position->y+=12;
                switch(objet->degats)
                {
                    case 1: info=TTF_RenderText_Solid(police,  "soin", couleur);
                SDL_BlitSurface(info, NULL, ecran, position);
                position->y+=12;
                    break;

                    case 2: info=TTF_RenderText_Solid(police,  "poison", couleur);
                    SDL_BlitSurface(info, NULL, ecran, position);
                    position->y+=12;
                    break;

                    default:
                    break;
                }
                sprintf(infoChar,"%d", objet->protection);
                info=TTF_RenderText_Solid(police,infoChar, couleur);
        break;

        case 4: info=TTF_RenderText_Solid(police,  "objet quete", couleur);
        break;

        default: info=TTF_RenderText_Solid(police,  "autre", couleur);
        break;
    }
    SDL_BlitSurface(info, NULL, ecran, position);
    position->y+=12;

    sprintf(infoChar,"%d", objet->valeur);
    info=TTF_RenderText_Solid(police,infoChar, couleur);
    SDL_BlitSurface(info, NULL, ecran, position);

    SDL_Flip(ecran);
    SDL_FreeSurface(cadre);
    SDL_FreeSurface(info);
    TTF_CloseFont(police);
    TTF_Quit();
}

void affCombat(Terrain* ter, Combattant* groupe, int l, char arene[TAILLE_MAX_H][TAILLE_MAX_L], SDL_Surface* ecran)
{
    SDL_Rect position;
    SDL_Rect tile;
    unsigned int i, j;
    char texte[255];
    SDL_Surface* texteCadre =NULL;
    TTF_Init();
    TTF_Font *police = NULL;
    police = TTF_OpenFont("data/Jester.ttf", 15);
    SDL_Color color = { 0 ,0,0};

    position.x = 0;
    position.y = 0;
    tile.w=TILE_LARGEUR;
    tile.h=TILE_HAUTEUR;

     for(i= 0; i<TAILLE_MAX_H; i++)
     {
         for(j=0; j<TAILLE_MAX_L; j++)
         {
            tile.x = getPosX(ter->tabChipset[ter->carte[i*CARTE_LARGEUR+j]]);
            tile.y = getPosY(ter->tabChipset[ter->carte[i*CARTE_LARGEUR+j]]);
            SDL_BlitSurface(ter->chipset, &tile, ecran, &position);

            position.x+= TILE_LARGEUR;
        }
        position.y+= TILE_HAUTEUR;
        position.x=0;
    }

    for (i=0; i<l; i++)
    {
    position.x = groupe[i].posX*TILE_LARGEUR;
    position.y = groupe[i].posY*TILE_HAUTEUR;
    SDL_BlitSurface(groupe[i].perso->avatar, NULL, ecran, &position);
    }

    position.x = TILE_LARGEUR;
    position.y = TILE_HAUTEUR;
    for(i=0; i<l; i++)
    {
        sprintf(texte, "Vie: %d", groupe[i].perso->ptDeVie );
        texteCadre = TTF_RenderText_Solid(police, texte, color);
        SDL_BlitSurface(texteCadre, NULL, ecran, &position);
        position.y+=25;
    }


    SDL_Flip(ecran);
}

void affArmesEqui(Combattant* combattant, int choix, SDL_Surface* ecran)
{
    int i;
    SDL_Surface* cadreArmes;
    SDL_Surface* texte = NULL;
    SDL_Rect position;
    TTF_Init();
    TTF_Font *police = NULL;
    police = TTF_OpenFont("data/Jester.ttf", 15);
    SDL_Color colorNoir = { 0 ,255,0};

    cadreArmes = SDL_CreateRGBSurface(SDL_HWSURFACE, (CARTE_LARGEUR-4)*TILE_LARGEUR, 4*TILE_HAUTEUR, 32, 0, 0, 0, 0);
    position.x = 2*TILE_LARGEUR;
    position.y = TAILLE_FENETRE_H-5*TILE_HAUTEUR;
    SDL_FillRect(cadreArmes, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    SDL_BlitSurface(cadreArmes, NULL, ecran,&position);

    for(i=0;i<=2;i++)
    {
        if(i==choix)
            {
                position.x = 2*TILE_LARGEUR+i*TILE_LARGEUR*3;
                position.y = TAILLE_FENETRE_H-5*TILE_HAUTEUR;
                texte = TTF_RenderText_Solid(police, "*", colorNoir);
                SDL_BlitSurface(texte, NULL, ecran, &position);
            }
        position.x = 3*TILE_LARGEUR+i*TILE_LARGEUR*3;
        position.y = TAILLE_FENETRE_H-5*TILE_HAUTEUR;
        SDL_BlitSurface(combattant->perso->equipement.armeDroite[i]->icon, NULL, ecran, &position);
    }

    SDL_Flip(ecran);
    SDL_FreeSurface(cadreArmes);
     TTF_CloseFont(police);
    TTF_Quit();
}

void affAttaque(int choix, SDL_Surface* ecran)
{
     int i;
    SDL_Surface* cadreAttaque;
    SDL_Surface* texte = NULL;
    SDL_Rect position;
    TTF_Init();
    TTF_Font *police = NULL;
    char attaques[5][20] = {"Attaque brutale", "Attaque prudente", "Attaque visee", "Feinte", "Parade"};
    police = TTF_OpenFont("data/Jester.ttf", 15);
    SDL_Color color = { 0 ,255,0};

    cadreAttaque = SDL_CreateRGBSurface(SDL_HWSURFACE, (CARTE_LARGEUR-4)*TILE_LARGEUR, 4*TILE_HAUTEUR, 32, 0, 0, 0, 0);
    position.x = 2*TILE_LARGEUR;
    position.y = TAILLE_FENETRE_H-5*TILE_HAUTEUR;
    SDL_FillRect(cadreAttaque, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    SDL_BlitSurface(cadreAttaque, NULL, ecran,&position);

    for(i=0;i<=4;i++)
    {
        if(i==choix)
            {
                position.x = 2*TILE_LARGEUR+i*TILE_LARGEUR*3;
                position.y = TAILLE_FENETRE_H-5*TILE_HAUTEUR;
                texte = TTF_RenderText_Solid(police, "*", color);
                SDL_BlitSurface(texte, NULL, ecran, &position);
            }
        position.x = 3*TILE_LARGEUR+i*TILE_LARGEUR*3;
        position.y = TAILLE_FENETRE_H-5*TILE_HAUTEUR;
        texte = TTF_RenderText_Solid(police, attaques[i], color);
        SDL_BlitSurface(texte, NULL, ecran, &position);
    }

    SDL_Flip(ecran);
    SDL_FreeSurface(cadreAttaque);
     TTF_CloseFont(police);
    TTF_Quit();
}

void eventJeuSDL(Personnage* hero, int nbrHero, Liste_Perso* pnjs, int nbrPnj, Mission* mission, Objet* tabObjets, Terrain* ter, SDL_Surface* ecran)
{
    int continuer = 1, i;
    SDL_Event event;
    Dialogue dialogue;
    char* reponse;
    reponse=malloc(400*sizeof(char));
    affCarte(ter, ecran);
    affPerso(hero, pnjs, nbrPnj, ecran);

    while (continuer)
    {


        int continuerMission = 1;
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            if(testMissionAllerA(mission, getPersoPosX(hero)/TILE_LARGEUR, getPersoPosY(hero)/TILE_HAUTEUR)==1)
            {
                missionAccomplir ( mission, tabObjets);
            }
            case SDL_KEYDOWN:
            { if(event.key.state==SDL_PRESSED)
                {
                    if(event.key.keysym.sym==SDLK_RIGHT)    /** Deplacement vers la droite*/
                    {   if(getCollision(ter->tabChipset[ter->carte[(getPersoPosX(&hero[0])+TILE_LARGEUR)/TILE_LARGEUR+CARTE_LARGEUR*(getPersoPosY(&hero[0])/TILE_HAUTEUR)]])==1)
                        {
                           if(testCollisionPerso(hero, pnjs, nbrPnj, 1)==-1)
                           {setPersoPosX(&hero[0], getPersoPosX(&hero[0])+TILE_LARGEUR);}
                        }
                    }
                    else if(event.key.keysym.sym==SDLK_LEFT)    /** Deplacement vers la gauche*/
                    {   if(getCollision(ter->tabChipset[ter->carte[(getPersoPosX(&hero[0])-TILE_LARGEUR)/TILE_LARGEUR+CARTE_LARGEUR*(getPersoPosY(&hero[0])/TILE_HAUTEUR)]])==1)
                        {
                            if(testCollisionPerso(hero, pnjs, nbrPnj, 2)==-1)
                            {setPersoPosX(&hero[0], getPersoPosX(&hero[0])-TILE_LARGEUR);}
                        }
                    }
                    else if(event.key.keysym.sym==SDLK_DOWN)    /** Deplacement vers le bas*/
                    {   if(getCollision(ter->tabChipset[ter->carte[getPersoPosX(&hero[0])/TILE_LARGEUR+CARTE_LARGEUR*((getPersoPosY(&hero[0])+TILE_HAUTEUR)/TILE_HAUTEUR)]])==1)
                        {
                            if(testCollisionPerso(hero, pnjs, nbrPnj, 3)==-1)
                            {setPersoPosY(&hero[0],getPersoPosY(&hero[0])+TILE_HAUTEUR);}
                        }
                    }
                    else if(event.key.keysym.sym==SDLK_UP)  /** Déplacement vers le haut */
                    {   if(getCollision(ter->tabChipset[ter->carte[getPersoPosX(&hero[0])/TILE_LARGEUR+CARTE_LARGEUR*((getPersoPosY(&hero[0])-TILE_HAUTEUR)/TILE_HAUTEUR)]])==1)
                        {
                            if(testCollisionPerso(hero, pnjs, nbrPnj, 4)==-1)
                            {setPersoPosY(&hero[0],getPersoPosY(&hero[0])-TILE_HAUTEUR);}
                        }
                    }
                      else if(event.key.keysym.sym==SDLK_RETURN) /** Touche d'action*/
                    {
                        for(i=0; i<nbrPnj; i++)
                        {
                        if(((getPersoPosX(&hero[0])+TILE_LARGEUR)==getPersoPosX(pnjs[i].perso) && getPersoPosY(&hero[0])==getPersoPosY(pnjs[i].perso))
                        || ((getPersoPosX(&hero[0])-TILE_LARGEUR)==getPersoPosX(pnjs[i].perso) && getPersoPosY(&hero[0])==getPersoPosY(pnjs[i].perso))
                        || ((getPersoPosY(&hero[0])+TILE_HAUTEUR)==getPersoPosY(pnjs[i].perso) && getPersoPosX(&hero[0])==getPersoPosX(pnjs[i].perso))
                        || ((getPersoPosY(&hero[0])-TILE_HAUTEUR)==getPersoPosY(pnjs[i].perso) && getPersoPosX(&hero[0])==getPersoPosX(pnjs[i].perso)))
                        {
                            if(getPersoFaction(pnjs[i].perso)==getPersoFaction(&hero[0]))
                            {
                            dialogueInit(&dialogue, &hero[0], pnjs[i].perso);
                            if(testMissionParlerA(mission, pnjs[i].perso))
                            {   parlerQuete(&dialogue, reponse);
                                affDialogue(dialogue.perso2, reponse, ecran);
                                missionAccomplir (mission,tabObjets);
                                while (continuerMission)
                                {
                                    SDL_WaitEvent(&event);
                                    switch(event.type)
                                    {case SDL_KEYDOWN:
                                        { if(event.key.state==SDL_PRESSED)
                                            {if(event.key.keysym.sym==SDLK_RETURN)
                                                {continuerMission=0;
                                                }}}}}
                            }
                            eventDialogueSDL(&dialogue, pnjs[i].perso, reponse, mission, tabObjets, ter, ecran);
                            }
                        else if(pnjs[i].perso->faction != hero[0].faction && getPersoPtDeVie(pnjs[i].perso)>0)
                        {

                            continuer=eventCombatSDL(hero, nbrHero, &pnjs[i], ter, ecran);
                            if(testMissionTuer(mission, pnjs[i].perso)==1)
                            {
                                missionAccomplir( mission, tabObjets);
                            }
                        }
                        }
                        else if(getPersoPosX(&hero[0])==getPersoPosX(pnjs[i].perso) && getPersoPosY(&hero[0])==getPersoPosY(pnjs[i].perso) && getPersoPtDeVie(pnjs[i].perso)<=0)
                        {
                            eventRecupInvSDL(hero, pnjs[i].perso, mission, tabObjets, ecran);
                        }
                    }
                    }
                    else if(event.key.keysym.sym==SDLK_i) /** Touche d'inventaire*/
                    {
                            eventInventaireSDL(hero, ecran);
                    }
                     else if(event.key.keysym.sym==SDLK_p) /** Touche de profil*/
                    {
                            eventProfilSDL(hero, ecran);
                    }
                    else if(event.key.keysym.sym==SDLK_j) /** Touche du journal de quete*/
                    {
                            eventJournalSDL(hero, mission, ecran);
                    }
                    affCarte(ter, ecran);
                    affPerso(hero, pnjs, nbrPnj, ecran);
                }
            }
            break;

            case SDL_QUIT:
                continuer = 0;
            break;
            }
        }
        free(reponse);
}

void eventJournalSDL(Personnage* hero, Mission* mission, SDL_Surface* ecran)
{
    int continuer = 1;
    SDL_Event event;

    affJournal(hero, mission, ecran);

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_KEYDOWN:
            { if(event.key.state==SDL_PRESSED)
                {
                       if(event.key.keysym.sym==SDLK_j)
                    {
                            continuer = 0;
                    }
                }
            }
            break;

            case SDL_QUIT:
                continuer = 0;
            break;
        }
    }
}

void eventProfilSDL(Personnage* hero, SDL_Surface* ecran)
{
    int continuer = 1;
    SDL_Event event;

    affProfil(hero, ecran);

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_KEYDOWN:
            { if(event.key.state==SDL_PRESSED)
                {
                       if(event.key.keysym.sym==SDLK_p)
                    {
                            continuer = 0;
                    }
                }
            }
            break;

            case SDL_QUIT:
                continuer = 0;
            break;
        }
    }
}

void eventInventaireSDL(Personnage* hero, SDL_Surface* ecran)
{
    int continuer = 1;
    SDL_Event event;
    Objet* objet;
    SDL_Rect position;

    affInventaire(hero, ecran);


    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
              case SDL_MOUSEMOTION:
            {
                 if(event.button.x>2*TILE_LARGEUR && event.button.x<(CARTE_LARGEUR-5)*TILE_LARGEUR && event.button.y>3*TILE_HAUTEUR && event.button.y<(CARTE_HAUTEUR-1)*TILE_HAUTEUR
                       && (event.button.y/TILE_HAUTEUR-3+event.button.x/TILE_LARGEUR-2)<hero->inventaire.nbObjet)
                   {
                    position.x = event.motion.x+10;
                    position.y = event.motion.y;
                    objet=hero->inventaire.st[event.button.y/TILE_HAUTEUR-3+event.button.x/TILE_LARGEUR-2].objet;
                    affInventaire(hero, ecran);
                    affInfOb(&position, objet, ecran);
                    }
            }
            break;

            case SDL_MOUSEBUTTONDOWN:
            {
             if(event.button.button==SDL_BUTTON_RIGHT)
               {
                    if(event.button.x>2*TILE_LARGEUR && event.button.x<(TAILLE_FENETRE_L-5*TILE_LARGEUR) && event.button.y>3*TILE_HAUTEUR && event.button.y<(TAILLE_FENETRE_H-TILE_HAUTEUR)
                       && (event.button.y/TILE_HAUTEUR-3+event.button.x/TILE_LARGEUR-2)<hero->inventaire.nbObjet)
                    {
                        objet=hero->inventaire.st[event.button.y/TILE_HAUTEUR-3+event.button.x/TILE_LARGEUR-2].objet;
                        if(getObjetType(objet)==3 || getObjetType(objet)==4 || getObjetType(objet)==5) /** utiliser objet */
                        { persoUtiliseObjet (hero, objet, hero); }
                        else if(getObjetType(objet)==2) /** equiper armure */
                        {   equiper(hero, objet, 0);}
                        else if(getObjetType(objet)==1) /** equiper arme */
                        {   setMainDroite(getPersoEquipement(hero), getEquiMainDroite(getPersoEquipement(hero), 1), 2 );
                            setMainDroite(getPersoEquipement(hero), getEquiMainDroite(getPersoEquipement(hero), 0), 1 );
                            equiper(hero, objet, 0);
                        }
                        affInventaire(hero, ecran);
                    }
                }
            }
            break;

            case SDL_KEYDOWN:
            { if(event.key.state==SDL_PRESSED)
                {
                       if(event.key.keysym.sym==SDLK_i)
                    {
                            continuer = 0;
                    }
                }
            }
            break;

            case SDL_QUIT:
                continuer = 0;
            break;
        }
    }
}

int eventCombatSDL(Personnage* hero, const int nbrHero, Liste_Perso* ennemi, Terrain* ter, SDL_Surface* ecran)
{
    Personnage* liste;
    char arene [TAILLE_MAX_H][TAILLE_MAX_L];
    int continuer =1, campJoueur, gagnant, i, nb=nbrHero+getNbrPerso(ennemi);
    Combattant* groupe;
    SDL_Event event;

    liste=(Personnage*)malloc(nb*sizeof(Personnage));

    for(i=0; i<nbrHero;i++)
    {
        liste[i]=hero[i];
    }
    for(i=nbrHero; i<nb; i++)
    {
        liste[i]=ennemi->perso[i-nbrHero];
    }

    areneInit(ter, arene);

    groupe=(Combattant*)malloc(nb*sizeof(Combattant));

    initCombat(liste, nb,groupe,arene);
    affCombat(ter, groupe,  nb, arene, ecran);
    campJoueur=groupe[0].camp;

    while (estLaFin(groupe, nb, campJoueur)==0)
    {
        for (i=0;i<nb;i++)
        {
            if(groupe[i].camp==campJoueur)
            {
                eventTourJoueurSDL( groupe, i, nbrHero+getNbrPerso(ennemi), arene, ter, ecran );
                nb=testNbCombattant(groupe, nb,arene);
            }
            else
            {
                tourIA(groupe,i,nb,arene);
                afficherTab2D(arene);
                nb=testNbCombattant(groupe,nb,arene);
            }
            affCombat(ter, groupe,nbrHero+getNbrPerso(ennemi), arene, ecran);
        }
    }

    for(i=0; i<nbrHero; i++)
    {
        liste[i].experience=30*getNbrPerso(ennemi);
        liste[i].niveau=calculNiveau(liste[i].experience);
    }
    for(i=0;i<nbrHero+getNbrPerso(ennemi);i++)
    {
        if(getPersoPtDeVie(groupe[i].perso)>0)
        {
            gagnant = groupe[i].camp;
        }
    }
    if(gagnant == campJoueur)
    {
        affDialogue( hero, "Bravo! Vous avez gagné!", ecran);
         while (continuer)
        {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_KEYDOWN:
            { if(event.key.state==SDL_PRESSED)
                {
                 if(event.key.keysym.sym==SDLK_RETURN)
                    {
                       continuer =0;
                       for(i=0; i<nbrHero;i++)
                       {
                           hero[i]=liste[i];
                       }
                       for(i=0; i<getNbrPerso(ennemi); i++)
                       {
                           ennemi->perso[i]=liste[i+nbrHero];
                       }
                       free (groupe);
                       return 1;
                    }
                }
            }
        }
        }
    }
    else
    {
        affDialogue(hero, "Game Over!", ecran);
         while (continuer)
        {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_KEYDOWN:
            { if(event.key.state==SDL_PRESSED)
                {
                 if(event.key.keysym.sym==SDLK_RETURN)
                    {
                       continuer =0;
                       free (groupe);
                       return 0;
                    }
                }
            }
        }
        }
    }
    free (groupe);
    return 1;
}

void eventTourJoueurSDL(Combattant* groupe, int i, int nbCombattant, char arene [TAILLE_MAX_H][TAILLE_MAX_L], Terrain* ter, SDL_Surface* ecran)
{
    int continuer =1;
    int j;
    SDL_Event event;
    int nbDeplacement = 5;
    int choixArme=0;
    Objet* armeChoisie=NULL;
    armeChoisie =getEquiMainDroite(&groupe[i].perso->equipement, choixArme);

     while (continuer)
                {
                    SDL_WaitEvent(&event);
                    switch(event.type)
                    {
                        case SDL_KEYDOWN:
                    { if(event.key.state==SDL_PRESSED)
                        {
                            if(event.key.keysym.sym==SDLK_RIGHT)    /** Deplacement vers la droite*/
                            {
                                nbDeplacement = deplaceCombDroite(&groupe[i], nbDeplacement, arene);
                            }
                            else if(event.key.keysym.sym==SDLK_LEFT)    /** Deplacement vers la gauche*/
                            {
                                nbDeplacement = deplaceCombGauche(&groupe[i], nbDeplacement, arene);
                            }
                            else if(event.key.keysym.sym==SDLK_DOWN)    /** Deplacement vers le bas*/
                            {
                                nbDeplacement = deplaceCombBas(&groupe[i], nbDeplacement, arene);
                            }
                            else if(event.key.keysym.sym==SDLK_UP)  /** Déplacement vers le haut */
                            {
                                nbDeplacement = deplaceCombHaut(&groupe[i], nbDeplacement, arene);
                            }
                            else if(event.key.keysym.sym==SDLK_a)
                            {
                                choixArme=eventArmesEquiSDL(&groupe[i], (int) choixArme, ecran);
                                armeChoisie = getEquiMainDroite(&groupe[i].perso->equipement, choixArme);
                            }
                            else if(event.key.keysym.sym==SDLK_RETURN)   /** attaquer */
                            {
                                for(j=0; j<nbCombattant; j++)
                                {
                                    if(groupe[i].camp != groupe[j].camp)
                                    {
                                        if(estAPortee(arene ,&groupe[i], &groupe[j], armeChoisie->portee) && groupe[j].perso->ptDeVie>0)
                                        {
                                            eventAttaqueSDL(&groupe[i], &groupe[j], armeChoisie, arene, ecran);
                                            continuer=0;
                                        }
                                        else if(nbDeplacement==0 && estAPortee(arene ,&groupe[i], &groupe[j], armeChoisie->portee)==1 && groupe[j].perso->ptDeVie>0)
                                        {
                                            eventAttaqueSDL(&groupe[i], &groupe[j], armeChoisie, arene, ecran);
                                            continuer=0;
                                        }
                                        else continuer=0;
                                    }
                                }
                            }
                            affCombat(ter, groupe, nbCombattant, arene, ecran);
                        }
                    }
                        default:
                        break;
                    }
                }
}

void eventAttaqueSDL(Combattant* combattant, Combattant* defenseur, Objet* arme, char arene[TAILLE_MAX_H][TAILLE_MAX_L], SDL_Surface* ecran)
{
    int continuer= 1;
    int rayon;
    char type;
    int choixAttaque=0;
    SDL_Event event;
    affAttaque(choixAttaque, ecran);
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_KEYDOWN:
            { if(event.key.state==SDL_PRESSED)
                {
                    if(event.key.keysym.sym==SDLK_RIGHT)
                    {   if(choixAttaque<5)
                        {   choixAttaque++;
                        }
                    }
                    else if(event.key.keysym.sym==SDLK_LEFT)
                    {   if(choixAttaque>0)
                        {   choixAttaque--;
                        }
                    }
                    else if(event.key.keysym.sym==SDLK_RETURN)
                    {
                        continuer = 0;
                    }
                    affAttaque(choixAttaque, ecran);
                }
            }
            break;

            case SDL_QUIT:
                continuer = 0;
            break;

            default:
            break;
        }
    }

    rayon=(int)sqrt(pow((defenseur->posX-combattant->posX),2)+pow((defenseur->posY-combattant->posY),2));
    if(rayon>1){ type = 0;}
    else {type = 1;}

    switch(choixAttaque)
    {
        case 0: attaqueBrutale (combattant, defenseur, arme->degats, type);
        break;

        case 1: attaquePrudente(combattant, defenseur, arme->degats, type);
        break;

        case 2: viserPourAttaque(combattant, defenseur, arme->degats, type);
        break;

        case 3: feinte(combattant, defenseur, arme->degats, type);
        break;

        case 4: preparerParade(combattant);
        break;

        default:
        break;
    }
}

int eventArmesEquiSDL(Combattant* combattant,int choix, SDL_Surface* ecran)
{
    int continuer= 1;
    int i;
    Objet* arme;
    SDL_Event event;
    SDL_Rect position;
    affArmesEqui(combattant, choix, ecran);
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_KEYDOWN:
            { if(event.key.state==SDL_PRESSED)
                {
                    if(event.key.keysym.sym==SDLK_RIGHT)
                    {   if(choix<2)
                        {   choix++;
                        }
                    }
                    else if(event.key.keysym.sym==SDLK_LEFT)
                    {   if(choix>0)
                        {   choix--;
                        }
                    }
                    else if(event.key.keysym.sym==SDLK_RETURN)
                    {
                        continuer = 0;
                    }
                    affArmesEqui(combattant, choix, ecran);
                }
            }

            case SDL_MOUSEMOTION:
            {
                for(i=0; i<=2; i++)
                {
                    if(event.button.x>3*TILE_LARGEUR+i*TILE_LARGEUR*3 && event.button.x<4*TILE_LARGEUR+i*TILE_LARGEUR*3 && event.button.y>TAILLE_FENETRE_H-5*TILE_HAUTEUR && event.button.y<TAILLE_FENETRE_H-4*TILE_HAUTEUR)
                    {
                    position.x = event.motion.x+10;
                    position.y = event.motion.y;
                    arme=combattant->perso->equipement.armeDroite[i];
                    affArmesEqui(combattant, choix, ecran);
                    affInfOb(&position, arme, ecran);
                    }
                }
            }

            break;

            case SDL_QUIT:
                continuer = 0;
            break;

            default:
            break;
        }
    }
    return choix;
}

void eventRecupInvSDL(Personnage* hero, Personnage* ennemi, Mission* mission, Objet* tabObjets, SDL_Surface* ecran)
{
    int continuer = 1, i, nb;
    SDL_Event event;
    Objet* objet;
    SDL_Rect position;

    affInvPnj(ennemi, ecran);

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_MOUSEMOTION:
            {
                 if(event.button.x>2*TILE_LARGEUR && event.button.x<(CARTE_LARGEUR-5)*TILE_LARGEUR && event.button.y>3*TILE_HAUTEUR && event.button.y<(CARTE_HAUTEUR-1)*TILE_HAUTEUR
                       && (event.button.y/TILE_HAUTEUR-3+event.button.x/TILE_LARGEUR-2)<ennemi->inventaire.nbObjet)
                   {
                    position.x = event.motion.x+10;
                    position.y = event.motion.y;
                    objet=ennemi->inventaire.st[event.button.y/TILE_HAUTEUR-3+event.button.x/TILE_LARGEUR-2].objet;
                    affInvPnj(ennemi, ecran);
                    affInfOb( &position, objet, ecran);
                    }
            }
            break;

            case SDL_KEYDOWN:
            {
                if(event.key.state==SDL_PRESSED)
                {
                    if(event.key.keysym.sym==SDLK_RETURN)
                    {
                        setPersoArgent(hero, getPersoArgent(hero)+getPersoArgent(ennemi));
                        setPersoArgent(ennemi, 0);
                        nb=getInventaireNbObjets(getPersoInventaire2(ennemi));
                        for(i=0; i<nb; i++)
                        {
                        ajouterInventaire(hero, ennemi->inventaire.st[0].objet);
                        if (testMissionObtenir( mission, ennemi->inventaire.st[0].objet))
                            {
                                missionAccomplir(mission, tabObjets);
                            }
                        soustraireInventaire(ennemi, ennemi->inventaire.st[0].objet);
                        }
                    }
                    else if(event.key.keysym.sym==SDLK_ESCAPE)
                    {
                        continuer = 0;
                    }
                }
            }
            break;

            case SDL_QUIT:
                    continuer = 0;
            break;

            default :
            break;
        }
        affInvPnj(ennemi, ecran);
    }
}

void eventDialogueSDL( Dialogue* dialogue, const Personnage* pnjs, char reponse[400], Mission* mission, Objet* tabObjets, Terrain* ter, SDL_Surface*ecran)
{
     int continuer = 1;
    SDL_Event event;
    int curseur = 0;
    affMenuDialogue(reponse, curseur, ecran);

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_KEYDOWN:
            { if(event.key.state==SDL_PRESSED)
                {
                    if(event.key.keysym.sym==SDLK_ESCAPE)
                    {
                        continuer=0;
                    }
                    else if(event.key.keysym.sym==SDLK_UP)
                    {
                        if(curseur>0)
                        {
                            curseur--;
                            affMenuDialogue(reponse, curseur, ecran);
                        }
                    }
                    else if(event.key.keysym.sym==SDLK_DOWN)
                    {
                        if(curseur<6)
                        {
                            curseur++;
                            affMenuDialogue(reponse, curseur, ecran);
                        }
                    }
                    else if(event.key.keysym.sym==SDLK_RETURN)
                    {
                        switch(curseur)
                        {
                            case 0: obtenirInfo(dialogue, reponse, mission, tabObjets);
                                    affDialogue( dialogue->perso2, reponse, ecran);
                                    while (continuer)
                                    {
                                        SDL_WaitEvent(&event);
                                        switch(event.type)
                                        {case SDL_KEYDOWN:
                                            { if(event.key.state==SDL_PRESSED)
                                                {if(event.key.keysym.sym==SDLK_RETURN)
                                                    {continuer=0;
                                                    }}}}
                                    }
                            break;

                            case 1: eventSoudoyerSDL( dialogue, reponse, ecran);
                                    affDialogue(dialogue->perso2, reponse, ecran);
                                    while (continuer)
                                    {
                                        SDL_WaitEvent(&event);
                                        switch(event.type)
                                        {case SDL_KEYDOWN:
                                            { if(event.key.state==SDL_PRESSED)
                                                {if(event.key.keysym.sym==SDLK_RETURN)
                                                    {continuer=0;
                                                    }}}}
                                    }
                                break;

                                case 2: menacer( dialogue, reponse);
                                        affDialogue( dialogue->perso2, reponse, ecran);
                                        while (continuer)
                                        {
                                            SDL_WaitEvent(&event);
                                            switch(event.type)
                                            {case SDL_KEYDOWN:
                                                { if(event.key.state==SDL_PRESSED)
                                                    {if(event.key.keysym.sym==SDLK_RETURN)
                                                        {continuer=0;
                                                        }}}}
                                        }
                                break;

                                case 3: seduire(dialogue, reponse);
                                        affDialogue( dialogue->perso2, reponse, ecran);
                                         while (continuer)
                                        {
                                            SDL_WaitEvent(&event);
                                            switch(event.type)
                                            {case SDL_KEYDOWN:
                                                { if(event.key.state==SDL_PRESSED)
                                                    {if(event.key.keysym.sym==SDLK_RETURN)
                                                        {continuer=0;
                                                        }}}}
                                        }
                                break;

                                case 4: eventAcheterSDL(dialogue, reponse, mission, tabObjets, ecran);
                                        continuer = 0;
                                break;

                                case 5: eventVendreSDL( dialogue, reponse, ecran);
                                        continuer = 0;
                                break;

                                default :
                                break;
                            }
                        }
                    }
                }
            break;

            case SDL_QUIT:
                continuer = 0;
            break;

            default :
            break;
        }
    }
}

void eventSoudoyerSDL( Dialogue* dialogue, char* rep, SDL_Surface* ecran)
{
    int continuer= 1;
    int curseur=0;
    SDL_Event event;
    affSoudoyer( dialogue->perso1, curseur, ecran);
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_KEYDOWN:
            { if(event.key.state==SDL_PRESSED)
                {
                    if(event.key.keysym.sym==SDLK_DOWN)
                    {   if(curseur<2)
                        {   curseur++;
                        }
                    }
                    else if(event.key.keysym.sym==SDLK_UP)
                    {   if(curseur>0)
                        {   curseur--;
                        }
                    }
                    else if(event.key.keysym.sym==SDLK_RETURN)
                    {
                        switch(curseur)
                        {
                            case 0: soudoyer(dialogue, 10, rep);
                            break;

                            case 1: soudoyer(dialogue, 50, rep);
                            break;

                            case 2: soudoyer(dialogue, 100, rep);
                            break;

                            default:
                            break;

                        }
                        continuer = 0;
                    }
                   affSoudoyer( dialogue->perso1, curseur, ecran);
                }
            }
            break;

            case SDL_QUIT:
                continuer = 0;
            break;

            default:
            break;
        }
    }

}

void eventAcheterSDL(Dialogue* dialogue, char* reponse, Mission* mission, Objet* tabObjets, SDL_Surface* ecran)
{
    int continuer = 1;
    SDL_Event event;
    Objet* objet;
    SDL_Rect position;
    strcpy(reponse, " ");
    objet=dialogue->perso2->inventaire.st[0].objet;

    affAcheter(dialogue, objet, ecran);

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_MOUSEMOTION:
            {
                 if(event.button.x>2*TILE_LARGEUR && event.button.x<(CARTE_LARGEUR-5)*TILE_LARGEUR && event.button.y>3*TILE_HAUTEUR && event.button.y<(CARTE_HAUTEUR-1)*TILE_HAUTEUR
                       && (event.button.y/TILE_HAUTEUR-3+event.button.x/TILE_LARGEUR-2)<dialogue->perso2->inventaire.nbObjet)
                   {
                    position.x = event.motion.x+10;
                    position.y = event.motion.y;
                    objet=dialogue->perso2->inventaire.st[event.button.y/TILE_HAUTEUR-3+event.button.x/TILE_LARGEUR-2].objet;
                    affAcheter(dialogue, objet, ecran);
                    affInfOb(&position, objet, ecran);
                    affDialogue( dialogue->perso2, reponse, ecran);
                    }
            }
            break;

            case SDL_MOUSEBUTTONDOWN:
            {
                if(event.button.button==SDL_BUTTON_LEFT)
                {
                    if(event.button.x>2*TILE_LARGEUR && event.button.x<(CARTE_LARGEUR-5)*TILE_LARGEUR && event.button.y>3*TILE_HAUTEUR && event.button.y<(CARTE_HAUTEUR-1)*TILE_HAUTEUR
                       && (event.button.y/TILE_HAUTEUR-3+event.button.x/TILE_LARGEUR-2)<dialogue->perso2->inventaire.nbObjet)
                    {   objet=dialogue->perso2->inventaire.st[event.button.y/TILE_HAUTEUR-3+event.button.x/TILE_LARGEUR-2].objet;
                    }
                }
                else if(event.button.button==SDL_BUTTON_RIGHT)
                {
                    if(event.button.x>2*TILE_LARGEUR && event.button.x<(CARTE_LARGEUR-5)*TILE_LARGEUR && event.button.y>3*TILE_HAUTEUR && event.button.y<(CARTE_HAUTEUR-1)*TILE_HAUTEUR
                       && (event.button.y/TILE_HAUTEUR-3+event.button.x/TILE_LARGEUR-2)<dialogue->perso2->inventaire.nbObjet)
                    {   objet=dialogue->perso2->inventaire.st[event.button.y/TILE_HAUTEUR-3+event.button.x/TILE_LARGEUR-2].objet;
                        acheter(dialogue, objet, reponse, mission, tabObjets);
                        affAcheter(dialogue, objet, ecran);
                        affDialogue(dialogue->perso2, reponse, ecran);
                    }
                }
            }
            break;

            case SDL_KEYDOWN:
            {
                if(event.key.state==SDL_PRESSED)
                {
                    if(event.key.keysym.sym==SDLK_RETURN)
                    {
                        acheter(dialogue, objet, reponse, mission, tabObjets);
                        affAcheter(dialogue, objet, ecran);
                        affDialogue(dialogue->perso2, reponse, ecran);

                    }
                    else if(event.key.keysym.sym==SDLK_ESCAPE)
                    {
                        continuer = 0;
                    }
                }
            }
            break;

            case SDL_QUIT:
                    continuer = 0;
            break;

            default :
            break;
        }
    }
}

void eventVendreSDL(Dialogue* dialogue, char* reponse, SDL_Surface* ecran)
{
    int continuer = 1;
    SDL_Event event;
    Objet* objet;
    SDL_Rect position;
    strcpy(reponse, " ");
    objet=dialogue->perso1->inventaire.st[0].objet;

    affVendre(dialogue, objet, ecran);

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_MOUSEMOTION:
            {
                 if(event.button.x>2*TILE_LARGEUR && event.button.x<(CARTE_LARGEUR-5)*TILE_LARGEUR && event.button.y>3*TILE_HAUTEUR && event.button.y<(CARTE_HAUTEUR-1)*TILE_HAUTEUR
                    && (event.button.y/TILE_HAUTEUR-3+event.button.x/TILE_LARGEUR-2)<dialogue->perso1->inventaire.nbObjet)
                   {
                    position.x = event.motion.x+10;
                    position.y = event.motion.y;
                    objet=dialogue->perso1->inventaire.st[event.button.y/TILE_HAUTEUR-3+event.button.x/TILE_LARGEUR-2].objet;
                    affVendre(dialogue, objet, ecran);
                    affInfOb(&position, objet, ecran);
                    affDialogue(dialogue->perso2, reponse, ecran);
                    }
            }
            break;

            case SDL_MOUSEBUTTONDOWN:
            {
                if(event.button.button==SDL_BUTTON_LEFT)
                {
                    if(event.button.x>2*TILE_LARGEUR && event.button.x<(CARTE_LARGEUR-5)*TILE_LARGEUR && event.button.y>3*TILE_HAUTEUR && event.button.y<(CARTE_HAUTEUR-1)*TILE_HAUTEUR
                       && (event.button.y/TILE_HAUTEUR-3+event.button.x/TILE_LARGEUR-2)<dialogue->perso2->inventaire.nbObjet)
                    {   objet=dialogue->perso1->inventaire.st[event.button.y/TILE_HAUTEUR-3+event.button.x/TILE_LARGEUR-2].objet;
                    }
                }
                else if(event.button.button==SDL_BUTTON_RIGHT)
                {
                    if(event.button.x>2*TILE_LARGEUR && event.button.x<(CARTE_LARGEUR-5)*TILE_LARGEUR && event.button.y>3*TILE_HAUTEUR && event.button.y<(CARTE_HAUTEUR-1)*TILE_HAUTEUR
                       && (event.button.y/TILE_HAUTEUR-3+event.button.x/TILE_LARGEUR-2)<dialogue->perso1->inventaire.nbObjet)
                    {   objet=dialogue->perso1->inventaire.st[event.button.y/TILE_HAUTEUR-3+event.button.x/TILE_LARGEUR-2].objet;
                        vendre(dialogue, objet, reponse);
                        affVendre(dialogue, objet, ecran);
                        affDialogue(dialogue->perso2, reponse, ecran);
                    }
                }
            }
            break;

            case SDL_KEYDOWN:
            {
                if(event.key.state==SDL_PRESSED)
                {
                    if(event.key.keysym.sym==SDLK_RETURN)
                    {
                        vendre(dialogue, objet, reponse);
                        affVendre(dialogue, objet, ecran);
                        affDialogue(dialogue->perso2, reponse, ecran);
                    }
                    else if(event.key.keysym.sym==SDLK_ESCAPE)
                    {
                        continuer = 0;
                    }
                }
            }
            break;

            case SDL_QUIT:
                    continuer = 0;
            break;

            default :
            break;
        }
    }
}


