#include "Game.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

WouldYouRather::WouldYouRather(const std::string &configPath) {
    isRunning = false;
    nlohmann::json config;
    std::ifstream configFile(configPath);
    configFile >> config;
    configFile.close();
    for (const auto &turn : config["turns"]) {
        turns.push_back(Turn(Card(turn["Options"][0]), Card(turn["Options"][1]), turn["Question"]));
        std::cout << turns.back() << std::endl;
    }
}

void WouldYouRather::start() {
    isRunning = true;
    std::cout << "Game started!" << std::endl;

    while (isRunning) {
        //random number between 0 and turns.size() - 1
        int randomIndex = rand() % turns.size();
        std::cout << turns[randomIndex] << std::endl;
    }
}