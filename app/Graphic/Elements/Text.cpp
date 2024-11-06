#include "Text.hpp"

Text::Text(const JsonText& jsonText) : AText(jsonText.getText(), jsonText.getFontPath(), jsonText.getSize()) {
    if (!jsonText.getFontPath().empty()) {
        _font.loadFromFile(jsonText.getFontPath());
        _text.setFont(_font);
    }
    _text.setString(jsonText.getText());
}

void Text::setFont(const std::string &font) {
    _font.loadFromFile(font);
    _text.setFont(_font);
}

void Text::setFont(const sf::Font &font) {
    _font = font;
    _text.setFont(_font);
}

const sf::Font Text::getFont() const {
    return _font;
}

void Text::update(std::shared_ptr<IGraphicElem> elem) {
    auto text = std::dynamic_pointer_cast<Text>(elem);
    if (text) {
        _text = text->_text;
        _font = text->_font;
    }
}

void Text::debug(std::size_t i) {
    printDebug("Text {", i);
    printDebug("String: " + _text.getString().toAnsiString(), i + 1);
    printDebug("Font: " + _font.getInfo().family, i + 1);
    printDebug("Size: " + std::to_string(_size), i + 1);
    printDebug("}", i);
}
