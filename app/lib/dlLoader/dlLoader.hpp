#pragma once
#include <memory>
#include <string>
#include <stdexcept>
#include <dlfcn.h>
#include "Debug.hpp"
#include <iostream>
#include <vector>

class DlLoader {
public:
    DlLoader() = default;
    ~DlLoader() {
        for (auto handle : handles) {
            dlclose(handle);
        }
    }
    template <typename T>
    std::shared_ptr<T> getInstance(const std::string &path, const std::string &name) {
        if (DEBUG_ENABLED()) {
            std::cout << "Loading library: " << path << std::endl;
            std::cout << "Loading symbol: " << name << std::endl;
        }
        void *handle = dlopen(path.c_str(), RTLD_LAZY | RTLD_GLOBAL);
        if (!handle) {
            std::cerr << "Cannot open library" << std::endl;
            throw std::runtime_error(dlerror());
        }
        T *(*create)();
        create = (T *(*)())dlsym(handle, name.c_str());
        if (!create) {
            std::cerr << "Cannot load symbol create" << std::endl;
            throw std::runtime_error(dlerror());
        }
        return std::shared_ptr<T>(create(), [handle](T *instance) {
            dlclose(handle);
            delete instance;
        });
    }
private:
    std::vector<void *> handles;
};
