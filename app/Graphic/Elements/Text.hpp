#pragma once

#include "AText.hpp"
#include "JsonText.hpp"
#include <SFML/Graphics/Text.hpp>

class Text final : public AText {
    public:
        Text() = default;
        Text(const JsonText& jsonText);
        ~Text() = default;

        void setFont(const std::string &font) final;
        void setFont(const sf::Font &font);
        const sf::Font getFont() const;
        void update(const std::shared_ptr<IGraphicElem> elem) final;
        void debug(const std::size_t i = 0) final;
    private:
        sf::Text _text;
        sf::Font _font;
};
