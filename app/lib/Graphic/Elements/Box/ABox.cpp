#include "ABox.hpp"
#include <algorithm>

void Abox::addText(const std::shared_ptr<IGraphicElem> text)
{
    _texts.push_back(text);
}

void Abox::addButton(const std::shared_ptr<IGraphicElem> text)
{
    _buttons.push_back(text);
}

void Abox::addImage(const std::shared_ptr<IGraphicElem> text)
{
    _images.push_back(text);
}

void Abox::removeText(const std::shared_ptr<IGraphicElem> text)
{
    _texts.erase(std::remove(_texts.begin(), _texts.end(), text), _texts.end());
}

void Abox::removeButton(const std::shared_ptr<IGraphicElem> text)
{
    _buttons.erase(std::remove(_buttons.begin(), _buttons.end(), text), _buttons.end());
}

void Abox::removeImage(const std::shared_ptr<IGraphicElem> text)
{
    _images.erase(std::remove(_images.begin(), _images.end(), text), _images.end());
}

void Abox::remove(const Iuuid &uuid)
{
    _texts.erase(std::remove_if(_texts.begin(), _texts.end(), [&uuid](const std::shared_ptr<IGraphicElem> &elem) {
        return elem->getUuid() == uuid;
    }), _texts.end());
    _buttons.erase(std::remove_if(_buttons.begin(), _buttons.end(), [&uuid](const std::shared_ptr<IGraphicElem> &elem) {
        return elem->getUuid() == uuid;
    }), _buttons.end());
    _images.erase(std::remove_if(_images.begin(), _images.end(), [&uuid](const std::shared_ptr<IGraphicElem> &elem) {
        return elem->getUuid() == uuid;
    }), _images.end());
}

void Abox::updateText(const std::shared_ptr<IGraphicElem> text)
{
    auto it = std::find_if(_texts.begin(), _texts.end(), [&text](const std::shared_ptr<IGraphicElem> &elem) {
        return elem->getUuid() == text->getUuid();
    });
    if (it != _texts.end())
        *it = text;
}

void Abox::updateButton(const std::shared_ptr<IGraphicElem> text)
{
    auto it = std::find_if(_buttons.begin(), _buttons.end(), [&text](const std::shared_ptr<IGraphicElem> &elem) {
        return elem->getUuid() == text->getUuid();
    });
    if (it != _buttons.end())
        *it = text;
}

void Abox::updateImage(const std::shared_ptr<IGraphicElem> text)
{
    auto it = std::find_if(_images.begin(), _images.end(), [&text](const std::shared_ptr<IGraphicElem> &elem) {
        return elem->getUuid() == text->getUuid();
    });
    if (it != _images.end())
        *it = text;
}

void Abox::updateElem(const std::shared_ptr<IGraphicElem> elem)
{
    updateText(elem);
    updateButton(elem);
    updateImage(elem);
}

const std::shared_ptr<IGraphicElem> Abox::getText(const Iuuid &uuid)
{
    auto it = std::find_if(_texts.begin(), _texts.end(), [&uuid](const std::shared_ptr<IGraphicElem> &elem) {
        return elem->getUuid() == uuid;
    });
    if (it != _texts.end())
        return *it;
    return nullptr;
}

const std::shared_ptr<IGraphicElem> Abox::getButton(const Iuuid &uuid)
{
    auto it = std::find_if(_buttons.begin(), _buttons.end(), [&uuid](const std::shared_ptr<IGraphicElem> &elem) {
        return elem->getUuid() == uuid;
    });
    if (it != _buttons.end())
        return *it;
    return nullptr;
}

const std::shared_ptr<IGraphicElem> Abox::getImage(const Iuuid &uuid)
{
    auto it = std::find_if(_images.begin(), _images.end(), [&uuid](const std::shared_ptr<IGraphicElem> &elem) {
        return elem->getUuid() == uuid;
    });
    if (it != _images.end())
        return *it;
    return nullptr;
}

const std::shared_ptr<IGraphicElem> Abox::getElem(const Iuuid &uuid)
{
    auto it = getText(uuid);
    if (it)
        return it;
    it = getButton(uuid);
    if (it)
        return it;
    return getImage(uuid);
}

const std::vector<std::shared_ptr<IGraphicElem>> Abox::getTexts()
{
    return _texts;
}

const std::vector<std::shared_ptr<IGraphicElem>> Abox::getButtons()
{
    return _buttons;
}

const std::vector<std::shared_ptr<IGraphicElem>> Abox::getImages()
{
    return _images;
}

bool Abox::contain(const Iuuid &uuid)
{
    return std::find_if(_texts.begin(), _texts.end(), [&uuid](const std::shared_ptr<IGraphicElem> &elem) {
        return elem->getUuid() == uuid;
    }) != _texts.end() ||
    std::find_if(_buttons.begin(), _buttons.end(), [&uuid](const std::shared_ptr<IGraphicElem> &elem) {
        return elem->getUuid() == uuid;
    }) != _buttons.end() ||
    std::find_if(_images.begin(), _images.end(), [&uuid](const std::shared_ptr<IGraphicElem> &elem) {
        return elem->getUuid() == uuid;
    }) != _images.end();
}

void Abox::update(const std::shared_ptr<IBox> &box)
{
    for (auto &elem : box->getTexts())
        updateText(elem);
    for (auto &elem : box->getButtons())
        updateButton(elem);
    for (auto &elem : box->getImages())
        updateImage(elem);
}

bool Abox::operator==(const std::shared_ptr<IBox> box) const
{
    return _uuid == box->getUuid();
}

bool Abox::operator!=(const std::shared_ptr<IBox> box) const
{
    return _uuid != box->getUuid();
}

void Abox::operator=(const std::shared_ptr<IBox> box)
{
    _texts = box->getTexts();
    _buttons = box->getButtons();
    _images = box->getImages();
    _uuid = box->getUuid();
}

Iuuid &Abox::getUuid()
{
    return _uuid;
}

