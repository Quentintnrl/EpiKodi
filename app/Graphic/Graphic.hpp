#pragma once

#include "AGraphic.hpp"
#include "GraphicBox.hpp"
#include "GraphicPage.hpp"
#include "GraphicEvent.hpp"
#include "GraphicPopUp.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <queue>
#include <mutex>
#include <thread>
#include <memory>
#include <atomic>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define DEFAULT_FRAME_RATE 60

namespace SFMLGraphic {
    class Graphic final : public AGraphic {
        public:
            Graphic(const std::string &appName);
            ~Graphic();
            void loop() override;

            void addBox(const JsonBox &jsonBox);
            void addPage(const JsonPage &jsonPage) override;
            void addPopUp(const JsonPopUp &jsonPopUp) override;
            void addButton(const Uuid &boxId, const JsonButton &jsonButton);
            void addImage(const Uuid &boxId, const JsonImage &jsonImage);
            void addText(const Uuid &boxId, const JsonText &jsonText);

            const std::tuple<std::size_t, std::size_t> getCursorPosition() const override;
            const std::tuple<std::size_t, std::size_t> getWindowSize() const override;
            void setButtonState(const Uuid buttonId, const bool state) override;
            const GraphicEvent getLastEvent() override;
            const void changePage(const std::string &pageName) override;
            const void addTempBox(const JsonBox &box) override;
            const void loadTempBox(const std::string &boxName) override;
            const void removeTempBox(const std::string &boxName) override;
            const void loadPopUp(const std::string &popUpName) override;
            const void displayMedia(const std::string &mediaPath) override;
            const void stopMedia() override;

            void debug(std::size_t i) override;
        private:
            void draw() override;
            void manageEvents() override;
            void displayVideo(const std::string &mediaPath);
            void playSound(const std::string &soundPath);
            void playRadio(const std::string &radioPath);
            std::vector<std::shared_ptr<GraphicBox>> _box;
            std::vector<std::shared_ptr<GraphicPage>> _pages;
            std::vector<std::shared_ptr<GraphicBox>> _tempBox;
            std::vector<std::shared_ptr<GraphicPopUp>> _popUps;
            sf::RenderWindow _window;
            std::string _appName;
            std::mutex _mutex;
            std::atomic<bool> _stopThread{false}; // Stop signal for the thread
            std::thread _mediaThread;            // Your media thread
            pid_t _vlcProcessHandle = 0;        // Handle to the VLC process
            std::queue<GraphicEvent> _eventQueue;
            std::shared_ptr<GraphicPopUp> _currentPopUp;
    };
}
