#include "systemP.hpp"

void afficheGrille(Case (&grille)[hMaxGrille][lMaxGrille], const Taille &term){
    cout << ' ';
    for(int i=0; i<term.lo; i++) cout << '-';
    cout << endl;
    for(int i=0; i<term.ha; i++){
        for(int j=0; j<term.lo; j++){
            if (j==0) cout << '|'; 
            if(grille[i][j].espece == 0) cout << " ";
            else if(grille[i][j].espece == 2) cout << "."; //lapins
            else cout << "®"; //renards
            if (j==term.lo-1) cout << '|'; 
        }
        cout << " " << endl;
    }
    cout << ' ';
    for(int i=0; i<term.lo; i++) cout << '-';
    cout << endl;
}

void initCase(Case (&grille)[hMaxGrille][lMaxGrille],const Animal &A, const Coordonnee &C){
    grille[C.x][C.y].espece = A;
    grille[C.x][C.y].coord.x = C.x;
    grille[C.x][C.y].coord.y = C.y;
    if(A==lapin){
        grille[C.x][C.y].age = rand() % AgeLapin;
        grille[C.x][C.y].food = FoodLapin;
        //initSexe(grille, C);
    }
    else{
        grille[C.x][C.y].age = rand() % AgeRenard;
        grille[C.x][C.y].food = FoodInit;  
        //initSexe(grille, C);
    }
}

void supprimeCase(Case (&grille)[hMaxGrille][lMaxGrille],const Coordonnee &C){
    grille[C.x][C.y] = {0 , nul, {C.x, C.y}, 0 , 0};
}


void initGrille(Case (&grille)[hMaxGrille][lMaxGrille],const Taille &term){   
    int nbLapin = term.lo*term.ha * PartLapin;
    int nbRenard = term.lo*term.ha * PartRenard;
    int x;
    int y;
    grilleVide(grille);
    while(nbLapin >= 0){
        x= rand() % term.ha;
        y= rand() % term.lo;
        if(grille[x][y].espece==nul){
            initCase(grille, lapin, {x,y});
            nbLapin--;
        } 
    }
    while(nbRenard >= 0){
        x= rand()%term.ha;
        y= rand()%term.lo;
        if(grille[x][y].espece==nul){
            initCase(grille, renard, {x,y});
            nbRenard--;
        } 
    }
}

void actualiseFaimAge(Case (&grille)[hMaxGrille][lMaxGrille],const Taille &term){
    for(int i=0; i<term.ha; i++){
        for(int j=0; j<term.lo; j++){
            if (grille[i][j].espece==renard){
                if (grille[i][j].food == 1) supprimeCase(grille, Coordonnee {i,j});
                else  grille[i][j].food -= 1;
            }
            if(grille[i][j].age==1 && grille[i][j].espece != nul) supprimeCase(grille,Coordonnee {i,j});
            else grille[i][j].age -= 1;
        }
    }
}

void grilleVide(Case (&grille)[hMaxGrille][lMaxGrille]){
    for(int i=0; i<hMaxGrille; i++){
        for(int j=0; j<lMaxGrille; j++){
            supprimeCase(grille, Coordonnee {i,j});
        }
    }
}

Coordonnee positionRandom(Case (&grille)[hMaxGrille][lMaxGrille],Case (&grille2)[hMaxGrille][lMaxGrille], Case C, const Taille &term){
    EnsCoordPossible ECP;
    ECP.taille = 8;

    CoordPossible Hg = {true, {C.coord.x-1, C.coord.y-1}};
    CoordPossible H = {true, {C.coord.x-1, C.coord.y}};
    CoordPossible Hd = {true, {C.coord.x-1, C.coord.y+1}};
    CoordPossible D = {true, {C.coord.x, C.coord.y+1}};
    CoordPossible Bd = {true, {C.coord.x+1, C.coord.y+1}};
    CoordPossible B = {true, {C.coord.x+1, C.coord.y}};
    CoordPossible Bg = {true, {C.coord.x+1, C.coord.y-1}};
    CoordPossible G = {true, {C.coord.x, C.coord.y-1}};

    ECP.tab[0]=Hg;
    ECP.tab[1]=H;
    ECP.tab[2]=Hd;
    ECP.tab[3]=D;
    ECP.tab[4]=Bd;
    ECP.tab[5]=B;
    ECP.tab[6]=Bg;
    ECP.tab[7]=G;

    for(int i=0; i<8; i++){
        if(ECP.tab[i].cord.x <0 or ECP.tab[i].cord.y <0 or ECP.tab[i].cord.x > term.ha-1 or ECP.tab[i].cord.y > term.lo-1 ){
            ECP.tab[i].possible = false;
            ECP.taille--;
        }
        else if(grille[ECP.tab[i].cord.x][ECP.tab[i].cord.y].espece != nul or grille2[ECP.tab[i].cord.x][ECP.tab[i].cord.y].espece != nul){
            ECP.tab[i].possible = false;
            ECP.taille--;
        }
    }
    grille[C.coord.x][C.coord.y].nbCaseVides = ECP.taille;
    if(ECP.taille==0) return C.coord;
    int random = rand() % ECP.taille;
    int k=0;
    for(int i=0; i<8; i++){
        if (k==random and ECP.tab[i].possible) return ECP.tab[i].cord;
        else if (ECP.tab[i].possible) k++;
    }
    return C.coord;
}

