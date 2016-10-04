#include "Machine.h"
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstdio>

Machine::Machine(const TypePiece & t, const float & tp) {
	// Initialisation des attributs
	Machine::type = t;
	Machine::etat = EtatMachine::libre;
	Machine::pieceCourante = 0;
	Machine::tempsUsinage = tp;
	Machine::tempsPieceCourante = 0;
	Machine::tempsPanne = 0;
}

Machine::~Machine() {
}

void Machine::usinerPiece(File<Piece> *pieces, File<Piece> *piecesUsinees, const float & tempsIteration) {
	switch (this->etat) {
	// Si la machine est libre
	case EtatMachine::libre:
		// Si au moins une pièce est disponible
		if (!pieces->estVide()) {
			this->pieceCourante = &pieces->defiler();
			this->etat = EtatMachine::occupee;
			this->tempsPieceCourante = this->tempsUsinage;
		}
		break;
	// Si la machine est en train d'usiner une pièce
	case EtatMachine::occupee :
		this->tempsPieceCourante = this->tempsPieceCourante - tempsIteration;
		// Si on a terminé d'usiner la pièce
		if (this->tempsPieceCourante <=0) {
			// On ajoute la pièce usinée
			if (!piecesUsinees->estPleine()) {
				piecesUsinees->enfiler(*this->pieceCourante);
				this->finPiece(this->type);
				this->pieceCourante = 0;
			}
			int panne = this->genererPanne();
			// Si la machine est tombée en panne
			if (panne > 0) {
				this->tempsPanne = panne;
				this->etat = EtatMachine::panne;
				this->afficherPanne(this->type,true);
			} else {
				this->etat = EtatMachine::libre;
			}
		}
		break;
	// Si la machine est en panne
	case EtatMachine::panne :
		this->tempsPanne = this->tempsPanne - tempsIteration;
		// Si la panne est terminée
		if (this->tempsPanne <= 0) {
			this->etat = EtatMachine::libre;
			this->afficherPanne(this->type, false);
		}
		break;
	}
}

void Machine::usinerPiston(File<Piece>* tetesUsinees, File<Piece>* jupesUsinees, File<Piece>* axesUsines, File<Piece>* pistons, const float & tempsIteration) {
	switch (this->etat) {
	case EtatMachine::libre:
		// Si au moins une pièce est disponible dans chaque file
		if (!tetesUsinees->estVide() && !jupesUsinees->estVide() && !axesUsines->estVide()) {
			// On défile les trois pièces usinées
			tetesUsinees->defiler();
			jupesUsinees->defiler();
			axesUsines->defiler();
			this->etat = EtatMachine::occupee;
			this->tempsPieceCourante = this->tempsUsinage;
		}
		break;
	case EtatMachine::occupee:
		this->tempsPieceCourante = this->tempsPieceCourante - tempsIteration;
		// Si on a terminé d'usiner la pièce
		if (this->tempsPieceCourante <= 0) {
			// On ajoute le piston
			if (!pistons->estPleine()) {
				pistons->enfiler(Piece(TypePiece::piston));
				this->finPiece(TypePiece::piston);
				this->pieceCourante = 0;
			}
			float panne = this->genererPanne();
			// Si la machine est tombée en panne
			if (panne > 0) {
				this->tempsPanne = panne;
				this->etat = EtatMachine::panne;
				this->afficherPanne(this->type, true);
			}
			else {
				this->etat = EtatMachine::libre;
			}
		}
		break;
	case EtatMachine::panne:
		this->tempsPanne = this->tempsPanne - tempsIteration;
		// Si la panne est terminée
		if (this->tempsPanne <= 0) {
			this->etat = EtatMachine::libre;
			this->afficherPanne(this->type, false);
		}
		break;
	}
}

float Machine::genererPanne() {
	float tempsPanne = 0;
	if (rand() % 4 == 0) {
		tempsPanne = rand() % 5 + 5;
	}
	return tempsPanne;
}

void Machine::afficherPanne(const TypePiece & type, const bool & debut) {
	int couleur = 7;
	std::string texte = "";
	// Si début de la panne
	if (debut) {
		texte = "Debut panne : ";
	}
	// Si fin de la panne
	else {
		texte = "Fin panne : ";
	}
	// Rajouter type machine
	switch (type) {
	case TypePiece::tete:
		texte = texte + "MT";
		couleur = 2;
		break;
	case TypePiece::jupe:
		texte = texte + "MJ";
		couleur = 4;
		break;
	case TypePiece::axe:
		texte = texte + "MA";
		couleur = 3;
		break;
	case TypePiece::piston:
		texte = texte + "MP";
		couleur = 1;
		break;
	}
    auto color = ("%c[1;3" + std::to_string(couleur) + "m").c_str();
    std::printf(color, 27);
	std::cout << texte << std::endl;
	// On rétablit la couleur à blanc
    std::printf("%c[1;37m", 27);
}

void Machine::finPiece(const TypePiece & type) {
	int couleur = 7;
	std::string texte = "";
	switch (type) {
	case TypePiece::tete :
		texte = "Tete fabriquee";
		couleur = 2;
		break;
	case TypePiece::jupe:
		texte = "Jupe fabriquee";
		couleur = 4;
		break;
	case TypePiece::axe:
		texte = "Axe fabrique";
		couleur = 3;
		break;
	case TypePiece::piston:
		texte = "Piston fabrique";
		couleur = 1;
		break;
	}
    auto color = ("%c[1;3" + std::to_string(couleur) + "m").c_str();
    std::printf(color, 27);
	std::cout << texte << std::endl;
	// On rétablit la couleur à blanc
    std::printf("%c[1;37m", 27);
}
