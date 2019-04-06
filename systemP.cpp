#include "systemP.h"

int main(){
    Case grille[nL][nl];
    srand (time(NULL));
    
    
    InitGrille(grille);

    int nbL=0, nbl=0, nbr=0, nbR=0;
    
    AfficheGrille(grille);

    for(int i=0; i<nL; i++){
        for(int j=0; j<nl ; j++){
            if(grille[i][j].espece==lapin) nbl+=1;
            if(grille[i][j].espece==renard) nbr+=1;
        }
    }

    for(int i=0; i<60; i++) cout << "#";
    cout << endl<< endl;

    for(int i=0; i<nL; i++){
        for(int j=0; j<nl ; j++){
            if(grille[i][j].espece==lapin) nbL+=1;
            if(grille[i][j].espece==renard) nbR+=1;
        }
    }

    AfficheGrille(grille);

    cout  << "lapins : avant : " << nbl << "  après : " << nbL << endl;
    cout  << "renards : avant : " << nbr << "  après : " << nbR << endl;
}