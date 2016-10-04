#ifndef CARD_DEQUE_HPP
#define CARD_DEQUE_HPP

#include <memory>
#include <ostream>

#include "Deque.hpp"
#include "Card.hpp"

class CardDeque : public Deque<std::shared_ptr<Card>> {
public:
    // Constructors
    CardDeque(int max_size = 8): Deque<std::shared_ptr<Card>>(max_size) {}

    // Methods
    float score() const {
        float s = 0;
        for(int k = 0; k < size(); k++) {
            s += items[k]->points();
        }
        return s;
    }

    // Operators
    friend std::ostream& operator<<(std::ostream& output, const CardDeque& d);
};

std::ostream& operator<<(std::ostream& output, const CardDeque& d) {
    output << "[";
    if(d.size() > 0) {
        output << *d.items[0];
        for(int k = 1; k < d.size(); k++) {
            output << " " << *(d.items[k]);
        }
    }
    output << "]";
    return output;
}

#endif

