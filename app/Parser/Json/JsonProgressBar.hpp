#pragma once
#include <string>
#include "AbstractJsonElem.hpp"

class JsonProgressBar : public AbstractJsonElem {
    public:
        JsonProgressBar() = default;
        JsonProgressBar(const nlohmann::json& json);
        ~JsonProgressBar() = default;

        //getters
        const std::tuple<int, int> getPosition() const;
        const std::tuple<int, int> getSize() const;
        const std::size_t getProgress() const;
        const std::size_t getMaxProgress() const;
        const std::tuple<short, short, short, short> getProgressColor() const;
        const bool getHide() const;

        const void debug(const std::size_t i) override;

    private:
        //parse methods
        const std::tuple<int, int> findPosition(const nlohmann::json& json) const;
        const std::tuple<int, int> findSize(const nlohmann::json& json) const;
        const std::size_t findProgress(const nlohmann::json& json) const;
        const std::size_t findMaxProgress(const nlohmann::json& json) const;
        const std::tuple<short, short, short, short> findProgressColor(const nlohmann::json& json) const;
        const bool findHide(const nlohmann::json& json) const;

        std::tuple<int, int> _position;
        std::tuple<int, int> _size;
        std::size_t _progress;
        std::size_t _maxProgress;
        std::tuple<short, short, short, short> _progressColor;
        bool _hide;
};