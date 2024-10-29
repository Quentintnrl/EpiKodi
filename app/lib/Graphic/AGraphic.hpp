#pragma once
#include "IGraphic.hpp"

class AGraphic : public IGraphic
{
    public:
        AGraphic() = default;
        virtual void draw() = 0;

        //add, remove, update, get

        void addBox(const std::shared_ptr<IBox> box) override;

        void removeBox(const std::shared_ptr<IBox> box) override;
        void removeElem(const std::shared_ptr<IGraphicElem> elem) override;

        void updateBox(const std::shared_ptr<IBox> box) override;
        void updateElem(const std::shared_ptr<IGraphicElem> elem) override;

        const std::vector<std::shared_ptr<IBox>> getBoxe(const Iuuid &uuid) override;
        const std::shared_ptr<IGraphicElem> getElem(const Iuuid &uuid) override;

        const std::vector<std::shared_ptr<IBox>> getBoxes() override;
        const std::vector<std::shared_ptr<IGraphicElem>> getTexts(const Iuuid &boxUuid) override;
        const std::vector<std::shared_ptr<IGraphicElem>> getButtons(const Iuuid &boxUuid) override;
        const std::vector<std::shared_ptr<IGraphicElem>> getImages(const Iuuid &boxUuid) override;
    protected:
        virtual ~AGraphic() = default;
        std::vector<std::shared_ptr<IBox>> _boxes;
};
