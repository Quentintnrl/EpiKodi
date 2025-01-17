#include "PopUp.hpp"

PopUp::PopUp(const JsonPopUp &jsonPopUp) : AppElement() {
    _type = jsonPopUp.getType();
    for (auto& jsonElement : jsonPopUp.getButtons()) {
        _buttons.push_back(std::make_shared<Button>(jsonElement));
    }
    for (auto& jsonElement : jsonPopUp.getImages()) {
        _images.push_back(std::make_shared<Image>(jsonElement));
    }
    for (auto& jsonElement : jsonPopUp.getTexts()) {
        _texts.push_back(std::make_shared<Text>(jsonElement));
    }
    _name = jsonPopUp.getName();
}

void PopUp::addButton(const Button& button) {
    std::lock_guard<std::mutex> lock(_mutex);
    _buttons.push_back(std::make_shared<Button>(button));
}

void PopUp::addImage(const Image& image) {
    std::lock_guard<std::mutex> lock(_mutex);
    _images.push_back(std::make_shared<Image>(image));
}

void PopUp::addText(const Text& text) {
    std::lock_guard<std::mutex> lock(_mutex);
    _texts.push_back(std::make_shared<Text>(text));
}

const std::string& PopUp::getType() const {
    return _type;
}

const std::vector<std::shared_ptr<Button>>& PopUp::getButtons() const {
    std::lock_guard<std::mutex> lock(_mutex);
    return _buttons;
}

const std::vector<std::shared_ptr<Image>>& PopUp::getImages() const {
    std::lock_guard<std::mutex> lock(_mutex);
    return _images;
}

const std::vector<std::shared_ptr<Text>>& PopUp::getTexts() const {
    std::lock_guard<std::mutex> lock(_mutex);
    return _texts;
}

const std::string& PopUp::getName() const {
    return _name;
}