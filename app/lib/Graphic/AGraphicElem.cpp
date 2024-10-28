#include "AGraphicElem.hpp"

AGraphicElem::AGraphicElem(const std::tuple<std::size_t, std::size_t> position, const std::tuple<std::size_t, std::size_t> size, const bool hide) : _position(position), _size(size), _hide(hide), _uuid(Uuid()) {}

void AGraphicElem::setPosition(const std::tuple<std::size_t, std::size_t> position) {
    _position = position;
}

void AGraphicElem::setSize(const std::tuple<std::size_t, std::size_t> size) {
    _size = size;
}

void AGraphicElem::setHide(const bool hide) {
    _hide = hide;
}

void AGraphicElem::setUuid(const Iuuid &uuid) {
    _uuid = uuid.toString();
}

const std::tuple<std::size_t, std::size_t> AGraphicElem::getPosition() const {
    return _position;
}

const std::tuple<std::size_t, std::size_t> &AGraphicElem::getPosition() {
    return _position;
}

const std::tuple<std::size_t, std::size_t> AGraphicElem::getSize() const {
    return _size;
}

const std::tuple<std::size_t, std::size_t> &AGraphicElem::getSize() {
    return _size;
}

const bool AGraphicElem::getHide() const {
    return _hide;
}

const bool &AGraphicElem::getHide() {
    return _hide;
}

const Iuuid &AGraphicElem::getUuid() {
    return _uuid;
}

bool AGraphicElem::operator==(const std::shared_ptr<IGraphicElem> elem) const {
    return _position == elem->getPosition() && _size == elem->getSize() && _hide == elem->getHide();
}

bool AGraphicElem::operator!=(const std::shared_ptr<IGraphicElem> elem) const {
    return !(*this == elem);
}
