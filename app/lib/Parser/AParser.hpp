#pragma once
#include "IParser.hpp"
#include <nlohmann/json.hpp>

class AParser : public IParser
{
    public:
        AParser() = default;
        AParser(const std::string path);
        void setFilePath(const std::string path);
        std::string getFilePath();
        const std::string &getFilePath() const;
        virtual void parse() = 0;
        virtual const JsonApp getParseResult() const = 0;
    protected:
        virtual ~AParser() = default;
        std::string _path;
        nlohmann::json _json;
};