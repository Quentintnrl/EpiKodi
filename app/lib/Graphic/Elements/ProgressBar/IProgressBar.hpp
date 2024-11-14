#pragma once
#include "AGraphicElem.hpp"
#include "JsonProgressBar.hpp"

class IProgressBar : public AGraphicElem
{
    public:
        //Setters
        virtual const void setProgress(const std::size_t progress) = 0;
        virtual const void setMaxProgress(const std::size_t maxProgress) = 0;
        virtual const void setProgressColor(const std::tuple<short, short, short, short> rgba) = 0;

        //Getters
        virtual const std::size_t getProgress() const = 0;
        virtual const std::size_t getMaxProgress() const = 0;
        virtual const std::tuple<short, short, short, short> getProgressColor() const = 0;

        virtual void update(const std::shared_ptr<IGraphicElem> elem) = 0;

        virtual void debug(const std::size_t i = 0) = 0;
    protected:
        virtual ~IProgressBar() = default;
};
