#pragma once

#include "IBox.hpp"
#include "Uuid.hpp"

class Abox : public IBox
{
    public:
        Abox() = default;
        Abox(const Abox& other) = default;

        void addText(const std::shared_ptr<IText> text) override final;
        void addButton(const std::shared_ptr<IButton> text) override final;
        void addImage(const std::shared_ptr<IImage> text) override final;

        void removeText(const std::shared_ptr<IText> text) override final;
        void removeButton(const std::shared_ptr<IButton> text) override final;
        void removeImage(const std::shared_ptr<IImage> text) override final;
        void remove(const Iuuid &uuid) override final;

        void updateText(const std::shared_ptr<IText> text) override final;
        void updateButton(const std::shared_ptr<IButton> text) override final;
        void updateImage(const std::shared_ptr<IImage> text) override final;
        void updateElem(const std::shared_ptr<IGraphicElem> elem) override final;

        const std::shared_ptr<IText> getText(const Iuuid &uuid) override final;
        const std::shared_ptr<IButton> getButton(const Iuuid &uuid) override final;
        const std::shared_ptr<IImage> getImage(const Iuuid &uuid) override final;
        const std::shared_ptr<IGraphicElem> getElem(const Iuuid &uuid) override final;

        const std::vector<std::shared_ptr<IText>> getTexts() override final;
        const std::vector<std::shared_ptr<IButton>> getButtons() override final;
        const std::vector<std::shared_ptr<IImage>> getImages() override final;

        bool contain(const Iuuid &uuid) override final;
        void update(const std::shared_ptr<IBox> &box) override final;

        bool operator==(const std::shared_ptr<IBox> box) const override final;
        bool operator!=(const std::shared_ptr<IBox> box) const override final;
        void operator=(const std::shared_ptr<IBox> box) override final;
        Iuuid &getUuid() override final;


        virtual void debug(std::size_t i = 0) = 0;
    protected:
        std::vector<std::shared_ptr<IText>> _texts;
        std::vector<std::shared_ptr<IButton>> _buttons;
        std::vector<std::shared_ptr<IImage>> _images;
        Uuid _uuid;
};
