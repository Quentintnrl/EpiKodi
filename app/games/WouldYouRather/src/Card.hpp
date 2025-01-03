#pragma once

#include <string>

class Card final {
    public:
        Card(const std::string &option);
        ~Card() = default;
        const std::string &getOption() const;
        std::string getOption();
        friend std::ostream &operator<<(std::ostream &os, const Card &card);
    private:
        const std::string option;
};