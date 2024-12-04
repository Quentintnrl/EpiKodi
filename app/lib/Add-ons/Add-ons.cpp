#include "Add-ons.hpp"

AddOn::AddOn(std::string name) : _name(name) {
    _run = true;
    _thread = std::thread(&AddOn::run, this);
    _thread.detach();
}

const std::string AddOn::getName() const {
    return _name;
}

const bool AddOn::isRunning() const {
    return _run;
}

void AddOn::stop() {
    _run = false;
}
