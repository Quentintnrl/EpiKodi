#pragma once

#include "appElement.hpp"
#include "JsonText.hpp"

class Text : public AppElement {
    public:
        Text(const JsonText &jsonText);
        Text(const Text&); // Delete copy constructor
        Text& operator=(const Text& other); // Delete copy assignment operator
};