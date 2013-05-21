#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"
#include "constante.h"

char eventScanf (SDL_Surface* ecran,char chiffre)
{
    char continuer=1, shift=0;
    char caractere=0;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
            case SDL_KEYDOWN:
                if (SDL_GetModState() & (KMOD_SHIFT|KMOD_CAPS))
                {
                    shift=1;
                }
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        caractere=1;
                        continuer=0;
                    break;
                    case SDLK_BACKSPACE:
                        caractere=2;
                        continuer=0;
                    break;
                    case SDLK_RETURN:
                        caractere=3;
                        continuer=0;
                    break;
                    case SDLK_KP_ENTER:
                        caractere=3;
                        continuer=0;
                    break;
                    case SDLK_SPACE:
                        caractere=' ';
                        continuer=0;
                    break;
                    case SDLK_KP0:
                        caractere='0';
                        continuer=0;
                    break;
                    case SDLK_KP1:
                        caractere='1';
                        continuer=0;
                    break;
                    case SDLK_KP2:
                        caractere='2';
                        continuer=0;
                    break;
                    case SDLK_KP3:
                        caractere='3';
                        continuer=0;
                    break;
                    case SDLK_KP4:
                        caractere='4';
                        continuer=0;
                    break;
                    case SDLK_KP5:
                        caractere='5';
                        continuer=0;
                    break;
                    case SDLK_KP6:
                        caractere='6';
                        continuer=0;
                    break;
                    case SDLK_KP7:
                        caractere='7';
                        continuer=0;
                    break;
                    case SDLK_KP8:
                        caractere='8';
                        continuer=0;
                    break;
                    case SDLK_KP9:
                        caractere='9';
                        continuer=0;
                    break;
                    case SDLK_a:
                        if (shift) caractere='A';
                        else caractere='a';
                        continuer=0;
                    break;
                    case SDLK_b:
                        if (shift) caractere='B';
                        else caractere='b';
                        continuer=0;
                    break;
                    case SDLK_c:
                        if (shift) caractere='C';
                        else caractere='c';
                        continuer=0;
                    break;
                    case SDLK_d:
                        if (shift) caractere='D';
                        else caractere='d';
                        continuer=0;
                    break;
                    case SDLK_e:
                        if (shift) caractere='E';
                        else caractere='e';
                        continuer=0;
                    break;
                    case SDLK_f:
                        if (shift) caractere='F';
                        else caractere='f';
                        continuer=0;
                    break;
                    case SDLK_g:
                        if (shift) caractere='G';
                        else caractere='g';
                        continuer=0;
                    break;
                    case SDLK_h:
                        if (shift) caractere='H';
                        else caractere='h';
                        continuer=0;
                    break;
                    case SDLK_i:
                        if (shift) caractere='I';
                        else caractere='i';
                        continuer=0;
                    break;
                    case SDLK_j:
                        if (shift) caractere='J';
                        else caractere='j';
                        continuer=0;
                    break;
                    case SDLK_k:
                        if (shift) caractere='K';
                        else caractere='k';
                        continuer=0;
                    break;
                    case SDLK_l:
                        if (shift) caractere='L';
                        else caractere='l';
                        continuer=0;
                    break;
                    case SDLK_m:
                        if (shift) caractere='M';
                        else caractere='m';
                        continuer=0;
                    break;
                    case SDLK_n:
                        if (shift) caractere='N';
                        else caractere='n';
                        continuer=0;
                    break;
                    case SDLK_o:
                        if (shift) caractere='O';
                        else caractere='o';
                        continuer=0;
                    break;
                    case SDLK_p:
                        if (shift) caractere='P';
                        else caractere='p';
                        continuer=0;
                    break;
                    case SDLK_q:
                        if (shift) caractere='Q';
                        else caractere='q';
                        continuer=0;
                    break;
                    case SDLK_r:
                        if (shift) caractere='R';
                        else caractere='r';
                        continuer=0;
                    break;
                    case SDLK_s:
                        if (shift) caractere='S';
                        else caractere='s';
                        continuer=0;
                    break;
                    case SDLK_t:
                        if (shift) caractere='T';
                        else caractere='t';
                        continuer=0;
                    break;
                    case SDLK_u:
                        if (shift) caractere='U';
                        else caractere='u';
                        continuer=0;
                    break;
                    case SDLK_v:
                        if (shift) caractere='V';
                        else caractere='v';
                        continuer=0;
                    break;
                    case SDLK_w:
                        if (shift) caractere='W';
                        else caractere='w';
                        continuer=0;
                    break;
                    case SDLK_x:
                        if (shift) caractere='X';
                        else caractere='x';
                        continuer=0;
                    break;
                    case SDLK_y:
                        if (shift) caractere='Y';
                        else caractere='y';
                        continuer=0;
                    break;
                    case SDLK_z:
                        if (shift) caractere='Z';
                        else caractere='z';
                        continuer=0;
                    break;

                    case SDLK_AMPERSAND:
                        if (shift) caractere='1';
                        else caractere='&';
                        continuer=0;
                    break;
                    case SDLK_WORLD_73:
                        if (shift) caractere='2';
                        else caractere='e';
                        continuer=0;
                    break;
                    case SDLK_QUOTEDBL:
                        if (shift) caractere='3';
                        else caractere='"';
                        continuer=0;
                    break;
                    case SDLK_QUOTE:
                        if (shift) caractere='4';
                        else caractere='\'';
                        continuer=0;
                    break;
                    case SDLK_LEFTPAREN:
                        if (shift) caractere='5';
                        else caractere='(';
                        continuer=0;
                    break;
                    case SDLK_MINUS:
                        if (shift) caractere='6';
                        else caractere='-';
                        continuer=0;
                    break;
                    case SDLK_WORLD_72:
                        if (shift) caractere='7';
                        else caractere='e';
                        continuer=0;
                    break;
                    case SDLK_UNDERSCORE:
                        if (shift) caractere='8';
                        else caractere='_';
                        continuer=0;
                    break;
                    case SDLK_WORLD_71:
                        if (shift) caractere='9';
                        else caractere='c';
                        continuer=0;
                    break;
                    case SDLK_WORLD_64:
                        if (shift) caractere='0';
                        else caractere='a';
                        continuer=0;
                    break;
                    case SDLK_RIGHTPAREN:
                        if (shift) caractere=' ';
                        else caractere=')';
                        continuer=0;
                    break;
                    case SDLK_EQUALS:
                        if (shift) caractere='+';
                        else caractere='=';
                        continuer=0;
                    break;
                    case SDLK_KP_MULTIPLY:
                        caractere='*';
                        continuer=0;
                    break;
                    case SDLK_KP_MINUS:
                        caractere='-';
                        continuer=0;
                    break;
                    case SDLK_KP_PLUS:
                        caractere='+';
                        continuer=0;
                    break;
                    case SDLK_KP_EQUALS:
                        caractere='=';
                        continuer=0;
                    break;
                    case SDLK_KP_PERIOD:
                        caractere='.';
                        continuer=0;
                    break;
                    case SDLK_COMMA:
                        if (shift) caractere='?';
                        else caractere=',';
                        continuer=0;
                    break;
                    case SDLK_SEMICOLON:
                        if (shift) caractere='.';
                        else caractere=';';
                        continuer=0;
                    break;
                    case SDLK_COLON:
                        caractere=':';
                        continuer=0;
                    break;
                    case SDLK_EXCLAIM:
                        caractere='!';
                        continuer=0;
                    break;
                    case SDLK_LESS:
                        if (shift) caractere='>';
                        else caractere='<';
                        continuer=0;
                    break;
                    default:
                    break;
                }
            break;
            case SDL_QUIT:
                continuer=0;
                caractere=0;
            break;
            default:
            break;
        }
        if (chiffre)
        {
            if ((caractere>3)&&(caractere>'9'||caractere<'0')) continuer=1;
        }
    }
    return caractere;
}

