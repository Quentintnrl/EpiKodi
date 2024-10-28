#pragma once
#include <string>

class Iuuid {
    public:
        virtual const std::string toString() const = 0;
        virtual bool operator==(const Iuuid& other) const = 0;
        virtual bool operator!=(const Iuuid& other) const = 0;
        virtual void operator=(Iuuid& other) = 0;
        virtual void operator=(std::string other) = 0;
        virtual std::ostream& operator<<(std::ostream& os) const = 0;

    protected:
        virtual ~Iuuid() = default;
};
