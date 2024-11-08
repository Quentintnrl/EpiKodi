#include "GraphicButton.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

const std::unordered_map<std::string, ButtonType> buttonTypeMap = {
    {"ToPopUp", ButtonType::ToPopUp},
    {"AddBox", ButtonType::AddBox},
    {"ToPage", ButtonType::ToPage}
};

const std::unordered_map<ButtonType, std::string> buttonTypeStringMap = {
    {ButtonType::ToPopUp, "ToPopUp"},
    {ButtonType::AddBox, "AddBox"},
    {ButtonType::ToPage, "ToPage"}
};

SFMLGraphic::GraphicButton::GraphicButton(const JsonButton &jsonButton)
{
    _type = jsonButton.getType();
    _name = jsonButton.getName();
    _image.loadFromFile(jsonButton.getImagePath());
    _hoverImage.loadFromFile(jsonButton.getHoverImagePath());
    _position = jsonButton.getPosition();
    _size = jsonButton.getSize();
    hide = jsonButton.getHide();
    hover = false;
    _uuid = jsonButton.getUuid();
}

const void SFMLGraphic::GraphicButton::setImage(const std::string imagePath)
{
    _image.loadFromFile(imagePath);
}

const void SFMLGraphic::GraphicButton::setHoverImage(const std::string hoverImagePath)
{
    _hoverImage.loadFromFile(hoverImagePath);
}

const void SFMLGraphic::GraphicButton::setHover(const bool hover)
{
    this->hover = hover;
}

const sf::Image &SFMLGraphic::GraphicButton::getImage() const
{
    return _image;
}

const sf::Image &SFMLGraphic::GraphicButton::getHoverImage() const
{
    return _hoverImage;
}

void SFMLGraphic::GraphicButton::update(const std::shared_ptr<IGraphicElem> elem)
{
    std::shared_ptr<GraphicButton> button = std::dynamic_pointer_cast<GraphicButton>(elem);
    if (button) {
        _type = button->_type;
        _name = button->_name;
        _image = button->_image;
        _hoverImage = button->_hoverImage;
        _position = button->_position;
        _size = button->_size;
        hide = button->hide;
    }
}

void SFMLGraphic::GraphicButton::debug(const std::size_t i)
{
    printDebug("Button {", i);
    printDebug("Type: " + buttonTypeStringMap.at(_type), i + 1);
    printDebug("Name: " + _name, i + 1);
    printDebug("Image Path: " + _imagePath, i + 1);
    printDebug("Hover Image Path: " + _hoverImagePath, i + 1);
    printDebug("Position: " + std::to_string(std::get<0>(_position)) + ", " + std::to_string(std::get<1>(_position)), i + 1);
    printDebug("Size: " + std::to_string(std::get<0>(_size)) + ", " + std::to_string(std::get<1>(_size)), i + 1);
    printDebug("Hide: " + std::to_string(hide), i + 1);
    printDebug("}", i);
}

void SFMLGraphic::GraphicButton::draw(sf::RenderWindow &window)
{
    sf::Sprite sprite;
    sf::Texture texture;
    if (hover) {
        texture.loadFromImage(_hoverImage);
    } else {
        texture.loadFromImage(_image);
    }
    sprite.setTexture(texture);
    sprite.setPosition(std::get<0>(_position), std::get<1>(_position));
    window.draw(sprite);
}
