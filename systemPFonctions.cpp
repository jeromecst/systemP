#include "systemP.h"

void AfficheGrille(Case (&grille)[nL][nl]){
    for(int i=0; i<nL; i++){
        for(int j=0; j<nl; j++){
            if (grille[i][j].espece == 0) cout << " . ";
            if (grille[i][j].espece == 1) cout << " R ";
            if (grille[i][j].espece == 2) cout << " L ";
        }
        cout << " " << endl;
    cout << endl;
    }
}

void InitGrille(Case (&grille)[nL][nl]){
    //7% renards
    //20% lapins
    int nbLapin = nl*nL * 0.2;
    int nbRenard = nl*nL * 0.07;
    int x;
    int y;
    GrilleVide(grille);
    while(nbLapin !=0 ){
        x= rand()%nl;
        y= rand()%nL;
        if(grille[x][y].espece==nul){
            grille[x][y].espece=lapin;
            grille[x][y].coord.x=x;
            grille[x][y].coord.y=y;
            nbLapin--;
        } 
    }
    while(nbRenard != 0){
        x= rand()%nl;
        y= rand()%nL;
        if(grille[x][y].espece==nul){
            grille[x][y].espece=renard;
            grille[x][y].food=FoodInit;
            grille[x][y].coord.x=x;
            grille[x][y].coord.y=y;
            nbRenard--;
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
    C.coord = coord;
    C.food = FoodInit;
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
        if(ECP.tab[i].cord.x <0 or ECP.tab[i].cord.y <0 or ECP.tab[i].cord.x > nl-1 or ECP.tab[i].cord.y > nL-1 ){
            ECP.tab[i].possible = false;
            ECP.taille--;
        }
        else if(grille[ECP.tab[i].cord.x][ECP.tab[i].cord.y].espece != nul or grille2[ECP.tab[i].cord.x][ECP.tab[i].cord.y].espece != nul){
            ECP.tab[i].possible = false;
            ECP.taille--;
        }
    }
    grille[C.coord.x][C.coord.y].nbCaseVides = ECP.taille;
    if(ECP.taille==0) return C.coord;
    int random = rand() % ECP.taille;
    int k=0;
    for(int i=0; i<8; i++){
        if (k==random) return ECP.tab[i].cord;
        else if (ECP.tab[i].possible) k++;
    }
    for(int i=0; i<2000; i++) cout << "#" <<endl;
}

bool Reproduction(Case C){
    int a;
    if (C.espece == lapin && C.nbCaseVides >= MinFreeBirthLapin){
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

void DeplacementLapin(Case (&grille)[nL][nl]){
    Case G[nL][nl];
    GrilleVide(G);
    for(int i=0; i<nL; i++){
        for(int j=0; j<nl; j++){
            if(grille[i][j].espece == renard) G[i][j]=grille[i][j];
        }
    }
    string a;
    Coordonnee newcoord;
    for(int i = 0; i < nL; i++){
        for(int j = 0; j < nl; j++){
            if(grille[i][j].espece == lapin){
                newcoord = PositionRandom(grille, G, grille[i][j]);
                G[newcoord.x][newcoord.y] = grille[i][j];
                G[newcoord.x][newcoord.y].coord = newcoord;
                if(Reproduction(grille[i][j])) G[i][j].espece=lapin;  
                grille[i][j].espece = nul;
                AfficheGrille(G);
                for(int k=0; k<60; k++) cout << '#';
                cin >>a;
            }
        }
    }
    GrilleVide(grille);
    for(int i=0; i<nL; i++){
        for(int j=0; j<nl; j++){
            grille[i][j]=G[i][j];
        }
    }     
}
/*
void DeplacementLapin(Case (&grille)[nL][nl]){
    Case G[nL][nl];
    GrilleVide(G);
    for(int i=0; i<nL; i++){
        for(int j=0; j<nl; j++){
            if(grille[i][j].espece == renard) G[i][j]=grille[i][j];
        }
    }
    Coordonnee newcoord;
    for(int i = 0; i < nL; i++){
        for(int j = 0; j < nl; j++){
            if(grille[i][j].espece == lapin){
                newcoord = PositionRandom(grille, G, grille[i][j]);
                if(newcoord.x != i and newcoord.y != j && Reproduction(grille[i][j])){
                    Coordonnee bb;
                    bb.x = i;
                    bb.y = j;
                    initCase(G[i][j], lapin, bb);
                } 
                G[newcoord.x][newcoord.y] = grille[i][j];
                G[newcoord.x][newcoord.y].coord = newcoord;
            }
        }

    }
    for(int i=0; i<nL; i++){
        for(int j=0; j<nl; j++){
            grille[i][j]=G[i][j];
        }
    }     
}
*/
