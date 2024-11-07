#include "AText.hpp"

AText::AText(const std::string &text, const std::string &font, const std::size_t &size)
    : _text(text), _size(size)
{
}

void AText::setText(const std::string &text)
{
    _text = text;
}

const std::string &AText::getText() const
{
    return _text;
}