bool reproduction(Case C){
    int a;
    if (C.espece == lapin && C.nbCaseVides >= MinFreeBirthLapin){
        if (rand()%ProbBirthLapin < 3){
            return true;
        }
        return false;
    }
    if (C.espece == renard){
        if (C.food >= FoodReprod){
           if (rand()%ProbBirthRenard == 0){
               return true;
           }
        }
        return false;
    }
    return false;
}

void deplacementLapin(Case (&grille)[hMaxGrille][lMaxGrille], const Taille &term){
    Case G[hMaxGrille][lMaxGrille];
    grilleVide(G);
    for(int i=0; i<term.ha; i++){
        for(int j=0; j<term.lo; j++){
            if(grille[i][j].espece == renard) G[i][j]=grille[i][j];
        }
    }
    Coordonnee newcoord;
    for(int i = 0; i < term.ha; i++){
        for(int j = 0; j < term.lo; j++){
            if(grille[i][j].espece == lapin){
                newcoord = positionRandom(grille, G, grille[i][j], term);
                G[newcoord.x][newcoord.y] = grille[i][j];
                G[newcoord.x][newcoord.y].coord = newcoord;
                if(reproduction(grille[i][j]) and (newcoord.x != i or newcoord.y != j) ){
                    G[i][j].espece=lapin;
                    G[i][j].coord.x=i;
                    G[i][j].coord.y=j;
                    G[i][j].age=AgeLapin;
                    //initSexe(grille, {i,j});
                }   
                supprimeCase(grille,Coordonnee {i,j});
            }
        }
    }
    grilleVide(grille);
    for(int i=0; i<term.ha; i++){
        for(int j=0; j<term.lo; j++){
            grille[i][j]=G[i][j];
        }
    }     
}

bool mangeLapin(Case (&grille)[hMaxGrille][lMaxGrille], Case (&grille2)[hMaxGrille][lMaxGrille], Case &C , const Taille &term){
    EnsCoordPossible ECP;
    ECP.taille = 8;

    CoordPossible Hg = {true, {C.coord.x-1, C.coord.y-1}};
    CoordPossible H = {true, {C.coord.x-1, C.coord.y}};
    CoordPossible Hd = {true, {C.coord.x-1, C.coord.y+1}};
    CoordPossible D = {true, {C.coord.x, C.coord.y+1}};
    CoordPossible Bd = {true, {C.coord.x+1, C.coord.y+1}};
    CoordPossible B = {true, {C.coord.x+1, C.coord.y}};
    CoordPossible Bg = {true, {C.coord.x+1, C.coord.y-1}};
    CoordPossible G = {true, {C.coord.x, C.coord.y-1}};

    ECP.tab[0]=Hg;
    ECP.tab[1]=H;
    ECP.tab[2]=Hd;
    ECP.tab[3]=D;
    ECP.tab[4]=Bd;
    ECP.tab[5]=B;
    ECP.tab[6]=Bg;
    ECP.tab[7]=G;

    for(int i=0; i<8; i++){
        if(ECP.tab[i].cord.x <0 or ECP.tab[i].cord.y <0 or ECP.tab[i].cord.x > term.ha-1 or ECP.tab[i].cord.y > term.lo-1 ){
            ECP.tab[i].possible = false;
            ECP.taille--;
        }
        else if(grille[ECP.tab[i].cord.x][ECP.tab[i].cord.y].espece != lapin or grille2[ECP.tab[i].cord.x][ECP.tab[i].cord.y].espece != lapin){
            ECP.tab[i].possible = false;
            ECP.taille--;
        }
    }
    if(ECP.taille==0) return false;
    int random = rand() % ECP.taille;
    int k=0;
    for(int i=0; i<8; i++){
        if (k==random and ECP.tab[i].possible){
            C.coord.x=ECP.tab[i].cord.x;
            C.coord.y=ECP.tab[i].cord.y;
            return true;
        } 
        else if (ECP.tab[i].possible) k++;
    }
    return false;
}

