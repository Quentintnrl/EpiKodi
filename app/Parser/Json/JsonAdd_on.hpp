#pragma once
#include "JsonPage.hpp"

class JsonAddOn : public AbstractJsonElem {
    public:
        JsonAddOn() = default;
        JsonAddOn(const nlohmann::json& json);
        ~JsonAddOn() = default;

        //getters
        const std::string getName() const;
        const std::string getPath() const;

        //debug
        const void debug(const std::size_t i) const override;
    private:
        //find methods
        const std::string findName(const nlohmann::json& json) const;
        const std::string findPath(const nlohmann::json& json) const;

        std::string _name;
        std::string _path;
};