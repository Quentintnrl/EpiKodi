#include "GraphicImage.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

SFMLGraphic::GraphicImage::GraphicImage(const JsonImage &json)
{
    _path = json.getImagePath();
    _position = json.getPosition();
    _size = json.getSize();
    _hide = json.getHide();
    _image.loadFromFile(_path);
}

void SFMLGraphic::GraphicImage::setTexture(const std::string &path)
{
    if (_path == path) {
        return;
    }
    _path = path;
    _image.loadFromFile(_path);
}

void SFMLGraphic::GraphicImage::setImage(const sf::Image &image)
{
    _image = image;
}

const sf::Image &SFMLGraphic::GraphicImage::getImage() const
{
    return _image;
}

void SFMLGraphic::GraphicImage::update(const std::shared_ptr<IGraphicElem> elem)
{
    auto image = std::dynamic_pointer_cast<GraphicImage>(elem);

    if (image) {
        _path = image->_path;
        _image = image->_image;
        _position = image->_position;
        _size = image->_size;
        _hide = image->_hide;
    }
}

void SFMLGraphic::GraphicImage::debug(const std::size_t i)
{
    printDebug("Image {", i);
    printDebug("path: " + _path, i + 1);
    printDebug("position: " + std::to_string(std::get<0>(_position)) + ", " + std::to_string(std::get<1>(_position)), i + 1);
    printDebug("size: " + std::to_string(std::get<0>(_size)) + ", " + std::to_string(std::get<1>(_size)), i + 1);
    printDebug("hide: " + std::to_string(_hide), i + 1);
    printDebug("}", i);
}

void SFMLGraphic::GraphicImage::draw(sf::RenderWindow &window)
{
    if (!_hide) {
        sf::Texture texture;
        texture.loadFromImage(_image);
        sf::Sprite sprite(texture);

        sprite.setPosition(std::get<0>(_position), std::get<1>(_position));
        window.draw(sprite);
    }
}
