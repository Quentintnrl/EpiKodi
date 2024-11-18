#include "JsonProgressBar.hpp"
#include <iostream>

JsonProgressBar::JsonProgressBar(const nlohmann::json& json) {
    if (DEBUG_ENABLED()) {
        std::cout << "JsonProgressBar: " << json.dump(4) << std::endl;
    }
    _position = findPosition(json);
    _size = findSize(json);
    _progress = findProgress(json);
    _maxProgress = findMaxProgress(json);
    _progressColor = findProgressColor(json);
    _hide = findHide(json);
}

const std::tuple<int, int> JsonProgressBar::getPosition() const {
    return _position;
}

const std::tuple<int, int> JsonProgressBar::getSize() const {
    return _size;
}

const std::size_t JsonProgressBar::getProgress() const {
    return _progress;
}

const std::size_t JsonProgressBar::getMaxProgress() const {
    return _maxProgress;
}

const std::tuple<short, short, short, short> JsonProgressBar::getProgressColor() const {
    return _progressColor;
}

const bool JsonProgressBar::getHide() const {
    return _hide;
}

const void JsonProgressBar::debug(const std::size_t i) {
    printDebug("ProgressBar: {", i);
    printDebug("position: (" + std::to_string(std::get<0>(_position)) + ", " + std::to_string(std::get<1>(_position)) + "),", i + 1);
    printDebug("size: (" + std::to_string(std::get<0>(_size)) + ", " + std::to_string(std::get<1>(_size)) + "),", i + 1);
    printDebug("progress: " + std::to_string(_progress) + ",", i + 1);
    printDebug("maxProgress: " + std::to_string(_maxProgress) + ",", i + 1);
    printDebug("progressColor: (" + std::to_string(std::get<0>(_progressColor)) + ", " + std::to_string(std::get<1>(_progressColor)) + ", " + std::to_string(std::get<2>(_progressColor)) + ", " + std::to_string(std::get<3>(_progressColor)) + "),", i + 1);
    printDebug("hide: " + std::to_string(_hide) + ",", i + 1);
    printDebug("}", i);
}

const std::tuple<int, int> JsonProgressBar::findPosition(const nlohmann::json& json) const {
    return std::make_tuple(json.at("position").at(0).get<int>(), json.at("position").at(1).get<int>());
}

const std::tuple<int, int> JsonProgressBar::findSize(const nlohmann::json& json) const {
    return std::make_tuple(json.at("size").at(0).get<int>(), json.at("size").at(1).get<int>());
}

const std::size_t JsonProgressBar::findProgress(const nlohmann::json& json) const {
    return json.at("progress").get<std::size_t>();
}

const std::size_t JsonProgressBar::findMaxProgress(const nlohmann::json& json) const {
    return json.at("maxProgress").get<std::size_t>();
}

const std::tuple<short, short, short, short> JsonProgressBar::findProgressColor(const nlohmann::json& json) const {
    return std::make_tuple(json.at("progressColor").at(0).get<short>(), json.at("progressColor").at(1).get<short>(), json.at("progressColor").at(2).get<short>(), json.at("progressColor").at(3).get<short>());
}

const bool JsonProgressBar::findHide(const nlohmann::json& json) const {
    return json.at("hide").get<bool>();
}
