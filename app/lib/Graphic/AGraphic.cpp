#include "AGraphic.hpp"

void AGraphic::addBox(const std::shared_ptr<IBox> box)
{
    _boxes.push_back(box);
}

void AGraphic::removeBox(const std::shared_ptr<IBox> box)
{
    for (std::size_t i = 0; i < _boxes.size(); i++) {
        if (_boxes[i] == box) {
            _boxes.erase(_boxes.begin() + i);
            return;
        }
    }
}

void AGraphic::removeElem(const std::shared_ptr<IGraphicElem> elem)
{
    for (auto &box: _boxes) {
        if (box->contain(elem->getUuid())) {
            box->remove(elem->getUuid());
            break;
        }
    }
}

void AGraphic::updateBox(const std::shared_ptr<IBox> box)
{
    for (std::size_t i = 0; i < _boxes.size(); i++) {
        if (_boxes[i] == box) {
            _boxes[i]->update(box);
            return;
        }
    }
}

void AGraphic::updateElem(const std::shared_ptr<IGraphicElem> elem)
{
    for (auto &box: _boxes) {
        if (box->contain(elem->getUuid())) {
            box->updateElem(elem);
            break;
        }
    }
}

const std::vector<std::shared_ptr<IBox>> AGraphic::getBoxe(const Iuuid &uuid)
{
    std::vector<std::shared_ptr<IBox>> box = {};

    for (std::size_t i = 0; i < _boxes.size(); i++) {
        if (_boxes[i]->getUuid() == uuid) {
            box.push_back(_boxes[i]);
        }
    }
    return box;
}

const std::shared_ptr<IGraphicElem> AGraphic::getElem(const Iuuid &uuid)
{
    std::shared_ptr<IGraphicElem> elem = nullptr;

    for (auto &box: _boxes) {
        if (box->contain(uuid)) {
            elem = box->getElem(uuid);
            break;
        }
    }
    return elem;
}

const std::vector<std::shared_ptr<IBox>> AGraphic::getBoxes()
{
    return _boxes;
}

const std::vector<std::shared_ptr<IGraphicElem>> AGraphic::getTexts(const Iuuid &boxUuid)
{
    std::vector<std::shared_ptr<IGraphicElem>> texts = {};

    for (auto &box: _boxes) {
        if (box->getUuid() == boxUuid) {
            texts = box->getTexts();
            break;
        }
    }
    return texts;
}

const std::vector<std::shared_ptr<IGraphicElem>> AGraphic::getButtons(const Iuuid &boxUuid)
{
    std::vector<std::shared_ptr<IGraphicElem>> buttons = {};

    for (auto &box: _boxes) {
        if (box->getUuid() == boxUuid) {
            buttons = box->getButtons();
            break;
        }
    }
    return buttons;
}

const std::vector<std::shared_ptr<IGraphicElem>> AGraphic::getImages(const Iuuid &boxUuid)
{
    std::vector<std::shared_ptr<IGraphicElem>> images = {};

    for (auto &box: _boxes) {
        if (box->getUuid() == boxUuid) {
            images = box->getImages();
            break;
        }
    }
    return images;
}
