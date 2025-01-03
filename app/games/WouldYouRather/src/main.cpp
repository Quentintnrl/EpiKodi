#include <string>
#include <iostream>
#include "Game.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << "configPath" << std::endl;
        return 84;
    }
    WouldYouRather game(argv[1]);
    game.start();
    return 0;
}