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

// Les nombres des animaux
int NA = 0;  // Nombre d'aigles
int NR = 0;  // Nombre de renards
int NL = 0;  // Nombre de lapins
int NT = 0;  // Nombre de trèfles

// Les classes des animaux
class Animal {
public:
    int nombre;
    Animal(int n) : nombre(n) {}
    virtual void Deplacement() = 0;
};

// Structure représentant une cellule de la carte
struct Cell {
    bool vivant = true;
    int ressource = 0;
    int eau = 0;
    int quete = 0;
    int deplacement = 0;
};

class Aigle : public Animal {
public:
    Aigle(int n) : Animal(n) {}
    void seDeplacer() {
        std::cout << "L'aigle se déplace." << std::endl;
    }
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
    void seDeplacer() {
        std::cout << "Le renard se déplace." << std::endl;
    }
    void Deplacement()
    {
        int n = 0;
        while (n < 2)
        {
            int n = rand() % 4;
        }
    }

};

class Lapin : public Animal {
public:
    Lapin(int n) : Animal(n) {}
    void seDeplacer() {
        std::cout << "Le lapin se déplace." << std::endl;
    }
    void Deplacement()
    {
        int n = 2;
    }
};

class Trefle : public Animal {
public:
    Trefle(int n) : Animal(n) {}
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
        while (nbEau < 6) {
<<<<<<< HEAD
            int x = rand() % (LARGEUR_MAP - 1);
            int y = rand() % (HAUTEUR_MAP - 1);
            if (map[y][x] == VIDE && map[y][x + 1] == VIDE && map[y + 1][x] == VIDE && map[y + 1][x + 1] == VIDE) {
=======
            int x = rand() % LARGEUR_MAP;
            int y = rand() % HAUTEUR_MAP;
            if (map[y][x] == VIDE) {
>>>>>>> 4e2ad112534c5f2dc36a06a9a32239a2ea5f7b37
                map[y][x] = EAU;
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
                std::cout << "| " << map[y][x] << " ";
            }
            std::cout << "|" << std::endl;
            for (int x = 0; x < LARGEUR_MAP; ++x) {
                std::cout << " ---";
            }
            std::cout << " " << std::endl;
        }
    }

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
};

int main() {
    srand(time(0));  // Initialisation du générateur de nombres aléatoires

    // Créer la carte
    Carte carte;

    // Remplir la carte avec des ressources et des points d'eau
    carte.remplirMap();

    // Placer des animaux (aigles, renards, lapins)
    carte.placerAnimaux(2, 8, 18);

    // Afficher la carte
    std::cout << "Bienvenue dans le simulateur ecosysteme\n";
    carte.afficherCarte();

    return 0;
}
