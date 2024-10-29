#pragma once
#include <tuple>
#include <string>
#include "IUuid.hpp"
#include <memory>

class IGraphicElem {
    public:

        //Setters
        virtual void setPosition(const std::tuple<std::size_t, std::size_t> position) = 0;
        virtual void setSize(const std::tuple<std::size_t, std::size_t> size) = 0;
        virtual void setHide(const bool hide) = 0;
        virtual void setUuid(const Iuuid &uuid) = 0;

        //Getters
        virtual const std::tuple<std::size_t, std::size_t> getPosition() const = 0;
        virtual const std::tuple<std::size_t, std::size_t> &getPosition() = 0;
        virtual const std::tuple<std::size_t, std::size_t> getSize() const = 0;
        virtual const std::tuple<std::size_t, std::size_t> &getSize() = 0;
        virtual const bool getHide() const = 0;
        virtual const bool &getHide() = 0;
        virtual const Iuuid &getUuid() = 0;

        virtual void update(const std::shared_ptr<IGraphicElem> elem) = 0;

        virtual void debug(std::size_t i = 0) = 0;


        //Operators
        virtual bool operator==(const std::shared_ptr<IGraphicElem> elem) const = 0;
        virtual bool operator!=(const std::shared_ptr<IGraphicElem> elem) const = 0;
    protected:
        virtual ~IGraphicElem() = default;
};
