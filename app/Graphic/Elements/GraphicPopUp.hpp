#pragma once

#include "ABox.hpp"
#include "JsonPopUp.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace SFMLGraphic {
    class GraphicPopUp final : public Abox {
        public:
            GraphicPopUp() = default;
            GraphicPopUp(const JsonPopUp &jsonPopUp);
            ~GraphicPopUp() = default;

            void addButton(const JsonButton &button);
            void addImage(const JsonImage &image);
            void addText(const JsonText &text);

            const std::string getName() const;

            void setButtonState(const Uuid buttonId, const bool state);

            void debug(const std::size_t i = 0) override final;
            void draw(sf::RenderWindow &window) const;
        private:
            PopUpType _type;
            std::string _name;
    };
}
