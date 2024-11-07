#pragma once
#include <string>
#include "JsonApp.hpp"

class IParser {
    public:
        IParser() = default;
        ~IParser() = default;
        virtual void setFilePath(const std::string path) = 0;
        virtual std::string getFilePath() = 0;
        virtual void parse() = 0;
        virtual const JsonApp getParseResult() const = 0;
};
