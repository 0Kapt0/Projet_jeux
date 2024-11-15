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
        quantite += 40;
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
        if (Trefle::manger(4) && Trefle::quantite >= 4) {
            treflesManges += 4;
            Lapin::totalManges += 4;
        }
    }

     bool peutSeReproduire() const {
        return treflesManges >= 4 && eauBue >= 4;
    }

    void resetReproduction() {
        Lapin::totalManges = max(0, Lapin::totalManges - 2);  //Emp�che les valeurs n�gatives
        eauBue -= 4;
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
        if (Eau::boire(5)) eauBue += 5;
    }

    void manger(vector<Lapin>& lapins) {
        if (Renard::population >= 1 && Lapin::population >= 2) {
            int p = rand() % 2;
            if (p == 1) {
                if (lapins.size() >= 2) {
                    lapins.pop_back();
                    lapins.pop_back(); 
                    Lapin::population -= 2;
                    Renard::totalManges += 2;
                }
                else if (lapins.size() >= 1) {
                    Lapin::fuites++;
                }
            }
        }
        
    }

    bool peutSeReproduire() const {
        return Lapin::totalManges >= 2 && eauBue >= 5;
    }

    void resetReproduction() {
        eauBue -= 5;
        Renard::totalManges = max(0, Renard::totalManges - 2);  //Emp�che les valeurs n�gatives
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
        if (Eau::boire(8)) eauBue += 8;
    }

    void manger(vector<Renard>& renards) {
        if (Aigle::population >= 1 && Renard::population >= 2) {
            int p = rand() % 2;
            if (p == 1) {
                if (renards.size() >= 2) {
                    renards.pop_back();
                    renards.pop_back();
                    Renard::population -= 2;
                    Aigle::totalManges += 2;
                }
                else if (renards.size() >= 1) {
                    Renard::fuites++;
                }
            }
        }
    }

    bool peutSeReproduire() const {
        return Aigle::totalManges >= 2 && eauBue >= 8;
    }

    void resetReproduction() {
        eauBue -= 8;
        Aigle::totalManges = max(0, Aigle::totalManges - 2);  //Emp�che les valeurs n�gatives
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

    for (int i = 0; i <= 50; ++i) {
        cout << "-";
    }
    cout << "\n\n";

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


void modifierPopulations() {
    int choix, souschoix;
    cout << "Choisissez la population que vous voulez controler :\n";
    cout << "1. Aigles\n";
    cout << "2. Renards\n";
    cout << "3. Lapins\n";
    cout << "4. Retourner au menu principal\n";
    cout << "Votre choix : ";
    cin >> choix;

    if (choix == 4) return;

    switch (choix) {
    case 1:
        Aigle::population;
        break;
    case 2:
        Renard::population;
        break;
    case 3:
        Lapin::population;
        break;
    default:
        cout << "Choix invalide.\n";
        return;
    }
    
    cout << "Choisissez une action a modifier pour cette population :\n";
    cout << "1. Ajouter 1 en reproduction\n";
    cout << "2. Ajouter 1 en chasser\n";
    cout << "3. Reduire une espece de 1\n";
    cout << "Votre choix : ";
    cin >> souschoix;

    switch (souschoix) {
    case 1:
        switch (choix) {
        case 1:
            Aigle::population += 1;
            cout << "Reproduction d'Aigles augmentee de 1.\n";
            break;
        case 2:
            Renard::population += 1;
            cout << "Reproduction de Renards augmentee de 1.\n";
            break;
        case 3:
            Lapin::population += 1;
            cout << "Reproduction de Lapins augmentee de 1.\n";
            break;
        default:
            cout << "Choix invalide.\n";
            break;
        }
        break;

    case 2:
        switch (choix) {
        case 1:
            Aigle::totalManges += 1;
            Renard::population -= 1;
            cout << "Chasse des Aigles augmentee de 1.\n";
            break;
        case 2:
            Renard::totalManges += 1;
            Lapin::totalManges -= 1;
            cout << "Chasse des Renards augmentee de 1.\n";
            break;
        case 3:
            Lapin::totalManges += 1;
            Trefle::quantite -= 4;
            cout << "La nourriture des Lapins augmentee de 4.\n";
            break;
        default:
            cout << "Choix invalide.\n";
            break;
        }
        break;

    case 3:
        switch (choix) {
        case 1:
            Aigle::population -= 1;
            cout << "Nombres d'Aigles reduit de 1.\n";
            break;
        case 2:
            Renard::population -= 1;
            cout << "Nombre de Renards reduit de 1.\n";
            break;
        case 3:
            Lapin::population -= 1;
            cout << "Nombre de Lapins reduit de 1.\n";
            break;
        default:
            cout << "Choix invalide.\n";
            break;
        }
        break;

    default:
        cout << "Choix invalide.\n";
        break;
    }
}

int main() {
    vector<Aigle> aigles(Aigle::population);
    vector<Renard> renards(Renard::population);
    vector<Lapin> lapins(Lapin::population);

    srand(time(0));

    cout << "Yokoso watashi no soul society !\n\n";

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
        // R�initialisation des statistiques
        Lapin::fuites = 0;
        Lapin::totalManges = 0;
        Lapin::reproductions = 0;

        Renard::fuites = 0;
        Renard::totalManges = 0;
        Renard::reproductions = 0;

        Aigle::totalManges = 0;
        Aigle::reproductions = 0;

        int choix;
        cout << "Voulez-vous :\n";
        cout << "1. Passer au tour suivant\n";
        cout << "2. Choisir une espece\n";
        cout << "3. Quitter la simulation\n";
        cout << "Votre choix : ";
        cin >> choix;

        // Actions de chaque type d'individu
        for (auto& lapin : lapins) {
            lapin.boire();
            lapin.manger();
        }
        Lapin::reproduire(lapins);

        for (auto& renard : renards) {
            renard.boire();
            renard.manger(lapins);
        }
        Renard::reproduire(renards);

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

        // Interaction avec l'utilisateur
        

        if (choix == 2) {
            modifierPopulations();
            // Mise � jour des vecteurs avec les nouvelles populations
            aigles.resize(Aigle::population);
            renards.resize(Renard::population);
            lapins.resize(Lapin::population);
        }
        else if (choix == 3) {
            cout << "Simulation terminee apres " << tour + 1 << " tours.\n";
            break;
        }
    }

    cout << "Simulation terminee apres " << toursMax << " tours.\n";
    return 0;
}
