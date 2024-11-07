#pragma once

#include "IUuid.hpp"
#include <uuid/uuid.h>

class Uuid : public Iuuid
{
    public:
        Uuid();
        Uuid(const std::string& uuid);
        Uuid(const Uuid& other);
        ~Uuid();

        const std::string toString() const;
        bool operator==(const Iuuid& other) const override;
        bool operator==(const uuid_t& other) const;
        bool operator!=(const Iuuid& other) const override;
        bool operator!=(const uuid_t& other) const;
        void operator=(Iuuid& other) override;
        void operator=(const std::string other);
        void operator=(uuid_t& other);
        std::ostream& operator<<(std::ostream& os) const;

        const uuid_t &getUuid() const;
        void setUuid(const uuid_t &uuid);
    protected:
        uuid_t _uuid;
};
