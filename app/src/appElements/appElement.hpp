#pragma once

#include "Uuid.hpp"
#include <tuple>
#include "mutex"

class AppElement {
    public:
        AppElement();
        ~AppElement();
        AppElement(const AppElement& other); // Delete copy constructor
        AppElement& operator=(const AppElement& other); // Delete copy assignment operator

        const Uuid& getUuid() const;
    protected:
        Uuid _uuid;
        mutable std::mutex _mutex;
};
