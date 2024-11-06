#pragma once

#include "AGraphicElem.hpp"
#include "JsonButton.hpp"

class IButton : public AGraphicElem
{
    public:
        //Setters
        virtual const void setType(const ButtonType type) = 0;
        virtual const void setName(const std::string name) = 0;
        virtual const void setImage(const std::string imagePath) = 0;
        virtual const void setHoverImage(const std::string hoverImagePath) = 0;

        //Getters
        virtual const ButtonType getType() const = 0;
        virtual const std::string getName() const = 0;

        virtual void update(const std::shared_ptr<IGraphicElem> elem) = 0;

        virtual void debug(const std::size_t i = 0) = 0;
    protected:
        virtual ~IButton() = default;
};
