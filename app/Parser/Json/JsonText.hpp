#pragma once
#include <string>
#include "AbstractJsonElem.hpp"

class JsonText : AbstractJsonElem {
    public:
        JsonText() = default;
        JsonText(const nlohmann::json& json);
        ~JsonText() = default;

        //getters
        const std::string getText() const;
        const std::string getFontPath() const;
        const std::tuple<int, int> getPosition() const;
        const std::size_t getSize() const;
        const bool getHide() const;

        const void debug(const std::size_t i) const override;

        bool operator==(const JsonText& other) const;

    private:
        //parse methods
        const std::string findText(const nlohmann::json& json) const;
        const std::string findFontPath(const nlohmann::json& json) const;
        const std::tuple<int, int> findPosition(const nlohmann::json& json) const;
        const std::size_t findSize(const nlohmann::json& json) const;
        const bool findHide(const nlohmann::json& json) const;

        std::string _text;
        std::string _fontPath;
        std::tuple<int, int> _position;
        std::size_t _size;
        bool hide;
};
