#pragma once

#include "appElement.hpp"
#include "JsonPage.hpp"
#include "Box.hpp"

class Page : public AppElement {
    public:
        Page(const JsonPage &jsonPage);

        void addBox(const Box &box);

        const std::vector<Box> getBoxes() const;
        const std::string getName() const;
    private:
        std::vector<Box> _boxes;
        std::string name;
};