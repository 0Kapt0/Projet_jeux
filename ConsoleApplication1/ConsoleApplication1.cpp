#include <iostream>
#include <vector>

using namespace std;

// Classes Eau, Trefle, Lapin, Renard, Aigle et leurs implémentations ici...

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

void modifierPopulations() {
    int choix, nb;

    cout << "Choisissez la population à modifier :\n";
    cout << "1. Aigles\n";
    cout << "2. Renards\n";
    cout << "3. Lapins\n";
    cout << "4. Retourner au menu principal\n";
    cout << "Votre choix : ";
    cin >> choix;

    if (choix == 4) return;

    cout << "Entrez le nouveau nombre : ";
    cin >> nb;

    switch (choix) {
    case 1:
        Aigle::population = nb;
        break;
    case 2:
        Renard::population = nb;
        break;
    case 3:
        Lapin::population = nb;
        break;
    default:
        cout << "Choix invalide.\n";
    }
    cout << "Population modifiée avec succès !\n\n";
}

int main() {
    vector<Aigle> aigles(Aigle::population);
    vector<Renard> renards(Renard::population);
    vector<Lapin> lapins(Lapin::population);

    cout << "Bienvenue dans le jeu de la foret !\n\n";

    const int toursMax = 15;
    for (int tour = 0; tour < toursMax; ++tour) {
        // Réinitialisation des statistiques
        Lapin::fuites = 0;
        Lapin::totalManges = 0;
        Lapin::reproductions = 0;

        Renard::fuites = 0;
        Renard::totalManges = 0;
        Renard::reproductions = 0;

        Aigle::totalManges = 0;
        Aigle::reproductions = 0;

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
        int choix;
        cout << "Voulez-vous :\n";
        cout << "1. Passer au tour suivant\n";
        cout << "2. Modifier le nombre d'individus\n";
        cout << "3. Quitter la simulation\n";
        cout << "Votre choix : ";
        cin >> choix;

        if (choix == 2) {
            modifierPopulations();
            // Mise à jour des vecteurs avec les nouvelles populations
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
