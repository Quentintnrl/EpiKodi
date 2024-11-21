#include "Graphic.hpp"
#include "GraphicBox.hpp"
#include "GraphicButton.hpp"
#include <iostream>
#include <vlc/vlc.h>
#include <thread>

enum MediaType {
    IMAGE,
    VIDEO,
    SOUND
};

const std::vector<std::tuple<std::vector<std::string>, MediaType>> mediaType {
    { {".png", ".jpg", ".jpeg", ".gif", ".bmp"}, IMAGE },
    { {".mp4", ".avi", ".mkv", ".mov", ".wmv"}, VIDEO },
    { {".mp3", ".wav", ".flac", ".ogg", ".m4a"}, SOUND }
};

SFMLGraphic::Graphic::Graphic(const std::string &appName) {
    _window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), appName, sf::Style::Fullscreen);
    _window.setFramerateLimit(DEFAULT_FRAME_RATE);
    _appName = appName;
}

SFMLGraphic::Graphic::~Graphic() {
    if (_window.isOpen())
        _window.close();
}

void SFMLGraphic::Graphic::loop() {
    draw();
    manageEvents();
}

void SFMLGraphic::Graphic::draw() {
    _window.clear();
    for (std::size_t i = 0; i < _box.size(); i++) {
        _box[i]->draw(_window);
    }
    _window.display();
}

void SFMLGraphic::Graphic::manageEvents() {
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            _eventQueue.push(GraphicEvent::QUIT);
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
            _eventQueue.push(GraphicEvent::KEY_UP);
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
            _eventQueue.push(GraphicEvent::KEY_RIGHT);
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
            _eventQueue.push(GraphicEvent::KEY_DOWN);
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
            _eventQueue.push(GraphicEvent::KEY_LEFT);
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
            _eventQueue.push(GraphicEvent::KEY_ENTER);
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            _eventQueue.push(GraphicEvent::MOUSE_CLICK);
        }
        if (event.type == sf::Event::MouseWheelScrolled && event.mouseWheelScroll.delta > 0) {
            _eventQueue.push(GraphicEvent::MOUSE_WHEEL_UP);
        }
        if (event.type == sf::Event::MouseWheelScrolled && event.mouseWheelScroll.delta < 0) {
            _eventQueue.push(GraphicEvent::MOUSE_WHEEL_DOWN);
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            _eventQueue.push(GraphicEvent::GO_BACK);
        }
    }
}

void SFMLGraphic::Graphic::addBox(const JsonBox &jsonBox) {
    _box.push_back(std::make_shared<GraphicBox>(jsonBox));
}

void SFMLGraphic::Graphic::addPage(const JsonPage &jsonPage) {
    _pages.push_back(std::make_shared<GraphicPage>(jsonPage));
}

void SFMLGraphic::Graphic::addButton(const Uuid &boxId, const JsonButton &jsonButton) {
    for (const auto &box : _box) {
        if (box->getUuid() == boxId) {
            auto tmpBox = std::dynamic_pointer_cast<GraphicBox>(box);
            tmpBox->addButton(jsonButton);
            return;
        }
    }
}

void SFMLGraphic::Graphic::addImage(const Uuid &boxId, const JsonImage &jsonImage) {
    for (const auto &box : _box) {
        if (box->getUuid() == boxId) {
            auto tmpBox = std::dynamic_pointer_cast<GraphicBox>(box);
            tmpBox->addImage(jsonImage);
            return;
        }
    }
}

void SFMLGraphic::Graphic::addText(const Uuid &boxId, const JsonText &jsonText) {
    for (const auto &box : _box) {
        if (box->getUuid() == boxId) {
            auto tmpBox = std::dynamic_pointer_cast<GraphicBox>(box);
            tmpBox->addText(jsonText);
            return;
        }
    }
}

const std::tuple<std::size_t, std::size_t> SFMLGraphic::Graphic::getCursorPosition() const {
    sf::Vector2i position = sf::Mouse::getPosition(_window);
    return std::make_tuple(position.x, position.y);
}

