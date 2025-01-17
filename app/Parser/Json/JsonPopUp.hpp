#pragma once
#include <vector>
#include "JsonText.hpp"
#include "JsonButton.hpp"
#include "JsonImage.hpp"

enum PopUpType {
    Static,
    Horizontal_Scroll,
    Vertical_Scroll,
};

class JsonPopUp : public AbstractJsonElem {
    public:
        JsonPopUp(const nlohmann::json &json);

        //getters
        const PopUpType getType() const;
        const std::vector<JsonText> getTexts() const;
        const std::vector<JsonButton> getButtons() const;
        const std::vector<JsonImage> getImages() const;
        const std::string getName() const;

        const void debug(const std::size_t i) const override;

        bool operator==(const JsonPopUp &rhs) const;
    private:
        //find methods
        const PopUpType findType(const nlohmann::json &json) const;
        const std::vector<JsonText> findTexts(const nlohmann::json &json) const;
        const std::vector<JsonButton> findButtons(const nlohmann::json &json) const;
        const std::vector<JsonImage> findImages(const nlohmann::json &json) const;
        const std::string findName(const nlohmann::json &json) const;

        PopUpType _type;
        std::vector<JsonText> _texts;
        std::vector<JsonButton> _buttons;
        std::vector<JsonImage> _images;
        std::string _name;
};
