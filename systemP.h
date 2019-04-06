#include <iostream>
#include <stdlib.h>     
#include <time.h>
#include <thread>         
#include <chrono>         


using namespace std;

const int nL = 30;
const int nl = 30;
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
    int nbCaseVides; 
    //sexe sx;
    //int age;
};

struct CoordPossible{
    bool possible;
    Coordonnee cord;
};
struct ensCoordPossible{
    int taille;
    CoordPossible tab[8];
};

void AfficheGrille(Case (&grille)[nL][nl]);
void InitGrille(Case (&grille)[nL][nl]);
void ActualiseFaim(Case (&grille)[nL][nl]);
void GrilleVide(Case (&grille)[nL][nl]);
Coordonnee PositionRandom(Case (&grille)[nL][nl],const Case (&grille2)[nL][nl], Case C);
bool CaseVide(const Case (&grille)[nL][nl],const Case (&grille2)[nL][nl],Coordonnee C);
void DeplacementRenard(Case (&grille)[nL][nl]);
void Manger(Case &C);
bool Reproduction(Case C);
void DeplacementLapin(Case (&grille)[nL][nl]);
void initCase(Case &C, animal A, Coordonnee coord);
bool MangeLapin(Case (&grille)[nL][nl], Case (&grille2)[nL][nl], Case &C);
bool TheEnd(Case (&grille)[nL][nl]);
void tour(Case (&grille)[nL][nl]);
