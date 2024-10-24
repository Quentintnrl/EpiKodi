#include "AParser.hpp"

AParser::AParser(const std::string path) {
    _path = path;
}

void AParser::setFilePath(const std::string path) {
    _path = path;
}

std::string AParser::getFilePath() {
    return _path;
}

const std::string &AParser::getFilePath() const {
    return _path;
}
