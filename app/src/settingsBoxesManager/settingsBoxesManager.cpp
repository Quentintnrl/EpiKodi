#include "settingsBoxesManager.hpp"
#include "Debug.hpp"
#include "Uuid.hpp"
#include <filesystem>
#include <chrono>
#include <iostream>

SettingsBoxFile::SettingsBoxFile(const std::string &path) : _path(path), _fileName(path.substr(path.find_last_of("/") + 1)) {
    if (DEBUG_ENABLED()) {
        printDebug("SettingsBoxFile created", 0);
        printDebug("Path: \"" + _path + "\"", 0);
    }
    _lastWriteTime = std::filesystem::file_time_type::min();
}

SettingsBoxFile::SettingsBoxFile(const SettingsBoxFile &other) : _path(other._path), _fileName(other._fileName), _lastWriteTime(other._lastWriteTime) {
    if (DEBUG_ENABLED()) {
        printDebug("SettingsBoxFile copied", 0);
    }
}

const std::string &SettingsBoxFile::getPath() const {
    return _path;
}

const std::string &SettingsBoxFile::getFileName() const {
    return _fileName;
}

const std::string SettingsBoxFile::getContent() {
    std::string content;
    if (_file.is_open()) {
        std::string line;
        while (std::getline(_file, line)) {
            content += line;
        }
    } else {
        _file.open(_path, std::ios::in);
        if (_file.is_open()) {
            std::string line;
            while (std::getline(_file, line)) {
                content += line;
            }
        } else {
            if (DEBUG_ENABLED()) {
                printDebug("Error opening file: " + _path, 1);
            }
        }
    }
    _file.close();
    return content;
}

const bool SettingsBoxFile::hasChange() {
    if (std::filesystem::last_write_time(_path) != _lastWriteTime) {
        _lastWriteTime = std::filesystem::last_write_time(_path);
        return true;
    }
    return false;
}

void SettingsBoxFile::setLastChauge(const std::filesystem::file_time_type lastChange) {
    _lastWriteTime = lastChange;
}

const std::size_t SettingsBoxFile::getLastChange() const {
    auto system_time = std::chrono::time_point_cast<std::chrono::system_clock::duration>(_lastWriteTime);
    auto duration_since_epoch = system_time.time_since_epoch();
    std::size_t timestamp = std::chrono::duration_cast<std::chrono::nanoseconds>(duration_since_epoch).count();
    if (DEBUG_ENABLED()) {
        printDebug("Last change: " + std::to_string(timestamp), 0);
    }
    return timestamp;
}

