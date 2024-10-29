#pragma once

#include "IText.hpp"

class AText : public IText
{
    public:
        AText(const std::string &text, const std::string &font, const std::size_t &size, const std::tuple<std::size_t, std::size_t, std::size_t, std::size_t> rgba);
        ~AText() = default;

        //setters
        void setText(const std::string &text) final;
        virtual void setFont(const std::string &font) = 0;
        void setFontSize(const std::size_t &size) final;
        void setFontColor(const std::tuple<std::size_t, std::size_t, std::size_t, std::size_t> rgba) final;

        //getters
        const std::string &getText() const final;
        virtual const std::string &getFont() const = 0;
        const std::size_t &getFontSize() const final;
        const std::tuple<std::size_t, std::size_t, std::size_t, std::size_t> &getFontColor() const final;

        virtual void update(std::shared_ptr<IGraphicElem> elem) = 0;

        virtual void debug(std::size_t i = 0) = 0;
    protected:
        std::string _text;
        std::size_t _size;
        std::tuple<std::size_t, std::size_t, std::size_t, std::size_t> _rgba;
};