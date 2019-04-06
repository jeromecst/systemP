#include <iostream>
#include <stdlib.h>     
#include <time.h>

using namespace std;

const int nl = 20;
const int nL = 20;
const unsigned int FoodReprod = 8; 
const unsigned int FoodInit = 5; 
const unsigned int FoodLapin = 5; 
const unsigned int MaxFood = 10; 
const unsigned int ProbBirthRenard = 0.05; 
const unsigned int ProbBirthLapin = 0.3; 
const unsigned int MinFreeBirthLapin = 4; 

enum animal {nul, renard, lapin};

enum sexe {male, femelle};

struct Coordonnee{
    int x,y;
};

struct Case{
    int food;
    animal espece;
    Coordonnee coord;
    //sexe sx;
    //int age;
};

//const int n = 20;
//using colone = Case[n];
//using grille = colone[n];

void AfficheGrille(Case (&grille)[nL][nl]);
void InitGrille(Case (&grille)[nL][nl]);
void ActualiseFaim(Case (&grille)[nL][nl]);
void GrilleVide(Case (&grille)[nL][nl]);
Coordonnee PositionRandom(Case (&grille)[nL][nl],const Case (&grille2)[nL][nl], Case C);
bool CaseVide(const Case (&grille)[nL][nl],const Case (&grille2)[nL][nl],Coordonnee C);

bool Reproduction(Case C);
void initCase(Case &C, animal A, Coordonnee coord);
