<<<<<<< Updated upstream
=======
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

<<<<<<< HEAD
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
=======
    void diminuerSante(int degats) {
        sante -= degats;
        if (sante < 0) sante = 0;
    }

    void restaurerSante(int points) {
        sante += points;
        if (sante > santeMax) sante = santeMax;
    }

    bool estVivant() const {
        return sante > 0;
    }

    std::string getNom() const { return nom; }
    int getSante() const { return sante; }
    int getScore() const { return score; }
};

//Classe Guerrier avec attaque puissante
class Guerrier : public Personnage {
public:
    Guerrier(std::string nom) : Personnage(nom, 100) {}

    void AuraSword(Personnage& cible) {
        int degats = 20;
        cible.diminuerSante(degats);
        score += 20;
        std::cout << nom << " utilise attaque [Epee d'Aura] sur " << cible.getNom()
            << " pour " << degats << " points de degats." << std::endl;
    }

    void utiliserCompetenceSpeciale(Personnage& cible) override {
        //Génére un nombre entre 0 et 1
        int chance = rand() % 2; //50% de chance d'utiliser AuraSword
        if (chance == 1) {
            AuraSword(cible);
        }
        else {
            std::cout << nom << " tente d'utiliser [Epee d'Aura], mais echoue." << std::endl;
        }
    }
};

//bonsoir et bonjour

//Salut c lolo

//Classe Archer avec une attaque à distance
class Archer : public Personnage {
public:
    Archer(std::string nom) : Personnage(nom, 80) {}

    void TirPercant(Personnage& cible) {
        int degats = 15;
        cible.diminuerSante(degats);
        score += 15;
        std::cout << nom << " utilise [Tir Percant] sur " << cible.getNom()
            << " pour " << degats << " points de degats." << std::endl;
    }

    void utiliserCompetenceSpeciale(Personnage& cible) override {
        //Genere un nombre entre 0 et 1
        int chance = rand() % 2;
        if (chance == 1) {
            TirPercant(cible);
        }
    }
};

// Boucle de jeu sans bibliothèques de mémoire et d'algorithme
void boucleDeJeu(std::vector<Personnage*>& personnages) {
    int tour = 1;
    bool jeuActif = true;

    while (jeuActif) {
        tour = tour + 1;
        for (size_t i = 0; i < personnages.size(); ++i) {
            if (personnages[i]->estVivant()) {
                int action = std::rand() % 2;  // Choix aléatoire de l'action
                size_t cibleIndex = std::rand() % personnages.size();
                Personnage& cible = *personnages[cibleIndex];

                if (action == 0) {
                    personnages[i]->attaquer(cible);
                    std::cout << "Tour : " << tour << " ";
                }
                else {
                    personnages[i]->utiliserCompetenceSpeciale(cible);
                    std::cout << "Tour : " << tour << " ";
                }
>>>>>>> 680fe1c2a2b91a0f28cdab7ebd277cde5d437efd
            }
        }

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



>>>>>>> Stashed changes
