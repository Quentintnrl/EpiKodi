#pragma once

#include "AButton.hpp"
#include "JsonButton.hpp"
#include <SFML/Graphics/Image.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace SFMLGraphic {
    class GraphicButton final : public AButton
    {
        public:
            GraphicButton() = default;
            GraphicButton(const JsonButton &jsonButton);
            ~GraphicButton() = default;

            const void setImage(const std::string imagePath);
            const void setHoverImage(const std::string hoverImagePath);
            const void setHover(const bool hover);

            const sf::Image &getImage() const;
            const sf::Image &getHoverImage() const;

            void update(const std::shared_ptr<IGraphicElem> elem);

            void debug(const std::size_t i = 0);

            void draw(sf::RenderWindow &window);

        private:
            ButtonType _type;
            std::string _name;
            std::string _imagePath;
            std::string _hoverImagePath;
            sf::Image _image;
            sf::Image _hoverImage;
            bool hide;
            bool hover;
    };
}
