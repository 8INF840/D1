#pragma once

#include <stdexcept>
#include <iostream>

// --------------------------- Déclaration des méthodes ---------------------------

template<typename T>
class File {
public:
	// Constructeur et destructeur
	File(const int& taille = 1000);
	File(const File& file);
	~File();
	// Modificateurs
	void enfiler(const T& element);
	T defiler();
	// Selecteurs
	int taille() const;
	bool estVide() const;
	bool estPleine() const;
	// Tete de la file
	const T& premier() const;
	// Queue de la file
	const T& dernier() const;
	// Afficher la file
	void afficherFile();
private:
	// Taille par défaut de la file
	static const int TAILLE_DEFAUT = 1000;
	// La file
	T *file;
	// Indice de la tete de la file
	int tete;
	// Indice de la queue de la file
	int queue;
	// Nombre d'éléments
	int nbElements;
	// La taille max actuelle de la file
	int tailleMax;
};

// ------------------------------ Corps des méthodes ------------------------------

template<typename T>
File<T>::File(const int & taille) {
	int t = taille;
	if (taille < 0) {
		t = File::TAILLE_DEFAUT;
	}
	File::file = new T[t];
	File::tete = 0;
	File::queue = 0;
	File::nbElements = 0;
	File::tailleMax = t;
}

template<typename T>
File<T>::File(const File & file) {
	// Copie des attributs
	File::tete = file.tete;
	File::queue = file.queue;
	File::nbElements = file.nbElements;
	File::tailleMax = file.tailleMax * 2;
	// Copie de la file
	int indice;
	T *nouvelleFile = new T[file.tailleMax * 2];
	for (int i = 0; i < file.nbElements; i++) {
		indice = (i + file.tete) % tailleMax;
		nouvelleFile[indice] = file.file[indice];
	}
	File::file = nouvelleFile;
}

template<typename T>
File<T>::~File() {
	delete file;
}

template<typename T>
void File<T>::enfiler(const T & element) {
	// Si la file n'est pas déjà pleine
	if (this->nbElements < this->tailleMax) {
		this->file[this->queue++%this->tailleMax] = element;
		this->nbElements++;
	}
}

template<typename T>
T File<T>::defiler() {
	// Si la file contient au moins un élément
	if (this->nbElements > 0) {
		T obj = this->file[this->tete++%this->tailleMax];
		this->nbElements--;
		return obj;
	}
	else {
		throw std::logic_error("File vide");
	}
}

template<typename T>
int File<T>::taille() const {
	return this->nbElements;
}

template<typename T>
bool File<T>::estVide() const {
	return this->nbElements == 0;
}

template<typename T>
bool File<T>::estPleine() const {
	return this->nbElements == this->tailleMax;
}

template<typename T>
const T & File<T>::premier() const {
	T obj = 0;
	// Si la file contient au moins un élément
	if (this->nbElements > 0) {
		obj = this->file[this->tete];
	}
	return obj;
}

template<typename T>
const T & File<T>::dernier() const {
	T obj = 0;
	// Si la file contient au moins un élément
	if (this->nbElements > 0) {
		obj = this->file[this->queue - 1];
	}
	return obj;
}

template<typename T>
void File<T>::afficherFile() {
	// Affichage de la taille max
	int tailleMax = this->tailleMax;
	std::cout << "Taille max: " << tailleMax << std::endl;
	// Affichage du nombre d'éléments
	int nbElements = this->nbElements;
	std::cout << "Nombre d'elements: " << nbElements << std::endl;
	// Affichage des éléments
	for (int i = 0; i < nbElements; i++) {
		std::cout << this->file[(i + this->tete) % tailleMax] << std::endl;
	}
	// Affichage indices premier et dernier
	std::cout << "Indice premier : " << this->tete << std::endl;
	std::cout << "Indice dernier : " << this->queue << std::endl;
}
