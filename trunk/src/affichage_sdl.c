#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"
#include "terrain.h"
#include "tile.h"
#include "affichage_sdl.h"
#include "stdlib.h"
#include "stdio.h"
#include "assert.h"
#include "constante.h"
#include "combat.h"
#include "deplacement.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

void affChipset(Terrain* ter, SDL_Surface* ecran)
{
    SDL_Rect position;
    SDL_Rect tile;
    unsigned int i;
    position.x = 0;
    position.y = 0;

    for(i=ter->defilY;i<getNbrTile(ter); i++)
       {
            tile.w=TILE_LARGEUR;
            tile.h=TILE_HAUTEUR;

            tile.x=getPosX(ter->tabChipset[i]);
            tile.y=getPosY(ter->tabChipset[i]);

            SDL_BlitSurface(ter->chipset, &tile, ecran, &position);

            position.w=4;
            position.h=4;
            SDL_FillRect(SDL_GetVideoSurface(),&position,
                         ((getCollision(ter->tabChipset[i]))==0)?
                         SDL_MapRGB(SDL_GetVideoSurface()->format,255,0,0)
                         : SDL_MapRGB(SDL_GetVideoSurface()->format,0,255,0));

            position.x+= TILE_LARGEUR;

            if(position.x>=ter->decalageX*TILE_LARGEUR)
            {
                position.y+= TILE_HAUTEUR;
                position.x=0;
           }
        }
            SDL_Flip(ecran);
}

void affEditeur(Terrain* ter, SDL_Surface* ecran)
{
    SDL_Rect position;
    SDL_Rect tile;
    unsigned int i;

    affChipset(ter, ecran);
    position.x = (ter->decalageX+1)*TILE_LARGEUR;
    position.y = 0;
    tile.w=TILE_LARGEUR;
    tile.h=TILE_HAUTEUR;

     for(i=0; i<CARTE_LARGEUR*CARTE_HAUTEUR; i++)
     {
            tile.x=getPosX(ter->tabChipset[ter->carte[i]]);
            tile.y=getPosY(ter->tabChipset[ter->carte[i]]);
            SDL_BlitSurface(ter->chipset, &tile, ecran, &position);

            position.x+= TILE_LARGEUR;
            if(position.x>(CARTE_LARGEUR+ter->decalageX)*TILE_LARGEUR)
            {
                position.y+= TILE_HAUTEUR;
                position.x=(ter->decalageX+1)*TILE_LARGEUR;
            }
    }
    SDL_Flip(ecran);
}

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

void affPerso(const Personnage* hero, const Personnage* pnjs, const Personnage* ennemis, SDL_Surface* ecran)
{

    SDL_Rect position;
    position.x = hero->posX;
    position.y = hero->posY;
    SDL_BlitSurface(hero->avatar, NULL, ecran, &position);

    position.x = pnjs->posX;
    position.y = pnjs->posY;
    SDL_BlitSurface(pnjs->avatar, NULL, ecran, &position);

    position.x = ennemis->posX;
    position.y = ennemis->posY;
    SDL_BlitSurface(ennemis->avatar, NULL, ecran, &position);

    SDL_Flip(ecran);
}

void affCombat(Terrain* ter, Combattant* groupe, int l, char arene[TAILLE_MAX][TAILLE_MAX], SDL_Surface* ecran)
{
    SDL_Rect position;
    SDL_Rect tile;
    unsigned int i, j;

    position.x = 0;
    position.y = 0;
    tile.w=TILE_LARGEUR;
    tile.h=TILE_HAUTEUR;

     for(i= 0; i<TAILLE_MAX; i++)
     {
         for(j=0; j<TAILLE_MAX; j++)
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
    SDL_BlitSurface(groupe[i].avatar, NULL, ecran, &position);
    }

    SDL_Flip(ecran);
}

