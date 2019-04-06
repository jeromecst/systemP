#include "systemP.h"

int main(){
    Case grille[nL][nl];
    srand (time(NULL));
    InitGrille(grille);
    while(not TheEnd(grille)){
        tour(grille);
        for(int i=0;  i<nl*3; i++) cout << "#";
        cout << endl;
        AfficheGrille(grille);
        std::this_thread::sleep_for (std::chrono::milliseconds(400));
    }
}