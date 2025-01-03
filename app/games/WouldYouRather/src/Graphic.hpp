#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Turn.hpp"

class Graphic final {
    public:
        Graphic() = default;
        ~Graphic() = default;

        void draw(sf::RenderWindow& window, const Turn& turn);
};