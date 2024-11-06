#pragma once

#include "AGraphic.hpp"
#include "Box.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define DEFAULT_FRAME_RATE 60

class Graphic final : AGraphic {
    public:
        Graphic(const std::string &appName);
        ~Graphic();
        void draw() override;

        void addBox(const JsonBox jsonBox);
        void addButton(const Uuid &boxId, const JsonButton &jsonButton);
        void addImage(const Uuid &boxId, const JsonImage &jsonImage);
        void addText(const Uuid &boxId, const JsonText &jsonText);

        void debug(std::size_t i) override;
        sf::RenderWindow getWindow;
    private:
        std::vector<std::shared_ptr<Box>> _box;
        sf::RenderWindow _window;
        std::string _appName;
};
