#ifndef PIECE_H_INCLUDED
#define PIECE_H_INCLUDED

#include <iostream>
#include "TypePiece.h"

class Piece {
public:
	Piece(const TypePiece & type = TypePiece::tete);
	~Piece();
	void afficherPiece();
	TypePiece getType() const;
private:
	TypePiece type;
};

std::ostream& operator<<(std::ostream &flux, Piece const & piece);

#endif