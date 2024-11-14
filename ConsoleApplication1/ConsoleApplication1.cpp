#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

class Eau {
public:
    static int quantite;

    static void produire() {
        quantite += 10;
    }

    static bool boire(int quantiteBoire) {
        if (quantite >= quantiteBoire) {
            quantite -= quantiteBoire;
            return true;
        }
        return false;
    }
};
int Eau::quantite = 100;

class Trefle {
public:
    static int quantite;

    static void produire() {
        quantite += 5;
    }

    static bool manger(int quantiteManger) {
        if (quantite >= quantiteManger) {
            quantite -= quantiteManger;
            return true;
        }
        return false;
    }
};
int Trefle::quantite = 100;

class Lapin {
public:
    static int population;
    static int totalManges;
    static int reproductions;
    static int fuites;

    int treflesManges = 0;
    int eauBue = 0;

    void boire() {
        if (Eau::boire(4)) eauBue += 4;
    }

    void manger() {
        if (Trefle::manger(4)) treflesManges += 4;
    }

    bool peutSeReproduire() const {
        return treflesManges >= 10 && eauBue >= 10;
    }

    void resetReproduction() {
        treflesManges = 0;
        eauBue = 0;
    }

    static void reproduire(vector<Lapin>& lapins) {
        for (size_t i = 0; i < lapins.size(); ++i) {
            if (lapins[i].peutSeReproduire()) {
                for (size_t j = i + 1; j < lapins.size(); ++j) {
                    if (lapins[j].peutSeReproduire()) {
                        lapins[i].resetReproduction();
                        lapins[j].resetReproduction();
                        lapins.push_back(Lapin());
                        ++population;
                        ++reproductions;
                        break;
                    }
                }
            }
        }
    }
};
int Lapin::population = 18;
int Lapin::totalManges = 0;
int Lapin::reproductions = 0;

class Renard {
public:
    static int population;
    static int totalManges;
    static int reproductions;
    static int fuites;

    int lapinsManges = 0;
    int eauBue = 0;

    void boire() {
        if (Eau::boire(4)) eauBue += 4;
    }

    void manger(vector<Lapin>& lapins) {
        int p = rand() % 2;
        if (p == 1) {
            if (lapins.size() >= 4) {
                lapins.erase(lapins.end() - 4, lapins.end());
                lapinsManges += 4;
                Lapin::population -= 4;
                Lapin::totalManges +=4;
            }
        }
        else{
            Lapin::fuites++;
        }

    }

    bool peutSeReproduire() const {
        return lapinsManges >= 20 && eauBue >= 20;
    }

    void resetReproduction() {
        lapinsManges = 0;
        eauBue = 0;
    }

    static void reproduire(vector<Renard>& renards) {
        for (size_t i = 0; i < renards.size(); ++i) {
            if (renards[i].peutSeReproduire()) {
                for (size_t j = i + 1; j < renards.size(); ++j) {
                    if (renards[j].peutSeReproduire()) {
                        renards[i].resetReproduction();
                        renards[j].resetReproduction();
                        renards.push_back(Renard());
                        ++population;
                        ++reproductions;
                        break;
                    }
                }
            }
        }
    }
};
int Renard::population = 8;
int Renard::totalManges = 0;
int Renard::reproductions = 0;

class Aigle {
public:
    static int population;
    static int totalMangesRenards;
    static int reproductions;

    int renardsManges = 0;
    int eauBue = 0;

    void boire() {
        if (Eau::boire(4)) eauBue += 4;
    }

    void manger(vector<Renard>& renards) {
        int p = rand() % 2;
        if (p == 1) {
            if (renards.size() >= 2) {
                renards.erase(renards.end() - 2, renards.end());
                renardsManges += 2;
                Renard::population -= 2;
                totalMangesRenards += 2;
            }
        }
        else{
            Renard::fuites++;
        }
    }

