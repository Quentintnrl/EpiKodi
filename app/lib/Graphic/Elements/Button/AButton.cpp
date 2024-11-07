#include "AButton.hpp"

const void AButton::setType(const ButtonType type)
{
    _type = type;
}

const void AButton::setName(const std::string name)
{
    _name = name;
}

const ButtonType AButton::getType() const
{
    return _type;
}

const std::string AButton::getName() const
{
    return _name;
}
