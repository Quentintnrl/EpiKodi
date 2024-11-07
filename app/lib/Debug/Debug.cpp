#include "Debug.hpp"
#include <iostream>

// Define the debug variable
bool debug_value = false;

void printDebug(const std::string string, const std::size_t i) {
    for (std::size_t j = 0; j < i; ++j) {
        std::cout << "\t";
    }
    std::cout << string << std::endl;
}
