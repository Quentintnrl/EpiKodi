#pragma once
#include <nlohmann/json.hpp>

class AbstractJsonElem {
    public:
        AbstractJsonElem() = default;
        virtual const void debug(const std::size_t i) = 0;
    protected:
        virtual ~AbstractJsonElem() = default;
        const void printDebug(const std::string &string, const std::size_t i) const;
};
