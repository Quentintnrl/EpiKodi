#include "Box.hpp"

Box::Box(const JsonBox &jsonBox) : AppElement() {
    for (auto& jsonElement : jsonBox.getButtons()) {
        _buttons.push_back(std::make_shared<Button>(jsonElement));
    }
    for (auto& jsonElement : jsonBox.getImages()) {
        _images.push_back(std::make_shared<Image>(jsonElement));
    }
    for (auto& jsonElement : jsonBox.getTexts()) {
        _texts.push_back(std::make_shared<Text>(jsonElement));
    }
}

void Box::addButton(const Button& button) {
    std::lock_guard<std::mutex> lock(_mutex);
    _buttons.push_back(std::make_shared<Button>(button));
}

void Box::addImage(const Image& image) {
    std::lock_guard<std::mutex> lock(_mutex);
    _images.push_back(std::make_shared<Image>(image));
}

void Box::addText(const Text& text) {
    std::lock_guard<std::mutex> lock(_mutex);
    _texts.push_back(std::make_shared<Text>(text));
}

const std::vector<std::shared_ptr<Button>>& Box::getButtons() const {
    std::lock_guard<std::mutex> lock(_mutex);
    return _buttons;
}

const std::vector<std::shared_ptr<Image>>& Box::getImages() const {
    std::lock_guard<std::mutex> lock(_mutex);
    return _images;
}

const std::vector<std::shared_ptr<Text>>& Box::getTexts() const {
    std::lock_guard<std::mutex> lock(_mutex);
    return _texts;
}