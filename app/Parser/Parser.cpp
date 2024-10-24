#include "Parser.hpp"
#include "Debug.hpp"
#include <iostream>
#include <fstream>

Parser::Parser(const std::string path) : AParser(path) {}

void Parser::parse() {
    const std::string completePath = getenv("PWD") + _path;
    if (DEBUG_ENABLED()) {
        std::cout << "Parsing file: " << completePath << std::endl;
    }
    std::ifstream file(completePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + completePath);
    }

    // Read the file content into a string
    std::stringstream buffer;
    buffer << file.rdbuf();

    // Parse the JSON from the string
    _json = nlohmann::json::parse(buffer.str());
    if (DEBUG_ENABLED()) {
        std::cout << "Parsed JSON: " << std::endl;
        std::cout << _json.dump(4) << std::endl;
    }
    _app = JsonApp(_json);
    if (DEBUG_ENABLED()) {
        _app.debug(0);
    }
}

const JsonApp Parser::getParseResult() const {
    return _app;
}
