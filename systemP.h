#include <iostream>
#include <stdlib.h>     

using namepsace std;

const unsigned int FoodInit = 5; 
const unsigned int FoodLapin = 5; 
const unsigned int FoodReprod = 8; 
const unsigned int MaxFood = 10; 
const unsigned int ProbBirthRenard = 0.05; 
const unsigned int ProbBirthLapin = 0.3; 
const unsigned int MinFreeBirthLapin = 4; 

enum animal = {nul, renard, lapin};

struct Coordonnee{
    int x,y;
};

struct Case{
    int food;
    animal animal;
    Coordonnee coord;
    bool deplace:
};

void InitGrille(int x, int y);
void Deplacement(animal A, grille G);
void Reproduction(Case C);
void ActualiseFaim(grille G);
bool Fin(grille G);
void Tour(grille G);
