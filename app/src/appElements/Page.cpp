#include "Page.hpp"
#include <iostream>

Page::Page(const JsonPage &jsonPage) : AppElement() {
    for (const auto &jsonBox : jsonPage.getBoxes()) {
        _boxes.push_back(Box(jsonBox));
    }
    name = jsonPage.getName();
    _nbBoxes = _boxes.size();
}

void Page::addBox(const Box &box) {
    std::lock_guard<std::mutex> lock(_mutex);
    _boxes.push_back(box);
}

const std::vector<Box> Page::getBoxes() const {
    std::lock_guard<std::mutex> lock(_mutex);
    return _boxes;
}

const std::string Page::getName() const {
    return name;
}

const std::size_t Page::getNbBoxes() const {
    return _nbBoxes;
}

const void Page::removeLastBox() {
    std::lock_guard<std::mutex> lock(_mutex);
    _boxes.pop_back();
}
