#include "affichage_sdl.h"


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
    char texte[255];
    SDL_Surface* texteCadre =NULL;
    TTF_Init();
    TTF_Font *police = NULL;
    police = TTF_OpenFont("data/fonts-japanese-gothic.ttf", 15);
    SDL_Color color = { 0 ,0,0};

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

    sprintf(texte, "Vie: %d", groupe[0].perso->ptDeVie );
    texteCadre = TTF_RenderText_Solid(police, texte, color);
    SDL_BlitSurface(texteCadre, NULL, ecran, &position);
    position.y+=25;
    sprintf(texte, "Vie: %d", groupe[1].perso->ptDeVie );
    texteCadre = TTF_RenderText_Solid(police, texte, color);
    SDL_BlitSurface(texteCadre, NULL, ecran, &position);
    position.y+=25;
    sprintf(texte, "Vie: %d", groupe[2].perso->ptDeVie );
    texteCadre = TTF_RenderText_Solid(police, texte, color);
    SDL_BlitSurface(texteCadre, NULL, ecran, &position);
    position.y+=25;
    sprintf(texte, "Vie: %d", groupe[3].perso->ptDeVie );
    texteCadre = TTF_RenderText_Solid(police, texte, color);
    SDL_BlitSurface(texteCadre, NULL, ecran, &position);


    SDL_Flip(ecran);
}

