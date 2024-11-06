#pragma once

#include "AGraphicElem.hpp"

class IText : public AGraphicElem
{
    public:
        //setters
        virtual void setText(const std::string &text) = 0;
        virtual void setFont(const std::string &font) = 0;

        //getters
        virtual const std::string &getText() const = 0;

        virtual void update(const std::shared_ptr<IGraphicElem> elem) = 0;

        virtual void debug(const std::size_t i = 0) = 0;
    protected:
        virtual ~IText() = default;
};
