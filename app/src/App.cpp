#include "App.hpp"
#include "dlLoader.hpp"
#include "GraphicEvent.hpp"
#include <iostream>

App::App(JsonApp jsonApp) {
    _Running = false;
    if (DEBUG_ENABLED()) {
        jsonApp.debug(0);
    }
    name = jsonApp.getName();
    std::string graphicPath = LIBS_PATH + jsonApp.getGraphicPath();
    if (DEBUG_ENABLED()) {
        std::cout << "Loading graphic library: " << graphicPath << std::endl;
    }
    DlLoader dlLoader;
    graphic = dlLoader.getInstance<IGraphic>(graphicPath, GRAPHIC_LOAD);
    _pages.push_back(std::make_shared<Page>(jsonApp.getPage()));
    for (auto &box : jsonApp.getPage().getBoxes()) {
        graphic->addBox(box);
    }
    if (DEBUG_ENABLED()) {
        graphic->debug(0);
    }
}

App::~App() {
    stop();
}

void App::start() {
    _Running = true;
}

void App::run() {
    while (_Running) {
        graphic->loop();
        std::tuple<std::size_t , std::size_t> pos = graphic->getCursorPosition();
        std::tuple<std::size_t , std::size_t> windowSize = graphic->getWindowSize();
        for (auto &box : _pages.back()->getBoxes()) {
            for (auto &button : box.getButtons()) {
                if (button->isHover(pos, windowSize, std::make_tuple(APP_WIDTH, APP_HEIGHT))) {
                    graphic->setButtonState(button->getUuid(), true);
                } else {
                    graphic->setButtonState(button->getUuid(), false);
                }
            }
        }
        handleEvents();
    }
}

void App::stop() {
    _Running = false;
}

void App::handleEvents() {
    GraphicEvent lastEvent = graphic->getLastEvent();
    if (lastEvent == GraphicEvent::QUIT) {
        stop();
    }
}