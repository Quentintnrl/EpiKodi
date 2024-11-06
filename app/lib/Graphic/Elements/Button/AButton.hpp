#pragma once

#include "IButton.hpp"

class AButton : public IButton
{
    public:
        AButton() = default;
        AButton(const ButtonType type, const std::string name) : _type(type), _name(name) {}
        virtual ~AButton() = default;

        //Setters
        const void setType(const ButtonType type) override final;
        const void setName(const std::string name) override final;
        virtual const void setImage(const std::string imagePath) = 0;
        virtual const void setHoverImage(const std::string hoverImagePath) = 0;

        //Getters
        const ButtonType getType() const override final;
        const std::string getName() const override final;

        virtual void update(const std::shared_ptr<IGraphicElem> elem) = 0;

        virtual void debug(const std::size_t i = 0) = 0;
    protected:
        ButtonType _type;
        std::string _name;
};
