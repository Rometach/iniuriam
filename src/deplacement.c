#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


#define TAILLE_MAX 22

char deplacerCase (int y, char tab [TAILLE_MAX])
{
    if (tab [y]==0||tab[y]==2||tab[y]>=7) return 0;
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
}

/*char chercher8 (char tab[TAILLE_MAX][TAILLE_MAX],int x, int y)
{
    if (tab[x][y-1]==8) return 1;
    else if (tab[x-1][y]==8) return 2;
    else if (tab[x+1][y]==8) return 3;
    else if (tab[x][y+1]==8) return 4;
    else return 0;
}*/

void tunnel (int x, int y, char tab [TAILLE_MAX][TAILLE_MAX], int i)
{
    char tamp [TAILLE_MAX];
    getColonne(y, tab,tamp);
    switch (i)
    {
        case 0:/*Déplacement en bas*/
            if ((tab[x][y-1]!=0)&&(tab[x][y-1]!=2)) tab [x][y-1]=7;
            else
            {
                if ((tab[x-1][y-1]==9)&&(tab[x][y-2]==1)) tab[x][y-1]=9;
            }
            if (deplacerCase(y+1,tab[x])!=0) tab[x][y+1]=7;
            else
            {
                if ((tab[x-1][y+1]==9)&&(tab[x][y+2]==1)) tab[x][y+1]=9;
            }
            if (deplacerCase(x-1,tamp)!=0) tab[x-1][y]=7;
            break;
        case 1:/*Déplacement à droite*/
            if (deplacerCase(y-1,tab[x])!=0) tab [x][y-1]=7;

            if (deplacerCase(x-1,tamp)!=0) tab[x-1][y]=7;
            else
            {
                if ((tab[x-1][y-1]!=0)&&(tab[x-1][y-1]!=2))
                {
                    tab[x-1][y]=9;
                }
            }
            if ((tab[x+1][y]!=0)&&(tab[x+1][y]!=2)) tab[x+1][y]=7;
            else
            {
                if ((tab[x+1][y-1]!=0)&&(tab[x+1][y-1]!=2))
                {
                    tab[x+1][y]=9;
                }
            }
            break;
        case 2:/*Déplacement en haut*/
            if ((tab[x][y-1]!=0)&&(tab[x][y-1]!=2)) tab [x][y-1]=7;
            else
            {
                if ((tab[x+1][y-1]==9)&&(tab[x][y-2]==1)) tab[x][y-1]=9;
            }
            if (deplacerCase(y+1,tab[x])!=0) tab[x][y+1]=7;
            else
            {
                if ((tab[x+1][y+1]==9)&&(tab[x][y+2]==1)) tab[x][y+1]=9;
            }
            if (deplacerCase(x+1,tamp)!=0) tab[x+1][y]=7;
            break;
        case 3:/*Déplacement à gauche*/
            if (deplacerCase(y+1,tab[x])!=0) tab [x][y+1]=7;

            if (deplacerCase(x-1,tamp)!=0) tab[x-1][y]=7;
            else
            {
                if ((tab[x-1][y+1]!=0)&&(tab[x-1][y+1]!=2))
                {
                    tab[x-1][y]=9;
                }
            }
            if ((tab[x+1][y]!=0)&&(tab[x+1][y]!=2)) tab[x+1][y]=7;
            else
            {
                if ((tab[x+1][y+1]!=0)&&(tab[x+1][y+1]!=2))
                {
                    tab[x+1][y]=9;
                }
            }
            break;
        default: break;
    }
}

void reinitTunnel (int x, int y, char tab [TAILLE_MAX][TAILLE_MAX])
{
    if (tab[x-1][y]==7)tab[x-1][y]=1;

    if (tab[x+1][y]==7)tab[x+1][y]=1;

    if (tab[x][y-1]==7)tab[x][y-1]=1;

    if (tab[x][y+1]==7)tab[x][y+1]=1;
}

