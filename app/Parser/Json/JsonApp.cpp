#include "JsonApp.hpp"
#include <fstream>
#include <iostream>
#include "Debug.hpp"

JsonApp::JsonApp(const nlohmann::json& json) {
    if (DEBUG_ENABLED()) {
        std::cout << json.dump(4) << std::endl;
    }
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
    printDebug("}", i);
}

JsonPage JsonApp::findPage(const nlohmann::json& json) {
    std::string path = json["home_page_path"];
    const std::string completePath = getenv("PWD") + path;
    std::ifstream file(completePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + completePath);
    }

    // Read the file content into a string
    std::stringstream buffer;
    buffer << file.rdbuf();
    nlohmann::json page = nlohmann::json::parse(buffer.str());
    return JsonPage(page);
}
