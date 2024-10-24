#pragma once
#include <vector>
#include "JsonText.hpp"
#include "JsonButton.hpp"
#include "JsonImage.hpp"

class JsonBox : public AbstractJsonElem {
    public:
        JsonBox(const nlohmann::json &json);

        //getters
        const std::vector<JsonText> getTexts() const;
        const std::vector<JsonButton> getButtons() const;
        const std::vector<JsonImage> getImages() const;

        const void debug(const std::size_t i) override;
    private:
        //find methods
        std::vector<JsonText> findTexts(const nlohmann::json &json);
        std::vector<JsonButton> findButtons(const nlohmann::json &json);
        std::vector<JsonImage> findImages(const nlohmann::json &json);

        std::vector<JsonText> _texts;
        std::vector<JsonButton> _buttons;
        std::vector<JsonImage> _images;
};
