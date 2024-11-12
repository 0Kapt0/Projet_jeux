#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Dimensions de la carte
const int LARGEUR_MAP = 20;
const int HAUTEUR_MAP = 20;

// Définition des types de terrain
const char VIDE = '.';
const char TREFLE = 'T';
const char EAU = 'W';

// Les nombres des animeaux
int NA;
int NR;
int NL;
int NT;

//Les classes des animeaux
class Animal {
public:
    int n;

    Animal(int n) : n(n) {}
    virtual void Deplacement() = 0;
};

struct cell {
    bool Vivant = true;
    int Trefle = 0;
    int Eau = 0;
    int Quete = 0;
    int Deplacement = 0;
};
cell Animal;

class Aigle : public Animal {
public:
    Aigle(int n) : Animal(n) {}
    void Deplacement() 
    {
        int n = 0;
        while (n < 3)
        {
            int n = rand() % 5;
        }
    }
};

class Renard : public Animal {
public:
    Renard(int n) : Animal(n) {}
    void Deplacement()
    {
        int n = 0;
        while (n < 2)
        {
            int n = rand() % 4;
        }
};

class Lapin : public Animal {
public:
    Lapin(int n) : Animal(n) {}
    void Deplacement() 
    {
        int n = 2;
    }
};


// Classe représentant la carte
class Carte {
public:
    std::vector<std::vector<char>> map;

    // Constructeur de la carte
    Carte() {
        map.resize(HAUTEUR_MAP, std::vector<char>(LARGEUR_MAP, VIDE));
        remplirMap();
    }

    // Remplir la carte avec des ressources et des points d'eau
    void remplirMap() {
        int nbEau = 0;  // Nombre de points d'eau
        int nbRessources = 0;  // Nombre de ressources

<<<<<<< HEAD
        // Placer les points d'eau (maximum 5)
        while (nbEau < 5) {
=======
        // Placer les points d'eau (maximum 6)
        while (nbEau < 6) {
>>>>>>> ee51a775c88a81ec5a83d0ecce56c9ba13326208
            int x = rand() % (LARGEUR_MAP - 1);
            int y = rand() % (HAUTEUR_MAP - 1);
            if (map[y][x] == VIDE) {
                map[y][x] = EAU;
                map[y][x + 1] = EAU;
                map[y + 1][x] = EAU;
                map[y + 1][x + 1] = EAU;
                nbEau++;
            }
        }
        
        // Placer les ressources (maximum 10)
        while (nbRessources < 10) {
            int x = rand() % LARGEUR_MAP;
            int y = rand() % HAUTEUR_MAP;
            if (map[y][x] == VIDE) {
                map[y][x] = TREFLE;
                nbRessources++;
            }
        }
    }

    // Afficher la carte
    void afficherCarte() const {
        for (int y = 0; y < HAUTEUR_MAP; ++y) {
            
            for (int x = 0; x < LARGEUR_MAP; ++x) {
                std::cout << "| "<< map[y][x] << " ";
            }
            std::cout << "|" << std::endl;
            for (int x = 0; x < LARGEUR_MAP; ++x) {
                std::cout << " ---";
            }
            std::cout << " " << std::endl;
        }
    }
<<<<<<< HEAD
=======

    // Placer des animaux sur la carte
    void placerAnimaux(int nombreAigles, int nombreRenards, int nombreLapins) {
        // Placer les aigles
        for (int i = 0; i < nombreAigles; ++i) {
            int x = rand() % LARGEUR_MAP;
            int y = rand() % HAUTEUR_MAP;
            if (map[y][x] == VIDE) {
                map[y][x] = 'A'; // A pour Aigle
            }
        }

        // Placer les renards
        for (int i = 0; i < nombreRenards; ++i) {
            int x = rand() % LARGEUR_MAP;
            int y = rand() % HAUTEUR_MAP;
            if (map[y][x] == VIDE) {
                map[y][x] = 'R'; // R pour renard
            }
        }

        // Placer les lapins
        for (int i = 0; i < nombreLapins; ++i) {
            int x = rand() % LARGEUR_MAP;
            int y = rand() % HAUTEUR_MAP;
            if (map[y][x] == VIDE) {
                map[y][x] = 'L'; // L pour Lapin
            }
        }
    }
>>>>>>> ee51a775c88a81ec5a83d0ecce56c9ba13326208
};

int main() {
    srand(time(0));  // Initialisation du générateur de nombres aléatoires

    Carte carte;  // Créer une carte

    // Afficher la carte
    std::cout << "Carte générée :\n";
    carte.afficherCarte();

    return 0;
}



