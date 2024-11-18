#pragma once
#include <string>
#include <tuple>
#include "AbstractJsonElem.hpp"
#include <unordered_map>

enum ButtonType {
    ToPopUp,
    AddBox,
    ToPage
};

class JsonButton : public AbstractJsonElem {
    public:
        JsonButton() = default;
        JsonButton(const nlohmann::json& json);

        //getters
        const ButtonType getType() const;
        const std::string getTypeString() const;
        const std::string getName() const;
        const std::string getImagePath() const;
        const std::string getHoverImagePath() const;
        const std::tuple<int, int> getPosition() const;
        const std::tuple<int, int> getSize() const;
        const bool getHide() const;
        const std::string getUuid() const;
        const std::string getTarget() const;

        const void debug(const std::size_t i) override;

        bool operator==(const JsonButton& other) const;

    private:
        //parse methods
        const ButtonType findButtonType(const nlohmann::json& json) const;
        const std::string findName(const nlohmann::json& json) const;
        const std::string findImagePath(const nlohmann::json& json) const;
        const std::string findHoverImagePath(const nlohmann::json& json) const;
        const std::tuple<int, int> findPosition(const nlohmann::json& json) const;
        const std::tuple<int, int> findSize(const nlohmann::json& json) const;
        const bool findHide(const nlohmann::json& json) const;
        const std::string findUuid(const nlohmann::json& json) const;
        const std::string findTarget(const nlohmann::json& json) const;

        enum ButtonType _type;
        std::string _name;
        std::string _ImagePath;
        std::string _hoverImagePath;
        std::tuple<int, int> _position;
        std::tuple<int, int> _size;
        bool hide;
        std::string _uuid;
        std::string _target;
};
