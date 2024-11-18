#include "GraphicText.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

SFMLGraphic::GraphicText::GraphicText(const JsonText& jsonText) : AText(jsonText.getText(), jsonText.getFontPath(), jsonText.getSize()) {
    if (!jsonText.getFontPath().empty()) {
        std::string fontPath = getenv("PWD") + jsonText.getFontPath();
        _font.loadFromFile(fontPath);
        _text.setFont(_font);
    }
    _text.setString(jsonText.getText());
    _position = sf::Vector2f(std::get<0>(jsonText.getPosition()), std::get<1>(jsonText.getPosition()));
}

void SFMLGraphic::GraphicText::setFont(const std::string &font) {
    _font.loadFromFile(font);
    _text.setFont(_font);
}

void SFMLGraphic::GraphicText::setFont(const sf::Font &font) {
    _font = font;
    _text.setFont(_font);
}

const sf::Font SFMLGraphic::GraphicText::getFont() const {
    return _font;
}

void SFMLGraphic::GraphicText::update(std::shared_ptr<IGraphicElem> elem) {
    auto text = std::dynamic_pointer_cast<GraphicText>(elem);
    if (text) {
        _text = text->_text;
        _font = text->_font;
    }
}

void SFMLGraphic::GraphicText::debug(std::size_t i) {
    printDebug("Text {", i);
    printDebug("String: " + _text.getString().toAnsiString(), i + 1);
    printDebug("Font: " + _font.getInfo().family, i + 1);
    printDebug("Size: " + std::to_string(_size), i + 1);
    printDebug("}", i);
}

void SFMLGraphic::GraphicText::draw(sf::RenderWindow &window) {
    _text.setCharacterSize(_size);
    _text.setFont(_font);
    _text.setPosition(_position);
    _text.setFillColor(sf::Color::White);
    window.draw(_text);
}
