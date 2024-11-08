#include "Image.hpp"

Image::Image(const JsonImage &jsonImage) : AppElement() {
}

Image::Image(const Image& other) {
    _uuid = other._uuid.toString();
}

Image& Image::operator=(const Image& other) {
    _uuid = other._uuid.toString();
    return *this;
}