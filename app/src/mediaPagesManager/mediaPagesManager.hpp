#pragma once

#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <memory>
#include "JsonPage.hpp"
#include <fstream>

class MediaPageFile {
    public:
        MediaPageFile(const std::string &path);
        MediaPageFile(const MediaPageFile &other);
        ~MediaPageFile() = default;
        const std::string &getPath() const;
        const std::string &getFileName() const;
        const std::string getContent();
        const bool hasChange();
    protected:
        std::string _path;
        std::string _fileName;
        std::fstream _file;
        std::filesystem::file_time_type _lastWriteTime;
};

class MediaPagesManager {
    public:
        MediaPagesManager(const std::string &path);
        MediaPagesManager(const MediaPagesManager &other);
        ~MediaPagesManager();
        void stop();
        const std::vector<JsonPage>& getPages() const;
        const void lock();
        const void unlock();
        const bool isLocked();
        const bool isRunning() const;
        const bool hasChange() const;
    protected:
        std::mutex _mutex;
        std::thread _thread;
        bool _running;
        bool _change;
        std::vector<JsonPage> _pages;
        std::vector<std::string> _differentPages;
        void editPage(const std::shared_ptr<MediaPageFile> file, nlohmann::json_abi_v3_11_3::json &json);
        void createPage(const std::shared_ptr<MediaPageFile> file, nlohmann::json_abi_v3_11_3::json &json);
};