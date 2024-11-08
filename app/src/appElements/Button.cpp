#include "Button.hpp"

Button::Button(const JsonButton &jsonButton) : AppElement() {
    _position = jsonButton.getPosition();
    _size = jsonButton.getSize();
    _uuid = jsonButton.getUuid();
    _type = jsonButton.getType();
}

Button::Button(const Button& other) : AppElement() {
    _uuid = other._uuid.toString();
    _position = other._position;
    _size = other._size;
}

const bool Button::isHover(std::tuple<std::size_t, std::size_t> CursorPosition, std::tuple<std::size_t, std::size_t> WindowSize, std::tuple<std::size_t, std::size_t> baseWindowSize) {
    _state = std::get<0>(CursorPosition) >= std::get<0>(_position) && std::get<0>(CursorPosition) <= std::get<0>(_position) + (std::get<0>(_size) * (std::get<0>(WindowSize) / std::get<0>(baseWindowSize))) &&
             std::get<1>(CursorPosition) >= std::get<1>(_position) && std::get<1>(CursorPosition) <= std::get<1>(_position) + (std::get<1>(_size) * (std::get<1>(WindowSize) / std::get<1>(baseWindowSize)));
    return _state;
}

const bool Button::getState() const {
    return _state;
}

const ButtonType Button::getType() const {
    return _type;
}

Button& Button::operator=(const Button& other) {
    _uuid = other._uuid.toString();
    _position = other._position;
    _size = other._size;
    return *this;
}