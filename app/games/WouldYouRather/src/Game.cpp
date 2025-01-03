#include "Game.hpp"
#include "Graphic.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

static bool optionIsClicked(const sf::Vector2i &mousePosition) {
    //if mouse is clicked on the left option
    if (mousePosition.x >= 0 && mousePosition.x <= 960) {
        return true;
    }
    //if mouse is clicked on the right option
    if (mousePosition.x >= 960 && mousePosition.x <= 1920) {
        return true;
    }
    return false;
}

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
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Would You Rather", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
    window.clear(sf::Color::Black);
    Graphic graphic;

    srand(static_cast<unsigned>(time(0)));
    int randomIndex = rand() % turns.size();
    std::cout << turns[randomIndex] << std::endl;
    graphic.draw(window, turns[randomIndex]);
    while (isRunning) {
        //random number between 0 and turns.size() - 1
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
                return;
            }
            //if mouse is clicked
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                if (optionIsClicked(mousePosition)) {
                    randomIndex = rand() % turns.size();
                    std::cout << turns[randomIndex] << std::endl;
                    graphic.draw(window, turns[randomIndex]);
                }
            }
        }
    }
}