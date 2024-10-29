#pragma once

#include "AGraphicElem.hpp"

class IText : public AGraphicElem
{
    public:
        //setters
        virtual void setText(const std::string &text) = 0;
        virtual void setFont(const std::string &font) = 0;
        virtual void setFontSize(const std::size_t &size) = 0;
        virtual void setFontColor(const std::tuple<std::size_t, std::size_t, std::size_t, std::size_t> rgba) = 0;

        //getters
        virtual const std::string &getText() const = 0;
        virtual const std::string &getFont() const = 0;
        virtual const std::size_t &getFontSize() const = 0;
        virtual const std::tuple<std::size_t, std::size_t, std::size_t, std::size_t> &getFontColor() const = 0;

        virtual void update(std::shared_ptr<IGraphicElem> elem) = 0;

        virtual void debug(std::size_t i = 0) = 0;
    protected:
        virtual ~IText() = default;
};
