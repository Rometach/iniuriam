#include "deplacement.h"


/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

void copieTab2D (char tab[TAILLE_MAX][TAILLE_MAX], char tab2 [TAILLE_MAX][TAILLE_MAX])
{
    int i,j;
    for (i=0;i<TAILLE_MAX;i++)
    {
        for (j=0;j<TAILLE_MAX;j++)
        {
            tab2[i][j]=tab[i][j];
        }
    }
}

char estDifferentTab2D (char tab1 [TAILLE_MAX][TAILLE_MAX],char tab2 [TAILLE_MAX][TAILLE_MAX])
{
    int i,j;
    for (i=0;i<TAILLE_MAX;i++)
    {
        for(j=0;j<TAILLE_MAX;j++)
        {
            if (tab1[i][j]!=tab2[i][j]) return 1;
        }
    }
    return 0;
}

char deplacerCase (int y, char tab [TAILLE_MAX])
{
    if (tab [y]==0||tab [y]==2||tab[y]>=7||tab[y]==4) return 0;
    /*La case est occupée si il y a un perso dessus ou si il s'agit d'un mur,
     ou d'une case qui empêche le retour du personnage ou encore d'un chemin déjà emprunté par l'IA*/
    else return 1;
}

char testRetour (int x, char tab [TAILLE_MAX])
{
    if ((tab[x-1]>=7&&tab[x-2]>=7)||(tab[x+1]>=7&&tab[x+2]>=7)) return 0;
    /*Vérifie si les cases qui entoure la case cible sont des cases empêchant le retour de l'IA*/
    else return 1;
}

void getColonne(int col, char tab[TAILLE_MAX][TAILLE_MAX], char*tamp)
{
    int i;
    for(i=0;i<TAILLE_MAX; i++)
    {
        tamp[i] = tab[i][col];
    }
}

char min (char a, char b)
{
    if (a-b>0) return b;
    else return a;
}

char max (char a, char b)
{
    if (a-b<0) return b;
    else return a;
}

