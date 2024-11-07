#pragma once

#include "ABox.hpp"
#include "JsonBox.hpp"

class Box final : public Abox {
    public:
        Box() = default;
        Box(const JsonBox &jsonBox);
        ~Box() = default;

        void addButton(const JsonButton &button);
        void addImage(const JsonImage &image);
        void addText(const JsonText &text);

        void debug(const std::size_t i = 0) override final;
    private:
        BoxType _type;
};
