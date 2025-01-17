#include "App.hpp"
#include "dlLoader.hpp"
#include "GraphicEvent.hpp"
#include <iostream>
#include <unistd.h>

App::App(JsonApp jsonApp) {
    _Running = false;
    _isMedia = false;
    _settingsManager = std::make_shared<SettingsManager>();
        // jsonApp.debug(0);
    if (DEBUG_ENABLED()) {
    }
    name = jsonApp.getName();
    std::string graphicPath = LIBS_PATH + jsonApp.getGraphicPath();
    if (DEBUG_ENABLED()) {
        std::cout << "Loading graphic library: " << graphicPath << std::endl;
    }
    DlLoader dlLoader;
    for (const auto &addOn : jsonApp.getAddOns()) {
        std::string addOnPath = LIBS_PATH + addOn.getPath();
        if (DEBUG_ENABLED()) {
            std::cout << "Loading add-on library: " << addOnPath << std::endl;
        }
        _addOns.push_back(dlLoader.getInstance<AddOn>(addOnPath, ADD_ON_LOAD));
        _addOns.back()->start();
    }
    graphic = dlLoader.getInstance<IGraphic>(graphicPath, GRAPHIC_LOAD);
    for (const auto &mediaPagesManager : jsonApp.getMediasDirPath()) {
        try {
            _mediaPagesManagers.push_back(std::make_shared<MediaPagesManager>(mediaPagesManager));
            sleep(1);
            _mediaPagesManagers.back()->lock();
            _mediaPagesManagers.back()->unlock();
            if (_mediaPagesManagers.back()->hasChange()) {
                _mediaPagesManagers.back()->lock();
                for (const auto &page : _mediaPagesManagers.back()->getPages()) {
                    _pagesList.push_back(std::make_shared<Page>(page));
                    graphic->addPage(page);
                }
                _mediaPagesManagers.back()->unlock();
            }
        } catch (const std::exception &e) {
            std::cerr << "Exception caught: " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "Unknown exception caught!" << std::endl;
        }
    }
    for (const auto &settingsPath : jsonApp.getSettingsPath()) {
        try {
            _settingsBoxesManagers.push_back(std::make_shared<SettingsBoxesManager>(settingsPath));
            sleep(1);
            _settingsBoxesManagers.back()->lock();
            _settingsBoxesManagers.back()->unlock();
            if (_settingsBoxesManagers.back()->hasChange()) {
                _settingsBoxesManagers.back()->lock();
                for (const auto &box : _settingsBoxesManagers.back()->getBoxes()) {
                    _boxes.push_back(std::make_shared<Box>(box));
                    graphic->addTempBox(box);
                }
                _settingsBoxesManagers.back()->resetChange();
                _settingsBoxesManagers.back()->unlock();
            }
        } catch (const std::exception &e) {
            std::cerr << "Exception caught: " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "Unknown exception caught!" << std::endl;
        }
    }
    _pages.push_back(std::make_shared<Page>(jsonApp.getPage()));
    graphic->addPage(jsonApp.getPage());
    for (auto &page : jsonApp.getPages()) {
        _pagesList.push_back(std::make_shared<Page>(page));
        graphic->addPage(page);
    }
    for (auto &box : jsonApp.getBoxes()) {
        _boxes.push_back(std::make_shared<Box>(box));
        graphic->addTempBox(box);
    }
    for (auto &popUp : jsonApp.getPopUps()) {
        _popUps.push_back(std::make_shared<PopUp>(popUp));
        graphic->addPopUp(popUp);
    }
    _popUp = nullptr;
    graphic->changePage(jsonApp.getPage().getName());
    if (DEBUG_ENABLED()) {
        // graphic->debug(0);
    }
    std::cout << "App created" << std::endl;
}

App::~App() {
    stop();
}

void App::start() {
    _Running = true;
}

void App::run() {
    while (_Running) {
        if (_settingsBoxesManagers.back()->hasChange() && !_settingsBoxesManagers.back()->isLocked()) {
                _settingsBoxesManagers.back()->lock();
                for (const auto &box : _settingsBoxesManagers.back()->getBoxes()) {
                    if (_pages.back()->getBoxes().back().getName() == box.getName()) {
                        _pages.back()->removeLastBox();
                        for (std::size_t i = 0; i < _boxes.size(); i++) {
                            if (_boxes[i]->getName() == box.getName()) {
                                _boxes.erase(_boxes.begin() + i);
                                break;
                            }
                        }
                    }
                    _boxes.push_back(std::make_shared<Box>(box));
                    _pages.back()->addBox(*_boxes.back());
                    graphic->removeTempBox(box.getName());
                    graphic->addTempBox(box);
                    graphic->loadTempBox(box.getName());
                }
                _settingsBoxesManagers.back()->resetChange();
                _settingsBoxesManagers.back()->unlock();
        }
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
        if (_popUp != nullptr) {
            for (auto &button : _popUp->getButtons()) {
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
    if (lastEvent == GraphicEvent::MOUSE_RIGHT_CLICK) {
        handleSpecial();
    }
}

void App::handleArrow(const GraphicEvent &event) {
    return;
}

void App::handleSelect() {
    if (_popUp != nullptr) {
        std::tuple<std::size_t , std::size_t> pos = graphic->getCursorPosition();
        std::tuple<std::size_t , std::size_t> windowSize = graphic->getWindowSize();
        // bool isOut = true;
        for (auto &button : _popUp->getButtons()) {
            if (button->isHover(pos, windowSize, std::make_tuple(APP_WIDTH, APP_HEIGHT))) {
                // isOut = false;
                if (button->getType() == ToPopUp) {
                    addPopUp(button);
                }
                if (button->getType() == AddBox) {
                    addBox(button);
                }
                if (button->getType() == ToPage) {
                    addPage(button);
                }
                if (button->getType() == ToMedia) {
                    addMedia(button);
                }
                if (button->getType() == ToParam) {
                    changeParam(button);
                }
                if (button->getType() == ToGame) {
                    playGame(button);
                }
                if (button->getType() == ToCommand) {
                    handleCommand(button);
                }
                return;
            }
        }
        // if (isOut) {
            _popUp = nullptr;
            graphic->resetPopUp();
        // }
    }
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
                if (button->getType() == ToMedia) {
                    addMedia(button);
                }
                if (button->getType() == ToParam) {
                    changeParam(button);
                }
                if (button->getType() == ToGame) {
                    playGame(button);
                }
                if (button->getType() == ToCommand) {
                    handleCommand(button);
                }
            }
        }
    }
    return;
}

