#include "JsonBox.hpp"
#include "Debug.hpp"
#include <iostream>

JsonBox::JsonBox(const nlohmann::json &json) : AbstractJsonElem() {
    if (DEBUG_ENABLED()) {
        std::cout << "JsonBox: " << json << std::endl;
    }
    _texts = findTexts(json);
    _buttons = findButtons(json);
    _images = findImages(json);
}

const std::vector<JsonText> JsonBox::getTexts() const {
    return _texts;
}

const std::vector<JsonButton> JsonBox::getButtons() const {
    return _buttons;
}

const std::vector<JsonImage> JsonBox::getImages() const {
    return _images;
}

const void JsonBox::debug(const std::size_t i) {
    printDebug("Box: {", i);
    printDebug("Texts: {", i + 1);
    for (auto &text : _texts) {
        text.debug(i + 2);
    }
    printDebug("}", i + 1);
    printDebug("Buttons: {", i + 1);
    for (auto &button : _buttons) {
        button.debug(i + 2);
    }
    printDebug("}", i + 1);
    printDebug("Images: {", i + 1);
    for (auto &image : _images) {
        image.debug(i + 2);
    }
    printDebug("}", i + 1);
    printDebug("}", i);
}

std::vector<JsonText> JsonBox::findTexts(const nlohmann::json &json) {
    std::vector<JsonText> texts;
    if (json.contains("texts")) {
        for (auto &text : json["texts"]) {
            texts.push_back(JsonText(text));
        }
    }
    return texts;
}

std::vector<JsonButton> JsonBox::findButtons(const nlohmann::json &json) {
    std::vector<JsonButton> buttons;
    if (json.contains("buttons")) {
        for (auto &button : json["buttons"]) {
            buttons.push_back(JsonButton(button));
        }
    }
    return buttons;
}

std::vector<JsonImage> JsonBox::findImages(const nlohmann::json &json) {
    std::vector<JsonImage> images;
    if (json.contains("images")) {
        for (auto &image : json["images"]) {
            images.push_back(JsonImage(image));
        }
    }
    return images;
}
