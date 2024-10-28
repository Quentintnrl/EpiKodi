#pragma once
#include "IGraphic.hpp"

class AGraphic : public IGraphic
{
    public:
        AGraphic() = default;
        virtual void draw() = 0;

        //add, remove, update, get

        virtual void addText(const std::shared_ptr<IGraphicElem> text) = 0;
        virtual void addButton(const std::shared_ptr<IGraphicElem> text) = 0;
        virtual void addImage(const std::shared_ptr<IGraphicElem> text) = 0;

        virtual void removeText(const std::shared_ptr<IGraphicElem> text) = 0;
        virtual void removeButton(const std::shared_ptr<IGraphicElem> text) = 0;
        virtual void removeImage(const std::shared_ptr<IGraphicElem> text) = 0;

        virtual void updateText(const std::shared_ptr<IGraphicElem> text) = 0;
        virtual void updateButton(const std::shared_ptr<IGraphicElem> text) = 0;
        virtual void updateImage(const std::shared_ptr<IGraphicElem> text) = 0;

        virtual const std::shared_ptr<IGraphicElem> getText(const Iuuid &uuid);
        virtual const std::shared_ptr<IGraphicElem> getButton(const Iuuid &uuid);
        virtual const std::shared_ptr<IGraphicElem> getImage(const Iuuid &uuid);

        virtual const std::vector<std::shared_ptr<IGraphicElem>> &getTexts() = 0;
        virtual const std::vector<std::shared_ptr<IGraphicElem>> &getButtons() = 0;
        virtual const std::vector<std::shared_ptr<IGraphicElem>> &getImages() = 0;
    protected:
        virtual ~AGraphic() = default;
        std::vector<std::shared_ptr<IGraphicElem>> _text;
        std::vector<std::shared_ptr<IGraphicElem>> _button;
        std::vector<std::shared_ptr<IGraphicElem>> _image;
};
