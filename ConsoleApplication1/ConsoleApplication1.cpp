#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <Windows.h>

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

const int COLOR_GREEN = 2;
const int COLOR_WHITE = 7;
const int COLOR_RED = 4;
const int COLOR_YELLOW = 6;
const int COLOR_BLUE = 1;

// Fonction pour définir la couleur de la console
void setConsoleColor(int couleur) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), couleur);
}

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
    char animal = ' ';
    int couleur = COLOR_WHITE;
};

class Aigle : public Animal {
public:
    Aigle(int n) : Animal(n) {}
    void seDeplacer() {
        std::cout << "aigle se déplace." << std::endl;
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
    std::vector<std::vector<Cell>> map;  // Carte de type Cell

    // Constructeur de la carte
    Carte() {
        map.resize(HAUTEUR_MAP, std::vector<Cell>(LARGEUR_MAP));
        remplirMap();
    }

    // Remplir la carte avec des ressources et des points d'eau
    void remplirMap() {
        int nbEau = 0;  // Nombre de points d'eau
        int nbRessources = 0;  // Nombre de ressources

        // Placer les points d'eau (maximum 5)
        while (nbEau < 3) {
            int x = rand() % (LARGEUR_MAP - 1);
            int y = rand() % (HAUTEUR_MAP - 1);
            if (map[y][x].animal == ' ') {
                map[y][x].animal = EAU;
                map[y][x].couleur = COLOR_BLUE; // Bleu pour l'eau
                nbEau++;
            }
        }

        // Placer les ressources (maximum 10)
        while (nbRessources < 10) {
            int x = rand() % LARGEUR_MAP;
            int y = rand() % HAUTEUR_MAP;
            if (map[y][x].animal == ' ') {
                map[y][x].animal = TREFLE;
                map[y][x].couleur = COLOR_WHITE; // Vert pour le trèfle
                nbRessources++;
            }
        }
    }

    // Placer des animaux sur la carte
    void placerAnimaux(int nombreAigles, int nombreRenards, int nombreLapins) {
        // Placer les aigles
        for (int i = 0; i < nombreAigles; ++i) {
            int x = rand() % LARGEUR_MAP;
            int y = rand() % HAUTEUR_MAP;
            if (map[y][x].animal == ' ') { // Si la case est vide
                map[y][x].animal = 'A'; // A pour Aigle
                map[y][x].couleur = COLOR_RED; // Couleur jaune pour les aigles
            }
        }

        // Placer les renards
        for (int i = 0; i < nombreRenards; ++i) {
            int x = rand() % LARGEUR_MAP;
            int y = rand() % HAUTEUR_MAP;
            if (map[y][x].animal == ' ') { // Si la case est vide
                map[y][x].animal = 'R'; // R pour Renard
                map[y][x].couleur = COLOR_YELLOW; // Couleur rouge pour les renards
            }
        }

        // Placer les lapins
        for (int i = 0; i < nombreLapins; ++i) {
            int x = rand() % LARGEUR_MAP;
            int y = rand() % HAUTEUR_MAP;
            if (map[y][x].animal == ' ') { // Si la case est vide
                map[y][x].animal = 'L'; // L pour Lapin
                map[y][x].couleur = COLOR_GREEN; // Couleur verte pour les lapins
            }
        }
    }

    // Afficher la carte
    void afficherCarte() const {
        for (int x = 0; x < LARGEUR_MAP; ++x) {
            std::cout << " ---";
        }
        std::cout << " " << std::endl;
        for (int y = 0; y < HAUTEUR_MAP; ++y) {
            for (int x = 0; x < LARGEUR_MAP; ++x) {
                setConsoleColor(map[y][x].couleur); // Appliquer la couleur de la cellule
                std::cout << "| " << map[y][x].animal << " "; // Afficher l'animal avec la couleur
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
