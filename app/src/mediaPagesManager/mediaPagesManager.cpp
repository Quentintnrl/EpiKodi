#include "mediaPagesManager.hpp"
#include "Debug.hpp"
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