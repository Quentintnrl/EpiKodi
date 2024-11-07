#pragma once

#include "IImage.hpp"

class AImage : public IImage
{
    public:
        AImage() = default;
        virtual ~AImage() = default;

        virtual void setTexture(const std::string &path) = 0;

        virtual void update(const std::shared_ptr<IGraphicElem> elem) = 0;

        virtual void debug(const std::size_t i = 0) = 0;
};
