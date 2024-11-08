#pragma once

#include "appElement.hpp"
#include "JsonButton.hpp"

class Button : public AppElement {
public:
    Button(const JsonButton &jsonButton);
    Button(const Button& other); // Delete copy constructor
    Button& operator=(const Button& other); // Delete copy assignment operator
    const bool isHover(std::tuple<std::size_t, std::size_t> CursorPosition, std::tuple<std::size_t, std::size_t> WindowSize, std::tuple<std::size_t, std::size_t> baseWindowSize);
    const bool getState() const;
    const ButtonType getType() const;
private:
    std::tuple<std::size_t, std::size_t> _position;
    std::tuple<std::size_t, std::size_t> _size;
    bool _state;
    ButtonType _type;
};