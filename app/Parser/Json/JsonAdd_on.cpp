#include "JsonAdd_on.hpp"

JsonAddOn::JsonAddOn(const nlohmann::json& json) {
    _name = findName(json);
    _path = findPath(json);
}

const std::string JsonAddOn::getName() const {
    return _name;
}

const std::string JsonAddOn::getPath() const {
    return {_path};
}

const void JsonAddOn::debug(const std::size_t i) const {
    printDebug("AddOn: {", i);
    printDebug("name: " + _name, i + 1);
    printDebug("path: " + _path, i + 1);
    printDebug("}", i);
}

const std::string JsonAddOn::findName(const nlohmann::json& json) const {
    return json.at("name").get<std::string>();
}

const std::string JsonAddOn::findPath(const nlohmann::json& json) const {
    return json.at("path").get<std::string>();
}