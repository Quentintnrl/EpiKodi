#include "App.hpp"

App::App(JsonApp jsonApp) {
    _Running = false;
    name = jsonApp.getName();
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
