#pragma once
#include <vector>
#include "IGraphicElem.hpp"

class IBox {
    public:
        virtual ~IBox() = default;
        virtual void draw() = 0;

        //add, remove, update, get
        virtual void addText(const std::shared_ptr<IGraphicElem> text) = 0;
        virtual void addButton(const std::shared_ptr<IGraphicElem> text) = 0;
        virtual void addImage(const std::shared_ptr<IGraphicElem> text) = 0;

        virtual void removeText(const std::shared_ptr<IGraphicElem> text) = 0;
        virtual void removeButton(const std::shared_ptr<IGraphicElem> text) = 0;
        virtual void removeImage(const std::shared_ptr<IGraphicElem> text) = 0;
        virtual void remove(const Iuuid &uuid) = 0;

        virtual void updateText(const std::shared_ptr<IGraphicElem> text) = 0;
        virtual void updateButton(const std::shared_ptr<IGraphicElem> text) = 0;
        virtual void updateImage(const std::shared_ptr<IGraphicElem> text) = 0;
        virtual void updateElem(const std::shared_ptr<IGraphicElem> elem) = 0;

        virtual const std::shared_ptr<IGraphicElem> getText(const Iuuid &uuid) = 0;
        virtual const std::shared_ptr<IGraphicElem> getButton(const Iuuid &uuid) = 0;
        virtual const std::shared_ptr<IGraphicElem> getImage(const Iuuid &uuid) = 0;
        virtual const std::shared_ptr<IGraphicElem> getElem(const Iuuid &uuid) = 0;

        virtual const std::vector<std::shared_ptr<IGraphicElem>> getTexts() = 0;
        virtual const std::vector<std::shared_ptr<IGraphicElem>> getButtons() = 0;
        virtual const std::vector<std::shared_ptr<IGraphicElem>> getImages() = 0;

        virtual bool contain(const Iuuid &uuid) = 0;
        virtual void update(const std::shared_ptr<IBox> &box) = 0;

        virtual bool operator==(const std::shared_ptr<IBox> box) const = 0;
        virtual bool operator!=(const std::shared_ptr<IBox> box) const = 0;
        virtual void operator=(const std::shared_ptr<IBox> box) = 0;
        virtual Iuuid &getUuid() = 0;


        virtual void debug(std::size_t i = 0) = 0;
};