void affInventaire(Personnage* perso, SDL_Surface* ecran)
{
    SDL_Surface* inventaire;
    SDL_Rect position;
    SDL_Rect tile;
    unsigned int i;
    char quantiteChar[255];

    TTF_Init();
    TTF_Font *police = NULL;
    police = TTF_OpenFont("data/fonts-japanese-gothic.ttf", 15);
    SDL_Surface* quantite=NULL;
    SDL_Color colorNoir = { 0, 0, 0};

    position.x = 0;
    position.y = 0;
    tile.w=TILE_LARGEUR;
    tile.h=TILE_HAUTEUR;

    inventaire = SDL_CreateRGBSurface(SDL_HWSURFACE, (CARTE_LARGEUR-2)*TILE_LARGEUR, (CARTE_HAUTEUR-2)*TILE_HAUTEUR, 32, 0, 0, 0, 0);
    position.x = TILE_LARGEUR;
    position.y = TILE_HAUTEUR;
    SDL_FillRect(inventaire, NULL, SDL_MapRGB(ecran->format, 76, 24, 0));
    SDL_BlitSurface(inventaire, NULL, ecran,&position);

    position.x = 3*TILE_LARGEUR;
    position.y = TILE_HAUTEUR;
    quantite = TTF_RenderText_Solid(police,  "Inventaire", colorNoir);
    SDL_BlitSurface(quantite, NULL, ecran,&position);

    position.x= 2*TILE_LARGEUR;
    position.y= 3*TILE_HAUTEUR;

     for(i=0; i<perso->inventaire.capacite; i++)
     {
         if(i<perso->inventaire.nbObjet)
        {
        SDL_BlitSurface(perso->inventaire.st[i].objet->icon, &tile, ecran, &position);
        sprintf (quantiteChar, "%d", perso->inventaire.st[i].quantite );
        quantite = TTF_RenderText_Solid(police,  quantiteChar, colorNoir);
        SDL_BlitSurface(quantite, NULL, ecran, &position);

        position.x+= TILE_LARGEUR;
            if(position.x>=CARTE_LARGEUR*TILE_LARGEUR)
            {
                position.y+= TILE_HAUTEUR;
                position.x= 2*TILE_LARGEUR;
            }
        }
     }

    position.y= (CARTE_HAUTEUR-3)*TILE_HAUTEUR;
    position.x= 2*TILE_LARGEUR;
    sprintf (quantiteChar, "Argent: %d ", perso->argent );
    quantite = TTF_RenderText_Solid(police,  quantiteChar, colorNoir);
    SDL_BlitSurface(quantite, NULL, ecran, &position);

    SDL_Flip(ecran);
    SDL_FreeSurface(inventaire);
    SDL_FreeSurface(quantite);
    TTF_CloseFont(police);
    TTF_Quit();
}

void affProfil(Personnage* hero, SDL_Surface* ecran)
{

}

void affDialogue( char* dialoguetab, SDL_Surface* ecran)
{
    SDL_Surface* cadreDialogue;
    SDL_Surface* texte = NULL;
    SDL_Rect position;

    TTF_Init();
    TTF_Font *police = NULL;
    police = TTF_OpenFont("data/fonts-japanese-gothic.ttf", 15);

    SDL_Color colorNoir = { 0 ,0,0};

    cadreDialogue = SDL_CreateRGBSurface(SDL_HWSURFACE, (CARTE_LARGEUR-4)*TILE_LARGEUR, 4*TILE_HAUTEUR, 32, 0, 0, 0, 0);
    position.x = 2*TILE_LARGEUR;
    position.y = (CARTE_HAUTEUR-5)*TILE_HAUTEUR;

    SDL_FillRect(cadreDialogue, NULL, SDL_MapRGB(ecran->format, 76, 24, 0));
    SDL_BlitSurface(cadreDialogue, NULL, ecran,&position);

    texte = TTF_RenderText_Solid(police, dialoguetab, colorNoir);
    SDL_BlitSurface(texte, NULL, ecran, &position);

    SDL_Flip(ecran);

    SDL_FreeSurface(cadreDialogue);
    SDL_FreeSurface(texte);
    TTF_CloseFont(police);
    TTF_Quit();
}

