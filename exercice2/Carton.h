#ifndef CARTON_H_INCLUDED
#define CARTON_H_INCLUDED

#include "File.hpp"
#include "Piece.h"

class Carton {
public:
	Carton(const int &);
	~Carton();
	Piece sortirPiece();
	void afficherCarton();
	int getTaille();
private:
	int nbPieces;
	File<Piece> *pieces;
};

#endif