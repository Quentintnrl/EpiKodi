#pragma once

#include <string>
#include <vector>
#include <memory>
#include <mutex>
#include <thread>

class AddOn {
    public:
        AddOn(std::string name);
        virtual ~AddOn() = default;
        const std::string getName() const;
        const bool isRunning() const;
        void stop();

    protected:
        virtual void run() = 0;
        const std::string _name;
        bool _run;
        std::thread _thread;
};