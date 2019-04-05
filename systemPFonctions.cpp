#include "systemP.h"

void InitGrille(int x, int y){
    Case grille[x][y];
    int randomNombre;
    for(int i=0; i<x; i++){
        for(int j=0; i<y; j++){
            grille[i][j].coord.x=i;
            grille[i][j].coord.y=j;
            randomNombre = rand() % 100 + 1;
            if(randomNombre <=20){ //lapin
                grille[i][j].animal = lapin;
            }
            else if(randomNombre >=93){ //renard
                grille[i][j].food = FoodInit;
                grille[i][j].animal = renard;
            }
            else{
                grille[i][j].animal = nul;
            }
        }
    }
}