void deplacementRenard(Case (&grille)[hMaxGrille][lMaxGrille], const Taille &term){   
    Case G[hMaxGrille][lMaxGrille];
    grilleVide(G);
    Coordonnee newcoord;
    for(int i=0; i<term.ha; i++){
        for(int j=0; j<term.lo; j++){
            if(grille[i][j].espece == lapin) G[i][j] = grille[i][j];
        }
    }
    for(int i = 0; i < term.ha; i++){
        for(int j = 0; j < term.lo; j++){
            if(grille[i][j].espece == renard){
               if(mangeLapin(grille,G, grille[i][j], term)){
                   if(reproduction(grille[i][j])){
                       G[i][j].espece = renard;
                       G[i][j].coord.x = i;
                       G[i][j].coord.y = j;
                       G[i][j].food = FoodInit;
                       G[i][j].age=AgeRenard;
                    }
                   G[grille[i][j].coord.x][grille[i][j].coord.y] = grille[i][j];
                   G[grille[i][j].coord.x][grille[i][j].coord.y].food+=5;
                   if (G[grille[i][j].coord.x][grille[i][j].coord.y].food >MaxFood) G[grille[i][j].coord.x][grille[i][j].coord.y].food = MaxFood;
               }
                else{
                    newcoord = positionRandom(grille, G, grille[i][j], term);
                    G[newcoord.x][newcoord.y] = grille[i][j];
                    G[newcoord.x][newcoord.y].coord = newcoord;
                    if( reproduction(grille[i][j]) && (newcoord.x != i or newcoord.y != j) ){
                        G[i][j].espece = renard; 
                        G[i][j].coord.x = i;
                        G[i][j].coord.y = j;
                        G[i][j].food = FoodInit;
                    }
                }
                grille[i][j].espece=nul;
            }
        }
    }
    grilleVide(grille);
    for(int i=0; i<term.ha; i++){
        for(int j=0; j<term.lo; j++){
            grille[i][j]=G[i][j];
        }
    }     
}

bool theEnd(Case (&grille)[hMaxGrille][lMaxGrille],const Taille &term){  
    for(int i=0; i<term.ha ; i++){
        for(int j=0; j<term.lo; j++){
            if(grille[i][j].espece==renard) return false;
        }
    }
    return true;
}

void tour(Case (&grille)[hMaxGrille][lMaxGrille], const Taille &term){
    deplacementLapin(grille, term);
    deplacementRenard(grille, term);
    actualiseFaimAge(grille, term);
}

void afficheCompteur(Case (&grille)[hMaxGrille][lMaxGrille],const Taille &term){
    int nbR=0;
    int nbL=0;
    for(int i=0; i<term.ha; i++){
        for(int j=0; j<term.lo; j++){
            if(grille[i][j].espece == renard) nbR++;
            else if(grille[i][j].espece == lapin) nbL++;
        }
    }
    int renardPourcent = floor(100.*(float(nbR)/float(term.ha*term.lo)));
    int lapinPourcent = floor(100.*(float(nbL)/float(term.ha*term.lo)));
    cout << "renard : ";
    for(int i=0; i<term.lo+longueurMoins - 15; i+=3){
		if(i<= floor(((float)nbR*((float)term.lo+(float)longueurMoins-14.)) / ((float)term.lo * (float)term.ha)) +15) cout << "###";
		else cout << "   ";
    }
    cout <<'(' << renardPourcent << '%'<<')';
    cout << endl;


    cout << "lapins : ";
    for(int i=0; i<term.lo+longueurMoins - 15; i++){
		if(i<= floor(((float)nbL*((float)term.lo+(float)longueurMoins-14.)) / ((float)term.lo * (float)term.ha)) +15) cout << "#";
		else cout << ' ';
    }	
    cout << '('<< lapinPourcent << '%'<<')';
    cout << endl;
}

void pause(const Taille &term, unsigned int &cstTemps){
    switch (term.ha * term.lo)
    {
        case 0 ... 400 : cstTemps = 120; break;
        case 401 ... 1000 : cstTemps = 100; break;
        case 1001 ... 3500 : cstTemps = 75; break;
        case 3501 ... 5000 : cstTemps = 60; break;
        case 5001 ... 10000 : cstTemps = 35; break;
        case 10001 ... 20000 : cstTemps = 25; break;
        default: cstTemps = 10; break;
    }
    std::this_thread::sleep_for (std::chrono::milliseconds(cstTemps));
}

void afficheTitre(const Taille &term, const unsigned int &cstTemps){
    string b = " (" + to_string(term.lo) + 'x' + to_string(term.ha) + ')';
    string c = titre + b + '@'+to_string(int(1./float(cstTemps*.001)))+"Hz";
    if(c.size() <= term.lo){
        cout << endl;
        for(int i=0; i < (term.lo - c.size())/2 ; i++) cout << " ";
        cout << c;
        for(int i=0; i < (term.lo - c.size())/2 ; i++) cout << " ";
        cout << endl;
    }
    else if (b.size() <= term.lo){
        cout << endl;
        cout << b+to_string(int(1./float(cstTemps*.001)))+"Hz";
        cout << endl;
    }
    else{
        for(int i=0; i<2; i++) cout << endl;
    }
}
