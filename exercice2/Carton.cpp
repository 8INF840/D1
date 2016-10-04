#include "Carton.h"
#include <cstdlib>
#include <ctime>
#include "File.hpp"
#include "TypePiece.h"

Carton::Carton(const int & nb) {
	// Création des attributs
	Carton::nbPieces = nb;
	Carton::pieces = new File<Piece>(nb);
	// Création des pièces du carton
	for (int i = 0; i < nb; i++) {
		int choix = rand() % 3;
		TypePiece type;
		switch (choix) {
		case 0: type = TypePiece::tete;
			break;
		case 1: type = TypePiece::jupe;
			break;
		case 2: type = TypePiece::axe;
			break;
		}
		Piece piece(type);
		Carton::pieces->enfiler(piece);
	}
}

Carton::~Carton() {
}

Piece Carton::sortirPiece() {
	return this->pieces->defiler();
}

void Carton::afficherCarton() {
	Carton::pieces->afficherFile();
}

int Carton::getTaille() {
	return this->nbPieces;
}
