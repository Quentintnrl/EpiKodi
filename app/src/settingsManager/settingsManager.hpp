#pragma once

#include <string>
#include <nlohmann/json.hpp>

class SettingsManager {
    public:
        SettingsManager();
        ~SettingsManager();
        const void changeSettings(const std::string filePath, const std::string target, const std::string param) const;
};