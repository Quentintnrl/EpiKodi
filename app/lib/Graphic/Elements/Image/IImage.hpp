#pragma once

#include "AGraphicElem.hpp"

class IImage : public AGraphicElem
{
    public:
        virtual ~IImage() = default;

        virtual void setTexture(const std::string &path) = 0;

        virtual void update(std::shared_ptr<IGraphicElem> elem) = 0;

        virtual void debug(std::size_t i = 0) = 0;
};
