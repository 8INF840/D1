#ifndef MACHINE_H_INCLUDED
#define MACHINE_H_INCLUDED

#include "File.hpp"
#include "Piece.h"
#include "TypePiece.h"
#include "EtatMachine.h"

class Machine {
public:
	Machine(const TypePiece & type = TypePiece::tete, const float & tempsPiece = 2);
	~Machine();
	void usinerPiece(File<Piece> *pieces, File<Piece> *piecesUsinees, const float & tempsIteration);
	void usinerPiston(File<Piece> *tetesUsinees, File<Piece> *jupesUsinees, File<Piece> *axesUsines, File<Piece> *pistons, const float & tempsIteration);
	float genererPanne();
	void afficherPanne(const TypePiece &, const bool &);
	void finPiece(const TypePiece &);
private:
	TypePiece type;
	EtatMachine etat;
	Piece* pieceCourante;
	float tempsUsinage;
	float tempsPieceCourante;
	float tempsPanne;
};

#endif