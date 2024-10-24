#include "JsonApp.hpp"

JsonApp::JsonApp(const nlohmann::json& json) {
    _page = findPage(json);
}

const std::string JsonApp::getName() const {
    return "name";
}

const JsonPage JsonApp::getPage() const {
    return _page;
}

const void JsonApp::debug(const std::size_t i) {
    printDebug("App: {", i);
    printDebug("name: " + getName(), i + 1);
    _page.debug(i + 1);
}

JsonPage JsonApp::findPage(const nlohmann::json& json) {
    std::string path = json["home_page_path"];
    nlohmann::json page = nlohmann::json::parse(path);
    return JsonPage(page);
}
