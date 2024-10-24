#include "AbstractJsonElem.hpp"
#include <iostream>

const void AbstractJsonElem::printDebug(const std::string &string, const std::size_t i) const {
    for (std::size_t j = 0; j < i; j++) {
        std::cout << "\t";
    }
    std::cout << string << std::endl;
}
