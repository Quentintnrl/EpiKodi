#pragma once

#include "Turn.hpp"
#include <vector>

class WouldYouRather final {
    public:
        WouldYouRather(const std::string &configPath);
        ~WouldYouRather() = default;
        void start();
    private:
        // Add private members here
        bool isRunning;
        std::vector<Turn> turns;
};