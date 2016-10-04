#ifndef USINE_H_INCLUDED
#define USINE_H_INCLUDED

#include "File.hpp"
#include "Machine.h"
#include "Piece.h"
#include "Carton.h"

class Usine {
public:
	Usine(const int tailleCarton, const float tempsIteration);
	~Usine();
	int lancerProduction(const int nbPistons, const int tailleCarton);
	void sortirPieces(Carton &);
	void afficherFiles();
	void afficherTemps();
private:
	float tempsIteration;
	File<Piece> *tetes;
	File<Piece> *jupes;
	File<Piece> *axes;
	File<Piece> *tetesUsinees;
	File<Piece> *jupesUsinees;
	File<Piece> *axesUsines;
	File<Piece> *pistons;
	Machine *MT;
	Machine *MJ;
	Machine *MA;
	Machine *MP;
	int nbIterations;
};

#endif