#pragma once

#include "appElement.hpp"
#include "JsonBox.hpp"
#include "Button.hpp"
#include "Image.hpp"
#include "Text.hpp"

class Box : public AppElement {
    public:
        Box(const JsonBox &jsonBox);

        void addButton(const Button& button);
        void addImage(const Image& image);
        void addText(const Text& text);

        const std::string& getType() const;
        const std::vector<std::shared_ptr<Button>>& getButtons() const;
        const std::vector<std::shared_ptr<Image>>& getImages() const;
        const std::vector<std::shared_ptr<Text>>& getTexts() const;
        const std::string& getName() const;
    private:
        std::string _type;
        std::vector<std::shared_ptr<Button>> _buttons;
        std::vector<std::shared_ptr<Image>> _images;
        std::vector<std::shared_ptr<Text>> _texts;
        std::string _name;
};