#include "AText.hpp"

AText::AText(const std::string &text, const std::string &font, const std::size_t &size, const std::tuple<std::size_t, std::size_t, std::size_t, std::size_t> rgba)
    : _text(text), _size(size), _rgba(rgba)
{
}

void AText::setText(const std::string &text)
{
    _text = text;
}

void AText::setFontSize(const std::size_t &size)
{
    _size = size;
}

void AText::setFontColor(const std::tuple<std::size_t, std::size_t, std::size_t, std::size_t> rgba)
{
    _rgba = rgba;
}

const std::string &AText::getText() const
{
    return _text;
}

const std::size_t &AText::getFontSize() const
{
    return _size;
}

const std::tuple<std::size_t, std::size_t, std::size_t, std::size_t> &AText::getFontColor() const
{
    return _rgba;
}