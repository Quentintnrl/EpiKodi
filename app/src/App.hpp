#pragma once
#include <string>

#define CONFIG_PATH "json/application.json"

class App {
    public:
        App();
        ~App();
        void start();
        void run();
        void stop();
    private:
        bool _Running;
        std::string name;
};
