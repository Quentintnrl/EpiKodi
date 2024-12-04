#pragma once
#include <string>
#include <tuple>
#include "AbstractJsonElem.hpp"

class JsonImage : public AbstractJsonElem {
    public:
        JsonImage() = default;
        JsonImage(const nlohmann::json& json);

        //getters
        const std::string getImagePath() const;
        const std::tuple<int, int> getPosition() const;
        const std::tuple<int, int> getSize() const;
        const bool getHide() const;

        const void debug(const std::size_t i) const override;

        bool operator==(const JsonImage& other) const;

    private:
        //parse methods
        const std::string findImagePath(const nlohmann::json& json) const;
        const std::tuple<int, int> findPosition(const nlohmann::json& json) const;
        const std::tuple<int, int> findSize(const nlohmann::json& json) const;
        const bool findHide(const nlohmann::json& json) const;

        std::string _ImagePath;
        std::tuple<int, int> _position;
        std::tuple<int, int> _size;
        bool hide;
};