    bool peutSeReproduire() const {
        return renardsManges >= 30 && eauBue >= 30;
    }

    void resetReproduction() {
        renardsManges = 0;
        eauBue = 0;
    }

    static void reproduire(vector<Aigle>& aigles) {
        for (size_t i = 0; i < aigles.size(); ++i) {
            if (aigles[i].peutSeReproduire()) {
                for (size_t j = i + 1; j < aigles.size(); ++j) {
                    if (aigles[j].peutSeReproduire()) {
                        aigles[i].resetReproduction();
                        aigles[j].resetReproduction();
                        aigles.push_back(Aigle());
                        ++population;
                        ++reproductions;
                        break;
                    }
                }
            }
        }
    }
};
int Aigle::population = 2;
int Aigle::totalMangesRenards = 0;
int Aigle::reproductions = 0;

void afficherStats(int tour) {
    cout << "Tour " << tour + 1 << ":\n";

    cout << "Aigles: " << Aigle::population << "\n";
    cout << "Nb de renards chasses: " << Aigle::totalMangesRenards << "\n";
    cout << "Nb de reproductions: " << Aigle::reproductions << "\n\n";

    cout << "Renards: " << Renard::population << "\n";
    cout << "Nb de lapins chasses: " << Renard::totalManges << "\n";
    cout << "Nb de reproductions: " << Renard::reproductions << "\n\n";
    cout << "Nb de fuites: " << Renard::fuites << "\n\n";

    cout << "Lapins: " << Lapin::population << "\n";
    cout << "Nb de trefles manges: " << Lapin::totalManges << "\n";
    cout << "Nb de reproductions: " << Lapin::reproductions << "\n\n";
    cout << "Nb de fuites: " << Lapin::fuites << "\n\n";

    cout << "Quantite d'eau restante: " << Eau::quantite << "\n";
    cout << "Quantite de trefles restants: " << Trefle::quantite << "\n\n";
}

int main() {
    vector<Aigle> aigles(Aigle::population);
    vector<Renard> renards(Renard::population);
    vector<Lapin> lapins(Lapin::population);

<<<<<<< Updated upstream
    cout << "Bienvenue Dans le jeu de la foret:" << "\n\n";

    cout << "Aigles: " << Aigle::population << "\n";
    cout << "Nb de renards chasses: " << Aigle::totalMangesRenards << "\n";
    cout << "Nb de reproductions: " << Aigle::reproductions << "\n\n";

    cout << "Renards: " << Renard::population << "\n";
    cout << "Nb de lapins chasses: " << Renard::totalManges << "\n";
    cout << "Nb de reproductions: " << Renard::reproductions << "\n\n";

    cout << "Lapins: " << Lapin::population << "\n";
    cout << "Nb de trefles manges: " << Lapin::totalManges << "\n";
    cout << "Nb de reproductions: " << Lapin::reproductions << "\n\n";

    cout << "Quantite d'eau restante: " << Eau::quantite << "\n";
    cout << "Quantite de trefles restants: " << Trefle::quantite << "\n\n";

=======
    //afficherStats();
>>>>>>> Stashed changes

    const int toursMax = 15;
    for (int tour = 0; tour < toursMax; ++tour) {
        // Actions des lapins
        for (auto& lapin : lapins) {
            lapin.boire();
            lapin.manger();
        }
        Lapin::reproduire(lapins);

        // Actions des renards
        for (auto& renard : renards) {
            renard.boire();
            renard.manger(lapins);
        }
        Renard::reproduire(renards);

        // Actions des aigles
        for (auto& aigle : aigles) {
            aigle.boire();
            aigle.manger(renards);
        }
        Aigle::reproduire(aigles);

        // Production des ressources (eau et trefles)
        Eau::produire();
        Trefle::produire();

        // Affichage des statistiques pour ce tour
        afficherStats(tour);
    }

    cout << "Simulation terminee apres " << toursMax << " tours.\n";
    return 0;
}