SettingsBoxesManager::SettingsBoxesManager(const std::string &path) : _running(true), _change(false) {
    if (DEBUG_ENABLED()) {
        printDebug("Settings path: \"" + path + "\"", 0);
    }
    const std::string complete_path = std::filesystem::current_path().string() + path;
    if (DEBUG_ENABLED()) {
        printDebug("Complete path: " + complete_path, 0);
    }
    _thread = std::thread([this, complete_path]() {
        _running = true;
        std::vector<std::shared_ptr<SettingsBoxFile>> settingsFile;
        for (const auto &entry : std::filesystem::directory_iterator(complete_path)) {
            if (entry.is_regular_file()) {
                settingsFile.push_back(std::make_shared<SettingsBoxFile>(entry.path().string()));
            }
        }
        while (_running) {
            _mutex.lock();
            for (auto &settingsFile : settingsFile) {
                nlohmann::json file = nlohmann::json::parse(settingsFile->getContent());
                if (file["ignore"] == true) {
                    continue;
                }
                if (DEBUG_ENABLED()) {
                    printDebug("File: " + settingsFile->getFileName(), 0);
                }
                bool change = file["has_changed"];
                std::string configPath = std::filesystem::current_path().string() + file["file_path"].get<std::string>() + settingsFile->getFileName();
                if (DEBUG_ENABLED()) {
                    printDebug("Config path: " + configPath, 0);
                }
                if (settingsFile != nullptr && change) {
                    if (DEBUG_ENABLED()) {
                        printDebug("Setting file: " + settingsFile->getFileName() + " has changed", 0);
                    }
                    if (DEBUG_ENABLED()) {
                        printDebug("Parsed JSON: " + file.dump(4), 0);
                    }
                    editBox(settingsFile, file);
                    _change = true;
                }
                for (auto &box : file["content"]) {
                    if (boxExist(box["name"]) && !change) {
                        continue;
                    } else if (boxExist(box["name"]) && change) {
                        removeBox(box["name"]);
                    }
                    configPath = configPath.substr(0, configPath.find_last_of(".")) + "/" + box["name"].get<std::string>() + ".json";
                    createJsonBox(box["name"], configPath);
                    _change = true;
                }
                file["has_changed"] = false;
                std::fstream File(settingsFile->getPath(), std::ios::out);
                File << file.dump(4);
            }
            _mutex.unlock();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });
}

SettingsBoxesManager::SettingsBoxesManager(const SettingsBoxesManager &other) : _running(other._running), _change(other._change) {
}

SettingsBoxesManager::~SettingsBoxesManager() {
    if (DEBUG_ENABLED()) {
        printDebug("SettingsBoxesManager destroyed", 0);
    }
    if (_running) {
        stop();
    }
    if (_thread.joinable()) {
        _thread.join();
    }
    if (_mutex.try_lock()) {
        _mutex.unlock();
    }
}

void SettingsBoxesManager::stop() {
    _running = false;
}

const std::vector<JsonBox>& SettingsBoxesManager::getBoxes() const {
    return _boxes;
}

const void SettingsBoxesManager::lock() {
    _mutex.lock();
}

const void SettingsBoxesManager::unlock() {
    _mutex.unlock();
}

const bool SettingsBoxesManager::isLocked() {
    if (_mutex.try_lock()) {
        _mutex.unlock();
        return false;
    }
    return true;
}

const bool SettingsBoxesManager::isRunning() const {
    return _running;
}

const bool SettingsBoxesManager::hasChange() const {
    return _change;
}

void SettingsBoxesManager::editBox(const std::shared_ptr<SettingsBoxFile> file, nlohmann::json &json) {
    if (DEBUG_ENABLED()) {
        printDebug("Editing box: " + file->getFileName(), 0);
    }
    if (_boxes.empty()) {
        if (DEBUG_ENABLED()) {
            printDebug("Boxes empty", 0);
        }
        createBox(file, json);
    }
    for (auto &box : _boxes) {
        if (box.getName() == file->getFileName()) {
            if (DEBUG_ENABLED()) {
                printDebug("Box found: " + file->getFileName(), 0);
            }
        } else {
            if (DEBUG_ENABLED()) {
                printDebug("Box not found: " + file->getFileName(), 0);
            }
        }
    }
}

void SettingsBoxesManager::createBox(const std::shared_ptr<SettingsBoxFile> file, nlohmann::json &json) {
    if (DEBUG_ENABLED()) {
        printDebug("Creating box: " + file->getFileName(), 0);
    }
    auto content = json["content"];
    if (DEBUG_ENABLED()) {
        printDebug("Content: " + content.dump(4), 0);
    }
    auto jsonContent = json["content"];
    for (const auto &content : jsonContent) {
        if (DEBUG_ENABLED()) {
            printDebug("Param content: " + content.dump(4), 0);
        }
        //create a new file
        std::string newFilePath = std::filesystem::current_path().string() + std::string(json["file_path"]) + file->getFileName().substr(0, file->getFileName().find_last_of(".")) + std::string("/") + content["name"].get<std::string>() + ".json";
        if (DEBUG_ENABLED()) {
            printDebug("New file path: " + newFilePath, 0);
        }
        //if file doesn't exist
        if (!std::filesystem ::exists(newFilePath)) {
            if (DEBUG_ENABLED()) {
                printDebug("File doesn't exist", 0);
            }
            //create file
            std::ofstream newFile(newFilePath);
            //close file
            newFile.close();
        } else {
            if (DEBUG_ENABLED()) {
                printDebug("File exists", 0);
            }
        }
        //open file
        std::fstream File(newFilePath, std::ios::out);
        //reset file
        File.seekp(0);
        nlohmann::json newJson;
        newJson["name"] = std::string("settings/") + file->getFileName().substr(0, file->getFileName().find_last_of(".")) + "/" + content["name"].get<std::string>();
        newJson["type"] = json["type"];
        auto jsonTexts = nlohmann::json::array();
        auto jsonImages = nlohmann::json::array();
        auto jsonButtons = nlohmann::json::array();
        std::size_t i = 0;
        for (auto &param : content["params"]) {
            if (param["type"].get<std::string>() == "reset") {
                continue;
            }
            auto jsonButton = nlohmann::json();
            jsonButton["name"] = param["name"];
            jsonButton["type"] = "ToParam";
            jsonButton["imagePath"] = json["button"];
            jsonButton["hoverImagePath"] = json["button_hover"];
            auto buttonSize = nlohmann::json::array();
            buttonSize.push_back(json["button_size"][0]);
            buttonSize.push_back(json["button_size"][1]);
            jsonButton["size"] = buttonSize;
            auto buttonPosition = nlohmann::json::array();
            buttonPosition.push_back(470);
            buttonPosition.push_back(i * json["button_size"][1].get<std::size_t>() + 180);
            jsonButton["position"] = buttonPosition;
            jsonButton["hide"] = false;
            jsonButton["uuid"] = Uuid().toString();
            jsonButton["target"] = std::string("settings/") + file->getFileName().substr(0, file->getFileName().find_last_of(".")) + "/" + content["name"].get<std::string>() + "/" + param["name"].get<std::string>();
            jsonButtons.push_back(jsonButton);
            auto jsonText = nlohmann::json();
            jsonText["fontPath"] = "/fonts/Viagram.otf";
            jsonText["hide"] = false;
            jsonText["position"];
            jsonText["position"].push_back(buttonPosition[0].get<std::size_t>() + 30);
            jsonText["position"].push_back(buttonPosition[1].get<std::size_t>() + 30);
            jsonText["size"] = 30;
            jsonText["text"] = param["text"];
            jsonText["uuid"] = Uuid().toString();
            jsonTexts.push_back(jsonText);
            i++;
        }
        newJson["texts"] = jsonTexts;
        newJson["images"] = jsonImages;
        newJson["buttons"] = jsonButtons;
        if (DEBUG_ENABLED()) {
            printDebug("New JSON: " + newJson.dump(4), 0);
        }
        i++;
        File << newJson.dump(4);
    }
}

const bool SettingsBoxesManager::boxExist(const std::string &name) const {
    for (const auto &box : _boxes) {
        if (box.getName() == name) {
            return true;
        }
    }
    return false;
}

const void SettingsBoxesManager::removeBox(const std::string &name) {
    if (DEBUG_ENABLED()) {
        printDebug("Removing box: " + name, 0);
    }
}

const void SettingsBoxesManager::createJsonBox(const std::string &name, const std::string &jsonPath) {
    if (DEBUG_ENABLED()) {
        printDebug("Creating JSON box: " + name, 0);
        printDebug("JSON path: " + jsonPath, 0);
    }
    std::fstream File(jsonPath, std::ios::in);
    if (File.is_open()) {
        nlohmann::json json = nlohmann::json::parse(File);
        if (DEBUG_ENABLED()) {
            printDebug("Parsed JSON: " + json.dump(4), 0);
        }
        JsonBox box(json);
        _boxes.push_back(box);
    } else {
        if (DEBUG_ENABLED()) {
            printDebug("Error opening file: " + jsonPath, 1);
        }
    }
}
