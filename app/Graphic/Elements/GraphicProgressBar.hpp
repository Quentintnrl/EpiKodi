#pragma once

#include "AProgressBar.hpp"
#include "JsonProgressBar.hpp"
#include <SFML/Graphics/Image.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace Graphic
{
    class GraphicProgressBar : public AProgressBar {
    public:
        GraphicProgressBar() = default;
        GraphicProgressBar(const JsonProgressBar &jsonProgressBar);
        ~GraphicProgressBar() = default;

        const void setProgressColor(const std::tuple<short, short, short, short> rgba) override final;

        const std::tuple<short, short, short, short> getProgressColor() const override final;

        void draw(sf::RenderWindow &window) const;

        void update(const std::shared_ptr<IGraphicElem> elem) override final;

        void debug(const std::size_t i = 0) override final;

    private:
        sf::RectangleShape _progress;
        sf::RectangleShape _progressBackground;
        sf::RectangleShape _progressBorder;
    };
}