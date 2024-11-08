#include "Graphic.hpp"
#include "GraphicBox.hpp"
#include "GraphicButton.hpp"
#include <iostream>

SFMLGraphic::Graphic::Graphic(const std::string &appName) {
    _window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), appName, sf::Style::Fullscreen);
    _window.setFramerateLimit(DEFAULT_FRAME_RATE);
    _appName = appName;
}

SFMLGraphic::Graphic::~Graphic() {
    if (_window.isOpen())
        _window.close();
}

void SFMLGraphic::Graphic::draw() {
    _window.clear();
    for (std::size_t i = 0; i < _box.size(); i++) {
        _box[i]->draw(_window);
    }
    _window.display();
}

void SFMLGraphic::Graphic::addBox(const JsonBox &jsonBox) {
    _box.push_back(std::make_shared<GraphicBox>(jsonBox));
}

void SFMLGraphic::Graphic::addButton(const Uuid &boxId, const JsonButton &jsonButton) {
    for (const auto &box : _box) {
        if (box->getUuid() == boxId) {
            auto tmpBox = std::dynamic_pointer_cast<GraphicBox>(box);
            tmpBox->addButton(jsonButton);
            return;
        }
    }
}

void SFMLGraphic::Graphic::addImage(const Uuid &boxId, const JsonImage &jsonImage) {
    for (const auto &box : _box) {
        if (box->getUuid() == boxId) {
            auto tmpBox = std::dynamic_pointer_cast<GraphicBox>(box);
            tmpBox->addImage(jsonImage);
            return;
        }
    }
}

void SFMLGraphic::Graphic::addText(const Uuid &boxId, const JsonText &jsonText) {
    for (const auto &box : _box) {
        if (box->getUuid() == boxId) {
            auto tmpBox = std::dynamic_pointer_cast<GraphicBox>(box);
            tmpBox->addText(jsonText);
            return;
        }
    }
}

const std::tuple<std::size_t, std::size_t> SFMLGraphic::Graphic::getCursorPosition() const {
    sf::Vector2i position = sf::Mouse::getPosition(_window);
    return std::make_tuple(position.x, position.y);
}

const std::tuple<std::size_t, std::size_t> SFMLGraphic::Graphic::getWindowSize() const {
    return std::make_tuple(_window.getSize().x, _window.getSize().y);
}

void SFMLGraphic::Graphic::setButtonState(const Uuid buttonId, const bool state) {
    for (const auto &box : _box) {
        auto tmpBox = std::dynamic_pointer_cast<GraphicBox>(box);
        tmpBox->setButtonState(buttonId, state);
    }
}

void SFMLGraphic::Graphic::debug(std::size_t i) {
    if (_appName.empty()) {
        printDebug("Graphic {", i);
    } else {
        printDebug(_appName + " {", i);
    }
    for (const auto &box : _box) {
        box->debug(i + 1);
    }
    printDebug("}", i);
}

extern "C" {
    IGraphic *createGraphic(const std::string &appName) {
        return new SFMLGraphic::Graphic(appName);
    }
}