const void App::handleSpecial() const {
    std::tuple<std::size_t , std::size_t> pos = graphic->getCursorPosition();
    std::tuple<std::size_t , std::size_t> windowSize = graphic->getWindowSize();
    for (const auto &box : _pages.back()->getBoxes()) {
        for (const auto &button : box.getButtons()) {
            if (button->isHover(pos, windowSize, std::make_tuple(APP_WIDTH, APP_HEIGHT))) {
                if (button->getType() == ToMedia) {
                    addMediaNext(button);
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
    if (_popUp != nullptr) {
        _popUp = nullptr;
        graphic->resetPopUp();
        return;
    }
    if (_isMedia) {
        std::cout << "Stop media" << std::endl;
        graphic->stopMedia();
        _isMedia = false;
        return;
    }
    if (_pages.size() > 1) {
        _pages.pop_back();
        graphic->changePage(_pages.back()->getName());
    }
}

void App::addPopUp(const std::shared_ptr<Button> button) {
    if (DEBUG_ENABLED()) {
        std::cout << "Adding pop-up: " << button->getTarget() << std::endl;
    }
    for (auto &popUp : _popUps) {
        if (popUp->getName() == button->getTarget()) {
            _popUp = popUp;
            graphic->loadPopUp(button->getTarget());
            break;
        }
    }
    return;
}

void App::addBox(const std::shared_ptr<Button> button) {
    for (auto &box : _boxes) {
        if (box->getName() == button->getTarget() && _pages.back()->getBoxes().back().getName() != button->getTarget()) {
            if (DEBUG_ENABLED()) {
                std::cout << "Adding box: " << button->getTarget() << std::endl;
            }
            if (_pages.back()->getNbBoxes() < _pages.back()->getBoxes().size()) {
                graphic->removeTempBox(_pages.back()->getBoxes().back().getName());
                _pages.back()->removeLastBox();
            }
            graphic->loadTempBox(button->getTarget());
            _pages.back()->addBox(*box);
            break;
        }
    }
}

void App::addPage(const std::shared_ptr<Button> button) {
    if (DEBUG_ENABLED()) {
        std::cout << "Changing page: " << button->getTarget() << std::endl;
    }
    for (auto &page : _pagesList) {
        if (page->getName() == button->getTarget()) {
            if (_pages.back()->getNbBoxes() < _pages.back()->getBoxes().size()) {
                _pages.back()->removeLastBox();
            }
            _pages.push_back(page);
            graphic->changePage(page->getName());
            break;
        }
    }
    return;
}

void App::addMedia(const std::shared_ptr<Button> button) {
    graphic->displayMedia(button->getTarget());
    _isMedia = true;
    return;
}

const void App::changeParam(const std::shared_ptr<Button> button) const {
    if (DEBUG_ENABLED()) {
        std::cout << "Changing param: " << button->getTarget() << std::endl;
    }
    std::string path = button->getTarget().substr(0, button->getTarget().find_last_of("/"));
    std::string param = path.substr(path.find_last_of("/") + 1);
    path = path.substr(0, path.find_last_of("/"));
    std::string target = button->getTarget().substr(button->getTarget().find_last_of("/") + 1);
    _settingsManager->changeSettings(path, target, param);
}

const void App::playGame(const std::shared_ptr<Button> button) const {
    if (DEBUG_ENABLED()) {
        std::cout << "Playing game: " << button->getTarget() << std::endl;
    }

    // Create a new thread to execute the game
    std::thread t1([button] {
        const std::string fullPath = getenv("PWD") + std::string("/") + button->getTarget();
        if (DEBUG_ENABLED()) {
            std::cout << "Launching game: " << fullPath << std::endl;
        }

        // Construct the command to execute
        const std::string command = fullPath + " " + getenv("PWD") + "/app" + button->getTarget() + "/json/config.json";
        if (DEBUG_ENABLED()) {
            std::cout << "Command: " << command << std::endl;
        }

        // Execute the command and wait for it to finish
        int result = std::system(command.c_str());
        if (result != 0) {
            std::cerr << "Failed to execute command. Exit code: " << result << std::endl;
        }
    });
    t1.detach();
}

const void App::handleCommand(const std::shared_ptr<Button> button) const {
    if (DEBUG_ENABLED()) {
        std::cout << "Executing command: " << button->getTarget() << std::endl;
    }

    // Execute the command
    const std::string command = button->getTarget();
    if (command == "exit") {
        std::exit(0);
    }
    if (command == "shut-down") {
        std::system("shutdown now");
    }
    if (command == "reboot") {
        std::system("reboot");
    }
    if (command == "suspend") {
        std::system("systemctl suspend");
    }
}

const void App::addMediaNext(const std::shared_ptr<Button> button) const {
    if (DEBUG_ENABLED()) {
        std::cout << "Changing media: " << button->getTarget() << std::endl;
    }
    graphic->playNextMedia(button->getTarget());
}
