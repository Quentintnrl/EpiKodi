#include "Template.hpp"
#include <iostream>

AddOnTemplate::AddOnTemplate(std::string name) : AddOn(name) {}

void AddOnTemplate::run() {
    while (_run) {
        std::cout << "Hello from AddOnTemplate!" << std::endl;
    }
}