void afficherTab2D (char tab[TAILLE_MAX][TAILLE_MAX])
{
    int i,j;
    for (i=0;i<TAILLE_MAX;i++)
    {
        for (j=0;j<TAILLE_MAX;j++)
        {
            printf("%d",tab[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

char chercher2 (char tab[TAILLE_MAX][TAILLE_MAX],int x, int y,char i)
{
    if (tab[x][y-1]==3) return 1; /* 2 à gauche*/
    else if (tab[x-1][y]==3) return 2; /*2 en haut*/
    else if (tab[x+1][y]==3) return 3;/*2 en bas*/
    else if (tab[x][y+1]==3) return 4;/*2 à droite*/
    else
    {
        switch (i)
        {
            case 1: /*Perso venant de la droite*/
                if (tab[x][y-1]==2) return 1;
                else if (tab[x-1][y]==2) return 2;
                else if(tab[x+1][y]==2) return 3;
                break;
            case 2: /*Perso venant du bas*/
                 if (tab[x-1][y]==2) return 2;
                 else if (tab[x][y+1]==2) return 4;
                 else if (tab[x][y-1]==2) return 1;
                 break;
            case 3:/*Perso venant du haut*/
                if (tab[x+1][y]==2) return 3;
                else if (tab[x][y+1]==2) return 4;
                else if (tab[x][y-1]==2) return 1;
                break;
            case 4:/*Perso venant de la gauche*/
                if (tab[x][y+1]==2) return 4;
                    else if (tab[x-1][y]==2) return 2;
                    else if (tab[x+1][y]==2) return 3;
            default:
                if (tab[x][y-1]==2) return 1;
                else if (tab[x-1][y]==2) return 2;
                else if(tab[x+1][y]==2) return 3;
                else if (tab[x][y+1]==2) return 4;
                break;
        }
    }
    return 0;
}

void tunnel (int x, int y, char tab [TAILLE_MAX][TAILLE_MAX], int i)
{
    char tamp [TAILLE_MAX];
    getColonne(y, tab,tamp);
    switch (i)
    {
        case 0:/*Déplacement en bas*/
            if (deplacerCase(y-1,tab[x])!=0&&tab [x][y-1]!=3) tab [x][y-1]=7;
            else if (tab [x][y-1]==7) tab[x][y-1]=9;

            if (deplacerCase(y+1,tab[x])!=0&&tab[x][y+1]!=3) tab[x][y+1]=7;
            else if (tab[x][y+1]==7) tab[x][y+1]=9;

            if (deplacerCase(x-1,tamp)!=0&&tab[x-1][y]!=3) tab[x-1][y]=7;
            else if (tab[x-1][y]==7) tab[x-1][y]=9;

            /*Bloque les cases à droite, à gauche et en haut du perso si elles sont accèssibles pour empêcher un retour en arrière*/
            break;
        case 1:/*Déplacement à droite*/
            if (deplacerCase(y-1,tab[x])!=0&&tab [x][y-1]!=3) tab [x][y-1]=7;
            else if (tab [x][y-1]==7) tab[x][y-1]=9;

            if (deplacerCase(x-1,tamp)!=0&&tab[x-1][y]!=3) tab[x-1][y]=7;
            else if (tab[x-1][y]==7) tab[x-1][y]=9;

            if (deplacerCase(x+1,tamp)!=0&&tab[x+1][y]!=3) tab[x+1][y]=7;
            else if (tab[x+1][y]==7) tab[x+1][y]=9;

            /*Bloque les cases à gauche, en haut et en bas du perso si elles sont accèssibles pour empêcher un retour en arrière*/
            break;
        case 2:/*Déplacement en haut*/
            if (deplacerCase(y-1,tab[x])!=0&&tab [x][y-1]!=3) tab [x][y-1]=7;
            else if (tab [x][y-1]==7) tab[x][y-1]=9;

            if (deplacerCase(y+1,tab[x])!=0&&tab[x][y+1]!=3) tab[x][y+1]=7;
            else if (tab[x][y+1]==7) tab[x][y+1]=9;

            if (deplacerCase(x+1,tamp)!=0&&tab[x+1][y]!=3) tab[x+1][y]=7;
            else if (tab[x+1][y]==7) tab[x+1][y]=9;

            /*Bloque les cases à droite, à gauche et en bas du perso si elles sont accèssibles pour empêcher un retour en arrière*/
            break;
        case 3:/*Déplacement à gauche*/
            if (deplacerCase(y+1,tab[x])!=0&&tab[x][y+1]!=3) tab[x][y+1]=7;
            else if (tab[x][y+1]==7) tab[x][y+1]=9;

            if (deplacerCase(x-1,tamp)!=0&&tab[x-1][y]!=3) tab[x-1][y]=7;
            else if (tab[x-1][y]==7) tab[x-1][y]=9;

            if (deplacerCase(x+1,tamp)!=0&&tab[x+1][y]!=3) tab[x+1][y]=7;
            else if (tab[x+1][y]==7) tab[x+1][y]=9;

            /*Bloque les cases à droite, en haut et en bas du perso si elles sont accèssibles pour empêcher un retour en arrière*/
            break;
        default: break;
    }
}

void reinitTunnel (int x, int y, char tab [TAILLE_MAX][TAILLE_MAX])
{
    if (tab[x-1][y]==7)tab[x-1][y]=1;
    else if (tab[x-1][y]==9)tab[x-1][y]=7;

    if (tab[x+1][y]==7)tab[x+1][y]=1;
    else if (tab[x+1][y]==9)tab[x+1][y]=7;

    if (tab[x][y-1]==7)tab[x][y-1]=1;
    else if (tab[x][y-1]==9)tab[x][y-1]=7;

    if (tab[x][y+1]==7)tab[x][y+1]=1;
    else if (tab[x][y+1]==9)tab[x][y+1]=7;
}

char quatresChemins (char droite, char haut, char bas, char gauche)
{
    char i=0,j=0;

    if ((gauche==0)&&(droite==0)&&(haut==0)&&(bas==0)) return 0;
    else if ((gauche==0)&&(bas==0)&&(haut==0)) return 1;
    else if ((gauche==0)&&(droite==0)&&(bas==0)) return 2;
    else if ((gauche==0)&&(droite==0)&&(haut==0)) return 3;
    else if ((droite==0)&&(haut==0)&&(bas==0)) return 4;
    else if ((bas==0)&&(gauche==0))
    {
        if (droite==min(droite,haut)) return 1;
        else return 2;
    }
    else if ((gauche==0)&&(haut==0))
    {
        if (droite==min(droite,bas)) return 1;
        else return 3;
    }
    else if ((bas==0)&&(haut==0))
    {
        if (droite==min(droite,gauche)) return 1;
        else return 4;
    }
    else if ((droite==0)&&(gauche==0))
    {
        if (haut==min(haut,bas)) return 2;
        else return 3;
    }
    else if ((droite==0)&&(bas==0))
    {
        if (haut==min(haut,gauche)) return 2;
        else return 4;
    }
    else if ((droite==0)&&(haut==0))
    {
        if (bas==min(bas,gauche)) return 3;
        else return 4;
    }
    else if (gauche==0)
    {
        i=min (droite,haut);
        i=min (i,bas);
        if (i==droite)return droite;
        else if (i==haut) return haut;
        else return bas;
    }
    else if (bas==0)
    {
        i=min (droite,haut);
        i=min (i,gauche);
        if (i==droite)return droite;
        else if (i==haut) return haut;
        else return gauche;
    }
    else if (haut==0)
    {
        i=min (droite,bas);
        i=min (i,gauche);
        if (i==droite)return droite;
        else if (i==bas) return bas;
        else return gauche;
    }
    else if (droite==0)
    {
        i= min (bas,haut);
        i=min (bas,gauche);
        if (i==bas)return bas;
        else if (i==haut) return haut;
        else return gauche;
    }
    else
    {
        i=min(droite,haut);
        j=min(bas,gauche);
        i=min (i, j);
        if (i==j)
        {
            if (j==bas)return bas;
            else return gauche;
        }
        else
        {
            if (i==droite) return droite;
            else return haut;
        }
    }
    return 0;
}

char deplacementIA (int x, int y, int z, int t, char tab [TAILLE_MAX][TAILLE_MAX])
{
    char tamp [TAILLE_MAX], droite=0, gauche=0, haut=0, bas=0;
    getColonne(y,tab,tamp);
    int i=1,j=1;
    if (y>t) j=-1;
    else if (y==t) j=0;
    if (x>z)i=-1;
    else if (x==z) i=0;
    tab[x][y]=8;

    /*Les 2 lignes suivantes permettent de visualiser les effets de la fonction au pas à pas.*/
    /*afficherTab2D(tab);
    getchar();*/
    /*Appuyez sur entrée pour faire progresser la fonction*/

    if((j==0)&&(i==0)) /*Vous êtes arrivé à destination*/
    {
        tab[x][y]=3;
        return 1;
    }
    else if ((j!=0)&&(deplacerCase(y+j,tab[x])!=0)) /*test de déplacement à droite/gauche de l'IA en fonction de j*/
    {
        tunnel (x,y,tab,(j+4)%4);
        droite=deplacementIA (x,y+j,z,t,tab);
        reinitTunnel(x,y,tab);
        if (droite==1)
        {
            tab[x][y]=2;
            return 2;
        }

        if (deplacerCase(x+i,tamp)!=0) /*test de déplacement en bas/haut de l'IA en fonction de i*/
        {
            tunnel (x,y,tab,(i+3)%4);
            bas=deplacementIA(x+i,y,z,t,tab);
            reinitTunnel(x,y,tab);
        }

        if (deplacerCase(x-i,tamp)!=0&&(testRetour(y,tab[x-i])!=0)) /*test de déplacement en haut/bas de l'IA en fonction de i*/
        {
            tunnel (x,y,tab,(-i+3)%4);
            haut=deplacementIA(x-i,y,z,t,tab);
            reinitTunnel(x,y,tab);
        }

        getColonne(y-j,tab,tamp);
        if ((deplacerCase(y-j,tab[x])!=0)&&(testRetour(x,tamp)!=0)) /*test de déplacement à gauche/droite de l'IA en fonction de j*/
        {
            tunnel (x,y,tab,(-j+4)%4);
            gauche=deplacementIA(x,y-j,z,t,tab);
            reinitTunnel(x,y,tab);
        }
        switch (quatresChemins(droite,bas,haut,gauche))
        {
            case 1: tab[x][y]=2;
                    return 1+droite;
                    break;
            case 2: tab[x][y]=2;
                    return 1+bas;
                    break;
            case 3: tab[x][y]=2;
                    return 1+haut;
                    break;
            case 4: tab[x][y]=2;
                    return 1+gauche;
                    break;
            default: tab[x][y]=0;
                    return 0;
                    break;
        }
    }
    else if (j==0) /*L'IA est aligné avec la colonne de la destination*/
    {
        if (deplacerCase(x+i,tamp)!=0) /*test de déplacement en bas/haut de l'IA en fonction de i*/
        {
            tunnel (x,y,tab,(i+3)%4);
            bas=deplacementIA(x+i,y,z,t,tab);
            reinitTunnel(x,y,tab);
            if (bas==1)
            {
                tab[x][y]=2;
                return 2;
            }
        }

        if (deplacerCase(y+1,tab[x])!=0) /*test de déplacement à droite de l'IA*/
        {
            tunnel (x,y,tab,1);
            droite=deplacementIA (x,y+1,z,t,tab);
            reinitTunnel(x,y,tab);
        }

        if (deplacerCase(x-i,tamp)!=0&&(testRetour(y,tab[x-i])!=0)) /*test de déplacement en haut/bas de l'IA en fonction de i*/
        {
            tunnel (x,y,tab,(-i+3)%4);
            haut=deplacementIA(x-i,y,z,t,tab);
            reinitTunnel(x,y,tab);
        }

        getColonne(y-1,tab,tamp);
        if ((deplacerCase(y-1,tab[x])!=0)&&(testRetour(x,tamp)!=0)) /*test de déplacement à gauche de l'IA*/
        {
            tunnel (x,y,tab,3);
            gauche=deplacementIA(x,y-1,z,t,tab);
            reinitTunnel(x,y,tab);
        }
        switch (quatresChemins(bas,droite,haut,gauche))
        {
            case 1: tab[x][y]=2;
                    return 1+bas;
                    break;
            case 2: tab[x][y]=2;
                    return 1+droite;
                    break;
            case 3: tab[x][y]=2;
                    return 1+haut;
                    break;
            case 4: tab[x][y]=2;
                    return 1+gauche;
                    break;
            default: tab[x][y]=0;
                    return 0;
                    break;
        }
    }
    else /*L'IA est alignée par rapport à l'axe des X ou le déplacement vers la case suivante est impossible*/
    {
        if (i==0) i=1;
        if (deplacerCase(x+i,tamp)!=0&&(testRetour(y,tab[x+i])!=0)) /*test de déplacement à droite de l'IA*/
        {
            tunnel (x,y,tab,(i+3)%4);
            bas=deplacementIA(x+i,y,z,t,tab);
            reinitTunnel(x,y,tab);
        }

        if ((deplacerCase(x-i,tamp)!=0)&&(testRetour(y,tab[x-i])!=0)) /*test de déplacement à gauche de l'IA*/
        {
            tunnel (x,y,tab,(-i+3)%4);
            haut=deplacementIA(x-i,y,z,t,tab);
            reinitTunnel(x,y,tab);
        }

        getColonne(y-j,tab,tamp);
        if (deplacerCase(y-j,tab[x])!=0&&(testRetour(x,tamp)!=0)) /*test de déplacement en haut/bas de l'IA en fonction de i*/
        {
            tunnel (x,y,tab,(-j+4)%4);
            gauche=deplacementIA(x,y-j,z,t,tab);
            reinitTunnel(x,y,tab);
        }
        switch (quatresChemins(bas,haut, gauche,0))
        {
            case 1: tab[x][y]=2;
                    return 1+bas;
                    break;
            case 2: tab[x][y]=2;
                    return 1+haut;
                    break;
            case 3: tab[x][y]=2;
                    return 1+gauche;
                    break;
            default: tab[x][y]=0;
                    return 0;
                    break;
        }
    }
    return 0;
}

char chemin (int x,int y, int z, int t, char tab[TAILLE_MAX][TAILLE_MAX])
{
    char tab2 [TAILLE_MAX][TAILLE_MAX];
    int i,j,n;

        tab[x][y]=3;
        tab[z][t]=3;
        /*Positionne l'arrivée et le départ*/

        copieTab2D(tab,tab2);
        i=deplacementIA(x,y,z,t,tab2);
        n=i;
        /*Affiche la distance parcourue*/
        /*printf("%d\n",i);*/

        j=0;
        while (i>1) /*rajoute le chemin découvert sur le terrain de départ*/
        {
            j=chercher2(tab2,x,y,j);
            switch (j)
            {
                case (1):tab[x][y-1]=2;
                y--;
                break;
                case (2):tab[x-1][y]=2;
                x--;
                break;
                case (3):tab[x+1][y]=2;
                x++;
                break;
                case (4):tab[x][y+1]=2;
                y++;
                break;
                default: break;
            }
            i--;
        }
    return n;
}
int seRapprocher(char tab[TAILLE_MAX][TAILLE_MAX], int a, int b, int nb,char* orientation)
{
    int i=nb,j=0,x=a,y=b;
    while (i>0)
    {
        tab[x][y]=1;
        j=chercher2(tab,x,y,j);
        switch (j)
        {
            case 1:
                y--;
            break;
            case 2:
                x--;
            break;
            case 3:
                x++;
            break;
            case 4:
                y++;
            break;
            default:
                tab[x][y]=4;
                return 0;
            break;
        }
        i--;
    }
    tab[x][y]=4;
    *orientation=chercher2(tab,x,y,j); /*Oriente l'IA vers la case suivante*/
    return x*TAILLE_MAX+y;
}

int sEloigner(char tab[TAILLE_MAX][TAILLE_MAX], int a, int b, int nb, char* orientation)
{
    int i=nb,j=0,x=a,y=b;
    while (i>0)
    {
        switch (chercher2(tab,x,y,j))
        {
            case 1:
                if (deplacerCase(y+1,tab[x]))
                {
                    j=4;
                    tab[x][y]=2;
                    y++;
                }
                else
                {
                    tab[x][y]=4;
                    return 0;
                }
            break;
            case 2:
                if (deplacerCase(y,tab[x+1]))
                {
                    j=3;
                    tab[x][y]=2;
                    x++;
                }
                else
                {
                    tab[x][y]=4;
                    return 0;
                }
            break;
            case 3:
                if (deplacerCase(y,tab[x-1]))
                {
                    j=2;
                    tab[x][y]=2;
                    x--;
                }
                else
                {
                    tab[x][y]=4;
                    return 0;
                }
            break;
            case 4:
                if (deplacerCase(y-1,tab[x]))
                {
                    j=1;
                    tab[x][y]=2;
                    y--;
                }
                else
                {
                    tab[x][y]=4;
                    return 0;
                }
            break;
            default:
                tab[x][y]=4;
                return 0;
            break;
        }
        tab[x][y]=2;
        i--;
    }
    return x*TAILLE_MAX+y;
}

int mainDeplacement ()
{
    char tab [TAILLE_MAX][TAILLE_MAX], ligne [TAILLE_MAX+2];
    FILE* fTerr=fopen("data/Terrains.txt", "r");
    int i,j;
    int type=2;
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
                tab[i][j]=ligne[j]-'0';
            }
        }
        fclose (fTerr);
        afficherTab2D(tab);
        printf("\n\n");
        chemin (1,1,15,17,tab);
        afficherTab2D(tab);
    }
    else printf ("\nImpossible d'ouvrir le fichier Terrains.txt\n");

    return 0;
}
