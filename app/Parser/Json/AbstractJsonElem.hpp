#pragma once
#include <nlohmann/json.hpp>
#include "Debug.hpp"

class AbstractJsonElem {
    public:
        AbstractJsonElem() = default;
        virtual const void debug(const std::size_t i) = 0;
    protected:
        virtual ~AbstractJsonElem() = default;
};
