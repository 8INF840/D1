#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>
#include <assert.h>

template <class T>
class Deque {
public:
    // Constructors
    Deque(int max_size = 8);
    Deque(const Deque<T>& d);
    // ~Deque();

    // Setters
    T pop();
    void push(T t);

    // Getters
    T top() const;
    bool isEmpty() const;
    int size() const;

    // Operators
    const Deque<T>& operator=(const Deque<T>& d);
    template <class U>
    friend std::ostream& operator<<(std::ostream& output, const Deque<U>& d);
protected:
    std::unique_ptr<T[]> items;
    int p;
    int max_size;
};

/* CONSTRUCTORS */
template <class T>
Deque<T>::Deque(int max_size): max_size{max_size}, p{-1} {
    this->items.reset(new T[max_size]);
}
template <class T>
Deque<T>::Deque(const Deque<T>& d) {
    this->p = -1;
    this->max_size = d.max_size;
    this->items = std::make_unique<T[]>(this->max_size);
    while(this->p < d.p) {
        this->p++;
        this->items[this->p] = d.items[this->p];
    }
}

/* SETTERS */
template <class T>
T Deque<T>::pop() {
    assert(!this->isEmpty());
    return this->items[this->p--];
}

template <class T>
void Deque<T>::push(T t) {
    // Si la pile a atteint la taille limite du tableau actuel
    if(this->p + 1 == this->max_size) {
        // Créer un nouveau tableau de taille double
        this->max_size *= 2;
        std::unique_ptr<T[]> new_items = std::make_unique<T[]>(this->max_size);
        // Recopier les anciens éléments
        for(int k = 0; k < this->max_size / 2; k++) {
            new_items[k] = this->items[k];
        }
        // Echanger les deux tableaux
        this->items = std::move(new_items);
    }
    // Ajouter l'élément à la position courante et incrémenter cette position
    this->items[++this->p] = t;
}

/* GETTERS */
template <class T>
T Deque<T>::top() const {
    assert(!this->isEmpty());
    return this->items[this->p];
}

template <class T>
bool Deque<T>::isEmpty() const {
    return this->p == -1;
}

template <class T>
int Deque<T>::size() const {
    return this->p + 1;
}

/* OPERATORS */
template <class T>
const Deque<T>& Deque<T>::operator=(const Deque<T>& d) {
    this->max_size = d.max_size;
    this->items = std::make_unique<T[]>(this->max_size);
    this->p = -1;
    while(this->p < d.p) {
        this->p++;
        this->items[this->p] = d.items[this->p];
    }
    return *this;
}

template <class T>
std::ostream& operator<<(std::ostream& output, const Deque<T>& d) {
    output << "[";
    if(d.size() > 0) {
        output << d.items[0];
        for(int k = 1; k < d.size(); k++) {
            output << " " << d.items[k];
        }
    }
    output << "]";
    return output;
}

#endif
