#pragma once
#include "AParser.hpp"
#include "JsonApp.hpp"

class Parser : public AParser {
    public:
        Parser() = default;
        Parser(const std::string path);
        ~Parser() = default;
        void parse();
        const JsonApp getParseResult() const;
    private:
        JsonApp _app;
};
