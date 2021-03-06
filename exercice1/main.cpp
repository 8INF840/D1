#include <iostream>
#include <string>
#include <random>
#include <memory>
// Pour la couleur
#include <cstdio>
#include <functional>

#include "Card.hpp"
#include "CardDeque.hpp"


int main() {
    bool again;
    do {
        // Choix du nombre de cartes par joueur
        int n;
        std::printf("%c[1;31m", 27); // Red
        std::cout << "# Initialisation du jeu :" << std::endl;
        std::printf("%c[1;37m", 27); // White
        std::cout << "Nombre de cartes pour chaque joueur : ";
        std::cin >> n;

        // Génération des cartes aléatoires
        CardDeque dequeArbitre(2 * n);
        std::shared_ptr<Card> cardArbitre;
        std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<int> valueDist(1, 10);
        auto values = std::bind(valueDist, generator);
        std::uniform_int_distribution<int> colorDist(0, 1);
        auto colors = std::bind(colorDist, generator);
        std::uniform_int_distribution<int> powerDist(1, 4);
        auto powers = std::bind(powerDist, generator);
        for(int k = 0; k < 2 * n; k++) {
            bool color = colors() == 1;
            int value = values();
            int power = powers();
            cardArbitre = std::make_shared<Card>(color, value, power);
            dequeArbitre.push(cardArbitre);
        }

        // Répartition des cartes selon les joueurs
        CardDeque dequeJoueurUn(n);
        CardDeque dequeJoueurDeux(n);
        for(int k = 0; k < n; k++) {
            dequeJoueurUn.push(dequeArbitre.pop());
            dequeJoueurDeux.push(dequeArbitre.pop());
        }
        std::cout << "Cartes initiales du joueur 1 : " << dequeJoueurUn << std::endl;
        std::cout << "Cartes initiales du joueur 2 : " << dequeJoueurDeux << std::endl;
        std::cout << "Score du joueur 1 : " << dequeJoueurUn.score() << std::endl;
        std::cout << "Score du joueur 2 : " << dequeJoueurDeux.score() << std::endl;

        // Lancement
        std::printf("%c[1;31m", 27); // Red
        std::cout << std::endl << "# Déroulement du jeu :" << std::endl;
        std::printf("%c[1;37m", 27); // White
        CardDeque gainsJoueurUn;
        CardDeque gainsJoueurDeux;
        for(int k = 0; k < n; k++) {
            // Récupération de la carte au dessus des paquets
            std::shared_ptr<Card> cardJoueurUn = dequeJoueurUn.pop();
            std::shared_ptr<Card> cardJoueurDeux = dequeJoueurDeux.pop();
            std::cout << *cardJoueurUn << " vs " << *cardJoueurDeux << std::endl;

            // Désignation de la cart gagnante
            if(cardJoueurUn->beats(*cardJoueurDeux)) {
                gainsJoueurUn.push(cardJoueurUn);
                gainsJoueurUn.push(cardJoueurDeux);
            }
            else if(cardJoueurDeux->beats(*cardJoueurUn)) {
                gainsJoueurDeux.push(cardJoueurDeux);
                gainsJoueurDeux.push(cardJoueurUn);
            }
            else {
                gainsJoueurUn.push(cardJoueurUn);
                gainsJoueurDeux.push(cardJoueurDeux);
            }
        }

        // Calcul des scores
        std::printf("%c[1;31m", 27); // Red
        std::cout << std::endl << "# Fin du jeu :" << std::endl;
        std::printf("%c[1;37m", 27); // White
        std::cout << "Cartes gagnées du joueur 1 : " << gainsJoueurUn << std::endl;
        std::cout << "Cartes gagnées du joueur 2 : " << gainsJoueurDeux << std::endl;
        std::cout << "Score du joueur 1 : " << gainsJoueurUn.score() << std::endl;
        std::cout << "Score du joueur 2 : " << gainsJoueurDeux.score() << std::endl;

        std::cout << std::endl;
        bool answer = false;
        while(!answer) {
            std::string doAgain;
            std::cout << "Recommencer ? (oui/non)";
            std::cin >> doAgain;
            if(doAgain.compare("oui") == 0) {
                answer = true;
                again = true;
            }
            else if(doAgain.compare("non") == 0) {
                answer = true;
                again = false;
            }
        }
        std::cout << std::endl;
    } while(again);
}
