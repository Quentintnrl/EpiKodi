#pragma once
#include "IGraphicElem.hpp"
#include "Uuid.hpp"

class AGraphicElem : public IGraphicElem {
    public:
        AGraphicElem() = default;
        AGraphicElem(const std::tuple<std::size_t, std::size_t> position, const std::tuple<std::size_t, std::size_t> size, const bool hide = false);
        ~AGraphicElem() = default;

        //Setters
        void setPosition(const std::tuple<std::size_t, std::size_t> position) override final;
        void setSize(const std::tuple<std::size_t, std::size_t> size) override final;
        void setHide(const bool hide) override final;
        void setUuid(const Iuuid &uuid) override final;

        //Getters
        const std::tuple<std::size_t, std::size_t> getPosition() const override final;
        const std::tuple<std::size_t, std::size_t> &getPosition() override final;
        const std::tuple<std::size_t, std::size_t> getSize() const override final;
        const std::tuple<std::size_t, std::size_t> &getSize() override final;
        const bool getHide() const override final;
        const bool &getHide() override final;
        const Iuuid &getUuid() override final;

        virtual void update(const std::shared_ptr<IGraphicElem> elem) = 0;

        virtual void debug(const std::size_t i = 0) = 0;

        //Operators
        bool operator==(const std::shared_ptr<IGraphicElem> elem) const final;
        bool operator!=(const std::shared_ptr<IGraphicElem> elem) const final;
    protected:
        std::tuple<std::size_t, std::size_t> _position;
        std::tuple<std::size_t, std::size_t> _size;
        bool _hide;
        Uuid _uuid;
};
