#include <string>

class App {
    public:
        App();
        ~App();
        void start();
        void run();
        void stop();
    private:
        bool _Running;
        std::string name;
};
