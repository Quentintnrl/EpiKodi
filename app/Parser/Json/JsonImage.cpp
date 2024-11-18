#include "JsonImage.hpp"
#include "Debug.hpp"
#include <iostream>

JsonImage::JsonImage(const nlohmann::json& json) {
    if (DEBUG_ENABLED()) {
        std::cout << "JsonImage: " << json << std::endl;
    }
    _ImagePath = findImagePath(json);
    _position = findPosition(json);
    _size = findSize(json);
    hide = findHide(json);
}

const std::string JsonImage::getImagePath() const {
    return _ImagePath;
}

const std::tuple<int, int> JsonImage::getPosition() const {
    return _position;
}

const std::tuple<int, int> JsonImage::getSize() const {
    return _size;
}

const bool JsonImage::getHide() const {
    return hide;
}

const void JsonImage::debug(const std::size_t i) {
    printDebug("Image: {", i);
    printDebug("Path: " + _ImagePath, i + 1);
    printDebug("Position: (" + std::to_string(std::get<0>(_position)) + ", " + std::to_string(std::get<1>(_position)) + ")", i + 1);
    printDebug("Size: (" + std::to_string(std::get<0>(_size)) + ", " + std::to_string(std::get<1>(_size)) + ")", i + 1);
    printDebug("Hide: " + std::to_string(hide), i + 1);
    printDebug("}", i);
}

bool JsonImage::operator==(const JsonImage& other) const {
    return _ImagePath == other._ImagePath && _position == other._position && _size == other._size && hide == other.hide;
}

const std::string JsonImage::findImagePath(const nlohmann::json& json) const {
    return json.at("path").get<std::string>();
}

const std::tuple<int, int> JsonImage::findPosition(const nlohmann::json& json) const {
    return std::make_tuple(json.at("position").at(0).get<int>(), json.at("position").at(1).get<int>());
}

const std::tuple<int, int> JsonImage::findSize(const nlohmann::json& json) const {
    return std::make_tuple(json.at("size").at(0).get<int>(), json.at("size").at(1).get<int>());
}

const bool JsonImage::findHide(const nlohmann::json& json) const {
    return json.at("hide").get<bool>();
}
