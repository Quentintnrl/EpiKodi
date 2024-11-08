#include "GraphicBox.hpp"
#include "GraphicButton.hpp"
#include <iostream>
#include "GraphicImage.hpp"
#include "GraphicText.hpp"

const std::unordered_map<std::string, BoxType> boxTypeMap = {
    {"static", BoxType::Static},
    {"hor_scroll", BoxType::Horizontal_Scroll}
};

const std::unordered_map<BoxType, std::string> boxTypeStringMap = {
    {BoxType::Static, "static"},
    {BoxType::Horizontal_Scroll, "hor_scroll"}
};

SFMLGraphic::GraphicBox::GraphicBox(const JsonBox &jsonBox)
{
    _type = jsonBox.getType();
    for (const auto &text : jsonBox.getTexts())
        addText(text);
    for (const auto &button : jsonBox.getButtons())
        addButton(button);
    for (const auto &image : jsonBox.getImages())
        addImage(image);
}

void SFMLGraphic::GraphicBox::addButton(const JsonButton &button)
{
    _buttons.push_back(std::make_shared<GraphicButton>(button));
}

void SFMLGraphic::GraphicBox::addImage(const JsonImage &image)
{
    _images.push_back(std::make_shared<GraphicImage>(image));
}

void SFMLGraphic::GraphicBox::addText(const JsonText &text)
{
    _texts.push_back(std::make_shared<GraphicText>(text));
}

void SFMLGraphic::GraphicBox::setButtonState(const Uuid buttonId, const bool state)
{
    for (const auto &button : _buttons) {
        if (button->getUuid() == buttonId) {
            std::dynamic_pointer_cast<GraphicButton>(button)->setHover(state);
            return;
        }
    }
}

void SFMLGraphic::GraphicBox::debug(const std::size_t i) {
    printDebug("Box {", i);
    printDebug("Type: " + boxTypeStringMap.at(_type), i + 1);
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
    printDebug("}", i);
}

void SFMLGraphic::GraphicBox::draw(sf::RenderWindow &window) const
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
