#include "Turn.hpp"
#include <iostream>

Turn::Turn(const Card &option1, const Card &option2, const std::string &question)
    : option1(std::make_shared<Card>(option1)), option2(std::make_shared<Card>(option2)), question(question) {}

const std::shared_ptr<Card> &Turn::getOption1() const {
    return option1;
}

const std::shared_ptr<Card> &Turn::getOption2() const {
    return option2;
}

const std::string &Turn::getQuestion() const {
    return question;
}

//print operator
std::ostream &operator<<(std::ostream &os, const Turn &turn) {
    os << "Question: " << turn.getQuestion() << std::endl;
    os << "Option 1: " << *turn.getOption1() << std::endl;
    os << "Option 2: " << *turn.getOption2() << std::endl;
    return os;
}