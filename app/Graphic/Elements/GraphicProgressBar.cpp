#include "GraphicProgressBar.hpp"

Graphic::GraphicProgressBar::GraphicProgressBar(const JsonProgressBar &jsonProgressBar) : AProgressBar(jsonProgressBar.getProgress(), jsonProgressBar.getMaxProgress()) {
    _progress.setSize(sf::Vector2f(std::get<0>(jsonProgressBar.getSize()), std::get<0>(jsonProgressBar.getSize())));
    _progressBackground.setSize(sf::Vector2f(std::get<0>(jsonProgressBar.getSize()), std::get<0>(jsonProgressBar.getSize())));
    _progressBorder.setSize(sf::Vector2f(std::get<0>(jsonProgressBar.getSize()), std::get<0>(jsonProgressBar.getSize())));

    _progress.setPosition(std::get<0>(jsonProgressBar.getPosition()), std::get<1>(jsonProgressBar.getPosition()));
    _progressBackground.setPosition(std::get<0>(jsonProgressBar.getPosition()), std::get<1>(jsonProgressBar.getPosition()));
    _progressBorder.setPosition(std::get<0>(jsonProgressBar.getPosition()), std::get<1>(jsonProgressBar.getPosition()));

    _progress.setFillColor(sf::Color::Green);
    _progressBackground.setFillColor(sf::Color::Transparent);
    _progressBorder.setFillColor(sf::Color::Black);

    _progressBorder.setOutlineThickness(1);
    _progressBorder.setOutlineColor(sf::Color::White);
}

const void Graphic::GraphicProgressBar::setProgressColor(const std::tuple<short, short, short, short> rgba) {
    _progress.setFillColor(sf::Color(std::get<0>(rgba), std::get<1>(rgba), std::get<2>(rgba), std::get<3>(rgba)));
}

const std::tuple<short, short, short, short> Graphic::GraphicProgressBar::getProgressColor() const {
    const sf::Color color = _progress.getFillColor();
    return std::make_tuple(color.r, color.g, color.b, color.a);
}

void Graphic::GraphicProgressBar::draw(sf::RenderWindow &window) const {
    window.draw(_progressBackground);
    window.draw(_progress);
    window.draw(_progressBorder);
}

void Graphic::GraphicProgressBar::update(const std::shared_ptr<IGraphicElem> elem) {
    const std::shared_ptr<GraphicProgressBar> ProgressBar = std::dynamic_pointer_cast<GraphicProgressBar>(elem);
    if (ProgressBar) {
        _progress.setSize(sf::Vector2f(ProgressBar->_progress.getSize().x, ProgressBar->_progress.getSize().y));
        _progressBackground.setSize(sf::Vector2f(ProgressBar->_progressBackground.getSize().x, ProgressBar->_progressBackground.getSize().y));
        _progressBorder.setSize(sf::Vector2f(ProgressBar->_progressBorder.getSize().x, ProgressBar->_progressBorder.getSize().y));

        _progress.setPosition(ProgressBar->_progress.getPosition().x, ProgressBar->_progress.getPosition().y);
        _progressBackground.setPosition(ProgressBar->_progressBackground.getPosition().x, ProgressBar->_progressBackground.getPosition().y);
        _progressBorder.setPosition(ProgressBar->_progressBorder.getPosition().x, ProgressBar->_progressBorder.getPosition().y);
    }
}

void Graphic::GraphicProgressBar::debug(const std::size_t i) {
    printDebug("GraphicProgressBar {", i);
    printDebug("ProgressColor: " + std::to_string(std::get<0>(getProgressColor())) + ", " + std::to_string(std::get<1>(getProgressColor())) + ", " + std::to_string(std::get<2>(getProgressColor())) + ", " + std::to_string(std::get<3>(getProgressColor())), i + 1);
    printDebug("}", i);
}
