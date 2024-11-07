#pragma once
#include <string>
#include <memory>
#include <dlfcn.h>
#include <iostream>

class DlLoader {
    public:
        DlLoader() = default;
        ~DlLoader() = default;

        template <typename T>
        std::shared_ptr<T> getInstance(const std::string &path, const std::string &name);
    private:
};