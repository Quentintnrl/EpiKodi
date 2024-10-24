#pragma once
#include "JsonBox.hpp"

class JsonPage : public AbstractJsonElem {
    public:
        JsonPage() = default;
        JsonPage(const nlohmann::json json);
        const std::string getTitle() const;
        const std::vector<JsonBox> getBoxes() const;

        const void debug(const std::size_t i) override;
    private:
        std::string title;
        std::vector<JsonBox> boxes;
};