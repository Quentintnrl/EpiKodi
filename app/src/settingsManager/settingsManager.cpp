#include "settingsManager.hpp"
#include <iostream>
#include <fstream>
#include "Debug.hpp"

SettingsManager::SettingsManager() {
    // Constructor
}

SettingsManager::~SettingsManager() {
    // Destructor
}

const void SettingsManager::changeSettings(const std::string filePath, const std::string target, const std::string param) const {
    // Change settings
    if (DEBUG_ENABLED()) {
        std::cout << "File  path: " << filePath << std::endl;
        std::cout << "Target: " << target << std::endl;
        std::cout << "Param: " << param << std::endl;
    }
    //get pwd
    std::string completePath = getenv("PWD") + std::string("/json/") + filePath + std::string(".json");
    if (DEBUG_ENABLED()) {
        std::cout << "Complete path: " << completePath << std::endl;
    }
    std::fstream file(completePath);
    if (!file.is_open()) {
        std::cerr << "Error: could not open file" << std::endl;
        return;
    }
    nlohmann::json j;
    file >> j;
    file.close();
    for (auto &element: j["content"]) {
        for (auto &param : element["params"]) {
            if (param["name"] == target) {
                if (DEBUG_ENABLED()) {
                    std::cout << "Changing param: " << param["name"].get<std::string>() << std::endl;
                }
                if (param["type"] == "boolean") {
                    param["value"] = !param["value"].get<bool>();
                    break;
                }
            }
        }
    }
    //delete file
    std::remove(completePath.c_str());
    //create new file
    file.open(completePath, std::ios::out);
    if (!file.is_open()) {
        std::cerr << "Error: could not open file" << std::endl;
        return;
    }
    if (DEBUG_ENABLED()) {
        std::cout << j.dump(4) << std::endl;
    }
    file << j.dump(4);
}