void affMenuDialogue(SDL_Surface* ecran, char* dialoguetab, int curseur)
{
    int i;
    SDL_Surface* dialogue=NULL;
    SDL_Surface* texte = NULL;
    SDL_Rect position;
    SDL_Color colorNoir = { 0, 0, 0};
    char menu[6][20];
    strcpy(menu[0], "Obtenir des infos");
    strcpy(menu[1], "Soudoyer");
    strcpy(menu[2], "Menacer");
    strcpy(menu[3], "Seduire");
    strcpy(menu[4], "Acheter");
    strcpy(menu[5],  "Vendre");

    TTF_Init();
    TTF_Font *police = NULL;
    police = TTF_OpenFont("data/fonts-japanese-gothic.ttf", 15);

    dialogue = SDL_CreateRGBSurface(SDL_HWSURFACE, (CARTE_LARGEUR-4)*TILE_LARGEUR, 4*TILE_HAUTEUR, 32, 0, 0, 0, 0);
    position.x = 2*TILE_LARGEUR;
    position.y = (CARTE_HAUTEUR-5)*TILE_HAUTEUR;

    SDL_FillRect(dialogue, NULL, SDL_MapRGB(ecran->format, 76, 24, 0));
    SDL_BlitSurface(dialogue, NULL, ecran,&position);

    for(i=0;i<6;i++)
    {
        if(i==curseur)
            {
                position.x = 2*TILE_LARGEUR;
                position.y = (CARTE_HAUTEUR-5+i)*TILE_HAUTEUR;
                texte = TTF_RenderText_Solid(police, "*", colorNoir);
                SDL_BlitSurface(texte, NULL, ecran, &position);
            }
        position.x = 3*TILE_LARGEUR;
        position.y = (CARTE_HAUTEUR-5+i)*TILE_HAUTEUR;
        texte = TTF_RenderText_Solid(police, menu[i], colorNoir);
        SDL_BlitSurface(texte, NULL, ecran, &position);
    }

    SDL_Flip(ecran);

    SDL_FreeSurface(dialogue);
    SDL_FreeSurface(texte);
    TTF_CloseFont(police);
    TTF_Quit();
}

