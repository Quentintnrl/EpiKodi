#include "JsonApp.hpp"
#include <fstream>
#include <iostream>
#include "Debug.hpp"

JsonApp::JsonApp(const nlohmann::json& json) {
    if (DEBUG_ENABLED()) {
        std::cout << json.dump(4) << std::endl;
    }
    _name = findName(json);
    _componentsPath = findComponentsPath(json);
    _graphicPath = findGraphicPath(json);
    _page = findPage(json);
    _pages = findPages(json);
}

const std::string JsonApp::getName() const {
    return _name;
}

const std::string JsonApp::getGraphicPath() const {
    return _graphicPath;
}

const std::vector<std::string> JsonApp::getComponentsPath() const {
    return _componentsPath;
}

const JsonPage JsonApp::getPage() const {
    return _page;
}

const std::vector<JsonPage> JsonApp::getPages() const {
    return _pages;
}

const void JsonApp::debug(const std::size_t i) {
    printDebug("App: {", i);
    printDebug("name: " + getName(), i + 1);
    printDebug("components: [", i + 1);
    for (const auto& component : getComponentsPath()) {
        printDebug(component, i + 2);
    }
    printDebug("],", i + 1);
    printDebug("graphic_path: " + _graphicPath, i + 1);
    _page.debug(i + 1);
    printDebug("pages: [", i + 1);
    for (auto& page : _pages) {
        page.debug(i + 2);
    }
    printDebug("]", i + 1);
    printDebug("}", i);
}

const std::string JsonApp::findName(const nlohmann::json& json) const {
    return json["name"];
}

const std::string JsonApp::findGraphicPath(const nlohmann::json& json) const {
    return json["graphic_path"];
}

const std::vector<std::string> JsonApp::findComponentsPath(const nlohmann::json& json) const {
    std::vector<std::string> componentsPath;
    for (const auto& component : json["components"]) {
        componentsPath.push_back(component["path"]);
    }
    return componentsPath;
}

const JsonPage JsonApp::findPage(const nlohmann::json& json) const {
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

const std::vector<JsonPage> JsonApp::findPages(const nlohmann::json& json) const {
    std::vector<JsonPage> pages;
    for (const auto& page : json["pages"]) {
        std::string path = page["path"];
        const std::string completePath = getenv("PWD") + path;
        if (DEBUG_ENABLED()) {
            std::cout << "Parsing file: " << completePath << std::endl;
        }
        std::ifstream file(completePath);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file: " + completePath);
        }

        // Read the file content into a string
        std::stringstream buffer;
        buffer << file.rdbuf();

        // Parse the JSON from the string
        nlohmann::json jsonPage = nlohmann::json::parse(buffer.str());
        pages.push_back(JsonPage(jsonPage));
    }
    return pages;
}
