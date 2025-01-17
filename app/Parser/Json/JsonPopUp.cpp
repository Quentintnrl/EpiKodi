#include "JsonPopUp.hpp"
#include "Debug.hpp"
#include <iostream>

JsonPopUp::JsonPopUp(const nlohmann::json &json) : AbstractJsonElem() {
    if (DEBUG_ENABLED()) {
        std::cout << "JsonPopUp: " << json.dump(4) << std::endl;
    }
    _texts = findTexts(json);
    _buttons = findButtons(json);
    _images = findImages(json);
    _name = findName(json);
}

const std::vector<JsonText> JsonPopUp::getTexts() const {
    return _texts;
}

const std::vector<JsonButton> JsonPopUp::getButtons() const {
    return _buttons;
}

const std::vector<JsonImage> JsonPopUp::getImages() const {
    return _images;
}

const std::string JsonPopUp::getName() const {
    return _name;
}

const void JsonPopUp::debug(const std::size_t i) const {
    printDebug("PopUp: {", i);
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
    printDebug("Name: " + _name, i + 1);
    printDebug("}", i);
}

bool JsonPopUp::operator==(const JsonPopUp &rhs) const {
    return _texts == rhs._texts &&
           _buttons == rhs._buttons &&
           _images == rhs._images &&
           _name == rhs._name;
}

const std::vector<JsonText> JsonPopUp::findTexts(const nlohmann::json &json) const {
    std::vector<JsonText> texts;
    if (json.contains("texts")) {
        for (auto &text : json["texts"]) {
            texts.push_back(JsonText(text));
        }
    }
    return texts;
}

const std::vector<JsonButton> JsonPopUp::findButtons(const nlohmann::json &json) const {
    std::vector<JsonButton> buttons;
    if (json.contains("buttons")) {
        for (auto &button : json["buttons"]) {
            buttons.push_back(JsonButton(button));
        }
    }
    return buttons;
}

const std::vector<JsonImage> JsonPopUp::findImages(const nlohmann::json &json) const {
    std::vector<JsonImage> images;
    if (json.contains("images")) {
        for (auto &image : json["images"]) {
            images.push_back(JsonImage(image));
        }
    }
    return images;
}

const std::string JsonPopUp::findName(const nlohmann::json &json) const {
    return json["name"];
}
