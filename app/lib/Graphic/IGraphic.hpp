#pragma once

#include "JsonBox.hpp"
#include <SFML/Graphics.hpp>

class IGraphic {
    public:
        virtual ~IGraphic() = default;
        virtual void draw() = 0;

        //add, remove, update, get
        virtual void addBox(const JsonBox &box) = 0;
        virtual void debug(std::size_t i = 0) = 0;
    protected:
};
