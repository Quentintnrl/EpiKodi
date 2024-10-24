#include "JsonButton.hpp"

const std::unordered_map<std::string, ButtonType> buttonTypeMap = {
    {"ToPopUp", ButtonType::ToPopUp},
    {"AddBox", ButtonType::AddBox},
    {"ToPage", ButtonType::ToPage}
};

const std::unordered_map<ButtonType, std::string> buttonTypeStringMap = {
    {ButtonType::ToPopUp, "ToPopUp"},
    {ButtonType::AddBox, "AddBox"},
    {ButtonType::ToPage, "ToPage"}
};

JsonButton::JsonButton(const nlohmann::json& json) {
    _type = findButtonType(json);
    _name = findName(json);
    _ImagePath = findImagePath(json);
    _hoverImagePath = findHoverImagePath(json);
    _position = findPosition(json);
    _size = findSize(json);
    hide = findHide(json);
}

const ButtonType JsonButton::getType() const {
    return _type;
}

const std::string JsonButton::getTypeString() const {
    return buttonTypeStringMap.at(_type);
}

const std::string JsonButton::getName() const {
    return _name;
}

const std::string JsonButton::getImagePath() const {
    return _ImagePath;
}

const std::string JsonButton::getHoverImagePath() const {
    return _hoverImagePath;
}

const std::tuple<int, int> JsonButton::getPosition() const {
    return _position;
}

const std::tuple<int, int> JsonButton::getSize() const {
    return _size;
}

const bool JsonButton::getHide() const {
    return hide;
}

const void JsonButton::debug(const std::size_t i) {
    printDebug("Button: {", i);
    printDebug("type: " + getTypeString(), i + 1);
    printDebug("name: " + _name, i + 1);
    printDebug("imagePath: " + _ImagePath, i + 1);
    printDebug("hoverImagePath: " + _hoverImagePath, i + 1);
    printDebug("position: (" + std::to_string(std::get<0>(_position)) + ", " + std::to_string(std::get<1>(_position)) + ")", i + 1);
    printDebug("size: (" + std::to_string(std::get<0>(_size)) + ", " + std::to_string(std::get<1>(_size)) + ")", i + 1);
    printDebug("hide: " + std::to_string(hide), i + 1);
    printDebug("}", i);
}

const ButtonType JsonButton::findButtonType(const nlohmann::json& json) const {
    std::string type = json.at("type").get<std::string>();
    return buttonTypeMap.at(type);
}

const std::string JsonButton::findName(const nlohmann::json& json) const {
    return json.at("name").get<std::string>();
}

const std::string JsonButton::findImagePath(const nlohmann::json& json) const {
    return json.at("imagePath").get<std::string>();
}

const std::string JsonButton::findHoverImagePath(const nlohmann::json& json) const {
    return json.at("hoverImagePath").get<std::string>();
}

const std::tuple<int, int> JsonButton::findPosition(const nlohmann::json& json) const {
    return std::make_tuple(json.at("position").at(0).get<int>(), json.at("position").at(1).get<int>());
}

const std::tuple<int, int> JsonButton::findSize(const nlohmann::json& json) const {
    return std::make_tuple(json.at("size").at(0).get<int>(), json.at("size").at(1).get<int>());
}

const bool JsonButton::findHide(const nlohmann::json& json) const {
    return json.at("hide").get<bool>();
}
