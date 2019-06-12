#include "systemP.hpp"

int main(){
    srand (time(NULL));
    struct winsize w;
    TCourbe courbesT;
    sf::RenderWindow courbe(sf::VideoMode(800,200), "systemPCourbes",sf::Style::Default);
    ioctl(0, TIOCGWINSZ, &w);
    Case grille[hMaxGrille][lMaxGrille];
    unsigned int cstTemps = 1;
    Taille term = {w.ws_row-hauteurMoins, w.ws_col-longueurMoins};
    initGrille(grille, term);
    while(not theEnd(grille, term)and (term.ha <= hMaxGrille and term.lo <= lMaxGrille) and courbe.isOpen()){
        ioctl(0, TIOCGWINSZ, &w); // on récupère la taille du terminal
        term = {w.ws_row-hauteurMoins, w.ws_col-longueurMoins};
        tour(grille, term);
        afficheTitre(term, cstTemps);
        afficheGrille(grille, term);
        afficheCompteur(grille, term);
        pause(term, cstTemps);
        afficheCompteurA(grille, term, courbe, courbesT);
        sf::Event event;
        for(int i=0; i<term.ha+hauteurMoins; i++) cout << "\033[A";
        while (courbe.pollEvent(event))
        {
            // évènement "fermeture demandée" : on ferme la fenêtre
            if (event.type == sf::Event::Closed)
                courbe.close();
        }
    }
}