const std::tuple<std::size_t, std::size_t> SFMLGraphic::Graphic::getWindowSize() const {
    return std::make_tuple(_window.getSize().x, _window.getSize().y);
}

void SFMLGraphic::Graphic::setButtonState(const Uuid buttonId, const bool state) {
    for (const auto &box : _box) {
        auto tmpBox = std::dynamic_pointer_cast<GraphicBox>(box);
        tmpBox->setButtonState(buttonId, state);
    }
}

const GraphicEvent SFMLGraphic::Graphic::getLastEvent() {
    if (_eventQueue.empty())
        return GraphicEvent::NONE;
    GraphicEvent event = _eventQueue.front();
    _eventQueue.pop();
    return event;
}

const void SFMLGraphic::Graphic::changePage(const std::string &pageName) {
    for (const auto &page : _pages) {
        if (page->getName() == pageName) {
            _box.clear();
            for (const auto &box : page->getBoxes()) {
                _box.push_back(box);
            }
            return;
        }
    }
}

const void SFMLGraphic::Graphic::addTempBox(const JsonBox &box) {
    _tempBox.push_back(std::make_shared<GraphicBox>(box));
}

const void SFMLGraphic::Graphic::loadTempBox(const std::string &boxName) {
    for (const auto &box : _tempBox) {
        if (box->getName() == boxName && _box.back()->getName() != boxName) {
            _box.push_back(box);
            return;
        }
    }
}

const void SFMLGraphic::Graphic::removeTempBox(const std::string &boxName) {
    for (std::size_t i = 0; i < _box.size(); i++) {
        if (_box[i]->getName() == boxName) {
            _box.erase(_box.begin() + i);
            return;
        }
    }
}

const void SFMLGraphic::Graphic::displayMedia(const std::string &mediaPath) {
    std::cout << "Display media: " << mediaPath << std::endl;
    std::string format = mediaPath.substr(mediaPath.find_last_of('.'));
    std::cout << "Media format: " << format << std::endl;
    for (const auto &type : mediaType) {
        for (const auto &ext : std::get<0>(type)) {
            if (ext == format) {
                switch (std::get<1>(type)) {
                    case IMAGE:
                        std::cout << "Displaying image" << std::endl;
                        break;
                    case VIDEO:
                        std::cout << "Displaying video" << std::endl;
                        //get pwd
                        displayVideo(getenv("PWD") + std::string("/medias") + mediaPath);
                        break;
                    case SOUND:
                        std::cout << "Playing sound" << std::endl;
                        break;
                }
                return;
            }
        }
    }
}

void SFMLGraphic::Graphic::displayVideo(const std::string &mediaPath) {
    std::cout << "Running mo: " << mediaPath << std::endl;
    std::size_t width = _window.getSize().x;
    std::size_t height = _window.getSize().y;
    std::string command = "cvlc --fullscreen" + std::string(" --width=") + std::to_string(width) + std::string(" --height=") + std::to_string(height) + std::string(" --video-x=") + std::to_string(width) + std::string(" --video-y=") + std::to_string(height) + std::string(" \"") + mediaPath + std::string("\"");
    std::cout << "command: " << command << std::endl;
    std::thread t([command] {
        std::system(command.c_str());
    });
    t.detach();
}

void SFMLGraphic::Graphic::debug(std::size_t i) {
    if (_appName.empty()) {
        printDebug("Graphic {", i);
    } else {
        printDebug(_appName + " {", i);
    }
    printDebug("Boxes {", i + 1);
    for (const auto &box : _box) {
        box->debug(i + 2);
    }
    printDebug("},", i + 1);
    printDebug("Pages {", i + 1);
    for (const auto &page : _pages) {
        page->debug(i + 2);
    }
    printDebug("}", i + 1);
    printDebug("TempBoxes {", i + 1);
    for (const auto &box : _tempBox) {
        box->debug(i + 2);
    }
    printDebug("}", i + 1);
    printDebug("}", i);
}

extern "C" {
    IGraphic *createGraphic(const std::string &appName) {
        return new SFMLGraphic::Graphic(appName);
    }
}
