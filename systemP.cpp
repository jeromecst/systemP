#include "systemP.h"

int main(){
    Case grille[nL][nl];
    srand (time(NULL));
    InitGrille(grille);
    afficheGrille(grille);
}