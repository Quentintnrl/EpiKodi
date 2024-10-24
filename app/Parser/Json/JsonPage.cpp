#include "JsonPage.hpp"

JsonPage::JsonPage(const nlohmann::json json) : AbstractJsonElem() {
    title = json["title"];
    for (const auto& box : json["boxes"]) {
        boxes.push_back(JsonBox(box));
    }
}

const std::string JsonPage::getTitle() const {
    return title;
}

const std::vector<JsonBox> JsonPage::getBoxes() const {
    return boxes;
}

const void JsonPage::debug(const std::size_t i) {
    printDebug("Page: {", i);
    printDebug("title: " + title, i + 1);
    for (auto& box : boxes) {
        box.debug(i + 1);
    }
    printDebug("}", i);
}
