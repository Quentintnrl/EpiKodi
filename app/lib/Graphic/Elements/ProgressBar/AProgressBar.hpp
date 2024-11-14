#pragma once

#include "IProgressBar.hpp"

class AProgressBar : public IProgressBar {
    public:
        AProgressBar() = default;
        AProgressBar(const std::size_t progress, const std::size_t maxProgress);

        //Setters
        const void setProgress(const std::size_t progress) override final;
        const void setMaxProgress(const std::size_t maxProgress) override final;
        virtual const void setProgressColor(const std::tuple<short, short, short, short> rgba) = 0;

        //Getters
        const std::size_t getProgress() const override final;
        const std::size_t getMaxProgress() const override final;
        virtual const std::tuple<short, short, short, short> getProgressColor() const = 0;

        virtual void update(const std::shared_ptr<IGraphicElem> elem) = 0;

        virtual void debug(const std::size_t i = 0) = 0;
    protected:
        std::size_t _progress;
        std::size_t _maxProgress;
};