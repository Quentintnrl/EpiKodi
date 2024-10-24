#pragma once
#include "JsonPage.hpp"

class JsonApp : public AbstractJsonElem {
    public:
        JsonApp() = default;
        JsonApp(const nlohmann::json& json);
        ~JsonApp() = default;

        //getters
        const std::string getName() const;
        const JsonPage getPage() const;

        const void debug(const std::size_t i) override;
    private:
        //find methods
        JsonPage findPage(const nlohmann::json& json);

        std::string _name;
        JsonPage _page;
};
