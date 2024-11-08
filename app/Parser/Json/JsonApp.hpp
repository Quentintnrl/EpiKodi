#pragma once
#include "JsonPage.hpp"

class JsonApp : public AbstractJsonElem {
    public:
        JsonApp() = default;
        JsonApp(const nlohmann::json& json);
        ~JsonApp() = default;

        //getters
        const std::string getName() const;
        const std::string getGraphicPath() const;
        const std::vector<std::string> getComponentsPath() const;
        const JsonPage getPage() const;
        const std::vector<JsonPage> getPages() const;

        const void debug(const std::size_t i) override;
    private:
        //find methods
        const std::string findName(const nlohmann::json& json) const;
        const std::string findGraphicPath(const nlohmann::json& json) const;
        const std::vector<std::string> findComponentsPath(const nlohmann::json& json) const;
        const JsonPage findPage(const nlohmann::json& json) const;
        const std::vector<JsonPage> findPages(const nlohmann::json& json) const;

        std::string _name;
        std::string _graphicPath;
        std::vector<std::string> _componentsPath;
        JsonPage _page;
        std::vector<JsonPage> _pages;
};
