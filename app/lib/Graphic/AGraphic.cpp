#include "AGraphic.hpp"

void AGraphic::addText(const std::shared_ptr<IGraphicElem> text)
{
    _text.push_back(text);
}

void AGraphic::addButton(const std::shared_ptr<IGraphicElem> button)
{
    _button.push_back(button);
}

void AGraphic::addImage(const std::shared_ptr<IGraphicElem> image)
{
    _image.push_back(image);
}

void AGraphic::removeText(const std::shared_ptr<IGraphicElem> text)
{
    for (std::size_t i = 0; i < _text.size(); i++) {
        if (_text[i] == text) {
            _text.erase(_text.begin() + i);
            return;
        }
    }
}

void AGraphic::removeButton(const std::shared_ptr<IGraphicElem> button)
{
    for (std::size_t i = 0; i < _button.size(); i++) {
        if (_button[i] == button) {
            _button.erase(_button.begin() + i);
            return;
        }
    }
}

void AGraphic::removeImage(const std::shared_ptr<IGraphicElem> image)
{
    for (std::size_t i = 0; i < _image.size(); i++) {
        if (_image[i] == image) {
            _image.erase(_image.begin() + i);
            return;
        }
    }
}

void AGraphic::updateText(const std::shared_ptr<IGraphicElem> text)
{
    for (std::size_t i = 0; i < _text.size(); i++) {
        if (_text[i] == text) {
            _text[i]->update(text);
            return;
        }
    }
}

void AGraphic::updateButton(const std::shared_ptr<IGraphicElem> button)
{
    for (std::size_t i = 0; i < _button.size(); i++) {
        if (_button[i] == button) {
            _button[i]->update(button);
            return;
        }
    }
}

void AGraphic::updateImage(const std::shared_ptr<IGraphicElem> image)
{
    for (std::size_t i = 0; i < _image.size(); i++) {
        if (_image[i] == image) {
            _image[i]->update(image);
            return;
        }
    }
}

const std::shared_ptr<IGraphicElem> AGraphic::getText(const Iuuid &uuid)
{
    std::shared_ptr<IGraphicElem> elem = nullptr;

    for (std::size_t i = 0; i < _text.size(); i++) {
        if (_text[i]->getUuid() == uuid) {
            elem = _text[i];
            break;
        }
    }
    return elem;
}

const std::shared_ptr<IGraphicElem> AGraphic::getButton(const Iuuid &uuid)
{
    std::shared_ptr<IGraphicElem> elem = nullptr;

    for (std::size_t i = 0; i < _button.size(); i++) {
        if (_button[i]->getUuid() == uuid) {
            elem = _button[i];
            break;
        }
    }
    return elem;
}

const std::shared_ptr<IGraphicElem> AGraphic::getImage(const Iuuid &uuid)
{
    std::shared_ptr<IGraphicElem> elem = nullptr;

    for (std::size_t i = 0; i < _image.size(); i++) {
        if (_image[i]->getUuid() == uuid) {
            elem = _image[i];
            break;
        }
    }
    return elem;
}

const std::vector<std::shared_ptr<IGraphicElem>> &AGraphic::getTexts()
{
    return _text;
}

const std::vector<std::shared_ptr<IGraphicElem>> &AGraphic::getButtons()
{
    return _button;
}

const std::vector<std::shared_ptr<IGraphicElem>> &AGraphic::getImages()
{
    return _image;
}
