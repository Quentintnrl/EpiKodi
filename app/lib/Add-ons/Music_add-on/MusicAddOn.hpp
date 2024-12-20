#include "Add-ons.hpp"
#define MUSICS_DIR "/medias/musics"
#define MUSICS_CONFIG_PATH "/json/musics/"

#define API_KEY "4f608862973812ae7ff556574cf164a1"

class MusicAddOn : public AddOn {
    public:
        MusicAddOn(std::string name);
        ~MusicAddOn() override = default;
    private:
        void run() override;
        void fetchSongYear(const std::string& artist, const std::string& title, const std::string& file);
        void fill_config(const std::string config_path, const std::string target, const std::string movie, const std::string moviePath);
};