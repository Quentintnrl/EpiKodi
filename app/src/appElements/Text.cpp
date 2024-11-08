#include "Text.hpp"

Text::Text(const JsonText &jsonText) : AppElement() {
}

Text::Text(const Text& other) {
    _uuid = other.getUuid().toString();
}

Text& Text::operator=(const Text& other) {
    _uuid = other.getUuid().toString();
    return *this;
};