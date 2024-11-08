#include "Page.hpp"

Page::Page(const JsonPage &jsonPage) : AppElement() {
    for (const auto &jsonBox : jsonPage.getBoxes()) {
        _boxes.push_back(Box(jsonBox));
    }
}

void Page::addBox(const Box &box) {
    std::lock_guard<std::mutex> lock(_mutex);
    _boxes.push_back(box);
}

const std::vector<Box> Page::getBoxes() const {
    std::lock_guard<std::mutex> lock(_mutex);
    return _boxes;
}