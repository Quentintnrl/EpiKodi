#pragma once

#include "GraphicBox.hpp"
#include "JsonPage.hpp"

namespace SFMLGraphic {
    class GraphicPage {
        public:
            GraphicPage() = default;
            GraphicPage(const JsonPage &jsonPage);
            ~GraphicPage() = default;
            void addBox(const JsonBox &jsonBox);
            const std::vector<std::shared_ptr<GraphicBox>> &getBoxes() const;
            void debug(const std::size_t i);
        private:
            std::vector<std::shared_ptr<GraphicBox>> _box;
            const std::string name;
    };
}