void scanfSDL (char* string,SDL_Surface* ecran, int longueur, char * action,TTF_Font *police,char chiffre)
{
    char continuer=1;
    char caractere[2];
    int i=0;
    SDL_Surface *texte=NULL,*rectangle;
    SDL_Rect position,position_rect;
    SDL_Color couleur_texte= {255, 255, 255},couleur_rect= {10, 10, 10};

    caractere[1]='\0';
    strcpy(string,"");

    position.x=TAILLE_FENETRE/2-250;
    position.y=TAILLE_FENETRE/3+150;

    position_rect.x=TAILLE_FENETRE/2-250;
    position_rect.y=TAILLE_FENETRE/3+150;

    while (continuer)
    {
        caractere[0]=eventScanf(ecran,chiffre);
        switch (caractere[0])
        {
            case 0: /*SDL_QUIT*/
                *action=0;
                continuer=0;
            break;
            case 1:/*Echap*/
                *action=1;
                continuer=0;
            break;
            case 2:/*Retour arrière*/
                if (i>0)
                {
                    i--;

                    rectangle= SDL_CreateRGBSurface(SDL_HWSURFACE, 500, 50, 32, 0, 0, 0, 0);
                    SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 10, 10, 10));
                    SDL_BlitSurface(rectangle, NULL, ecran, &position_rect);
                    SDL_FreeSurface(rectangle);

                    string[i]='\0';
                    texte=TTF_RenderText_Shaded(police, string, couleur_texte,couleur_rect);
                    SDL_BlitSurface(texte, NULL, ecran, &position);
                    SDL_FreeSurface(texte);
                    SDL_Flip(ecran);
                }
            break;
            case 3:/*Entrée*/
                *action=2;
                continuer=0;
            break;
            default:
                if (i<longueur)
                {
                    i++;

                    rectangle= SDL_CreateRGBSurface(SDL_HWSURFACE, 500, 50, 32, 0, 0, 0, 0);
                    SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 10, 10, 10));
                    SDL_BlitSurface(rectangle, NULL, ecran, &position_rect);
                    SDL_FreeSurface(rectangle);

                    strcat (string,caractere);
                    texte=TTF_RenderText_Shaded(police, string, couleur_texte,couleur_rect);
                    SDL_BlitSurface(texte, NULL, ecran, &position);
                    SDL_FreeSurface(texte);
                    SDL_Flip(ecran);
                }
            break;
        }
    }
}
