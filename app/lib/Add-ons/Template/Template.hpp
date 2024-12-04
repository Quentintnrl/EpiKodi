#include "Add-ons.hpp"

class AddOnTemplate : public AddOn {
    public:
        AddOnTemplate(std::string name);
        ~AddOnTemplate() override = default;
    private:
        void run() override;
};