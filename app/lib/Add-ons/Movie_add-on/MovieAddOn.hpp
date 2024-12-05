#include "Add-ons.hpp"
#define MOVIES_DIR "/medias/movies"
#define MOVIES_CONFIG_PATH "/json/movies/"

#define API_KEY "4f608862973812ae7ff556574cf164a1"

class MovieAddOn : public AddOn {
    public:
        MovieAddOn(std::string name);
        ~MovieAddOn() override = default;
    private:
        void run() override;
        void fetchMovieDetailsByName(const std::string& api_key, const std::string& movie_name, const std::string& moviePath);
        void fill_config(const std::string config_path, const std::string target, const std::string movie, const std::string moviePath);
};