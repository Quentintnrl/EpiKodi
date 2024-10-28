#pragma once
#include "IGraphicElem.hpp"
#include "Uuid.hpp"

class AGraphicElem : public IGraphicElem {
    public:
        AGraphicElem() = default;
        AGraphicElem(const std::tuple<std::size_t, std::size_t> position, const std::tuple<std::size_t, std::size_t> size, const bool hide = false);
        virtual ~AGraphicElem() = default;

        //Setters
        void setPosition(const std::tuple<std::size_t, std::size_t> position) override;
        void setSize(const std::tuple<std::size_t, std::size_t> size) override;
        void setHide(const bool hide) override;
        void setUuid(const Iuuid &uuid) override;

        //Getters
        const std::tuple<std::size_t, std::size_t> getPosition() const override;
        const std::tuple<std::size_t, std::size_t> &getPosition() override;
        const std::tuple<std::size_t, std::size_t> getSize() const override;
        const std::tuple<std::size_t, std::size_t> &getSize() override;
        const bool getHide() const override;
        const bool &getHide() override;
        const Iuuid &getUuid() override;

        virtual void update(std::shared_ptr<IGraphicElem> elem) = 0;

        virtual void debug(std::size_t i = 0) = 0;

        //Operators
        bool operator==(const std::shared_ptr<IGraphicElem> elem) const;
        bool operator!=(const std::shared_ptr<IGraphicElem> elem) const;
    protected:
        virtual void printDebug(std::string &string, std::size_t i = 0) = 0;

        std::tuple<std::size_t, std::size_t> _position;
        std::tuple<std::size_t, std::size_t> _size;
        bool _hide;
        Uuid _uuid;
};
