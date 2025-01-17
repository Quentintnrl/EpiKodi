#include "GraphicPopUp.hpp"
#include "GraphicButton.hpp"
#include <iostream>
#include "GraphicImage.hpp"
#include "GraphicText.hpp"

const std::unordered_map<std::string, PopUpType> PopUpTypeMap = {
    {"static", PopUpType::Static}
};

const std::unordered_map<PopUpType, std::string> PopUpTypeStringMap = {
    {PopUpType::Static, "static"}
};

SFMLGraphic::GraphicPopUp::GraphicPopUp(const JsonPopUp &jsonPopUp)
{
    _type = jsonPopUp.getType();
    for (const auto &text : jsonPopUp.getTexts())
        addText(text);
    for (const auto &button : jsonPopUp.getButtons())
        addButton(button);
    for (const auto &image : jsonPopUp.getImages())
        addImage(image);
    _name = jsonPopUp.getName();
}

void SFMLGraphic::GraphicPopUp::addButton(const JsonButton &button)
{
    _buttons.push_back(std::make_shared<GraphicButton>(button));
}

void SFMLGraphic::GraphicPopUp::addImage(const JsonImage &image)
{
    _images.push_back(std::make_shared<GraphicImage>(image));
}

void SFMLGraphic::GraphicPopUp::addText(const JsonText &text)
{
    _texts.push_back(std::make_shared<GraphicText>(text));
}

const std::string SFMLGraphic::GraphicPopUp::getName() const
{
    return _name;
}

void SFMLGraphic::GraphicPopUp::setButtonState(const Uuid buttonId, const bool state)
{
    for (const auto &button : _buttons) {
        if (button->getUuid() == buttonId) {
            std::dynamic_pointer_cast<GraphicButton>(button)->setHover(state);
            return;
        }
    }
}

void SFMLGraphic::GraphicPopUp::debug(const std::size_t i) {
    printDebug("PopUp {", i);
    printDebug("Type: " + PopUpTypeStringMap.at(_type), i + 1);
    printDebug("Buttons { ", i + 1);
    for (const auto &button : _buttons)
        button->debug(i + 2);
    printDebug("}", i + 1);
    printDebug("Images { ", i + 1);
    for (const auto &image : _images)
        image->debug(i + 2);
    printDebug("}", i + 1);
    printDebug("Texts { ", i + 1);
    for (const auto &text : _texts)
        text->debug(i + 2);
    printDebug("}", i + 1);
    printDebug("Name: " + _name, i + 1);
    printDebug("}", i);
}

void SFMLGraphic::GraphicPopUp::draw(sf::RenderWindow &window) const
{
    for (const auto &button : _buttons) {
        std::dynamic_pointer_cast<GraphicButton>(button)->draw(window);
    }
    for (const auto &image : _images) {
        std::dynamic_pointer_cast<GraphicImage>(image)->draw(window);
    }
    for (const auto &text : _texts) {
        std::dynamic_pointer_cast<GraphicText>(text)->draw(window);
    }
}
