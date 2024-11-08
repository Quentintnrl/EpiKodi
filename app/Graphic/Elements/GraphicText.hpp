#pragma once

#include "AText.hpp"
#include "JsonText.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace SFMLGraphic {
    class GraphicText final : public AText {
        public:
            GraphicText() = default;
            GraphicText(const JsonText& jsonText);
            ~GraphicText() = default;

            void setFont(const std::string &font) final;
            void setFont(const sf::Font &font);
            const sf::Font getFont() const;
            void update(const std::shared_ptr<IGraphicElem> elem) final;
            void debug(const std::size_t i = 0) final;
            void draw(sf::RenderWindow &window);
        private:
            sf::Text _text;
            sf::Font _font;
    };
}
