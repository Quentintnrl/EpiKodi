#include "Graphic.hpp"
#include "Box.hpp"

Graphic::Graphic(const std::string &appName) {
    _window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), appName);
    _window.setFramerateLimit(DEFAULT_FRAME_RATE);
    _appName = appName;
}

Graphic::~Graphic() {
    if (_window.isOpen())
        _window.close();
}

void Graphic::draw() {
    _window.clear();
    for (const auto &box : _box) {
    }
    _window.display();
}

void Graphic::addBox(const JsonBox jsonBox) {
    _box.push_back(std::make_shared<Box>(jsonBox));
}

void Graphic::addButton(const Uuid &boxId, const JsonButton &jsonButton) {
    for (const auto &box : _box) {
        if (box->getUuid() == boxId) {
            auto tmpBox = std::dynamic_pointer_cast<Box>(box);
            tmpBox->addButton(jsonButton);
            return;
        }
    }
}

void Graphic::addImage(const Uuid &boxId, const JsonImage &jsonImage) {
    for (const auto &box : _box) {
        if (box->getUuid() == boxId) {
            auto tmpBox = std::dynamic_pointer_cast<Box>(box);
            tmpBox->addImage(jsonImage);
            return;
        }
    }
}

void Graphic::addText(const Uuid &boxId, const JsonText &jsonText) {
    for (const auto &box : _box) {
        if (box->getUuid() == boxId) {
            auto tmpBox = std::dynamic_pointer_cast<Box>(box);
            tmpBox->addText(jsonText);
            return;
        }
    }
}

void Graphic::debug(std::size_t i) {
    printDebug(_appName + " {", i);
    for (const auto &box : _box) {
        box->debug(i + 1);
    }
    printDebug("}", i);
}

extern "C" {
    IGraphic *createGraphic(const std::string &appName) {
        return new Graphic(appName);
    }
}
