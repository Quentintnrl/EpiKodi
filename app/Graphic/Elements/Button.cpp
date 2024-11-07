#include "Button.hpp"

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

Button::Button(const JsonButton &jsonButton)
{
    _type = jsonButton.getType();
    _name = jsonButton.getName();
    _image.loadFromFile(jsonButton.getImagePath());
    _hoverImage.loadFromFile(jsonButton.getHoverImagePath());
    _position = jsonButton.getPosition();
    _size = jsonButton.getSize();
    hide = jsonButton.getHide();
}

const void Button::setImage(const std::string imagePath)
{
    _image.loadFromFile(imagePath);
}

const void Button::setHoverImage(const std::string hoverImagePath)
{
    _hoverImage.loadFromFile(hoverImagePath);
}

const sf::Image &Button::getImage() const
{
    return _image;
}

const sf::Image &Button::getHoverImage() const
{
    return _hoverImage;
}

void Button::update(const std::shared_ptr<IGraphicElem> elem)
{
    std::shared_ptr<Button> button = std::dynamic_pointer_cast<Button>(elem);
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

void Button::debug(const std::size_t i)
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
