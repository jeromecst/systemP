#include "systemP.hpp"

int main(){
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;
    sf::RenderWindow window(sf::VideoMode(1500,800), "systemPGrille",sf::Style::Default,  settings);
    sf::RenderWindow courbe(sf::VideoMode(800,200), "systemPCourbes",sf::Style::Default,  settings);
    window.setFramerateLimit(1000);
    courbe.setFramerateLimit(1000);

    srand (time(NULL));
    Case grille[hMaxGrille][lMaxGrille];
    unsigned int cstTemps = 5;
    sf::Vector2u size = window.getSize();
    int taillePoint=1;
    while((size.y / taillePoint) > lMaxGrille or (size.x / taillePoint) > hMaxGrille){
        taillePoint++;
    }

    TCourbe courbesT;
    Taille term = {(int)(size.x/taillePoint),(int) (size.y/taillePoint)};
    initGrille(grille, term);
    cout << "taille grille : " << term.lo << "x"<<term.ha<<endl<< "taille case : " << taillePoint<<"px"<<endl;
    while(not theEnd(grille, term)and (term.ha <= hMaxGrille and term.lo <= lMaxGrille) and window.isOpen() and courbe.isOpen()){
        sf::Event event;
        while (window.pollEvent(event) or courbe.pollEvent(event))
        {
            // évènement "fermeture demandée" : on ferme la fenêtre
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Closed)
                courbe.close();
        }
        tour(grille, term);
        std::thread t1(afficheCompteurA, std::ref(grille), std::ref(term), std::ref(courbe), std::ref(courbesT));
        afficheGrille(grille, term, window, taillePoint);
        t1.join();
    }
}
