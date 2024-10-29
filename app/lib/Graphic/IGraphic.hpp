#pragma once

#include "IBox.hpp"
#include "IGraphicElem.hpp"
#include "IUuid.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class IGraphic {
    public:
        virtual ~IGraphic() = default;
        virtual void draw() = 0;

        //add, remove, update, get
        virtual void addBox(const std::shared_ptr<IBox> box) = 0;

        virtual void removeBox(const std::shared_ptr<IBox> box) = 0;
        virtual void removeElem(const std::shared_ptr<IGraphicElem> elem) = 0;

        virtual void updateBox(const std::shared_ptr<IBox> box) = 0;
        virtual void updateElem(const std::shared_ptr<IGraphicElem> elem) = 0;

        virtual const std::vector<std::shared_ptr<IBox>> getBoxe(const Iuuid &uuid) = 0;
        virtual const std::shared_ptr<IGraphicElem> getElem(const Iuuid &uuid) = 0;

        virtual const std::vector<std::shared_ptr<IBox>> getBoxes() = 0;
        virtual const std::vector<std::shared_ptr<IGraphicElem>> getTexts(const Iuuid &boxUuid) = 0;
        virtual const std::vector<std::shared_ptr<IGraphicElem>> getButtons(const Iuuid &boxUuid) = 0;
        virtual const std::vector<std::shared_ptr<IGraphicElem>> getImages(const Iuuid &boxUuid) = 0;


        virtual void debug(std::size_t i = 0) = 0;
    protected:
};
