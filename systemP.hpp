#include <iostream>
#include <stdlib.h>     
#include <time.h>
#include <thread>         
#include <chrono>   
#include <sys/ioctl.h>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "colors.h"

using namespace std;

//constantes grilles
const int hMaxGrille = 400;
const int lMaxGrille = 400;
const int longueurMoins=3;
const int hauteurMoins=7;

//constantes pourcentages
const float PartLapin = .01; //part de lapin entre 0 et 1
const float PartRenard = .1; //part de renard entre 0 et 1

//constantes age
const unsigned int AgeLapin = 50; 
const unsigned int AgeRenard = 300; 

//constantes probabilité d'apparaître
const unsigned int ProbBirthRenard = 15; //une chance sur 15
const unsigned int ProbBirthLapin = 3; //une chance sur 3


//constantes nourriture
const unsigned int FoodReprod = 8; 
const unsigned int FoodInit = 5; 
const unsigned int FoodLapin = 5;
const unsigned int MaxFood = 10;
const unsigned int MinFreeBirthLapin = 5; //nombres de cases vides pour qu'un lapin se reproduise

const string titre = "Système Prédateurs / Proies";

enum Animal {nul, renard, lapin};

struct Coordonnee{
    int x,y;
};

struct Case{
    int food;
    Animal espece;
    Coordonnee coord;
    int nbCaseVides; 
    int age;
    //Sexe sexe;
};

struct CoordPossible{
    bool possible;
    Coordonnee cord;
};
struct EnsCoordPossible{
    int taille;
    CoordPossible tab[8];
};

struct Taille{
    int ha, lo;
};

struct TCourbe{
    int courbeRenard[800];
    int courbeLapin[800];
};

//############################################ SFML //############################################

/**
 * Dessine un lapin à sa coordonnée sur la fenêtre
 * @param C : la coordonnée de l'animal dans la grille
 * @param window : la fenêtre graphique
 * @param taillePoint : la taille d'un point en pixel sur la grille
 */
void drawLapin(const Coordonnee &C, sf::RenderWindow& window,int taillePoint);


/**
 * Dessine un renard à sa coordonnée sur la fenêtre
 * @param C : la coordonnée de l'animal dans la grille
 * @param window : la fenêtre graphique
 * @param taillePoint : la taille d'un point en pixel sur la grille
 */
void drawRenard(const Coordonnee &C, sf::RenderWindow& window,int taillePoint);


/**
 * Affiche la courbe à un instant donné de la grille
 * @param la grille : un tableau Case à deux dimensions
 * @param Taille term : la taille actuelle du terminal
 * @param window : la fenêtre graphique
 * @param courbesT : deux tableaux int avec les données des courbes
 */
void afficheCompteurA(Case (&grille)[hMaxGrille][lMaxGrille], const Taille &term,sf::RenderWindow& window, TCourbe &courbesT);

/**
 * Affiche la grille sur la fenêtre à un instant donné
 * @param la grille : un tableau Case à deux dimensions
 * @param Taille term : la taille actuelle du terminal
 * @param window : la fenêtre graphique
 * @param taillePoint : la taille d'un point en pixel sur la grille
 */
void afficheGrille(Case (&grille)[hMaxGrille][lMaxGrille], const Taille &term,sf::RenderWindow& window, int taillePoint);


/**
 * Supprimer la première valeur de chaque tableau et les tasse à gauche
 * @param courbesT : deux tableaux int avec les données des courbes
 */ 
void translation(TCourbe &courbestT);


//############################################ AFFICHAGE //############################################


/**
 * Affiche le titre au dessus de la grille
 * @param Taille term : la taille actuelle du terminal
 * @param la constante du temps
 */
void afficheTitre(const Taille &term, const unsigned int &cstTemps);


/**
 * Affiche les compteurs de lapins et de renards sous la grille
 * @param la grille : un tableau Case à deux dimensions
 * @param Taille term : la taille actuelle du terminal
 */
void afficheCompteur(Case (&grille)[hMaxGrille][lMaxGrille],const Taille &term);


/**
 * Affiche la grille avec des bordures 
 * @param la grille : un tableau Case à deux dimensions
 * @param Taille term : la taille actuelle du terminal
 */
void afficheGrille(Case (&grille)[hMaxGrille][lMaxGrille],const Taille &term);


//############################################ INITIALISATION //############################################


/**
 * Initialise une nouvelle case de la grille
 * @param la grille : un tableau Case à deux dimensions
 * @param A : un animal
 * @param C : les coordonnées dans la grille 
 */
