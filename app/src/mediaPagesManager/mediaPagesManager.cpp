#include "mediaPagesManager.hpp"
#include "Debug.hpp"
#include "Uuid.hpp"
#include <iostream>

MediaPageFile::MediaPageFile(const std::string &path) : _path(path), _fileName(path.substr(path.find_last_of("/") + 1)) {
    if (DEBUG_ENABLED()) {
        printDebug("MediaPageFile created", 0);
        printDebug("Path: \"" + _path + "\"", 0);
    }
    _lastWriteTime = std::filesystem::file_time_type::min();
}

MediaPageFile::MediaPageFile(const MediaPageFile &other) : _path(other._path), _fileName(other._fileName), _lastWriteTime(other._lastWriteTime) {
    if (DEBUG_ENABLED()) {
        printDebug("MediaPageFile copied", 0);
    }
}

const std::string &MediaPageFile::getPath() const {
    return _path;
}

const std::string &MediaPageFile::getFileName() const {
    return _fileName;
}

const std::string MediaPageFile::getContent() {
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

const bool MediaPageFile::hasChange() {
    if (std::filesystem::last_write_time(_path) != _lastWriteTime) {
        _lastWriteTime = std::filesystem::last_write_time(_path);
        return true;
    }
    return false;
}

MediaPagesManager::MediaPagesManager(const std::string &path) : _running(true), _change(false) {
    if (DEBUG_ENABLED()) {
        printDebug("Media path: " + path, 0);
    }
    const std::string complete_path = std::filesystem::current_path().string() + path;
    if (DEBUG_ENABLED()) {
        printDebug("Complete path: " + complete_path, 0);
    }
    _thread = std::thread([this, complete_path] {
        _running = true;
        std::vector<std::shared_ptr<MediaPageFile>> mediaFiles;
        for (const auto &entry : std::filesystem::directory_iterator(complete_path)) {
            mediaFiles.push_back(std::make_shared<MediaPageFile>(entry.path().string()));
        }
        while (_running) {
            _mutex.lock();
            for (auto &mediaFile : mediaFiles) {
                if (mediaFile != nullptr && mediaFile->hasChange()) {
                    if (DEBUG_ENABLED()) {
                        printDebug("Media file: " + mediaFile->getFileName() + " has changed", 0);
                    }
                    nlohmann::json_abi_v3_11_3::json file = nlohmann::json::parse(mediaFile->getContent());
                    if (DEBUG_ENABLED()) {
                        printDebug("Parsed JSON: " + file.dump(4), 0);
                    }
                    editPage(mediaFile, file);
                    _change = true;
                }
            }
            _mutex.unlock();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });
}

MediaPagesManager::MediaPagesManager(const MediaPagesManager &other) : _running(other._running), _change(other._change), _pages(other._pages), _differentPages(other._differentPages) {
}

MediaPagesManager::~MediaPagesManager() {
    if (DEBUG_ENABLED()) {
        printDebug("MediaPagesManager destroyed", 0);
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

void MediaPagesManager::stop() {
    _running = false;
}

const std::vector<JsonPage>& MediaPagesManager::getPages() const {
    return _pages;
}

const void MediaPagesManager::lock() {
    _mutex.lock();
}

const void MediaPagesManager::unlock() {
    _mutex.unlock();
}

const bool MediaPagesManager::isLocked() {
    if (_mutex.try_lock()) {
        _mutex.unlock();
        return false;
    }
    return true;
}

const bool MediaPagesManager::isRunning() const {
    return _running;
}

const bool MediaPagesManager::hasChange() const {
    return _change;
}

void MediaPagesManager::editPage(const std::shared_ptr<MediaPageFile> file, nlohmann::json_abi_v3_11_3::json &json) {
    if (DEBUG_ENABLED()) {
        printDebug("Editing page: " + file->getFileName(), 0);
    }
    if (_pages.empty()) {
        if (DEBUG_ENABLED()) {
            printDebug("Pages empty", 0);
        }
        createPage(file, json);
    }
    for (auto &page : _pages) {
        if (page.getName() == file->getFileName()) {
            if (DEBUG_ENABLED()) {
                printDebug("Page found: " + file->getFileName(), 0);
            }
        } else {
            if (DEBUG_ENABLED()) {
                printDebug("Page not found: " + file->getFileName(), 0);
            }
        }
    }
}

void MediaPagesManager::createPage(const std::shared_ptr<MediaPageFile> file, nlohmann::json_abi_v3_11_3::json &json) {
    if (DEBUG_ENABLED()) {
        printDebug("Creating page: " + file->getFileName(), 0);
    }
    if (json["ignore"] == true) {
        return;
    }
    auto content = json["content"];
    if (DEBUG_ENABLED()) {
        printDebug("Content: " + content.dump(4), 0);
    }
    //create a new file
    std::string newFilePath = std::filesystem::current_path().string() + std::string(json["file_path"]) + file->getFileName();
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
    //get file name without the .json
    newJson["name"] = file->getFileName().substr(0, file->getFileName().find(".json"));
    //create an array "texts" in the newJson
    auto jsonBoxes = nlohmann::json::array();
    auto jsonBox = nlohmann::json();
    jsonBox["texts"] = nlohmann::json::array();
    jsonBox["type"] = "ver_scroll";
    jsonBox["buttons"] = nlohmann::json::array();
    jsonBox["images"] = nlohmann::json::array();
    auto jsonLeftImage = nlohmann::json();
    jsonLeftImage["path"] = json["left_border"];
    jsonLeftImage["position"] = nlohmann::json::array({0, 0});
    jsonLeftImage["size"] = json["left_border_size"];
    jsonLeftImage["hide"] = false;
    jsonLeftImage["uuid"] = Uuid().toString();
    auto jsonCenterImage = nlohmann::json();
    jsonCenterImage["path"] = json["middle_part"];
    jsonCenterImage["position"] = nlohmann::json::array({jsonLeftImage["size"][0].get<int>(), 0});
    jsonCenterImage["size"] = json["middle_part_size"];
    jsonCenterImage["hide"] = false;
    jsonCenterImage["uuid"] = Uuid().toString();
    auto jsonRightImage = nlohmann::json();
    jsonRightImage["path"] = json["right_border"];
    jsonRightImage["position"] = nlohmann::json::array({jsonCenterImage["size"][0].get<int>() + jsonLeftImage["size"][0].get<int>(), 0});
    jsonRightImage["size"] = json["right_border_size"];
    jsonRightImage["hide"] = false;
    jsonRightImage["uuid"] = Uuid().toString();
    jsonBox["images"].push_back(jsonLeftImage);
    jsonBox["images"].push_back(jsonCenterImage);
    jsonBox["images"].push_back(jsonRightImage);
    jsonBox["name"] = "core";
    std::size_t i = 0;
    for (auto &contentElement : content) {
        auto jsonElem = nlohmann::json();
        jsonElem["name"] = contentElement["name"];
        jsonElem["imagePath"] = contentElement["button"];
        jsonElem["hoverImagePath"] = contentElement["hover_button"];
        auto position = nlohmann::json::array();
        position.push_back(jsonLeftImage["size"][0].get<int>());
        position.push_back(i * contentElement["size"][1].get<int>());
        jsonElem["position"] = position;
        jsonElem["size"] = contentElement["size"];
        jsonElem["hide"] = false;
        jsonElem["uuid"] = Uuid().toString();
        jsonElem["target"] = contentElement["name"];
        if (contentElement["type"] != "movies") {
            //add new page
        }
        jsonBox["buttons"].push_back(jsonElem);
        i++;
    }
    jsonBoxes.push_back(jsonBox);
    newJson["boxes"] = jsonBoxes;
    if (DEBUG_ENABLED()) {
        printDebug("New JSON: " + newJson.dump(4), 0);
    }
    //write newJson to file
    File << newJson.dump(4);
}