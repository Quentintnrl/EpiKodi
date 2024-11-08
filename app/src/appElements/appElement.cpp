#include "appElement.hpp"

AppElement::AppElement() : _uuid(Uuid()) {
}

AppElement::AppElement(const AppElement& other) {
    _uuid = other._uuid.toString();
}

AppElement::~AppElement() {
}

const Uuid& AppElement::getUuid() const {
    std::lock_guard<std::mutex> lock(_mutex);
    return _uuid;
}

AppElement& AppElement::operator=(const AppElement& other) {
    if (this != &other) {
        std::lock(_mutex, other._mutex);
        std::lock_guard<std::mutex> selfLock(_mutex, std::adopt_lock);
        std::lock_guard<std::mutex> otherLock(other._mutex, std::adopt_lock);
        _uuid = other._uuid.toString();
    }
    return *this;
}
