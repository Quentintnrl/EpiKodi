#include "Uuid.hpp"

Uuid::Uuid() {
    uuid_generate(_uuid);
}

Uuid::Uuid(const std::string& uuid) {
    uuid_parse(uuid.c_str(), _uuid);
}

Uuid::Uuid(const Uuid& other) {
    uuid_copy(_uuid, other.getUuid());
}

Uuid::~Uuid() {}

const std::string Uuid::toString() const {
    char uuidStr[37];
    uuid_unparse(_uuid, uuidStr);
    return std::string(uuidStr);
}

bool Uuid::operator==(const Iuuid& other) const {
    return toString() == other.toString();
}

bool Uuid::operator==(const uuid_t& other) const {
    return uuid_compare(_uuid, other) == 0;
}

bool Uuid::operator!=(const Iuuid& other) const {
    return !(*this == other);
}

bool Uuid::operator!=(const uuid_t& other) const {
    return uuid_compare(_uuid, other) != 0;
}

void Uuid::operator=(Iuuid& other) {
    uuid_t _uuid;
    uuid_parse(other.toString().c_str(), _uuid);
    uuid_copy(_uuid, _uuid);
}

void Uuid::operator=(std::string other) {
    uuid_parse(other.c_str(), _uuid);
}

void Uuid::operator=(uuid_t& other) {
    uuid_copy(_uuid, other);
}

std::ostream& Uuid::operator<<(std::ostream& os) const {
    os << toString();
    return os;
}

const uuid_t &Uuid::getUuid() const {
    return _uuid;
}

void Uuid::setUuid(const uuid_t &uuid) {
    uuid_copy(_uuid, uuid);
}
