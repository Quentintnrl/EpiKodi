#include <string>
#include "Debug.hpp"
#include "App.hpp"

int main(int argc, char **argv) {
    if (argc == 2) {
        if (std::string(argv[1]) == "debug") {
            SET_DEBUG(true);
        } else {
            SET_DEBUG(false);
        }
    }
    App app;
    app.start();
    app.run();
    return 0;
}