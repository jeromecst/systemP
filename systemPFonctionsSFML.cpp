#include "systemP.hpp"

void drawRenard(const Coordonnee &C, sf::RenderWindow& window,int taillePoint){
    sf::RectangleShape figure(sf::Vector2f(taillePoint,taillePoint*.5));
    figure.setPosition(taillePoint*C.x, taillePoint*C.y);
    switch (rand()%8){
        case 0 : figure.setFillColor(sf::Color(196, 101, 0)); break;
        case 1 : figure.setFillColor(sf::Color(200, 101, 0)); break;
        case 2 : figure.setFillColor(sf::Color(205, 101, 0)); break;
        case 3 : figure.setFillColor(sf::Color(196, 110, 0)); break;
        case 4 : figure.setFillColor(sf::Color(237, 150, 11)); break;
        case 5 : figure.setFillColor(sf::Color(240, 150, 12)); break;
        case 6 : figure.setFillColor(sf::Color(237, 150, 11)); break;
        case 7 : figure.setFillColor(sf::Color(230, 145, 9)); break;
    }
    figure.rotate(rand()%180 - 90);
    window.draw(figure);
}


void drawLapin(const Coordonnee &C, sf::RenderWindow& window,int taillePoint){
    sf::RectangleShape figure(sf::Vector2f(taillePoint*.5,taillePoint*.456));
    figure.setPosition(taillePoint*C.x, taillePoint*C.y);
    switch (rand()%8){
        case 0 : figure.setFillColor(sf::Color(153, 162, 164)); break;
        case 1 : figure.setFillColor(sf::Color(150, 162, 164)); break;
        case 2 : figure.setFillColor(sf::Color(153, 155, 164)); break;
        case 3 : figure.setFillColor(sf::Color(153, 162, 170)); break;
        case 4 : figure.setFillColor(sf::Color(254, 227, 197)); break;
        case 5 : figure.setFillColor(sf::Color(260, 227, 197)); break;
        case 6 : figure.setFillColor(sf::Color(254, 235, 197)); break;
        case 7 : figure.setFillColor(sf::Color(254, 227, 203)); break;
    }
    figure.rotate(rand()%360);
    window.draw(figure);
}


void afficheGrille(Case (&grille)[hMaxGrille][lMaxGrille], const Taille &term,sf::RenderWindow& window, int taillePoint){
    window.clear(sf::Color(0, 25, 0));

    for(int i=0; i<term.ha; i++){
        for (int j=0; j< term.lo; j++){
            switch (grille[i][j].espece){
                case nul: break;
                case lapin: drawLapin({i,j}, window, taillePoint); break;
                default : drawRenard({i,j}, window, taillePoint); break;
            }
        }
    }
    window.display();
}

void translation(TCourbe &courbestT){
    for(int i=800-1; i>0; i--){
        courbestT.courbeLapin[i]=courbestT.courbeLapin[i-1];
        courbestT.courbeRenard[i]=courbestT.courbeRenard[i-1];
    }
}

void afficheCompteurA(Case (&grille)[hMaxGrille][lMaxGrille], const Taille &term,sf::RenderWindow& courbe, TCourbe &courbesT){
    courbe.clear(sf::Color(25, 25, 25));
    int nbRenard=0;
    int nbLapin= 0;
    for(int i=0; i<term.ha; i++){
        for(int j=0; j<term.lo; j++){
            if(grille[i][j].espece != nul && grille[i][j].espece==lapin) nbLapin++;
            else if(grille[i][j].espece!=nul) nbRenard++;
        }
    }
    nbLapin=((float) (nbLapin*800) /  (float)(term.ha * term.lo*2));
    nbRenard=((float)(nbRenard*800 * 3) /  (float)(term.ha * term.lo*2));
    translation(courbesT);
    courbesT.courbeLapin[0]=nbLapin;
    courbesT.courbeRenard[0]=nbRenard;
    sf::CircleShape figLapin(2);
    sf::CircleShape figRenard(2);
    figLapin.setFillColor(sf::Color::White);
    figRenard.setFillColor(sf::Color::Red);
    for(int i=0; i<800; i++){
        figLapin.setPosition(800-2*i,200-courbesT.courbeLapin[i]);
        courbe.draw(figLapin);
        figRenard.setPosition(800-2*i,200-courbesT.courbeRenard[i]);
        courbe.draw(figRenard);
    }
    courbe.display();
}