void affInventaire(Personnage* perso, SDL_Surface* ecran)
{
    SDL_Surface* cadreInventaire;
    SDL_Rect position;
    unsigned int i;
    char quantiteChar[255];

    TTF_Init();
    TTF_Font *police = NULL;
    police = TTF_OpenFont("data/fonts-japanese-gothic.ttf", 15);
    SDL_Surface* quantite=NULL;
    SDL_Color color = { 160, 115, 25};

    position.x = 0;
    position.y = 0;

    cadreInventaire = SDL_LoadBMP("data/Chipsets/inventaire.bmp");
    SDL_BlitSurface(cadreInventaire, NULL, ecran,&position);

    position.x = TAILLE_FENETRE/6;
    position.y = TILE_HAUTEUR;
    quantite = TTF_RenderText_Solid(police,  "Inventaire", color);
    SDL_BlitSurface(quantite, NULL, ecran,&position);

    position.x= 2*TILE_LARGEUR;
    position.y= 3*TILE_HAUTEUR;

     for(i=0; i<perso->inventaire.capacite; i++)
     {
         if(i<perso->inventaire.nbObjet && position.y<TAILLE_FENETRE-3*TILE_HAUTEUR)
        {
        SDL_BlitSurface(perso->inventaire.st[i].objet->icon, NULL, ecran, &position);
        sprintf (quantiteChar, "%d", perso->inventaire.st[i].quantite );
        quantite = TTF_RenderText_Solid(police,  quantiteChar, color);
        SDL_BlitSurface(quantite, NULL, ecran, &position);

        position.x+= TILE_LARGEUR;
            if(position.x>=TAILLE_FENETRE/2-TILE_LARGEUR)
            {
                position.y+= TILE_HAUTEUR;
                position.x= 2*TILE_LARGEUR;
            }
        }
     }


    position.x = TAILLE_FENETRE*2/3;
    position.y = TILE_HAUTEUR;
    quantite = TTF_RenderText_Solid(police,  "Equipement", color);
    SDL_BlitSurface(quantite, NULL, ecran,&position);

    position.x= TAILLE_FENETRE/2+2*TILE_LARGEUR;
    position.y= 3*TILE_HAUTEUR;
    if(perso->equipement.tete==NULL)
    {

    }
    else
    { SDL_BlitSurface(perso->equipement.tete->icon, NULL, ecran, &position);}

    position.y= TAILLE_FENETRE-2*TILE_HAUTEUR;
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
    char info[255];

    TTF_Init();
    TTF_Font *police = NULL;
    police = TTF_OpenFont("data/fonts-japanese-gothic.ttf", 15);
    SDL_Surface* quantite=NULL;
    SDL_Color colorNoir = { 0, 255, 0};

    position.x = 0;
    position.y = 0;

    cadreProfil = SDL_CreateRGBSurface(SDL_HWSURFACE, TAILLE_FENETRE, TAILLE_FENETRE, 32, 0, 0, 0, 0);
    SDL_FillRect(cadreProfil, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    SDL_BlitSurface(cadreProfil, NULL, ecran,&position);

    position.x = TAILLE_FENETRE/3;
    position.y = TAILLE_FENETRE/10;
    quantite = TTF_RenderText_Solid(police,  "Profil", colorNoir);
    SDL_BlitSurface(quantite, NULL, ecran,&position);

    position.x=TAILLE_FENETRE/6;
    position.y=TAILLE_FENETRE/6;

    quantite = TTF_RenderText_Solid(police, perso->nom, colorNoir);
    SDL_BlitSurface(quantite, NULL, ecran,&position);

    position.y+= 25;
    switch(perso->race)
    {
        case 1:
        quantite = TTF_RenderText_Solid(police,  "Race: humain", colorNoir);
        SDL_BlitSurface(quantite, NULL, ecran,&position);
        break;

        case 2:
        quantite = TTF_RenderText_Solid(police,  "Race: cyborg", colorNoir);
        SDL_BlitSurface(quantite, NULL, ecran,&position);
        break;

        case 3:
        quantite = TTF_RenderText_Solid(police,  "Race: sicaris", colorNoir);
        SDL_BlitSurface(quantite, NULL, ecran,&position);
        break;

        case 4:
        quantite = TTF_RenderText_Solid(police,  "Race: medarsin", colorNoir);
        SDL_BlitSurface(quantite, NULL, ecran,&position);
        break;

        default:
        quantite = TTF_RenderText_Solid(police,  "Race: inconnu", colorNoir);
        SDL_BlitSurface(quantite, NULL, ecran,&position);
        break;
    }

    position.y+= 25;
    switch(perso->sexe)
    {
        case 1:
        quantite = TTF_RenderText_Solid(police,  "Sexe: homme", colorNoir);
        SDL_BlitSurface(quantite, NULL, ecran,&position);
        break;

        case 2:
        quantite = TTF_RenderText_Solid(police,  "Sexe: femme", colorNoir);
        SDL_BlitSurface(quantite, NULL, ecran,&position);
        break;

        default:
        quantite = TTF_RenderText_Solid(police,  "Sexe: inconnu", colorNoir);
        SDL_BlitSurface(quantite, NULL, ecran,&position);
        break;
    }

    position.y+= 25;
    switch(perso->faction)
    {
        case 1:
        quantite = TTF_RenderText_Solid(police,  "Faction: Sisteen", colorNoir);
        SDL_BlitSurface(quantite, NULL, ecran,&position);
        break;

        case 2:
        quantite = TTF_RenderText_Solid(police,  "Faction: Heredian", colorNoir);
        SDL_BlitSurface(quantite, NULL, ecran,&position);
        break;

        case 3:
        quantite = TTF_RenderText_Solid(police,  "Faction: Marchand", colorNoir);
        SDL_BlitSurface(quantite, NULL, ecran,&position);
        break;

        default:
        quantite = TTF_RenderText_Solid(police,  "Faction: inconnu", colorNoir);
        SDL_BlitSurface(quantite, NULL, ecran,&position);
        break;
    }

    position.y+= 25;
    switch(perso->carriere)
    {
        case 1:
        quantite = TTF_RenderText_Solid(police,  "Carriere: Plombier", colorNoir);
        SDL_BlitSurface(quantite, NULL, ecran,&position);
        break;

        case 2:
        quantite = TTF_RenderText_Solid(police,  "Faction: Heredian", colorNoir);
        SDL_BlitSurface(quantite, NULL, ecran,&position);
        break;

        case 3:
        quantite = TTF_RenderText_Solid(police,  "Faction: Marchand", colorNoir);
        SDL_BlitSurface(quantite, NULL, ecran,&position);
        break;

        default:
        quantite = TTF_RenderText_Solid(police,  "Faction: inconnu", colorNoir);
        SDL_BlitSurface(quantite, NULL, ecran,&position);
        break;
    }

    position.x=TAILLE_FENETRE/2;
    position.y=TAILLE_FENETRE/6;
    sprintf(info, "Experience: %d", perso->experience);
    quantite = TTF_RenderText_Solid(police,  info, colorNoir);
    SDL_BlitSurface(quantite, NULL, ecran,&position);

    position.y+=25;
    sprintf(info, "Niveau: %d", perso->niveau);
    quantite = TTF_RenderText_Solid(police,  info, colorNoir);
    SDL_BlitSurface(quantite, NULL, ecran,&position);

    position.y+=25;
    sprintf(info, "Points de vie: %d", perso->ptDeVie);
    quantite = TTF_RenderText_Solid(police,  info, colorNoir);
    SDL_BlitSurface(quantite, NULL, ecran,&position);

    position.x=TAILLE_FENETRE/6;
    position.y=TAILLE_FENETRE*3/7;
    sprintf(info, "Attaque: %d", perso->attaque);
    quantite = TTF_RenderText_Solid(police,  info, colorNoir);
    SDL_BlitSurface(quantite, NULL, ecran,&position);

    position.y += 25;
    sprintf(info, "Defense: %d", perso->defense);
    quantite = TTF_RenderText_Solid(police,  info, colorNoir);
    SDL_BlitSurface(quantite, NULL, ecran, &position);

    position.y += 25;
    sprintf(info, "Intelligence: %d", perso->intelligence);
    quantite = TTF_RenderText_Solid(police,  info, colorNoir);
    SDL_BlitSurface(quantite, NULL, ecran, &position);

    position.y += 25;
    sprintf(info, "Agilite: %d", perso->agilite);
    quantite = TTF_RenderText_Solid(police,  info, colorNoir);
    SDL_BlitSurface(quantite, NULL, ecran, &position);

    position.y += 25;
    sprintf(info, "Charisme: %d", perso->charisme);
    quantite = TTF_RenderText_Solid(police,  info, colorNoir);
    SDL_BlitSurface(quantite, NULL, ecran, &position);


    SDL_Flip(ecran);
    SDL_FreeSurface(cadreProfil);
    SDL_FreeSurface(quantite);
    TTF_CloseFont(police);
    TTF_Quit();
}

void affDialogue( char* dialoguetab, SDL_Surface* ecran)
{
    SDL_Surface* cadreDialogue;
    SDL_Surface* texte = NULL;
    SDL_Rect position;
    char* tampon;
    //char * phrase;
    TTF_Init();
    TTF_Font *police = NULL;
    int i=1;
    police = TTF_OpenFont("data/fonts-japanese-gothic.ttf", 15);

    SDL_Color color = { 0, 225, 0};
    tampon=malloc(400*sizeof(char));
    //phrase = malloc(400*sizeof(char));
    cadreDialogue = SDL_CreateRGBSurface(SDL_HWSURFACE, (CARTE_LARGEUR-4)*TILE_LARGEUR, 4*TILE_HAUTEUR, 32, 0, 0, 0, 0);
    position.x = 2*TILE_LARGEUR;
    position.y = (CARTE_HAUTEUR-5)*TILE_HAUTEUR;

    SDL_FillRect(cadreDialogue, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    SDL_BlitSurface(cadreDialogue, NULL, ecran,&position);

    strcpy(tampon, &dialoguetab[0]);
    texte = TTF_RenderText_Solid(police, tampon, color);
    if(texte->w>cadreDialogue->w-10)
    {   strncpy(tampon, dialoguetab, 0);
                tampon[1] = '\0';
                texte = TTF_RenderText_Solid(police, tampon, color);
            while(texte->w<cadreDialogue->w-10 && dialoguetab[i]!='\0')
            {
                strncpy(tampon, dialoguetab, i);
                tampon[i+1] = '\0';
                texte = TTF_RenderText_Solid(police, tampon, color);
                printf("%s \n", tampon);
                i+=2;
            }
//             phrase=(tampon - strrchr(tampon, (int)" "));
//             printf("%s \n", phrase);
    }
    SDL_BlitSurface(texte, NULL, ecran, &position);
    SDL_Flip(ecran);

    SDL_FreeSurface(cadreDialogue);
    SDL_FreeSurface(texte);
    TTF_CloseFont(police);
    TTF_Quit();
}

void affMenuDialogue(char* dialoguetab, int curseur, SDL_Surface* ecran)
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
    police = TTF_OpenFont("data/fonts-japanese-gothic.ttf", 15);

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

void affSoudoyer(char* dialoguetab, int curseur, SDL_Surface* ecran)
{
    int i;
    SDL_Surface* dialogue=NULL;
    SDL_Surface* texte = NULL;
    SDL_Rect position;
    SDL_Color couleur = { 0, 255, 0};
    char menu[3][20]={"10", "50", "100"};

    TTF_Init();
    TTF_Font *police = NULL;
    police = TTF_OpenFont("data/fonts-japanese-gothic.ttf", 15);

    dialogue = SDL_CreateRGBSurface(SDL_HWSURFACE, (CARTE_LARGEUR-4)*TILE_LARGEUR, 4*TILE_HAUTEUR, 32, 0, 0, 0, 0);
    position.x = 2*TILE_LARGEUR;
    position.y = (CARTE_HAUTEUR-5)*TILE_HAUTEUR;

    SDL_FillRect(dialogue, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    SDL_BlitSurface(dialogue, NULL, ecran,&position);

    position.x = 3*TILE_LARGEUR;
    position.y = (CARTE_HAUTEUR-5)*TILE_HAUTEUR;
    texte = TTF_RenderText_Solid(police, "Combien souhaitez-vous donnez?", couleur);
    SDL_BlitSurface(texte, NULL, ecran, &position);

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

    police = TTF_OpenFont("data/fonts-japanese-gothic.ttf", 15);
    position.x = 0;
    position.y = 0;

    inventaire = SDL_CreateRGBSurface(SDL_HWSURFACE, TAILLE_FENETRE, TAILLE_FENETRE, 32, 0, 0, 0, 0);
    SDL_FillRect(inventaire, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
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

    police = TTF_OpenFont("data/fonts-japanese-gothic.ttf", 15);
    position.x = 0;
    position.y = 0;

    inventaire = SDL_CreateRGBSurface(SDL_HWSURFACE, TAILLE_FENETRE, TAILLE_FENETRE, 32, 0, 0, 0, 0);
    SDL_FillRect(inventaire, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
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

void affArmesEqui(Combattant* combattant, int choix, SDL_Surface* ecran)
{
    int i;
    SDL_Surface* cadreArmes;
    SDL_Surface* texte = NULL;
    SDL_Rect position;
    TTF_Init();
    TTF_Font *police = NULL;
    police = TTF_OpenFont("data/fonts-japanese-gothic.ttf", 15);
    SDL_Color colorNoir = { 0 ,255,0};

    cadreArmes = SDL_CreateRGBSurface(SDL_HWSURFACE, (CARTE_LARGEUR-4)*TILE_LARGEUR, 4*TILE_HAUTEUR, 32, 0, 0, 0, 0);
    position.x = 2*TILE_LARGEUR;
    position.y = TAILLE_FENETRE-5*TILE_HAUTEUR;
    SDL_FillRect(cadreArmes, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    SDL_BlitSurface(cadreArmes, NULL, ecran,&position);

    for(i=0;i<=2;i++)
    {
        if(i==choix)
            {
                position.x = 2*TILE_LARGEUR+i*TILE_LARGEUR*3;
                position.y = TAILLE_FENETRE-5*TILE_HAUTEUR;
                texte = TTF_RenderText_Solid(police, "*", colorNoir);
                SDL_BlitSurface(texte, NULL, ecran, &position);
            }
        position.x = 3*TILE_LARGEUR+i*TILE_LARGEUR*3;
        position.y = TAILLE_FENETRE-5*TILE_HAUTEUR;
        SDL_BlitSurface(combattant->perso->equipement.armeDroite[i]->icon, NULL, ecran, &position);
    }

    SDL_Flip(ecran);
    SDL_FreeSurface(cadreArmes);
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
    police = TTF_OpenFont("data/fonts-japanese-gothic.ttf", 15);
    SDL_Surface* texte=NULL;
    SDL_Color couleur = { 0, 255, 0};

    position.x = 0;
    position.y = 0;

    cadreProfil = SDL_CreateRGBSurface(SDL_HWSURFACE, TAILLE_FENETRE, TAILLE_FENETRE, 32, 0, 0, 0, 0);
    SDL_FillRect(cadreProfil, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    SDL_BlitSurface(cadreProfil, NULL, ecran,&position);

    position.x = TAILLE_FENETRE/3;
    position.y = TAILLE_FENETRE/10;
    texte = TTF_RenderText_Solid(police,  "Journal de quetes", couleur);
    SDL_BlitSurface(texte, NULL, ecran,&position);

    position.x=TAILLE_FENETRE/6;
    position.y=TAILLE_FENETRE/6;

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

void affAttaque(int choix, SDL_Surface* ecran)
{
     int i;
    SDL_Surface* cadreAttaque;
    SDL_Surface* texte = NULL;
    SDL_Rect position;
    TTF_Init();
    TTF_Font *police = NULL;
    char attaques[5][20] = {"Attaque brutale", "Attaque prudente", "Attaque visee", "Feinte", "Parade"};
    police = TTF_OpenFont("data/fonts-japanese-gothic.ttf", 15);
    SDL_Color color = { 0 ,255,0};

    cadreAttaque = SDL_CreateRGBSurface(SDL_HWSURFACE, (CARTE_LARGEUR-4)*TILE_LARGEUR, 4*TILE_HAUTEUR, 32, 0, 0, 0, 0);
    position.x = 2*TILE_LARGEUR;
    position.y = TAILLE_FENETRE-5*TILE_HAUTEUR;
    SDL_FillRect(cadreAttaque, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    SDL_BlitSurface(cadreAttaque, NULL, ecran,&position);

    for(i=0;i<=4;i++)
    {
        if(i==choix)
            {
                position.x = 2*TILE_LARGEUR+i*TILE_LARGEUR*3;
                position.y = TAILLE_FENETRE-5*TILE_HAUTEUR;
                texte = TTF_RenderText_Solid(police, "*", color);
                SDL_BlitSurface(texte, NULL, ecran, &position);
            }
        position.x = 3*TILE_LARGEUR+i*TILE_LARGEUR*3;
        position.y = TAILLE_FENETRE-5*TILE_HAUTEUR;
        texte = TTF_RenderText_Solid(police, attaques[i], color);
        SDL_BlitSurface(texte, NULL, ecran, &position);
    }

    SDL_Flip(ecran);
    SDL_FreeSurface(cadreAttaque);
     TTF_CloseFont(police);
    TTF_Quit();
}

void eventAttaqueSDL(Combattant* combattant, Combattant* defenseur, Objet* arme, char arene[TAILLE_MAX][TAILLE_MAX], SDL_Surface* ecran)
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
                    else if(event.key.keysym.sym==SDLK_c)
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
                    else if(event.key.keysym.sym==SDLK_a)
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
                    if(event.button.x>3*TILE_LARGEUR+i*TILE_LARGEUR*3 && event.button.x<4*TILE_LARGEUR+i*TILE_LARGEUR*3 && event.button.y>TAILLE_FENETRE-5*TILE_HAUTEUR && event.button.y<TAILLE_FENETRE-4*TILE_HAUTEUR)
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
    //int continuer =1;
    //SDL_Event event;

    Objet *tabObjets=NULL;

    initialiserTousLesObjets(&tabObjets);

    liste=(Personnage*)malloc(4*sizeof(Personnage));

    liste[0]=*hero;
    liste[1]=*ennemi;
    nouveauPerso (&liste[2], "MechantII", 2, 1, 2, 1, 0, 100, tabObjets);
    nouveauPerso (&liste[3], "Allie", 1, 1, 1, 1, 0, 100, tabObjets);

    areneInit(ter, arene);
    int i, nb=4;
    Combattant* groupe;
    groupe=(Combattant*)malloc(4*sizeof(Combattant));

    initCombat(liste,4,groupe,arene);
    groupe[0].avatar=SDL_LoadBMP("data/Media/humain.bmp");
    groupe[1].avatar=SDL_LoadBMP("data/Media/cyborg.bmp");
    groupe[3].avatar=SDL_LoadBMP("data/Media/humain.bmp");
    groupe[2].avatar=SDL_LoadBMP("data/Media/cyborg.bmp");

    affCombat(ter, groupe,4, arene, ecran);

    while (estLaFin(groupe, nb)==0)
    {
        for (i=0;i<nb;i++)
        {
            if(groupe[i].camp==groupe[0].camp)
            {
                eventTourJoueurSDL( groupe, i, nb, arene, ter, ecran );
                nb=testNbCombattant(groupe,nb,arene);
            }
            else
            {
                printf("Debut du tour IA \n");
                tourIA(groupe,i,nb,arene);
                printf("Fin du tour IA \n");
                nb=testNbCombattant(groupe,nb,arene);
                afficherTab2D(arene);
                printf("Sortie du tour IA \n");
                /*getchar();*/
            }
            affCombat(ter, groupe,4, arene, ecran);
        }
    }
    /*Ajouter expérience fin de combat*/
 /* free (groupe);*/

}

void eventTourJoueurSDL(Combattant* groupe, int i, int nbCombattant, char arene [TAILLE_MAX][TAILLE_MAX], Terrain* ter, SDL_Surface* ecran)
{
    int choix = 0;
    int continuer =1;
    int j;
    SDL_Event event;
    Objet* armeChoisie=NULL;
    int nbDeplacement = 5;

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
                                nbDeplacement = deplaceCombDroite(groupe, nbDeplacement, arene);
                            }
                            else if(event.key.keysym.sym==SDLK_LEFT)    /** Deplacement vers la gauche*/
                            {
                                nbDeplacement = deplaceCombGauche(groupe, nbDeplacement, arene);
                            }
                            else if(event.key.keysym.sym==SDLK_DOWN)    /** Deplacement vers le bas*/
                            {
                                nbDeplacement = deplaceCombBas(groupe, nbDeplacement, arene);
                            }
                            else if(event.key.keysym.sym==SDLK_UP)  /** Déplacement vers le haut */
                            {
                                nbDeplacement = deplaceCombHaut( groupe, nbDeplacement, arene);
                            }
                            else if(event.key.keysym.sym==SDLK_a)
                            {
                                choix=eventArmesEquiSDL(&groupe[i], choix, ecran);
                                armeChoisie = getEquiMainDroite(&groupe[i].perso->equipement, choix);
                            }
                            else if(event.key.keysym.sym==SDLK_c)
                            {
                                for(j=0; j<nbCombattant; j++)
                                {
                                    if(groupe[i].camp != groupe[j].camp)
                                    {
                                        printf("%s! \n", groupe[j].perso->nom);
                                        if(estAPortee (arene ,&groupe[i], &groupe[j], armeChoisie->portee))
                                        {
                                            printf("Attaque! \n");
                                            eventAttaqueSDL(&groupe[i], &groupe[j], armeChoisie, arene, ecran);
                                            continuer=0;
                                        }
                                    }
                                }
                            }
                            affCombat(ter, groupe, 4, arene, ecran);
                        }
                    }
                        default:
                        break;
                    }
                }
}

void eventJeuSDL(Personnage* hero, Personnage* pnjs, Personnage* ennemis, Mission* mission, Terrain* ter, Dialogue* dialogue, SDL_Surface* ecran)
{
    int continuer = 1;
    SDL_Event event;
    char* reponse;
    reponse=malloc(400*sizeof(char));
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
                            if(testMissionParlerA(mission, pnjs))
                            {   parlerQuete(dialogue, reponse);
                                affDialogue( reponse, ecran);
                                while (continuer)
                                {
                                    SDL_WaitEvent(&event);
                                    switch(event.type)
                                    {case SDL_KEYDOWN:
                                        { if(event.key.state==SDL_PRESSED)
                                            {if(event.key.keysym.sym==SDLK_e)
                                                {continuer=0;
                                                }}}}
                                }
                            }
                            eventDialogueSDL(dialogue, hero, pnjs, ennemis, reponse, ter, ecran);
                        }
                        if( ((hero->posX+TILE_LARGEUR)==ennemis->posX && hero->posY==ennemis->posY)
                           || ((hero->posX-TILE_LARGEUR)==ennemis->posX && hero->posY==ennemis->posY)
                           || ((hero->posY+TILE_HAUTEUR)==ennemis->posY && hero->posX==ennemis->posX)
                           || ((hero->posY-TILE_HAUTEUR)==ennemis->posY && hero->posX==ennemis->posX))
                        {
                            printf("Plop \n");
                            eventCombatSDL(hero, ennemis, ter, ecran);
                            printf("Plop? \n");
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
                    affPerso(hero, pnjs, ennemis, ecran);
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
                    if(event.button.x>2*TILE_LARGEUR && event.button.x<(TAILLE_FENETRE-5*TILE_LARGEUR) && event.button.y>3*TILE_HAUTEUR && event.button.y<(TAILLE_FENETRE-TILE_HAUTEUR)
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
}

void eventAcheterSDL(Dialogue* dialogue, char* reponse, SDL_Surface* ecran)
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
                    affDialogue(reponse, ecran);
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
                        acheter(dialogue, objet, reponse);
                        affAcheter(dialogue, objet, ecran);
                        affDialogue(reponse, ecran);
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
                        acheter(dialogue, objet, reponse);
                        affAcheter(dialogue, objet, ecran);
                        affDialogue(reponse, ecran);

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
                    affDialogue(reponse, ecran);
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
                        affDialogue(reponse, ecran);
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
                        affDialogue(reponse, ecran);
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

void eventSoudoyerSDL( Dialogue* dialogue, char* rep, SDL_Surface* ecran)
{
    int continuer= 1;
    int curseur=0;
    SDL_Event event;
    affSoudoyer(rep, curseur, ecran);
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
                    else if(event.key.keysym.sym==SDLK_e)
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
                   affSoudoyer(rep, curseur, ecran);
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

void eventDialogueSDL( Dialogue* dialogue, const Personnage* hero, const Personnage* pnjs, const Personnage* ennemis, char reponse[400], Terrain* ter, SDL_Surface*ecran)
{   int continuer = 1;
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
                    if(event.key.keysym.sym==SDLK_RETURN)
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
                    else if(event.key.keysym.sym==SDLK_e)
                    {
                        switch(curseur)
                        {
                            case 0: obtenirInfo(dialogue, reponse);
                                    affDialogue( reponse, ecran);
                                    while (continuer)
                                    {
                                        SDL_WaitEvent(&event);
                                        switch(event.type)
                                        {case SDL_KEYDOWN:
                                            { if(event.key.state==SDL_PRESSED)
                                                {if(event.key.keysym.sym==SDLK_e)
                                                    {continuer=0;
                                                    }}}}
                                    }
                            break;

                            case 1: eventSoudoyerSDL( dialogue, reponse, ecran);
                                    affDialogue( reponse, ecran);
                                    while (continuer)
                                    {
                                        SDL_WaitEvent(&event);
                                        switch(event.type)
                                        {case SDL_KEYDOWN:
                                            { if(event.key.state==SDL_PRESSED)
                                                {if(event.key.keysym.sym==SDLK_e)
                                                    {continuer=0;
                                                    }}}}
                                    }
                                break;

                                case 2: menacer( dialogue, reponse);
                                        affDialogue( reponse, ecran);
                                        while (continuer)
                                        {
                                            SDL_WaitEvent(&event);
                                            switch(event.type)
                                            {case SDL_KEYDOWN:
                                                { if(event.key.state==SDL_PRESSED)
                                                    {if(event.key.keysym.sym==SDLK_e)
                                                        {continuer=0;
                                                        }}}}
                                        }
                                break;

                                case 3: seduire( dialogue, reponse);
                                        affDialogue( reponse, ecran);
                                         while (continuer)
                                        {
                                            SDL_WaitEvent(&event);
                                            switch(event.type)
                                            {case SDL_KEYDOWN:
                                                { if(event.key.state==SDL_PRESSED)
                                                    {if(event.key.keysym.sym==SDLK_e)
                                                        {continuer=0;
                                                        }}}}
                                        }
                                break;

                                case 4: eventAcheterSDL(dialogue, reponse, ecran);
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
