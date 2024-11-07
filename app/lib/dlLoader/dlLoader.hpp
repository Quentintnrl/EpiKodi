#pragma once
#include <memory>
#include <string>
#include <stdexcept>
#include <dlfcn.h>

class DlLoader {
public:
    template <typename T>
    std::shared_ptr<T> getInstance(const std::string &path, const std::string &name) {
        void *handle = dlopen(path.c_str(), RTLD_LAZY);
        if (!handle) {
            throw std::runtime_error(dlerror());
        }
        T *(*create)();
        create = (T *(*)())dlsym(handle, name.c_str());
        if (!create) {
            throw std::runtime_error(dlerror());
        }
        return std::shared_ptr<T>(create(), [handle](T *instance) {
            dlclose(handle);
            delete instance;
        });
    }
};
