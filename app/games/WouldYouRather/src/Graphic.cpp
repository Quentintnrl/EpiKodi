#include "Graphic.hpp"

void Graphic::draw(sf::RenderWindow& window, const Turn& turn) {
    window.clear(sf::Color::Black);
    sf::Font font;
    if (!font.loadFromFile("fonts/Viagram.otf")) {
        // handle error
    }
    sf::Text question(turn.getQuestion(), font, 50);
    //set text color
    question.setFillColor(sf::Color::White);
    //set text position
    question.setPosition(960 - question.getGlobalBounds().width / 2, 200);
    window.draw(question);
    sf::Text answerA(turn.getOption1()->getOption(), font, 30);
    answerA.setFillColor(sf::Color::White);
    answerA.setPosition(480 - answerA.getGlobalBounds().width / 2, 540 - answerA.getGlobalBounds().height / 2);
    window.draw(answerA);
    sf::Text answerB(turn.getOption2()->getOption(), font, 30);
    answerB.setFillColor(sf::Color::White);
    answerB.setPosition(1440 - answerB.getGlobalBounds().width / 2, 540 - answerB.getGlobalBounds().height / 2);
    window.draw(answerB);
    window.display();
}