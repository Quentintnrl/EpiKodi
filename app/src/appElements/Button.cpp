#include "Button.hpp"

Button::Button(const JsonButton &jsonButton) : AppElement() {
}

Button::Button(const Button& other) : AppElement() {
    _uuid = other._uuid.toString();
}

Button& Button::operator=(const Button& other) {
    _uuid = other._uuid.toString();
    return *this;
}