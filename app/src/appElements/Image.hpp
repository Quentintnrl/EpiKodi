#pragma once

#include "appElement.hpp"
#include "JsonImage.hpp"

class Image : public AppElement {
    public:
        Image(const JsonImage &jsonImage);
        Image(const Image& other); // Delete copy constructor
        Image& operator=(const Image& other); // Delete copy assignment operator
};