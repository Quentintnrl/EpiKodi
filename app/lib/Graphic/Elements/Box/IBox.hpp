#pragma once
#include <vector>
#include "IGraphicElem.hpp"
#include "IButton.hpp"
#include "IImage.hpp"
#include "IText.hpp"

class IBox {
    public:
        virtual ~IBox() = default;

        //add, remove, update, get
        virtual void addText(const std::shared_ptr<IText> text) = 0;
        virtual void addButton(const std::shared_ptr<IButton> button) = 0;
        virtual void addImage(const std::shared_ptr<IImage> image) = 0;

        virtual void removeText(const std::shared_ptr<IText> text) = 0;
        virtual void removeButton(const std::shared_ptr<IButton> button) = 0;
        virtual void removeImage(const std::shared_ptr<IImage> image) = 0;
        virtual void remove(const Iuuid &uuid) = 0;

        virtual void updateText(const std::shared_ptr<IText> text) = 0;
        virtual void updateButton(const std::shared_ptr<IButton> button) = 0;
        virtual void updateImage(const std::shared_ptr<IImage> image) = 0;
        virtual void updateElem(const std::shared_ptr<IGraphicElem> elem) = 0;

        virtual const std::shared_ptr<IText> getText(const Iuuid &uuid) = 0;
        virtual const std::shared_ptr<IButton> getButton(const Iuuid &uuid) = 0;
        virtual const std::shared_ptr<IImage> getImage(const Iuuid &uuid) = 0;
        virtual const std::shared_ptr<IGraphicElem> getElem(const Iuuid &uuid) = 0;

        virtual const std::vector<std::shared_ptr<IText>> getTexts() = 0;
        virtual const std::vector<std::shared_ptr<IButton>> getButtons() = 0;
        virtual const std::vector<std::shared_ptr<IImage>> getImages() = 0;

        virtual bool contain(const Iuuid &uuid) = 0;
        virtual void update(const std::shared_ptr<IBox> &box) = 0;

        virtual bool operator==(const std::shared_ptr<IBox> box) const = 0;
        virtual bool operator!=(const std::shared_ptr<IBox> box) const = 0;
        virtual void operator=(const std::shared_ptr<IBox> box) = 0;
        virtual Iuuid &getUuid() = 0;

        virtual void debug(const std::size_t i = 0) = 0;
};
