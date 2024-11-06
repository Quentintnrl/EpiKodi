#include "JsonText.hpp"
#include "Debug.hpp"
#include <iostream>

JsonText::JsonText(const nlohmann::json& json) {
    if (DEBUG_ENABLED()) {
        std::cout << "JsonText: " << json << std::endl;
    }
    _text = findText(json);
    _fontPath = findFontPath(json);
    _position = findPosition(json);
    _size = findSize(json);
    hide = findHide(json);
}

const std::string JsonText::getText() const {
    return _text;
}

const std::string JsonText::getFontPath() const {
    return _fontPath;
}

const std::tuple<int, int> JsonText::getPosition() const {
    return _position;
}

const std::size_t JsonText::getSize() const {
    return _size;
}

const bool JsonText::getHide() const {
    return hide;
}
const void JsonText::debug(const std::size_t i) {
    printDebug("Text: {", i);
    printDebug("text: " + _text + ",", i + 1);
    printDebug("fontPath: " + _fontPath + ",", i + 1);
    printDebug("position: (" + std::to_string(std::get<0>(_position)) + ", " + std::to_string(std::get<1>(_position)) + "),", i + 1);
    printDebug("size: " + std::to_string(_size) + ",", i + 1);
    printDebug("hide: " + std::to_string(hide) + ",", i + 1);
    printDebug("}", i);
}

const std::string JsonText::findText(const nlohmann::json& json) const {
    return json.at("text").get<std::string>();
}

const std::string JsonText::findFontPath(const nlohmann::json& json) const {
    return json.at("fontPath").get<std::string>();
}

const std::tuple<int, int> JsonText::findPosition(const nlohmann::json& json) const {
    return std::make_tuple(json.at("position").at(0).get<int>(), json.at("position").at(1).get<int>());
}

const std::size_t JsonText::findSize(const nlohmann::json& json) const {
    return json.at("size").get<std::size_t>();
}

const bool JsonText::findHide(const nlohmann::json& json) const {
    return json.at("hide").get<bool>();
}
