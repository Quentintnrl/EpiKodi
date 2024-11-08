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
    graphic->addPage(jsonApp.getPage());
    for (auto &page : jsonApp.getPages()) {
        _pagesList.push_back(std::make_shared<Page>(page));
        graphic->addPage(page);
    }
    graphic->changePage(jsonApp.getPage().getName());
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
    if (lastEvent == GraphicEvent::KEY_UP ||
        lastEvent == GraphicEvent::KEY_DOWN ||
        lastEvent == GraphicEvent::KEY_LEFT ||
        lastEvent == GraphicEvent::KEY_RIGHT) {
        handleArrow(lastEvent);
    }
    if (lastEvent == GraphicEvent::KEY_ENTER ||
        lastEvent == GraphicEvent::MOUSE_CLICK) {
        handleSelect();
    }
    if (lastEvent == GraphicEvent::MOUSE_WHEEL_UP ||
        lastEvent == GraphicEvent::MOUSE_WHEEL_DOWN) {
        handleWheel(lastEvent);
    }
    if (lastEvent == GraphicEvent::GO_BACK) {
        handleBack();
    }
}

void App::handleArrow(const GraphicEvent &event) {
    return;
}

void App::handleSelect() {
    for (const auto &box : _pages.back()->getBoxes()) {
        for (const auto &button : box.getButtons()) {
            if (button->getState()) {
                if (button->getType() == ToPopUp) {
                    addPopUp(button);
                }
                if (button->getType() == AddBox) {
                    addBox(button);
                }
                if (button->getType() == ToPage) {
                    addPage(button);
                }
            }
        }
    }
    return;
}

void App::handleWheel(const GraphicEvent &event) {
    return;
}

void App::handleBack() {
    if (_pages.size() > 1) {
        _pages.pop_back();
    }
}

void App::addPopUp(const std::shared_ptr<Button> button) {
    return;
}

void App::addBox(const std::shared_ptr<Button> button) {
    return;
}

void App::addPage(const std::shared_ptr<Button> button) {
    for (auto &page : _pagesList) {
        std::cout << "search: " << button->getTarget() << std::endl;
        std::cout << "page:   " << page->getName() << std::endl;
        if (page->getName() == button->getTarget()) {
            _pages.push_back(page);
            graphic->changePage(page->getName());
            std::cout << "find" << std::endl;
            break;
        }
    }
    return;
}