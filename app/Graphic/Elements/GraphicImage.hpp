#pragma once

#include "AImage.hpp"
#include "JsonImage.hpp"
#include <SFML/Graphics/Image.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace SFMLGraphic {
    class GraphicImage final : public AImage {
        public:
            GraphicImage() = default;
            GraphicImage(const JsonImage& json);
            ~GraphicImage() = default;

            void setTexture(const std::string &path) override;
            void setImage(const sf::Image &image);
            const sf::Image &getImage() const;
            void update(const std::shared_ptr<IGraphicElem> elem) override;
            void debug(const std::size_t i = 0) override;
            void draw(sf::RenderWindow &window);
        private:
            sf::Image _image;
            std::string _path;
    };
}