void affAcheter(Dialogue* dialogue, Objet* objet, SDL_Surface* ecran)
{
 SDL_Surface* inventaire;
    SDL_Rect position;
    SDL_Rect tile;
    unsigned int i;
    char infoChar[255];

    TTF_Init();
    TTF_Font *police = NULL;

    SDL_Surface* info=NULL;
    SDL_Color colorNoir = { 0, 0, 0};

    police = TTF_OpenFont("data/fonts-japanese-gothic.ttf", 15);
    position.x = 0;
    position.y = 0;
    tile.w=TILE_LARGEUR;
    tile.h=TILE_HAUTEUR;

    inventaire = SDL_CreateRGBSurface(SDL_HWSURFACE, (CARTE_LARGEUR-2)*TILE_LARGEUR, (CARTE_HAUTEUR-6)*TILE_HAUTEUR, 32, 0, 0, 0, 0);
    position.x = TILE_LARGEUR;
    position.y = TILE_HAUTEUR;
    SDL_FillRect(inventaire, NULL, SDL_MapRGB(ecran->format, 76, 24, 0));
    SDL_BlitSurface(inventaire, NULL, ecran,&position);

    position.x = 3*TILE_LARGEUR;
    position.y = TILE_HAUTEUR;
    info = TTF_RenderText_Solid(police,  "Acheter", colorNoir);
    SDL_BlitSurface(info, NULL, ecran,&position);

    position.x= 2*TILE_LARGEUR;
    position.y= 3*TILE_HAUTEUR;

     for(i=0; i<dialogue->perso2->inventaire.capacite && position.y<((TILE_HAUTEUR-4)*CARTE_HAUTEUR); i++)
     {
         if(i<dialogue->perso2->inventaire.nbObjet)
        {
        SDL_BlitSurface(dialogue->perso2->inventaire.st[i].objet->icon, &tile, ecran, &position);

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
    info = TTF_RenderText_Solid(police,  infoChar, colorNoir);
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
    SDL_Color colorNoir = { 0, 0, 0};

    police = TTF_OpenFont("data/fonts-japanese-gothic.ttf", 15);

    cadre = SDL_CreateRGBSurface(SDL_HWSURFACE, 4*TILE_LARGEUR, 4*TILE_HAUTEUR, 32, 0, 0, 0, 0);
    SDL_FillRect(cadre, NULL, SDL_MapRGB(ecran->format, 76, 24, 100));
    SDL_BlitSurface(cadre, NULL, ecran, position);

    sprintf(infoChar,"%s", objet->nom);
    info=TTF_RenderText_Solid(police,  infoChar, colorNoir);
    SDL_BlitSurface(info, NULL, ecran, position);
    position->y+=10;

    switch(objet->utilite)
    {
       case 1: info=TTF_RenderText_Solid(police,  "arme", colorNoir);
                SDL_BlitSurface(info, NULL, ecran, position);
                 position->y+=10;
                sprintf(infoChar,"%d", objet->portee);
                info=TTF_RenderText_Solid(police,infoChar, colorNoir);
                SDL_BlitSurface(info, NULL, ecran, position);
                position->y+=10;
                sprintf(infoChar,"%d", objet->degats);
                info=TTF_RenderText_Solid(police,infoChar, colorNoir);
        break;

        case 2: info=TTF_RenderText_Solid(police,  "armure", colorNoir);
                SDL_BlitSurface(info, NULL, ecran, position);
                position->y+=10;
                sprintf(infoChar,"%d", objet->protection);
                info=TTF_RenderText_Solid(police,infoChar, colorNoir);
        break;

        case 3: info=TTF_RenderText_Solid(police,  "potion/nourriture", colorNoir);
                SDL_BlitSurface(info, NULL, ecran, position);
                position->y+=10;
                sprintf(infoChar,"%d", objet->portee);
                info=TTF_RenderText_Solid(police,infoChar, colorNoir);
                SDL_BlitSurface(info, NULL, ecran, position);
                position->y+=10;
                switch(objet->degats)
                {
                    case 1: info=TTF_RenderText_Solid(police,  "soin", colorNoir);
                SDL_BlitSurface(info, NULL, ecran, position);
                position->y+=10;
                    break;

                    case 2: info=TTF_RenderText_Solid(police,  "poison", colorNoir);
                    SDL_BlitSurface(info, NULL, ecran, position);
                    position->y+=10;
                    break;

                    default:
                    break;
                }
                sprintf(infoChar,"%d", objet->protection);
                info=TTF_RenderText_Solid(police,infoChar, colorNoir);
        break;

        case 4: info=TTF_RenderText_Solid(police,  "objet quete", colorNoir);
        break;

        default: info=TTF_RenderText_Solid(police,  "autre", colorNoir);
        break;
    }
    SDL_BlitSurface(info, NULL, ecran, position);
    position->y+=10;

    sprintf(infoChar,"%d", objet->valeur);
    info=TTF_RenderText_Solid(police,infoChar, colorNoir);
    SDL_BlitSurface(info, NULL, ecran, position);

    SDL_Flip(ecran);
    SDL_FreeSurface(cadre);
    SDL_FreeSurface(info);
    TTF_CloseFont(police);
    TTF_Quit();
}

void eventEditeurSDL(Terrain* ter, SDL_Surface* ecran )
{
    int i;
    int continuer = 1;
    SDL_Event event;

    affEditeur(ter, ecran);

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_KEYDOWN:
            { if(event.key.state==SDL_PRESSED)
                {
                 if(event.key.keysym.sym==SDLK_PAGEUP)  /** Défilement du chipset vers le haut */
                    {
                       if(ter->defilY>0){ ter->defilY-=ter->decalageX;}
                    }
                    else if(event.key.keysym.sym==SDLK_PAGEDOWN)    /** Défilement du chipset vers le bas */
                    {
                        if(ter->defilY<ter->nbrTileChipset-TAILLE_FENETRE/TILE_HAUTEUR){ter->defilY+=ter->decalageX;}
                    }
                    else if(event.key.keysym.sym==SDLK_s) /** Sauvegarde de la carte */
                    {
                        terSauvegarde(ter, "data/Cartes/save.map", "data/Chipsets/desertChipset.bmp");
                    }
                    else if(event.key.keysym.sym==SDLK_l) /** Chargement de la carte */
                    {   terLibere(ter);
                        terInit(ter);
                        terCharger(ter, "data/Cartes/save.map");
                    }
                }
            }
            break;

            case SDL_MOUSEBUTTONDOWN:
             if(event.button.button==SDL_BUTTON_LEFT)
            {
                if(event.button.x<ter->decalageX*TILE_LARGEUR)
                {   ter->tileSel=((event.button.y/TILE_HAUTEUR)*(ter->decalageX)+event.button.x/TILE_LARGEUR+ter->defilY)%ter->nbrTileChipset;
                    if(ter->tileSel>=ter->nbrTileChipset) ter->tileSel=ter->nbrTileChipset-1;
                }
                else if(event.button.x>ter->decalageX*TILE_LARGEUR)
                {
                   i=((event.button.y/TILE_HAUTEUR)*CARTE_LARGEUR+event.button.x/TILE_LARGEUR-ter->decalageX-1);

                    if(i>=CARTE_LARGEUR*CARTE_HAUTEUR) i=CARTE_LARGEUR*CARTE_HAUTEUR-1;
                    setCarte(ter, i, ter->tileSel);
                }
            }

            else if(event.button.button==SDL_BUTTON_RIGHT)
            {
                if(event.button.x<ter->decalageX*TILE_LARGEUR)
                {
                    i=(event.button.y/TILE_HAUTEUR)*(ter->decalageX)+event.button.x/TILE_LARGEUR+ter->defilY;
                   setCollision(&ter->tabChipset[i], (ter->tabChipset[i].collision+1)%2);
                }
            }
            break;

            case SDL_QUIT:
                continuer = 0;
            break;
        }
        affEditeur(ter, ecran);
    }
}