void initCase(Case (&grille)[hMaxGrille][lMaxGrille],const Animal &A, const Coordonnee &C);


/**
 * Initilise la grille aléatoirement en fonction des constantes AgeLapins, PartRenards... 
 * @param la grille : un tableau Case à deux dimensions
 * @param Taille term : la taille actuelle du terminal
 */
void initGrille(Case (&grille)[hMaxGrille][lMaxGrille],const Taille &term);


/**
 * Supprime tous les éléments d'une grille
 * @param la grille : un tableau Case à deux dimensions
 */
void grilleVide(Case (&grille)[hMaxGrille][lMaxGrille]);


/**
 * Supprime la case d'une grille
 * @param la grille : un tableau Case à deux dimensions
 * @param une coordonnée : la coordonnée de la grille considérée
 */
void supprimeCase(Case (&grille)[hMaxGrille][lMaxGrille],const Coordonnee &C);


//############################################ OPERATIONS SUR LA GRILLE //############################################


/**
 * Actualise la faim des renards de toute la grille, tue les renards s'ils sont à zéro.
 * Actualise l'age des renards et des lapins de tout la grille, les tue s'ils sont à zéro.
 * @param la grille : un tableau Case à deux dimensions
 * @param Taille term : la taille actuelle du terminal
 */
void actualiseFaimAge(Case (&grille)[hMaxGrille][lMaxGrille], const Taille &term);


/**
 * Cherche autour d'une case toutes les positions où le déplacement est possible, en renvoie un de manière aléatoire * 
 * @param grille1 : un tableau Case à deux dimensions
 * @param grille2 : un tableau Case à deux dimensions
 * @param Case : la case du tableau considérée
 * @param Taille term : la taille actuelle du terminal
 * @return Coordonnee : une coordonnée choisie aléatoirement parmi celles qui sont possibles
 */
Coordonnee positionRandom(Case (&grille)[hMaxGrille][lMaxGrille],const Case (&grille2)[hMaxGrille][lMaxGrille], Case C, const Taille &term);


/**
 * Déplacement tous les renard de manière aléatoire, si un lapin est à proximité, il sera mangé 
 * @param la grille : un tableau Case à deux dimensions
 * @param Taille term : la taille actuelle du terminal
 */
void deplacementRenard(Case (&grille)[hMaxGrille][lMaxGrille], const Taille &term);


/**
 * En fonction de Food et de nbCaseVide, renvoie si l'animal de Case peut se reproduire 
 * @param Case : l'animal contenu dans Case considéré
 * @return bool : vrai s'il peut se reproduire, faux sinon
 */
bool reproduction(Case C);


/**
 * Déplacement tous les lapins de manière aléatoire, il se reproduit si c'est possible, de manière aléatoire 
 * @param la grille : un tableau Case à deux dimensions
 * @param Taille term : la taille actuelle du terminal
 */
void deplacementLapin(Case (&grille)[hMaxGrille][lMaxGrille], const Taille &term);


/**
 * Cherche autour d'une case Renard tous les positions où il y a un lapin
 * @param grille1 : un tableau Case à deux dimensions
 * @param grille2 : un tableau Case à deux dimensions
 * @param Case : l'animal de la case du tableau considéré, qui change de coordonnée s'il mange un lapin 
 * @param Taille term : la taille actuelle du terminal
 * @return bool : vrai si une coordonnée a été changée, faux sinon
 */
bool mangeLapin(Case (&grille)[hMaxGrille][lMaxGrille], Case (&grille2)[hMaxGrille][lMaxGrille], Case &C, const Taille &term);


//############################################ GESTION DES TOURS //############################################


/**
 * Renvoie vrai si il n'y a plus de renard, faux sinon
 * @param la grille : un tableau Case à deux dimensions
 * @param Taille term : la taille actuelle du terminal
 * @return bool : vrai si c'est la fin, faux sinon
 */
bool theEnd(Case (&grille)[hMaxGrille][lMaxGrille],const Taille &term);


/**
 * Effectue un tour complet : délpacement des renards, des lapins et actualise la faim
 * @param la grille : un tableau Case à deux dimensions
 * @param Taille term : la taille actuelle du terminal
 */
void tour(Case (&grille)[hMaxGrille][lMaxGrille], const Taille &term);


/**
 * Met une pause en fonction de la taille du terminal, utilisé entre chaque tour
 * @param Taille term : la taille actuelle du terminal
 * @param cstTemps : le temps de pause en ms
 */
void pause(const Taille &term, unsigned int &cstTemps);
