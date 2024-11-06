#pragma once

#include "AButton.hpp"
#include "JsonButton.hpp"
#include <SFML/Graphics/Image.hpp>

class Button final : public AButton
{
    public:
        Button() = default;
        Button(const JsonButton &jsonButton);
        ~Button() = default;

        const void setImage(const std::string imagePath);
        const void setHoverImage(const std::string hoverImagePath);

        const sf::Image &getImage() const;
        const sf::Image &getHoverImage() const;

        void update(const std::shared_ptr<IGraphicElem> elem);

        void debug(const std::size_t i = 0);

    private:
        ButtonType _type;
        std::string _name;
        std::string _imagePath;
        std::string _hoverImagePath;
        sf::Image _image;
        sf::Image _hoverImage;
        bool hide;
};