void eventCombatSDL(Personnage* hero, Personnage* ennemi, Terrain* ter, SDL_Surface* ecran)
{
    Personnage* liste;
    char arene [TAILLE_MAX][TAILLE_MAX];
    int continuer =1;
    SDL_Event event;

    Objet *tabObjets=NULL;

    initialiserTousLesObjets(&tabObjets);

    liste=(Personnage*)malloc(4*sizeof(Personnage));

    liste[0]=*hero;
    liste[1]=*ennemi;
    nouveauPerso (&liste[2], "MechantII", 2, 1, 2, 1, 0, 100, tabObjets);
    nouveauPerso (&liste[3], "Allie", 1, 1, 1, 1, 0, 100, tabObjets);

    areneInit(ter, arene);
    afficherTab2D(arene);
    int i, nb=4;
    Combattant* groupe;
    groupe=(Combattant*)malloc(4*sizeof(Combattant));

    initCombat(liste,4,groupe,arene);
    afficherTab2D(arene);
    groupe[0].avatar=SDL_LoadBMP("data/Chipsets/perso.bmp");
    groupe[1].avatar=SDL_LoadBMP("data/Chipsets/pnj.bmp");
     groupe[3].avatar=SDL_LoadBMP("data/Chipsets/perso.bmp");
    groupe[2].avatar=SDL_LoadBMP("data/Chipsets/pnj.bmp");

    affCombat(ter, groupe,4, arene, ecran);

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
            affCombat(ter, groupe,4, arene, ecran);
        }
    }
    /*Ajouter expérience fin de combat*/
 /* free (groupe);*/


    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            default:
            break;
        }
    }


}


