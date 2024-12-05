#pragma once
#include "JsonApp.hpp"
#include "IGraphic.hpp"
#include "Page.hpp"
#include "mediaPagesManager.hpp"
#include "settingsBoxesManager.hpp"
#include "settingsManager.hpp"
#include "Add-ons.hpp"
#include <memory>

#define CONFIG_PATH "/json/application.json"
#define LIBS_PATH "libs/"
#define PARSER_LOAD "createParser"
#define GRAPHIC_LOAD "createGraphic"
#define ADD_ON_LOAD "createAddOn"

#define APP_WIDTH 1920
#define APP_HEIGHT 1080

class App {
    public:
        App(JsonApp jsonApp);
        ~App();
        void start();
        void run();
        void stop();
    private:
        void handleEvents();
        void handleArrow(const GraphicEvent &event);
        void handleSelect();
        void handleWheel(const GraphicEvent &event);
        void handleBack();

        void addPopUp(const std::shared_ptr<Button> button);
        void addBox(const std::shared_ptr<Button> button);
        void addPage(const std::shared_ptr<Button> button);
        void addMedia(const std::shared_ptr<Button> button);
        const void changeParam(const std::shared_ptr<Button> button) const;
        bool _Running;
        bool _isMedia;
        std::string name;
        std::shared_ptr<IGraphic> graphic;
        std::vector<std::shared_ptr<Page>> _pages;
        std::vector<std::shared_ptr<Page>> _pagesList;
        std::vector<std::shared_ptr<Box>> _boxes;
        std::vector<std::shared_ptr<MediaPagesManager>> _mediaPagesManagers;
        std::vector<std::shared_ptr<SettingsBoxesManager>> _settingsBoxesManagers;
        std::shared_ptr<SettingsManager> _settingsManager;
        std::vector<std::shared_ptr<AddOn>> _addOns;
};
