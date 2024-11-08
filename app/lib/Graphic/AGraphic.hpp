#pragma once
#include "IGraphic.hpp"
#include "Uuid.hpp" // Include the header file that defines Uuid

class AGraphic : public IGraphic
{
    public:
        AGraphic() = default;
        virtual void loop() = 0;

        //add, remove, update, get

        virtual void addBox(const JsonBox &box) = 0;
        virtual void addPage(const JsonPage &page) = 0;

        virtual void debug(std::size_t i = 0) = 0;
        virtual const std::tuple<std::size_t, std::size_t> getCursorPosition() const = 0;
        virtual const std::tuple<std::size_t, std::size_t> getWindowSize() const = 0;
        virtual void setButtonState(const Uuid buttonId, const bool state) = 0;
        virtual const GraphicEvent getLastEvent() = 0;
        virtual const void changePage(const std::string &pageName) = 0;
    protected:
        virtual void draw() = 0;
        virtual void manageEvents() = 0;
        virtual ~AGraphic() = default;
};
