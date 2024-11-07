#pragma once
#include "JsonApp.hpp"
#include "IGraphic.hpp"
#include <memory>

#define CONFIG_PATH "/json/application.json"
#define LIBS_PATH "libs/"
#define PARSER_LOAD "createParser"
#define GRAPHIC_LOAD "createGraphic"

class App {
    public:
        App(JsonApp jsonApp);
        ~App();
        void start();
        void run();
        void stop();
    private:
        bool _Running;
        std::string name;
        std::shared_ptr<IGraphic> graphic;
};
