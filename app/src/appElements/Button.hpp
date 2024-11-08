#pragma once

#include "appElement.hpp"
#include "JsonButton.hpp"

class Button : public AppElement {
public:
    Button(const JsonButton &jsonButton);
    Button(const Button& other); // Delete copy constructor
    Button& operator=(const Button& other); // Delete copy assignment operator
    bool isHover(std::tuple<std::size_t, std::size_t> CursorPosition, std::tuple<std::size_t, std::size_t> WindowSize, std::tuple<std::size_t, std::size_t> baseWindowSize);
private:
    std::tuple<std::size_t, std::size_t> _position;
    std::tuple<std::size_t, std::size_t> _size;
};