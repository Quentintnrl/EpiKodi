#pragma once

#include "JsonBox.hpp"
#include "JsonPage.hpp"
#include "GraphicEvent.hpp"
#include <SFML/Graphics.hpp>
#include "Uuid.hpp"

class IGraphic {
    public:
        virtual ~IGraphic() = default;
        virtual void loop() = 0;

        //add, remove, update, get
        virtual void addBox(const JsonBox &box) = 0;
        virtual void addPage(const JsonPage &page) = 0;
        virtual const std::tuple<std::size_t, std::size_t> getCursorPosition() const = 0;
        virtual const std::tuple<std::size_t, std::size_t> getWindowSize() const = 0;
        virtual void setButtonState(const Uuid buttonId, const bool state) = 0;
        virtual void debug(std::size_t i = 0) = 0;
        virtual const GraphicEvent getLastEvent() = 0;
        virtual const void changePage(const std::string &pageName) = 0;
        virtual const void addTempBox(const JsonBox &box) = 0;
        virtual const void loadTempBox(const std::string &boxName) = 0;
        virtual const void removeTempBox(const std::string &boxName) = 0;
        virtual const void displayMedia(const std::string &mediaPath) = 0;
    protected:
        virtual void draw() = 0;
        virtual void manageEvents() = 0;
};
