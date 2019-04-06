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

