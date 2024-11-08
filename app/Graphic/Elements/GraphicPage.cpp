#include "GraphicPage.hpp"
#include <iostream>

SFMLGraphic::GraphicPage::GraphicPage(const JsonPage &jsonPage) : name(jsonPage.getName()) {
    for (const auto &jsonBox : jsonPage.getBoxes()) {
        addBox(jsonBox);
    }
}

void SFMLGraphic::GraphicPage::addBox(const JsonBox &jsonBox) {
    _box.push_back(std::make_shared<GraphicBox>(jsonBox));
}

const std::vector<std::shared_ptr<SFMLGraphic::GraphicBox>> &SFMLGraphic::GraphicPage::getBoxes() const {
    return _box;
}

const std::string &SFMLGraphic::GraphicPage::getName() const {
    return name;
}

void SFMLGraphic::GraphicPage::debug(const std::size_t i) {
    printDebug("Page {", i);
    for (const auto &box : _box) {
        box->debug(i + 1);
    }
    printDebug("}", i);
}