char deplacementIA (int x, int y, int z, int t, char tab [TAILLE_MAX][TAILLE_MAX])
{
    char tamp [TAILLE_MAX], droite, gauche, haut, bas;
    getColonne(y,tab,tamp);
    int i=1,j=1;
    if (y>t) j=-1;
    else if (y==t) j=0;
    if (x>z)i=-1;
    else if (x==t) i=0;
    tab[x][y]=8;

    if((j==0)&&(i==0))
    {
        tab[x][y]=2;
        return 1;
    }
    else if ((j!=0)&&(deplacerCase(y+j,tab[x])!=0))
    {
        tunnel (x,y,tab,(j+4)%4);
        droite=deplacementIA (x,y+j,z,t,tab);
        reinitTunnel(x,y,tab);
        if (deplacerCase(x+i,tamp)==0)
        {
            if (deplacerCase(x-i,tamp)==0)
            {
                if (deplacerCase(y-j, tab[x])==0||(tab[x-1][y-j]>=7)||(tab[x+1][y-j]>=7))
                {
                    if (droite==0)
                    {
                        tab[x][y]=0;
                    }
                    else
                    {
                        tab[x][y]=2;
                        return 1+droite;
                    }
                }
                else
                {
                    tunnel (x,y,tab,(-j+4)%4);
                    gauche=deplacementIA(x,y-j,z,t,tab);
                    reinitTunnel(x,y,tab);
                    if ((droite==0)&&(gauche==0))
                    {
                        tab[x][y]=0;
                        return 0;
                    }
                    else
                    {
                        tab [x][y]=2;
                        if (gauche==0)return 1+droite;
                        else if (droite==0)return 1+gauche;
                        else return 1+min(droite, gauche);
                    }
                }
            }
            else
            {
                tunnel (x,y,tab,(-i+3)%4);
                haut=deplacementIA(x-i,y,z,t,tab);
                reinitTunnel(x,y,tab);
                if (deplacerCase(y-j, tab[x])==0||(tab[x-1][y-j]>=7)||(tab[x+1][y-j]>=7))
                {
                    if ((haut==0)&&(droite==0))
                    {
                        tab[x][y]=0;
                        return 0;
                    }
                    else
                    {
                        tab [x][y]=2;
                        if (haut==0) return 1+droite;
                        else if (droite==0) return 1+haut;
                        else return 1+min(droite,haut);
                    }
                }
                else
                {
                    tunnel (x,y,tab,(-j+4)%4);
                    gauche=deplacementIA(x,y-j,z,t,tab);
                    reinitTunnel(x,y,tab);
                    if ((droite==0)&&(gauche==0)&&(haut==0))
                    {
                        tab[x][y]=0;
                        return 0;
                    }
                    else
                    {
                        tab [x][y]=2;
                        if ((gauche==0)&&(haut==0)) return 1+droite;
                        else if ((gauche==0)&&(droite==0)) return 1+haut;
                        else if((droite==0)&&(haut==0)) return 1+gauche;
                        else if (haut==0) return 1+min (droite,gauche);
                        else if (gauche==0) return 1+min (droite,haut);
                        else if (droite==0) return 1+min (haut,gauche);
                        else
                        {
                            droite=min(droite,haut);
                            return 1+min(droite,gauche);
                        }
                    }
                }
            }
        }
        else
        {
            tunnel (x,y,tab,(i+3)%4);
            bas=deplacementIA(x+i,y,z,t,tab);
            reinitTunnel(x,y,tab);
            if (deplacerCase(x-i,tamp)==0)
            {
                if (deplacerCase(y-j, tab[x])==0||(tab[x-1][y-j]>=7)||(tab[x+1][y-j]>=7))
                {
                    if ((droite==0)&&(bas==0))
                    {
                        tab[x][y]=0;
                        return 0;
                    }
                    else
                    {
                        tab [x][y]=2;
                        if (droite==0) return 1+bas;
                        else if (bas==0) return 1+droite;
                        else return 1+min (droite,bas);
                    }
                }
                else
                {
                    tunnel (x,y,tab,(-j+4)%4);
                    gauche=deplacementIA(x,y-j,z,t,tab);
                    reinitTunnel(x,y,tab);
                    if ((droite==0)&&(gauche==0)&&(bas==0))
                    {
                        tab[x][y]=0;
                        return 0;
                    }
                    else
                    {
                        tab [x][y]=2;
                        if ((gauche==0)&&(bas==0)) return 1+droite;
                        else if ((gauche==0)&&(droite==0)) return 1+bas;
                        else if((droite==0)&&(bas==0)) return 1+gauche;
                        else if (bas==0) return 1+min (droite,gauche);
                        else if (gauche==0) return 1+min (droite,bas);
                        else if (droite==0) return 1+min (bas,gauche);
                        else
                        {
                            droite=min(droite,bas);
                            return 1+min(droite,gauche);
                        }
                    }
                }
            }
            else
            {
                tunnel (x,y,tab,(-i+3)%4);
                haut=deplacementIA(x-i,y,z,t,tab);
                reinitTunnel(x,y,tab);
                if (deplacerCase(y-j, tab[x])==0||(tab[x-1][y-j]>=7)||(tab[x+1][y-j]>=7))
                {
                    if ((droite==0)&&(bas==0)&&(haut==0))
                    {
                        tab[x][y]=0;
                        return 0;
                    }
                    else
                    {
                        tab [x][y]=2;
                        if ((bas==0)&&(haut==0)) return 1+droite;
                        else if ((bas==0)&&(droite==0)) return 1+haut;
                        else if((droite==0)&&(haut==0)) return 1+bas;
                        else if (haut==0) return 1+min (droite,bas);
                        else if (bas==0) return 1+min (droite,haut);
                        else if (droite==0) return 1+min (bas,haut);
                        else
                        {
                            droite=min(droite,bas);
                            return 1+min(droite,haut);
                        }
                    }
                }
                else
                {
                    tunnel (x,y,tab,(-j+4)%4);
                    gauche=deplacementIA(x,y-j,z,t,tab);
                    reinitTunnel(x,y,tab);
                    if (gauche==0)
                    {
                        if ((droite==0)&&(bas==0)&&(haut==0))
                        {
                            tab[x][y]=0;
                            return 0;
                        }
                        else
                        {
                            tab [x][y]=2;
                            if ((bas==0)&&(haut==0)) return 1+droite;
                            else if ((bas==0)&&(droite==0)) return 1+haut;
                            else if((droite==0)&&(haut==0)) return 1+bas;
                            else if (haut==0) return 1+min (droite,bas);
                            else if (bas==0) return 1+min (droite,haut);
                            else if (droite==0) return 1+min (bas,haut);
                            else
                            {
                                droite=min(droite,bas);
                                return 1+min(droite,haut);
                            }
                        }
                    }
                    else
                    {
                        tab[x][y]=2;
                        if ((bas==0)&&(haut==0)) return 1+min(droite,gauche);
                        else if ((droite==0)&&(haut==0)) return 1+min(bas,gauche);
                        else if ((droite==0)&&(bas==0)) return 1+min(haut,gauche);
                        else if (haut==0)
                        {
                            droite=min (droite,bas);
                            return 1+min (droite,gauche);
                        }
                        else if (bas==0)
                        {
                            droite=min (droite,haut);
                            return 1+min (droite,gauche);
                        }
                        else if (droite==0)
                        {
                            bas= min (bas,haut);
                            return 1+min (bas,gauche);
                        }
                        else
                        {
                            droite=min(droite,bas);
                            gauche=min(haut,gauche);
                            return 1+min (droite, gauche);
                        }
                    }
                }
            }
        }
    }
    else if (deplacerCase(y+j,tab[x])!=0)
    {

    }
    else
    {
        if (deplacerCase(x+i,tamp)==0)
        {
            if (deplacerCase(x-i,tamp)==0)
            {
                if (deplacerCase(y-j, tab[x])==0||(tab[x-1][y-j]>=7)||(tab[x+1][y-j]>=7))
                {
                    tab[x][y]=0;
                    return 0;
                }
                else
                {
                    tunnel (x,y,tab,(-j+4)%4);
                    gauche=deplacementIA(x,y-j,z,t,tab);
                    reinitTunnel(x,y,tab);
                    if (gauche==0)
                    {
                        tab[x][y]=0;
                        return 0;
                    }
                    else
                    {
                        tab [x][y]=2;
                        return 1+gauche;
                    }
                }
            }
            else
            {
                tunnel (x,y,tab,(-i+3)%4);
                haut=deplacementIA(x-i,y,z,t,tab);
                reinitTunnel(x,y,tab);
                if (deplacerCase(y-j, tab[x])==0||(tab[x-1][y-j]>=7)||(tab[x+1][y-j]>=7))
                {
                    if (haut==0)
                    {
                        tab[x][y]=0;
                        return 0;
                    }
                    else
                    {
                        tab [x][y]=2;
                        return 1+haut;
                    }
                }
                else
                {
                    tunnel (x,y,tab,(-j+4)%4);
                    gauche=deplacementIA(x,y-j,z,t,tab);
                    reinitTunnel(x,y,tab);
                    if ((haut==0)&&(gauche==0))
                    {
                        tab[x][y]=0;
                        return 0;
                    }
                    else
                    {
                        tab [x][y]=2;
                        if (gauche==0) return 1+haut;
                        else if (haut==0) return 1+gauche;
                        else return 1+min(haut,gauche);
                    }
                }
            }
        }
        else
        {
            tunnel (x,y,tab,(i+3)%4);
            bas=deplacementIA(x+i,y,z,t,tab);
            reinitTunnel(x,y,tab);
            if (deplacerCase(x-i,tamp)==0)
            {
                if (deplacerCase(y-j, tab[x])==0||(tab[x-1][y-j]>=7)||(tab[x+1][y-j]>=7))
                {
                    if (bas==0)
                    {
                        tab[x][y]=0;
                        return 0;
                    }
                    else
                    {
                        tab [x][y]=2;
                        return 1+bas;
                    }
                }
                else
                {
                    tunnel (x,y,tab,(-j+4)%4);
                    gauche=deplacementIA(x,y-j,z,t,tab);
                    reinitTunnel(x,y,tab);
                    if ((bas==0)&&(gauche==0))
                    {
                        tab[x][y]=0;
                        return 0;
                    }
                    else
                    {
                        tab [x][y]=2;
                        if (bas==0) return 1+gauche;
                        else if (gauche==0) return 1+bas;
                        else return 1+min(bas,gauche);
                    }
                }
            }
            else
            {
                tunnel (x,y,tab,(-i+3)%4);
                haut=deplacementIA(x-i,y,z,t,tab);
                reinitTunnel(x,y,tab);
                if (deplacerCase(y-j, tab[x])==0||(tab[x-1][y-j]>=7)||(tab[x+1][y-j]>=7))
                {
                    if ((bas==0)&&(haut==0))
                    {
                        tab[x][y]=0;
                        return 0;
                    }
                    else
                    {
                        tab [x][y]=2;
                        if (bas==0) return 1+haut;
                        else if (haut==0) return 1+bas;
                        else return 1+min(haut,bas);
                    }
                }
                else
                {
                    tunnel (x,y,tab,(-j+4)%4);
                    gauche=deplacementIA(x,y-j,z,t,tab);
                    reinitTunnel(x,y,tab);
                    if (bas==0)
                    {
                        if ((haut==0)&&(gauche==0))
                        {
                            tab[x][y]=0;
                            return 0;
                        }
                        else
                        {
                            tab [x][y]=2;
                            if (haut==0) return 1+gauche;
                            else if (gauche==0) return 1+haut;
                            else return 1+min(gauche, haut);
                        }
                    }
                    else
                    {
                        if ((haut==0)&&(gauche==0)&&(bas==0))
                        {
                            tab[x][y]=0;
                            return 0;
                        }
                        else
                        {
                            tab [x][y]=2;
                            if ((haut==0)&&(gauche==0)) return 1+bas;
                            else if ((bas==0)&&(gauche==0)) return 1+haut;
                            else if ((bas==0)&&(haut==0)) return 1+gauche;
                            else if (haut==0) return 1+min(bas, gauche);
                            else if (gauche==0) return 1+min (bas, haut);
                            else if (bas==0) return 1+min (haut, gauche);
                            else
                            {
                                bas = min (bas,haut);
                                return 1+min (bas, gauche);
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int mainDeplacement()
{
    char tab [TAILLE_MAX][TAILLE_MAX], ligne [TAILLE_MAX+2];
    FILE* fTerr=fopen("data/Terrains.txt", "r");
    int i,j;
    if (fTerr!=NULL)
    {
        for (i=0; i<4;i++)
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
        tab[3][3]=3;
        tab[17][17]=3;
        afficherTab2D(tab);
        printf("\n%d\n", deplacementIA(3,3,17,17,tab));
        afficherTab2D(tab);

    }
    else printf ("\nImpossible d'ouvrir le fichier Terrains.txt\n");

    return 0;
}
