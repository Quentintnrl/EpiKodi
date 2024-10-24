#include "Parser.hpp"
#include "Debug.hpp"

Parser::Parser(const std::string path) : AParser(path) {}

void Parser::parse() {
    const std::string completePath = getenv("PWD") + std::string("/") + _path;
    _json = nlohmann::json::parse(_path);
    _app = JsonApp(_json);
    if (DEBUG_ENABLED()) {
        _app.debug(0);
    }
}

const JsonApp Parser::getParseResult() const {
    return _app;
}
