#include "Piece.h"
#include <iostream>

Piece::Piece(const TypePiece & t) {
	Piece::type = t;
}

Piece::~Piece() {
}

void Piece::afficherPiece() {
	std::cout << "Type : " << this->type << std::endl;
}

TypePiece Piece::getType() const {
	return this->type;
}

std::ostream & operator<<(std::ostream & flux, Piece const & piece) {
	flux << "Type : " << piece.getType();
	return flux;
}