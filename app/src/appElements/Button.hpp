#pragma once

#include "appElement.hpp"
#include "JsonButton.hpp"

class Button : public AppElement {
public:
    Button(const JsonButton &jsonButton);
    Button(const Button& other); // Delete copy constructor
    Button& operator=(const Button& other); // Delete copy assignment operator
};