#include "App.hpp"
#include "dlLoader.hpp"
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
    if (_Running) {
        stop();
    }
    stop();
}

void App::start() {
    _Running = true;
}

void App::run() {
    while (_Running) {
        graphic->draw();
        // Do something
    }
}

void App::stop() {
    _Running = false;
}
