#include "Box.hpp"
#include "Button.hpp"
#include "Image.hpp"
#include "Text.hpp"

const std::unordered_map<std::string, BoxType> boxTypeMap = {
    {"static", BoxType::Static},
    {"hor_scroll", BoxType::Horizontal_Scroll}
};

const std::unordered_map<BoxType, std::string> boxTypeStringMap = {
    {BoxType::Static, "static"},
    {BoxType::Horizontal_Scroll, "hor_scroll"}
};

Box::Box(const JsonBox &jsonBox)
{
    _type = jsonBox.getType();
    for (const auto &text : jsonBox.getTexts())
        addText(text);
    for (const auto &button : jsonBox.getButtons())
        addButton(button);
    for (const auto &image : jsonBox.getImages())
        addImage(image);
}

void Box::addButton(const JsonButton &button)
{
    _buttons.push_back(std::make_shared<Button>(button));
}

void Box::addImage(const JsonImage &image)
{
    _images.push_back(std::make_shared<Image>(image));
}

void Box::addText(const JsonText &text)
{
    _texts.push_back(std::make_shared<Text>(text));
}

void Box::debug(const std::size_t i) {
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
