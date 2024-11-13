#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <Windows.h>

//Dimensions de la carte
const int LARGEUR_MAP = 20;
const int HAUTEUR_MAP = 20;

//Définition des types de terrain
const char VIDE = '.';
const char TREFLE = 'T';
const char EAU = 'W';

//Les nombres des animaux
int NA = 0;  //Nombre d'aigles
int NR = 0;  //Nombre de renards
int NL = 0;  //Nombre de lapins
int NT = 0;  //Nombre de trèfles

const int COLOR_GREEN = 2;
const int COLOR_WHITE = 7;
const int COLOR_RED = 4;
const int COLOR_YELLOW = 6;
const int COLOR_BLUE = 1;

//Fonction pour définir la couleur de la console
void setConsoleColor(int couleur) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), couleur);
}

struct Position {
    int x, y;
    Position(int _x, int _y) : x(_x), y(_y) {}
};

//Structure représentant une cellule de la carte
struct Cell {
    bool vivant = true;
    int ressource = 0;
    int eau = 0;
    int quete = 0;
    int deplacement = 0;
    char animal = ' ';
    int couleur = COLOR_WHITE;
};

class Carte {
public:
    std::vector<std::vector<Cell>> map;  // Carte de type Cell

    //Construit de la carte
    Carte() {
        map.resize(HAUTEUR_MAP, std::vector<Cell>(LARGEUR_MAP));
        remplirMap();
    }

    //Rempli la carte avec des ressources et des points d'eau
    void remplirMap() {
        int nbEau = 0;  // Nombre de points d'eau
        int nbRessources = 0;  // Nombre de ressources

        //Place les points d'eau (maximum 5)
        while (nbEau < 3) {
            int x = rand() % LARGEUR_MAP;
            int y = rand() % HAUTEUR_MAP;
            if (map[y][x].animal == ' ') {
                map[y][x].animal = EAU;
                map[y][x].couleur = COLOR_BLUE; // Bleu pour l'eau
                nbEau++;
            }
        }

        //Place les ressources (maximum 10)
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
    
    //Verifi si une position est libre
    bool estlibre(int x, int y) {
        return x >= 0 && x < LARGEUR_MAP && y >= 0 && y < HAUTEUR_MAP && map[y][x].animal == ' ';
    }
    
    //Met à jour la position d'un animal
    void mettreAJourPosition(Position& anciennePos, Position nouvellePos, char symboleAnimal, int couleurAnimal) {
        map[anciennePos.y][anciennePos.x].animal = VIDE; //Efface ancienne position
        map[nouvellePos.y][nouvellePos.x].animal = symboleAnimal; //Place l'animal à la nouvelle position
        map[nouvellePos.y][nouvellePos.x].couleur = couleurAnimal;
        anciennePos = nouvellePos;
    }

    //Place des animaux sur la carte
    void placerAnimaux(int nombreAigles, int nombreRenards, int nombreLapins) {
        //Place les aigles
        for (int i = 0; i < nombreAigles; ++i) {
            int x = rand() % LARGEUR_MAP;
            int y = rand() % HAUTEUR_MAP;
            if (map[y][x].animal == ' ') { // Si la case est vide
                map[y][x].animal = 'A'; // A pour Aigle
                map[y][x].couleur = COLOR_RED; // Couleur jaune pour les aigles
            }
        }

        //Place les renards
        for (int i = 0; i < nombreRenards; ++i) {
            int x = rand() % LARGEUR_MAP;
            int y = rand() % HAUTEUR_MAP;
            if (map[y][x].animal == ' ') { // Si la case est vide
                map[y][x].animal = 'R'; // R pour Renard
                map[y][x].couleur = COLOR_YELLOW; // Couleur rouge pour les renards
            }
        }

        //Place les lapins
        for (int i = 0; i < nombreLapins; ++i) {
            int x = rand() % LARGEUR_MAP;
            int y = rand() % HAUTEUR_MAP;
            if (map[y][x].animal == ' ') { // Si la case est vide
                map[y][x].animal = 'L'; // L pour Lapin
                map[y][x].couleur = COLOR_GREEN; // Couleur verte pour les lapins
            }
        }
    }

    //Affiche la carte
    void afficherCarte() const {
        for (int x = 0; x < LARGEUR_MAP; ++x) {
            std::cout << " ---";
        }
        std::cout << " " << std::endl;
        for (int y = 0; y < HAUTEUR_MAP; ++y) {
            for (int x = 0; x < LARGEUR_MAP; ++x) {
                setConsoleColor(map[y][x].couleur); //Applique la couleur de la cellule
                std::cout << "| " << map[y][x].animal << " "; //Affiche l'animal avec la couleur
            }
            std::cout << "|" << std::endl;
            for (int x = 0; x < LARGEUR_MAP; ++x) {
                std::cout << " ---";
            }
            std::cout << " " << std::endl;
        }
    }
};

//Les classes des animaux
class Animal {
protected:
    Position pos;
    Carte* carte;
    char symbole;
    int couleur;

public:
    Animal(int x, int y, Carte* _carte, char _symbole, int _couleur)
        : pos(x, y), carte(_carte), symbole(_symbole), couleur(_couleur) {
        carte->map[y][x].animal = symbole;
        carte->map[y][x].couleur = couleur;
    }

