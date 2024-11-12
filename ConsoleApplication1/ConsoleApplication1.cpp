#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Dimensions de la carte
const int LARGEUR_MAP = 50;
const int HAUTEUR_MAP = 20;

// Définition des types de terrain
const char VIDE = '.';
const char RESSOURCE = 'R';
const char EAU = 'W';

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
        //caca
        // 
        // Placer les ressources (maximum 10)
        while (nbRessources < 10) {
            int x = rand() % LARGEUR_MAP;
            int y = rand() % HAUTEUR_MAP;
            if (map[y][x] == VIDE) {
                map[y][x] = RESSOURCE;
                nbRessources++;
            }
        }
    }

    // Afficher la carte
    void afficherCarte() const {
        for (int y = 0; y < HAUTEUR_MAP; ++y) {
            for (int x = 0; x < LARGEUR_MAP; ++x) {
                std::cout << map[y][x] << " ";
            }
            std::cout << std::endl;
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



