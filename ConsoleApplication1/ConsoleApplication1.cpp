#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Dimensions de la carte
const int LARGEUR_MAP = 20;
const int HAUTEUR_MAP = 20;

// Définition des types de terrain
const char VIDE = '.';
const char TREFLE = 'R';
const char EAU = 'W';

// Les nombres des animeaux
int NA;
int NR;
int NL;
int NT;

//Les classes des animeaux
class Animal {
public:
    int nombre;

    Animal(int n) : nombre(n) {}
};

struct cell {
    bool Vivant = true;
    int Ressource = 0;
    int Eau = 0;
    int Quete = 0;
    int Deplacement = 0;
};
cell Animal;

class Aigle : public Animal {
public:
    Aigle(int n) : Animal(NA) {}

};

class Renard : public Animal {
public:
    Renard(int n) : Animal(NR) {}

};

class Lapin : public Animal {
public:
    Lapin(int n) : Animal(NL) {}

};

class Trefle : public Animal {
public:
    Trefle(int n) : Animal(NT) {}

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

        // Placer les points d'eau (maximum 5)
        while (nbEau < 5) {
            int x = rand() % (LARGEUR_MAP - 1);
            int y = rand() % (HAUTEUR_MAP - 1);
            if (map[y][x] == VIDE && map[y][x + 1] == VIDE && map[y + 1][x] == VIDE && map[y + 1][x + 1] == VIDE) {
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
};

int main() {
    srand(time(0));  // Initialisation du générateur de nombres aléatoires

    Carte carte;  // Créer une carte

    // Afficher la carte
    std::cout << "Carte générée :\n";
    carte.afficherCarte();

    return 0;
}



