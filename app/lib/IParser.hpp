#pragma once
#include <string>

class IParser {
    public:
        IParser() = default;
        ~IParser() = default;
        virtual void setFilePath(const std::string path) = 0;
        virtual std::string getFilePath() = 0;
        virtual void parse() = 0;
};
