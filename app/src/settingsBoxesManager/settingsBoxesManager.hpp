#pragma once
#include <thread>
#include <mutex>
#include <memory>
#include "JsonBox.hpp"
#include <fstream>

class SettingsBoxFile {
    public:
        SettingsBoxFile(const std::string &path);
        SettingsBoxFile(const SettingsBoxFile &other);
        ~SettingsBoxFile() = default;
        const std::string &getPath() const;
        const std::string &getFileName() const;
        const std::string getContent();
        const bool hasChange();
        void setLastChauge(const std::filesystem::file_time_type lastChange);
        const std::size_t getLastChange() const;
    protected:
        std::string _path;
        std::string _fileName;
        std::fstream _file;
        std::filesystem::file_time_type _lastWriteTime;
};

class SettingsBoxesManager {
    public:
        SettingsBoxesManager() = default;
        SettingsBoxesManager(const std::string &path);
        SettingsBoxesManager(const SettingsBoxesManager &other);
        ~SettingsBoxesManager();
        void stop();
        const std::vector<JsonBox>& getBoxes() const;
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
        std::vector<JsonBox> _boxes;
        std::vector<std::string> _differentPages;
        void editBox(const std::shared_ptr<SettingsBoxFile> file, nlohmann::json_abi_v3_11_3::json &json);
        void createBox(const std::shared_ptr<SettingsBoxFile> file, nlohmann::json_abi_v3_11_3::json &json);
        const bool boxExist(const std::string &name) const;
        const void removeBox(const std::string &name);
        const void createJsonBox(const std::string &name, const std::string &jsonPath);
};