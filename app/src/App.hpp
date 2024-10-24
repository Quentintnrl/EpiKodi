#pragma once
#include "JsonApp.hpp"

#define CONFIG_PATH "json/application.json"

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
};