void eventJeuSDL(Personnage* hero, Personnage* pnjs, Personnage* ennemis,Terrain* ter, Dialogue* dialogue, SDL_Surface* ecran)
{
    int continuer = 1;
    SDL_Event event;

    affCarte(ter, ecran);
    affPerso(hero, pnjs, ennemis, ecran);
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_KEYDOWN:
            { if(event.key.state==SDL_PRESSED)
                {
                    if(event.key.keysym.sym==SDLK_RIGHT)    /** Deplacement vers la droite*/
                    {   if(getCollision(ter->tabChipset[ter->carte[(hero->posX+TILE_LARGEUR)/TILE_LARGEUR+CARTE_LARGEUR*(hero->posY/TILE_HAUTEUR)]])==1)
                        {hero->posX+=TILE_LARGEUR;}
                    }
                    else if(event.key.keysym.sym==SDLK_LEFT)    /** Deplacement vers la gauche*/
                    {   if(getCollision(ter->tabChipset[ter->carte[(hero->posX-TILE_LARGEUR)/TILE_LARGEUR+CARTE_LARGEUR*(hero->posY/TILE_HAUTEUR)]])==1)
                        {hero->posX-=TILE_LARGEUR;}
                    }
                    else if(event.key.keysym.sym==SDLK_DOWN)    /** Deplacement vers le bas*/
                    {   if(getCollision(ter->tabChipset[ter->carte[hero->posX/TILE_LARGEUR+CARTE_LARGEUR*((hero->posY+TILE_HAUTEUR)/TILE_HAUTEUR)]])==1)
                        {hero->posY+=TILE_HAUTEUR;}
                    }
                    else if(event.key.keysym.sym==SDLK_UP)  /** Déplacement vers le haut */
                    {   if(getCollision(ter->tabChipset[ter->carte[hero->posX/TILE_LARGEUR+CARTE_LARGEUR*((hero->posY-TILE_HAUTEUR)/TILE_HAUTEUR)]])==1)
                        {hero->posY-=TILE_HAUTEUR;}
                    }
                      else if(event.key.keysym.sym==SDLK_e) /** Touche d'action*/
                    {
                        if( ((hero->posX+TILE_LARGEUR)==pnjs->posX && hero->posY==pnjs->posY)
                           || ((hero->posX-TILE_LARGEUR)==pnjs->posX && hero->posY==pnjs->posY)
                           || ((hero->posY+TILE_HAUTEUR)==pnjs->posY && hero->posX==pnjs->posX)
                           || ((hero->posY-TILE_HAUTEUR)==pnjs->posY && hero->posX==pnjs->posX) )
                        {
                            eventDialogueSDL(dialogue, hero, pnjs, ennemis, ter, ecran);
                        }
                        if( ((hero->posX+TILE_LARGEUR)==ennemis->posX && hero->posY==ennemis->posY)
                           || ((hero->posX-TILE_LARGEUR)==ennemis->posX && hero->posY==ennemis->posY)
                           || ((hero->posY+TILE_HAUTEUR)==ennemis->posY && hero->posX==ennemis->posX)
                           || ((hero->posY-TILE_HAUTEUR)==ennemis->posY && hero->posX==ennemis->posX) )
                        {
                            eventCombatSDL(hero, ennemis, ter, ecran);
                        }
                    }
                    else if(event.key.keysym.sym==SDLK_i) /** Touche d'inventaire*/
                    {
                            eventInventaireSDL(hero, ecran);
                    }
                    affCarte(ter, ecran);
                    affPerso(hero, pnjs, ennemis, ecran);
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
                    if(event.button.x>2*TILE_LARGEUR && event.button.x<(CARTE_LARGEUR-5)*TILE_LARGEUR && event.button.y>3*TILE_HAUTEUR && event.button.y<(CARTE_HAUTEUR-1)*TILE_HAUTEUR
                       && (event.button.y/TILE_HAUTEUR-3+event.button.x/TILE_LARGEUR-2)<hero->inventaire.nbObjet)
                    {   objet=hero->inventaire.st[event.button.y/TILE_HAUTEUR-3+event.button.x/TILE_LARGEUR-2].objet;

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
//        TTF_CloseFont(police);
//        free(dialoguetab);
//        TTF_Quit();
//       fclose(fichier);

}

void eventAcheterSDL( Dialogue* dialogue, char* dialoguetab, const Personnage* hero, const Personnage* pnjs, const Personnage* ennemis, const Terrain* ter, SDL_Surface* ecran)
{
    int continuer = 1;
    SDL_Event event;
    Objet* objet;
    SDL_Rect position;

    objet=dialogue->perso2->inventaire.st[0].objet;

    affCarte(ter, ecran);
    affPerso(hero, pnjs, ennemis, ecran);
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
//                        acheter(dialogue, objet, dialoguetab, ecran);
                        affAcheter(dialogue, objet, ecran);
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
                        acheter(dialogue, objet, dialoguetab, ecran);
                        affAcheter(dialogue, objet, ecran);
                        affDialogue(dialoguetab, ecran);
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

void eventDialogueSDL( Dialogue* dialogue, const Personnage* hero, const Personnage* pnjs, const Personnage* ennemis, Terrain* ter, SDL_Surface*ecran)
{   int continuer = 1;
    SDL_Event event;
    int curseur = 0;

    char* reponse;
    reponse=malloc(400*sizeof(char));
    affMenuDialogue(ecran, reponse, curseur);


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
                            continuer=0;
                        }
                       else if(event.key.keysym.sym==SDLK_UP)
                        {
                            if(curseur>0)
                            {
                                curseur--;
                                affMenuDialogue(ecran, reponse, curseur);
                            }
                        }
                        else if(event.key.keysym.sym==SDLK_DOWN)
                        {
                            if(curseur<4)
                            {
                                curseur++;
                                affMenuDialogue(ecran, reponse, curseur);
                            }
                        }
                        else if(event.key.keysym.sym==SDLK_e)
                        {
                            switch(curseur)
                            {
                                case 0: obtenirInfo(dialogue, reponse, ecran);
                                        affDialogue( reponse, ecran);
                                        while (continuer)
                                        {
                                            SDL_WaitEvent(&event);
                                            switch(event.type)
                                            {case SDL_KEYDOWN:
                                                { if(event.key.state==SDL_PRESSED)
                                                    {
                                                        if(event.key.keysym.sym==SDLK_e)
                                                        {
                                                        continuer=0;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                break;

                                case 1: //soudoyer( dialogue, int argent, reponse, ecran);
                                break;

                                case 2: menacer( dialogue, reponse, ecran);
                                         affDialogue( reponse, ecran);
                                         while (continuer)
                                        {
                                            SDL_WaitEvent(&event);
                                            switch(event.type)
                                            {case SDL_KEYDOWN:
                                                { if(event.key.state==SDL_PRESSED)
                                                    {
                                                        if(event.key.keysym.sym==SDLK_e)
                                                        {
                                                        continuer=0;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                break;

                                case 3: seduire( dialogue, reponse, ecran);
                                        affDialogue( reponse, ecran);
                                         while (continuer)
                                        {
                                            SDL_WaitEvent(&event);
                                            switch(event.type)
                                            {case SDL_KEYDOWN:
                                                { if(event.key.state==SDL_PRESSED)
                                                    {
                                                        if(event.key.keysym.sym==SDLK_e)
                                                        {
                                                        continuer=0;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                break;

                                case 4: eventAcheterSDL(dialogue, reponse, hero, pnjs, ennemis, ter, ecran);

                                break;

                                case 5: // vendre( dialogue, Objet* objet, reponse, ecran);
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
        free(reponse);
}

void editerCarte ()
{
    Terrain terrain;
    SDL_Surface* ecran = NULL;
    SDL_Init(SDL_INIT_VIDEO);

    terInit(&terrain);
    terRemplirStruct(&terrain);

    ecran = SDL_SetVideoMode(TAILLE_FENETRE+32*terrain.decalageX, TAILLE_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Iniuriam", NULL);



    eventEditeurSDL(&terrain, ecran);

    terLibere(&terrain);
    SDL_Quit();
}
