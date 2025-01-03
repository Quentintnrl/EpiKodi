#include "Card.hpp"

Card::Card(const std::string &option) : option(option) {}

const std::string &Card::getOption() const {
    return option;
}

std::string Card::getOption() {
    return option;
}

std::ostream &operator<<(std::ostream &os, const Card &card) {
    os << card.getOption();
    return os;
}