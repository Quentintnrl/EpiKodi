#include "JsonPage.hpp"
#include "Debug.hpp"
#include <iostream>

JsonPage::JsonPage(const nlohmann::json json) : AbstractJsonElem() {
    if (DEBUG_ENABLED()) {
        std::cout << "JsonPage: " << json.dump(4) << std::endl;
    }
    _name = findName(json);
    _boxes = findBoxes(json);
}

const std::string JsonPage::getName() const {
    return _name;
}

const std::vector<JsonBox> JsonPage::getBoxes() const {
    return _boxes;
}

const void JsonPage::debug(const std::size_t i) {
    printDebug("Page: {", i);
    printDebug("_name: " + _name, i + 1);
    for (auto& box : _boxes) {
        box.debug(i + 1);
    }
    printDebug("}", i);
}

std::string JsonPage::findName(const nlohmann::json &json) {
    return json["name"];
}

std::vector<JsonBox> JsonPage::findBoxes(const nlohmann::json &json) {
    std::vector<JsonBox> boxes;
    for (const auto& box : json["boxes"]) {
        boxes.push_back(JsonBox(box));
    }
    return boxes;
}
