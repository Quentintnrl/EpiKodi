#include <string>
#include <iostream>
#include "Debug.hpp"
#include "App.hpp"
#include "IParser.hpp"
#include "dlLoader.hpp"

int main(int argc, char **argv) {
    if (argc == 2) {
        if (std::string(argv[1]) == "debug") {
            std::cout << "Debug mode enabled" << std::endl;
            SET_DEBUG(true);
        } else {
            std::cout << "Debug mode disabled" << std::endl;
            SET_DEBUG(false);
        }
    }
    DlLoader dlLoader;
    std::shared_ptr<IParser> parser = dlLoader.getInstance<IParser>(std::string(LIBS_PATH) + "libParser.so", PARSER_LOAD);
    parser->setFilePath(std::string(CONFIG_PATH));
    parser->parse();
    App app(parser->getParseResult());
    app.start();
    app.run();
    return 0;
}