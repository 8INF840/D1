#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Usine.h"

int nombrePistons();
int tailleCarton(const int & nbPistons);
float tempsIteration();

int main() {
	// Choix du nombre de pistons
	int nbPistons = nombrePistons();
	// Choix de la taille du carton
	int tailleC = tailleCarton(nbPistons);
	// Choix du pas de temps
	float pas = tempsIteration();
	// Création de l'usine et lancement de la production
	Usine usine(tailleC, pas);
	usine.lancerProduction(nbPistons, tailleC);
	system("PAUSE");
}

int nombrePistons() {
	int nbPistons = 0;
	while (nbPistons <=0) {
		std::cout << "# Nombre de pistons a fabriquer : ";
		std::string entree;
		std::getline(std::cin, entree);
		nbPistons = atoi(entree.c_str());
		if (nbPistons <= 0) {
			std::cout << "# Erreur : Le nombre de pistons a fabriquer doit etre positif." << std::endl;
		}
	}
	return nbPistons;
}

int tailleCarton(const int & nbPistons) {
	int tailleCarton = 0;
	while (tailleCarton < 4*nbPistons) {
		std::cout << "# Taille du carton de pieces en entree : ";
		std::string entree;
		std::getline(std::cin, entree);
		tailleCarton = atoi(entree.c_str());
		if (tailleCarton < 4*nbPistons) {
			std::cout << "# Erreur : La taille du carton doit valoir au moins 4 fois le nombre de pistons a fabriquer." << std::endl;
		}
	}
	return tailleCarton;
}

float tempsIteration() {
	float temps = 0;
	while (temps <= 0) {
		std::cout << "# Temps par iteration de l'algorithme : ";
		std::string entree;
		std::getline(std::cin, entree);
		temps = (double)atof(entree.c_str());
		if (temps <= 0) {
			std::cout << "# Erreur : Le pas de temps doit être positif." << std::endl;
		}
	}
	return temps;
}