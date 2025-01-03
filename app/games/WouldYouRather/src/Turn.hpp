#pragma once

#include "Card.hpp"
#include <memory>

class Turn {
public:
    Turn(const Card &option1, const Card &option2, const std::string &question);
    ~Turn() = default;
    const std::shared_ptr<Card> &getOption1() const;
    const std::shared_ptr<Card> &getOption2() const;
    const std::string &getQuestion() const;
    friend std::ostream &operator<<(std::ostream &os, const Turn &turn);
private:
    const std::shared_ptr<Card> option1;
    const std::shared_ptr<Card> option2;
    const std::string question;
};