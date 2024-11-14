#include <iostream>
#include <vector>

using namespace std;

class Eau {
public:
    static int quantite;

    static void produire() {
        quantite += 30;
    }

    static bool boire(int quantiteBoire) {
        if (quantite >= quantiteBoire) {
            quantite -= quantiteBoire;
            return true;
        }
        return false;
    }
};
int Eau::quantite = 300;

class Trefle {
public:
    static int quantite;

    static void produire() {
        quantite += 30;
    }

    static bool manger(int quantiteManger) {
        if (quantite >= quantiteManger) {
            quantite -= quantiteManger;
            return true;
        }
        return false;
    }
};
int Trefle::quantite = 150;

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
        return treflesManges >= 2 && eauBue >= 2;
    }

    void resetReproduction() {
        treflesManges -= 2;
        eauBue -= 2;
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
int Lapin::fuites = 0;

class Renard {
public:
    static int population;
    static int totalManges;
    static int reproductions;
    static int fuites;

    int eauBue = 0;

    void boire() {
        if (Eau::boire(4)) eauBue += 8;
    }

    void manger(vector<Lapin>& lapins) {
        if (Lapin::population >= 1) {
            int p = rand() % 2;
            if (p == 1) {
                if (lapins.size() >= 2) {
                    lapins.erase(lapins.end() - 2, lapins.end());
                    Lapin::population -= 2;
                    Lapin::totalManges += 2;
                    Renard::totalManges += 2;
                }
            }
            else if (Lapin::population >= 1) {
                Lapin::fuites++;
            }
        }
        
    }

    bool peutSeReproduire() const {
        return Lapin::totalManges >= 2 && eauBue >= 4;
    }

    void resetReproduction() {
        eauBue -= 4;
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
int Renard::fuites = 0;

class Aigle {
public:
    static int population;
    static int totalManges;
    static int reproductions;

    int eauBue = 0;

    void boire() {
        if (Eau::boire(4)) eauBue += 10;
    }

    void manger(vector<Renard>& renards) {
        if (Renard::population >= 1) {
            int p = rand() % 2;
            if (p == 1) {
                if (renards.size() >= 2) {
                    renards.erase(renards.end() - 2, renards.end());
                    Renard::population -= 2;
                    Renard::totalManges += 2;
                    Aigle::totalManges += 2;
                }
            }
            else if (Renard::population >= 1) {
                Renard::fuites++;
            }
        }
    }

    bool peutSeReproduire() const {
        return Renard::totalManges >= 2 && eauBue >= 10;
    }

    void resetReproduction() {
        eauBue = 5;
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
int Aigle::totalManges = 0;
int Aigle::reproductions = 0;

void afficherStats(int tour) {
    cout << "Tour " << tour + 1 << ":\n";

    cout << "Aigles: " << Aigle::population << "\n";
    cout << "Nb de renards chasses: " << Aigle::totalManges << "\n";
    cout << "Nb de reproductions: " << Aigle::reproductions << "\n\n";

    cout << "Renards: " << Renard::population << "\n";
    cout << "Nb de lapins chasses: " << Renard::totalManges << "\n";
    cout << "Nb de reproductions: " << Renard::reproductions << "\n";
    cout << "Nb de fuites: " << Renard::fuites << "\n\n";

    cout << "Lapins: " << Lapin::population << "\n";
    cout << "Nb de trefles manges: " << Lapin::totalManges << "\n";
    cout << "Nb de reproductions: " << Lapin::reproductions << "\n";
    cout << "Nb de fuites: " << Lapin::fuites << "\n\n";

    cout << "Quantite d'eau restante: " << Eau::quantite << "\n";
    cout << "Quantite de trefles restants: " << Trefle::quantite << "\n\n";
    for (int i = 0; i <= 50; ++i) {
        cout << "-";
    }
    cout << "\n\n";
}

int main() {
    vector<Aigle> aigles(Aigle::population);
    vector<Renard> renards(Renard::population);
    vector<Lapin> lapins(Lapin::population);

    srand(static_cast<unsigned>(time(0))); //initailise le rand sur le temps pour le rendre vraiment aleatoire

    cout << "Bienvenue Dans le jeu de la foret:" << "\n\n";

    for (int i = 0; i <= 50; ++i) {
        cout << "-";
    }
    cout << "\n\n";

    cout << "Aigles: " << Aigle::population << "\n";
    cout << "Nb de renards chasses: " << Aigle::totalManges << "\n";
    cout << "Nb de reproductions: " << Aigle::reproductions << "\n\n";

    cout << "Renards: " << Renard::population << "\n";
    cout << "Nb de lapins chasses: " << Renard::totalManges << "\n";
    cout << "Nb de reproductions: " << Renard::reproductions << "\n";
    cout << "Nb de fuites: " << Renard::fuites << "\n\n";

    cout << "Lapins: " << Lapin::population << "\n";
    cout << "Nb de trefles manges: " << Lapin::totalManges << "\n";
    cout << "Nb de reproductions: " << Lapin::reproductions << "\n";
    cout << "Nb de fuites: " << Lapin::fuites << "\n\n";

    cout << "Quantite d'eau restante: " << Eau::quantite << "\n";
    cout << "Quantite de trefles restants: " << Trefle::quantite << "\n\n";
    for (int i = 0; i <= 50; ++i) {
        cout << "-";
    }
    cout << "\n\n";

    const int toursMax = 15;
    for (int tour = 0; tour < toursMax; ++tour) {
        Lapin::fuites = 0;
        Lapin::reproductions = 0;
        Lapin::totalManges = 0;

        Renard::fuites = 0;
        Renard::reproductions = 0;
        Renard::totalManges = 0;

        Aigle::reproductions = 0;
        Aigle::totalManges = 0;

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
