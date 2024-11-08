#pragma once

#include "ABox.hpp"
#include "JsonBox.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace SFMLGraphic {
    class GraphicBox final : public Abox {
        public:
            GraphicBox() = default;
            GraphicBox(const JsonBox &jsonBox);
            ~GraphicBox() = default;

            void addButton(const JsonButton &button);
            void addImage(const JsonImage &image);
            void addText(const JsonText &text);

            void debug(const std::size_t i = 0) override final;
            void draw(sf::RenderWindow &window) const;
        private:
            BoxType _type;
    };
}
