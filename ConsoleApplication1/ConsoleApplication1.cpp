#include <iostream>
#include <string>
#include <vector>

class Personnage {
protected:
    std::string nom;
    int sante;
    int santeMax;
    int score;

public:
    Personnage(std::string n, int s) : nom(n), sante(s), santeMax(s), score(0) {}

    virtual void attaquer(Personnage& cible) {
        int degats = 10; //Dégâts standard
        cible.diminuerSante(degats);
        score += 10;
        std::cout << nom << " attaque " << cible.getNom() << " pour " << degats << " points de degats." << std::endl;
    }

    virtual void utiliserCompetenceSpeciale(Personnage& cible) = 0;

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
            }
        }

        // Suppression des personnages morts du jeu
        for (size_t i = 0; i < personnages.size(); ++i) {
            if (!personnages[i]->estVivant()) {
                delete personnages[i];  // Libération de la mémoire du personnage
                personnages.erase(personnages.begin() + i);
                --i;  // Ajustement de l'indice après la suppression
            }
        }

        // Arrêter le jeu si un seul personnage reste
        if (personnages.size() <= 1 || tour >= 10) {
            jeuActif = false;
            std::cout << "Le jeu est termine !" << std::endl;
            if (personnages.size() == 1) {
                std::cout << "Vainqueur : " << personnages[0]->getNom() << " avec un score de " << personnages[0]->getScore() << " !" << std::endl;
            }
        }
    }
}

int main() {
    //Création de personnages avec pointeurs bruts
    std::vector<Personnage*> personnages;
    personnages.push_back(new Guerrier("Guerrier"));
    personnages.push_back(new Archer("Archer"));

    //Lance la boucle de jeu
    boucleDeJeu(personnages);

    //Nettoie de la mémoire des personnages restants
    for (Personnage* personnage : personnages) {
        delete personnage;
    }

    return 0;
}
