#pragma once
#include "AParser.hpp"
#include "JsonApp.hpp"

class Parser : public AParser {
    public:
        Parser() = default;
        Parser(const std::string path);
        ~Parser() = default;
        void setFilePath(const std::string path);
        void parse();
        const JsonApp getParseResult() const;
    private:
        JsonApp _app;
};
