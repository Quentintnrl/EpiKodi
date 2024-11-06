#pragma once

#include "IText.hpp"

class AText : public IText
{
    public:
        AText(const std::string &text, const std::string &font, const std::size_t &size);
        ~AText() = default;

        //setters
        void setText(const std::string &text) final;
        virtual void setFont(const std::string &font) = 0;

        //getters
        const std::string &getText() const final;

        virtual void update(const std::shared_ptr<IGraphicElem> elem) = 0;

        virtual void debug(const std::size_t i = 0) = 0;
    protected:
        std::string _text;
        std::size_t _size;
};