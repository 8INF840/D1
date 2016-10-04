#include "Usine.h"
#include <cstdlib>
#include <ctime>
#include "TypePiece.h"

Usine::Usine(const int tailleCarton, const float tempsIteration) {
	// Initialisation des files
	Usine::tetes = new File<Piece>(tailleCarton);
	Usine::jupes = new File<Piece>(tailleCarton);
	Usine::axes = new File<Piece>(tailleCarton);
	Usine::tetesUsinees = new File<Piece>(tailleCarton);
	Usine::jupesUsinees = new File<Piece>(tailleCarton);
	Usine::axesUsines = new File<Piece>(tailleCarton);
	Usine::pistons = new File<Piece>(tailleCarton);
	// Initialisation des machines
	Usine::MT = new Machine(TypePiece::tete, 2);
	Usine::MJ = new Machine(TypePiece::jupe, 3);
	Usine::MA = new Machine(TypePiece::axe, 2.5);
	Usine::MP = new Machine(TypePiece::piston, 1);
	// Initialisation du temps (en min) représenté par une itération
	Usine::tempsIteration = tempsIteration;
	// Initialisation du nombre d'itérations
	Usine::nbIterations = 0;
}

Usine::~Usine() {
}

int Usine::lancerProduction(const int nbPistons, const int tailleCarton) {
	srand(time(NULL));
	// Création du carton
	Carton carton(tailleCarton);
	// Sortie des pièces du carton
	this->sortirPieces(carton);
	std::cout << "# Etat au depart :" << std::endl;
	this->afficherFiles();
	// Tant que les pistons n'ont pas été créés
	while (this->pistons->taille() < nbPistons) {
		this->afficherTemps();
		// On commence par le piston : on ne peut pas utiliser une pièce usinée à la même itération
		this->MP->usinerPiston(this->tetesUsinees, this->jupesUsinees, this->axesUsines, this->pistons, this->tempsIteration);
		this->MT->usinerPiece(this->tetes, this->tetesUsinees,this->tempsIteration);
		this->MJ->usinerPiece(this->jupes, this->jupesUsinees, this->tempsIteration);
		this->MA->usinerPiece(this->axes, this->axesUsines, this->tempsIteration);
		this->nbIterations++;
	}
	return 0;
}

void Usine::sortirPieces(Carton & carton) {
	int nbPieces = carton.getTaille();
	for (int i = 0; i < nbPieces; i++) {
		Piece pieceCourante = carton.sortirPiece();
		TypePiece type = pieceCourante.getType();
		switch (type) {
		case TypePiece::tete: this->tetes->enfiler(pieceCourante);
			break;
		case TypePiece::jupe : this->jupes->enfiler(pieceCourante);
			break;
		case TypePiece::axe : this->axes->enfiler(pieceCourante);
			break;
		default : throw std::logic_error("# Un piston ne peut pas se trouver dans le carton");
			break;
		}
	}
}

void Usine::afficherFiles() {
	std::cout << "~~~~~~~ TETES : ~~~~~~~" << std::endl;
	this->tetes->afficherFile();
	std::cout << "~~~~~~~ JUPES : ~~~~~~~" << std::endl;
	this->jupes->afficherFile();
	std::cout << "~~~~~~~ AXES : ~~~~~~~" << std::endl;
	this->axes->afficherFile();
	std::cout << "~~~~~~~ PISTONS : ~~~~~~~" << std::endl;
	this->pistons->afficherFile();
}

void Usine::afficherTemps() {
	std::cout << "~~~~~~~ t = " << this->nbIterations*this->tempsIteration << " min ~~~~~~~" << std::endl;
}