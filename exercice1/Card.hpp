#ifndef CARD_HPP
#define CARD_HPP

class Card {
private:
    bool color;
    int value;
    int power;
public:
    Card(bool color, int value, int power): color{color}, value{value},
            power{power} {}
    float points() const {
        return (color ? 1.5 : 1) * value * power;
    }

    bool beats(const Card& c) {
        return c.value < this->value || (this->color && !c.color);
    }
    friend std::ostream& operator<<(std::ostream& output, const Card& c) {
        output << c.value << (c.color ? "R" : "N") << "^" << c.power;
        return output;
    }
};


#endif
