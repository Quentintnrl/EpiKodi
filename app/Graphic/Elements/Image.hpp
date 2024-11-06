#pragma once

#include "AImage.hpp"
#include "JsonImage.hpp"
#include <SFML/Graphics/Image.hpp>

class Image final : public AImage {
    public:
        Image() = default;
        Image(const JsonImage& json);
        ~Image() = default;

        void setTexture(const std::string &path) override;
        void setImage(const sf::Image &image);
        const sf::Image &getImage() const;
        void update(const std::shared_ptr<IGraphicElem> elem) override;
        void debug(const std::size_t i = 0) override;
    private:
        sf::Image _image;
        std::string _path;
};
