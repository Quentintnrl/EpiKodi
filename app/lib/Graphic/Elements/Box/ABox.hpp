#pragma once

#include "IBox.hpp"
#include "Uuid.hpp"

class Abox : public IBox
{
    public:
        Abox() = default;
        Abox(const Abox& other) = default;

        void addText(const std::shared_ptr<IGraphicElem> text) override;
        void addButton(const std::shared_ptr<IGraphicElem> text) override;
        void addImage(const std::shared_ptr<IGraphicElem> text) override;

        void removeText(const std::shared_ptr<IGraphicElem> text) override;
        void removeButton(const std::shared_ptr<IGraphicElem> text) override;
        void removeImage(const std::shared_ptr<IGraphicElem> text) override;
        void remove(const Iuuid &uuid) override;

        void updateText(const std::shared_ptr<IGraphicElem> text) override;
        void updateButton(const std::shared_ptr<IGraphicElem> text) override;
        void updateImage(const std::shared_ptr<IGraphicElem> text) override;
        void updateElem(const std::shared_ptr<IGraphicElem> elem) override;

        const std::shared_ptr<IGraphicElem> getText(const Iuuid &uuid) override;
        const std::shared_ptr<IGraphicElem> getButton(const Iuuid &uuid) override;
        const std::shared_ptr<IGraphicElem> getImage(const Iuuid &uuid) override;
        const std::shared_ptr<IGraphicElem> getElem(const Iuuid &uuid) override;

        const std::vector<std::shared_ptr<IGraphicElem>> getTexts() override;
        const std::vector<std::shared_ptr<IGraphicElem>> getButtons() override;
        const std::vector<std::shared_ptr<IGraphicElem>> getImages() override;

        bool contain(const Iuuid &uuid) override;
        void update(const std::shared_ptr<IBox> &box) override;

        bool operator==(const std::shared_ptr<IBox> box) const override;
        bool operator!=(const std::shared_ptr<IBox> box) const override;
        void operator=(const std::shared_ptr<IBox> box) override;
        Iuuid &getUuid() override;


        virtual void debug(std::size_t i = 0) = 0;
    protected:
        std::vector<std::shared_ptr<IGraphicElem>> _texts;
        std::vector<std::shared_ptr<IGraphicElem>> _buttons;
        std::vector<std::shared_ptr<IGraphicElem>> _images;
        Uuid _uuid;
};
