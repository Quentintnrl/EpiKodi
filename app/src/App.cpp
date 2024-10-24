#include "App.hpp"
#include "Parser.hpp"

App::App() {
    _Running = false;
    name = "App";
    Parser parser("path/to/file");
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
        // Do something
    }
}

void App::stop() {
    _Running = false;
}