    virtual void seDeplacer() = 0;
};

// Classe Aigle
class Aigle : public Animal {
public:
    Aigle(int x, int y, Carte* _carte) : Animal(x, y, _carte, 'A', COLOR_RED) {}

    void seDeplacer() override {
        int distance = rand() % 3 + 3; // 3 à 5 cases
        deplacementAleatoire(distance);
    }

private:
    void deplacementAleatoire(int distance) {
        int dx[] = { 0, 1, 0, -1 }; // Droite, Haut, Gauche, Bas
        int dy[] = { 1, 0, -1, 0 };

        int direction = rand() % 4;
        int nx = pos.x + dx[direction] * distance;
        int ny = pos.y + dy[direction] * distance;

        if (carte->estlibre(nx, ny)) {
            carte->mettreAJourPosition(pos, Position(nx, ny), symbole, couleur);
        }
    }
};

// Classe Renard
class Renard : public Animal {
public:
    Renard(int x, int y, Carte* _carte) : Animal(x, y, _carte, 'R', COLOR_YELLOW) {}

    void seDeplacer() override {
        int distance = rand() % 3 + 2; // 2 à 4 cases
        deplacementAleatoire(distance);
    }

private:
    void deplacementAleatoire(int distance) {
        int dx[] = { 0, 1, 0, -1 };
        int dy[] = { 1, 0, -1, 0 };

        int direction = rand() % 4;
        int nx = pos.x + dx[direction] * distance;
        int ny = pos.y + dy[direction] * distance;

        if (carte->estlibre(nx, ny)) {
            carte->mettreAJourPosition(pos, Position(nx, ny), symbole, couleur);
        }
    }
};

// Classe Lapin
class Lapin : public Animal {
public:
    Lapin(int x, int y, Carte* _carte) : Animal(x, y, _carte, 'L', COLOR_GREEN) {}

    void seDeplacer() override {
        int distance = 2; // Toujours 2 cases
        deplacementAleatoire(distance);
    }

private:
    void deplacementAleatoire(int distance) {
        int dx[] = { 0, 1, 0, -1 };
        int dy[] = { 1, 0, -1, 0 };

        int direction = rand() % 4;
        int nx = pos.x + dx[direction] * distance;
        int ny = pos.y + dy[direction] * distance;

        if (carte->estlibre(nx, ny)) {
            carte->mettreAJourPosition(pos, Position(nx, ny), symbole, couleur);
        }
    }
};

int main() {
    srand(time(0));  // Initialise le générateur de nombres aléatoires

    Carte carte;
    Aigle aigle(5, 5, &carte);
    Renard renard(10, 10, &carte);
    Lapin lapin(15, 15, &carte);

    carte.afficherCarte();

    // Simulation d'un tour de déplacement
    std::cout << "\nDéplacement des animaux :\n";
    aigle.seDeplacer();
    renard.seDeplacer();
    lapin.seDeplacer();

    carte.afficherCarte();

    return 0;
}