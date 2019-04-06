#include "systemP.h"

void afficheGrille(Case (&grille)[nL][nl]){
    for(int i=0; i<nL; i++){
        for(int j=0; j<nl; j++){
            if (grille[i][j].espece == 0) cout << " 0 ";
            if (grille[i][j].espece == 1) cout << " R ";
            if (grille[i][j].espece == 2) cout << " L ";
        }
        cout << " " << endl;
    cout << endl;
    }
}

void InitGrille(Case (&grille)[nL][nl]){
    int randomNombre;
    for(int i=0; i<nL; i++){
        for(int j=0; j<nl; j++){
            grille[i][j].coord.x=i;
            grille[i][j].coord.y=j;
            randomNombre = rand() % 101;
            if(randomNombre <=20){
                grille[i][j].espece = lapin;
            }
            else if(randomNombre >=93){
                grille[i][j].espece = renard;
                grille[i][j].food = FoodInit;
            }
            else{
                grille[i][j].espece = nul;
            }
        }
    }
}

void ActualiseFaim(Case (&grille)[nL][nl]){
    for(int i=0; i<nL; i++){
        for(int j=0; j<nl; j++){
            if (grille[i][j].espece==renard){
                if (grille[i][j].food == 1) grille[i][j].espece = nul;
                else  grille[i][j].food -= 1;
            }
        }
    }
}

void GrilleVide(Case (&grille)[nL][nl]){
    for(int i=0; i<nL; i++){
        for(int j=0; j<nl; j++){
            grille[i][j].espece = nul;
        }
    }
}


void initCase(Case &C, animal A, Coordonnee coord){
    C.espece = A;
    C.Coordonnee = coord;
    C.food = FoodInit;
}


bool Reproduction(Case C){
    int a;
    if (C.espece == lapin && C.nbCaseVides >= ){
        a = rand()%10;
        if (a < 3){
            return true;
        }
        return false;
    }
    if (C.espece == renard){
        if (C.food >= FoodReprod){
           a = rand()%20;
           if (a == 0){
               return true;
           }
        }
        return false;
    }
    return false;
}

Coordonnee PositionRandom(Case (&grille)[nL][nl],const Case (&grille2)[nL][nl], Case C){
    struct CoordPossible{
        bool possible;
        Coordonnee cord;
    };
    struct ensCoordPossible{
        int taille;
        CoordPossible tab[8];
    };

    ensCoordPossible ECP;
    ECP.taille = 8;

    CoordPossible Hg = {true, {C.coord.x-1, C.coord.y-1}};
    ECP.tab[0]=Hg;

    CoordPossible H = {true, {C.coord.x-1, C.coord.y}};
    ECP.tab[1]=H;

    CoordPossible Hd = {true, {C.coord.x-1, C.coord.y+1}};
    ECP.tab[2]=Hd;

    CoordPossible D = {true, {C.coord.x, C.coord.y+1}};
    ECP.tab[3]=D;

    CoordPossible Bd = {true, {C.coord.x+1, C.coord.y+1}};
    ECP.tab[4]=Bd;

    CoordPossible B = {true, {C.coord.x+1, C.coord.y}};
    ECP.tab[5]=B;

    CoordPossible Bg = {true, {C.coord.x+1, C.coord.y-1}};
    ECP.tab[6]=Bg;

    CoordPossible G = {true, {C.coord.x, C.coord.y-1}};
    ECP.tab[7]=G;

    for(int i=0; i<8; i++){
        if(ECP.tab[i].cord.x <0 or ECP.tab[i].cord.y <0 or ECP.tab[i].cord.x >19 or ECP.tab[i].cord.y > 19 ){
            ECP.tab[i].possible = false;
            ECP.taille-= 1;
        }
        else if(grille[ECP.tab[i].cord.x][ECP.tab[i].cord.y].espece != nul and grille2[ECP.tab[i].cord.x][ECP.tab[i].cord.y].espece != nul){
            ECP.tab[i].possible = false;
            ECP.taille-= 1;
        }
    }

    grille[C.coord.x][C.coord.y].nbCaseVides = ECP.taille;

    int random = rand() % ECP.taille;
    int k=0;
    for(int i=0; i<8; i++){
        if (k==random) return ECP.tab[i].cord;
        else if (ECP.tab[i].possible){
            k++;
        }
    }
    return C.coord;
}

void DeplacementLapin(Case (&grille)[nL][nl]){
    Case G[nL][nl];
    GrilleVide(G);
    Coordonnee newcoord;
    for(int i = 0; i < nL; i++){
        for(int j = 0; j < nl; j++){
            if(grille[i][j].espece == lapin){
                newcoord = PositionRandom(grille, G, grille[i][j]);
                if(newcoord != grille[i][j].coord && Reproduction(grille[i][j])){
                    Coordonee bb;
                    bb.x = i;
                    bb.y = j;
                    initCase(G.[i][j], lapin, bb);
                } 
                G.[newcoord.x][newcoord.y] = grille[i][j];
                G.[newcoord.x][newcoord.y].coord = newcoord;
            }
            if(grille[i][j].espece == renard){
                G[i][j] = grille[i][j];
            }
        }

    }
    grille = G;     
}
