#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <Windows.h>

//Dimensions de la carte qqqqqq
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


    //Affiche la carte
    void afficherCarte() const {
        system("cls"); // Efface l'écran
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
        setConsoleColor(COLOR_WHITE); // Réinitialise la couleur
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
    Animal(Carte* _carte, char _symbole, int _couleur)
        : carte(_carte), symbole(_symbole), couleur(_couleur) {
        placerAleatoirement();
    }

    virtual void seDeplacer() = 0;

    void placerAleatoirement() {
        int x, y;
        do {
            x = rand() % LARGEUR_MAP;
            y = rand() % HAUTEUR_MAP;
        } while (!carte->estlibre(x, y));
        pos = Position(x, y);
        carte->map[y][x].animal = symbole;
        carte->map[y][x].couleur = couleur;
    }
};

class Aigle : public Animal {
public:
    Aigle(Carte* carte) : Animal(carte, 'A', COLOR_RED) {}

    void seDeplacer() override {
        int dx = (rand() % 7) - 3;
        int dy = (rand() % 7) - 3;
        Position nouvellePos(pos.x + dx, pos.y + dy);

        if (carte->estlibre(nouvellePos.x, nouvellePos.y)) {
            carte->mettreAJourPosition(pos, nouvellePos, symbole, couleur);
        }
    }
};

class Renard : public Animal {
public:
    Renard(Carte* carte) : Animal(carte, 'R', COLOR_YELLOW) {}

    void seDeplacer() override {
        int dx = (rand() % 5) - 2;
        int dy = (rand() % 5) - 2;
        Position nouvellePos(pos.x + dx, pos.y + dy);

        if (carte->estlibre(nouvellePos.x, nouvellePos.y)) {
            carte->mettreAJourPosition(pos, nouvellePos, symbole, couleur);
        }
    }
};

class Lapin : public Animal {
public:
    Lapin(Carte* carte) : Animal(carte, 'L', COLOR_GREEN) {}

    void seDeplacer() override {
        int dx = (rand() % 3) - 1;
        int dy = (rand() % 3) - 1;
        Position nouvellePos(pos.x + dx, pos.y + dy);

        if (carte->estlibre(nouvellePos.x, nouvellePos.y)) {
            carte->mettreAJourPosition(pos, nouvellePos, symbole, couleur);
        }
    }
};

// Classe Jeu
class Jeu {
private:
    Carte carte;
    std::vector<Animal*> animaux;

public:
    Jeu() {
        // Crée les animaux et les ajoute à la liste
        for (int i = 0; i < 2; ++i) animaux.push_back(new Aigle(&carte));
        for (int i = 0; i < 6; ++i) animaux.push_back(new Renard(&carte));
        for (int i = 0; i < 18; ++i) animaux.push_back(new Lapin(&carte));
    }

    ~Jeu() {
        // Libère la mémoire allouée pour chaque animal
        for (auto& animal : animaux) delete animal;
    }

    void demarrer() {
        char choix;
        do {
            carte.afficherCarte(); // Affiche la carte

            std::cout << "Voulez-vous continuer ? (o/n): ";
            std::cin >> choix;

            if (choix == 'o') {
                // Déplacer chaque animal
                for (auto& animal : animaux) {
                    animal->seDeplacer();
                }
            }
        } while (choix == 'o');
    }
};

int main() {
    srand(static_cast<unsigned>(time(0))); // Initialise le générateur de nombres aléatoires

    Jeu jeu;
    jeu.demarrer();

    return 0;
}