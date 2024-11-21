#pragma once
#include "JsonBox.hpp"

class JsonPage : public AbstractJsonElem {
    public:
        JsonPage() = default;
        JsonPage(const nlohmann::json json);
        const std::string getName() const;
        const std::vector<JsonBox> getBoxes() const;

        const void debug(const std::size_t i) override;

        bool operator==(const JsonPage &other) const;
    private:
        std::string findName(const nlohmann::json &json);
        std::vector<JsonBox> findBoxes(const nlohmann::json &json);

        std::string _name;
        std::vector<JsonBox> _boxes;
};